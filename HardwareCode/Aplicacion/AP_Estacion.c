/*******************************************************************************************************************************//**
 *
 * @file		AP_Estacion.c
 * @brief		Aplicaciones de la Estacion Meteorologica
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "AP_Estacion.h"
#include <stdio.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint8_t BufferUART[12];
uint8_t BufferFrec[2];
Date Fecha;
uint16_t frecuencia = 20; //frecuencia de envio de datos en segundos
uint16_t tiempo = 4;
uint32_t espera_parametros;
uint16_t Temperatura;
uint16_t Temperatura_coma;
long presion;
uint16_t presion_coma;
uint8_t Humedad;
uint8_t Flag_T = 0;
uint8_t Flag_Espera = 0;
uint8_t Flag_timeout = 0;
uint8_t timer_timeout = 0;
uint8_t Flag_memoria = 0;
uint8_t Flag_firstTime = 1;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/**
 \fn    	void Maquina_estado (void)
 \brief 	Maquina de estado para el funcionamiento del proyecto
 \param 	void
 \return 	void
 */
void maquina_estado (void)
{
	static uint8_t estado = 0;
	static uint16_t i;
	char cadena[256];


	switch (estado)
	{
	case 0x00:
		if (Flag_T == 1)
		{
			estado++;
			Flag_T = 0;
			Start_Temperatura ( );
			espera_parametros = 2;      //Espera 5ms para tomar temperatura de BMP180
			if (Flag_firstTime)
			{
				Flag_firstTime = 0;
			}
		}
		if (Flag_memoria)
		{
			estado = ENVIAR_MEMORIA;
			Transmitir ("#@");
			espera_parametros = 4;
			i=0;
		}
	break;

	case ENVIAR_MEMORIA:
		if (Flag_Espera == 1)
		{
			LeerPagina(i);
  			Transmitir_datos(BufferMemoria, 64);
  			i++;
  			Flag_Espera = 0;
  			estado = ENVIAR_MEMORIA_2;
		}
	break;

	case ENVIAR_MEMORIA_2:
		if (i > final/64)
		{
			if (((final%64)!=0)&&(final>63))
			{
				LeerPagina(i);
				Transmitir_datos(BufferMemoria, 64);
			}
			estado = 0x00;
			Flag_memoria = 0;
			Display_lcd("MEMO ENVIADA        ", 0, 2);
			Display_lcd("                    ", 1, 0);
		}
		else
		{
			estado = ENVIAR_MEMORIA;
			espera_parametros = 50;
		}
	break;

	case 0x01:
		if (Flag_Espera == 1)
		{
			estado++;
			Flag_Espera = 0;
			Temperatura = BMP180_Temperatura ( );
			Start_pressure();
			espera_parametros = 4;	//Espera 10ms para tomar presion de BMP180
		}
	break;

	case 0x02:
		if (Flag_Espera == 1)
		{
	  		presion = BMP180_Presion ( );
	  		Humedad = HumedadDHT ( );

	  		// Envia datos a la pc
	  		Transmitir ("PR");
	  		Push_TX(Temperatura>>8);
	  		Push_TX(Temperatura&0xFF);
	  		Push_TX(presion>>16);
	  		Push_TX((presion>>8)&0xFF);
	  		Push_TX(presion&0xFF);
	  		Push_TX(Humedad);


	  		//Guardar en memoria
	  		//Formato de guardado
	  		//(K,anio_highbyte, anio_lowbyte, mes, dia,hora,min,seg,D,temp high byte, temp low byte,humedad, presionbyte1, presionbyte2, presionbyte3)
	  		sprintf (cadena, "K%c%c%c%c%c%c%cD%c%c%c%c%c%c",Fecha.anio>>8,(char)Fecha.anio&0xFF, Fecha.mes,Fecha.dia,Fecha.hora, Fecha.min, Fecha.seg, (char)Temperatura>>8,(char)Temperatura&0xFF, Humedad, presion>>16, presion>>8, (char)presion&0xFF);
	  		final = Insertar_Memoria_bytes (cadena, final, 15);

	  		estado = 0x03;
	  		Flag_Espera = 0;
	  		espera_parametros = 5;
		}

	break;

	case 0x03:
		if (Flag_Espera == 1)
		{
			Cambiar_ultimaposicion(final);
			tiempo = frecuencia;
			Flag_Espera = 0;
			estado = 0x00;
		}
	break;
	}



}


//Si envio una cadena &%F, el software interpreta que estoy pidiendo datos de fecha y hora y me los devuelve
void PedirFecha (void)
{
	Transmitir ("&%F");
}

/**
 \fn  		void RecibiendoDatos(void)
 \brief 	Maquina de estados que recibe los datos y los almacena en la memoria
 \brief 	Trama esperada: (0xAA,0xA1,dia, mes, año, añobyte2, hora, min, segundo, checksum)
 \brief 	Trama esperada: (0xF7,0xF6) Me pide que envie los datos de la memoria
 \brief 	Trama esperada: (0xA7,0xA6, Frecuencia) Me envía la frecuencia con la que quiere tomar los datos
 \param 	void
 \return 	void
 */

void RecibiendoDatos(void)
{
	uint8_t aux, dato;
	char cadena[256];
	static uint8_t i = 0;
	static uint8_t estado = 0;

	if (Flag_timeout == 1)
	{
		Flag_timeout = 0;
		estado = INICIO;
	}
	dato = Pop_RX();
	if (dato != 255)
	{
	switch (estado)
	{
	case INICIO:
		if (dato == 0xAA){
			estado = FECHA1;
			timer_timeout = 5; 			//Si no termina la trama en menos de 5 segundos vuelve al estado 0
		}
		if (dato == 0xF7)
		{
			estado = ENVIAR_MEMO;
			timer_timeout = 5;
		}
		if (dato == 0xA7)
		{
			estado = FREC1;
			timer_timeout = 5;
		}
	break;

	case FECHA1:
		if (dato == 0xA1)
			estado = FECHA2;
		else
			estado = INICIO;

	break;

	case FECHA2:
		BufferUART[i] = dato;
		i++;
		if (i == 8)
		{
			i=0;
			aux = (BufferUART[0]+BufferUART[1]+BufferUART[2]+BufferUART[3]+BufferUART[4]+BufferUART[5]+BufferUART[6])&0xFF;
			if (BufferUART[7] == aux)
			{
				rellenar_fecha ();
			}
			estado = INICIO;
		}
	break;


	case ENVIAR_MEMO:
		if (dato == 0xF6)
		{
			//EnviarMemoria ();
			Flag_memoria = 1;
		}
		estado = INICIO;
	break;


	case FREC1:
		if (dato == 0xA6)
		{
			estado = LEER_FREC;
		}
		else
		{
			estado = INICIO;
		}
	break;

	case LEER_FREC:
		BufferFrec[i] = dato;
		i++;
		if (i == 2)
		{
			i = 0;
			frecuencia = ((BufferFrec[0]<<8) | BufferFrec[1]);
			sprintf (cadena,"Frecuencia: %d   ", frecuencia);
			Display_lcd(cadena, 1, 0);
			estado = INICIO;

		}
	break;

	}
	}


}

/**
 \fn  		void rellenar_fecha (void)
 \brief 	Toma los datos del buffer de la UART0 y los ordena en formato fecha/hora
 \param 	void
 \return 	void
 */
void rellenar_fecha (void)
{
	char cadena [256], cadena1 [256];

	Fecha.dia  = BufferUART[0];
	Fecha.mes  = BufferUART[1];
	Fecha.anio = ((BufferUART[2]<<8) | BufferUART[3]);
	Fecha.hora = BufferUART[4];
	Fecha.min  = BufferUART[5];
	Fecha.seg  = BufferUART[6];

	sprintf (cadena ,"Hora  %d:%d:%d",Fecha.hora, Fecha.min, Fecha.seg);
	sprintf (cadena1,"Fecha %d/%d/%d",Fecha.dia, Fecha.mes, Fecha.anio);
}

/**
 \fn  		void get_fecha (void)
 \brief 	Muestra en el display LCD la fecha
 \param 	void
 \return 	void
 */

void get_fecha(void)
{
		char cadena[256];

//
		sprintf (cadena,"Fecha %d/%d/%d",Fecha.dia, Fecha.mes, Fecha.anio);

		Display_lcd(cadena, 1, 0);

}

/**
 \fn  		void get_fecha (void)
 \brief 	Muestra en el display LCD la hora
 \param 	void
 \return 	void
 */

void get_hora(void)
{
	char cadena [256];


		sprintf (cadena ,"Hora  %d:%d:%d       ",Fecha.hora, Fecha.min, Fecha.seg);

		Display_lcd(cadena, 0, 0);

}

/**
 \fn  		void get_temperatura (void)
 \brief 	Muestra en el display LCD la temperatura tomada del BMP180
 \param 	void
 \return 	void
 */
void get_temperatura(void)
{
	char renglon1[256];



		sprintf (renglon1, "Temp:  %.1f%cC     ", (float)Temperatura/10, 210);

		Display_lcd( renglon1, 0, 0);
}

/**
 \fn  		void get_humedad (void)
 \brief 	Muestra en el display LCD la humedad tomada del DHT11
 \param 	void
 \return 	void
 */
void get_humedad(void)
{
	char renglon2[256];


		sprintf(renglon2, "Hume:  %d %c         ",Humedad, '%');

		Display_lcd( renglon2, 1, 0);
}

/**
 \fn  		void get_presion (void)
 \brief 	Muestra en el display LCD la presion tomada del BMP180
 \param 	void
 \return 	void
 */
void get_presion(void)
{
	char renglon1[256];


	sprintf (renglon1, "Pres:  %.2f hPa      ", (float)presion/100);

	Display_lcd( renglon1, 0, 0);
	Display_lcd("                ",1,0);
}

/**
 \fn  		void Fecha_AutoIncremento (void)
 \brief 	Funcion que realiza el auto-incremento en el formato correspondiente de la fecha/hora
 \param 	void
 \return 	void
 */

//Se debe entrar a esta funcion cada un segundo
void Fecha_AutoIncremento (void)
{
	Fecha.seg++;
	if (Fecha.seg == 60)
	{
		Fecha.seg = 0;
		Fecha.min++;
		if (Fecha.min == 60)
		{
		Fecha.min = 0;
		Fecha.hora++;
			if(Fecha.hora == 24)
			{
				Fecha.hora = 0;
				Fecha.dia++;
				if (Fecha.mes == 2)
				{
					if (Fecha.dia == 29)
					{
						Fecha.dia = 1;
						Fecha.mes++;
						if (Fecha.mes == 12)
						{
							Fecha.anio++;
							Fecha.mes = 1;
						}
					}
				}
				else if (Fecha.mes == 4 || Fecha.mes==6 || Fecha.mes==9 ||Fecha.mes==11)
				{
					if (Fecha.dia == 31)
					{
						Fecha.dia = 1;
						Fecha.mes++;
						if (Fecha.mes == 12)
						{
							Fecha.anio++;
							Fecha.mes = 1;
						}
					}
				}
				else
				{
					if (Fecha.dia == 32)
					{
						Fecha.dia = 1;
						Fecha.mes++;
						if (Fecha.mes == 12)
						{
							Fecha.anio++;
							Fecha.mes = 1;
						}
					}
				}
			}
		}
	}

}



void Inicializar_Fecha (void)
{
	Fecha.dia = 1;
	Fecha.mes = 1;
	Fecha.anio = 2000;
	Fecha.hora = 0;
	Fecha.min = 0;
	Fecha.seg = 0;
}


/**
 \fn  		void Seleccion_Teclas (void)
 \brief 	Muestra en el display los datos necesarios luego de oprimir una tecla en el kit
 \param 	void
 \return 	void
 */
void Seleccion_Teclas (void)
{
	uint8_t tecla;

		tecla = GetKey();

	switch(tecla)
		{
			case 0:
					get_hora();
					get_fecha();
					break;
			case 1:
					get_temperatura();
					get_humedad();
					break;
			case 2:
					get_presion();
					break;
			case 3:
					Display_lcd("                    ",0,0);
					Display_lcd("                    ",1,0);
					Display_lcd( "   Estacion " , 0 , 0 );
					Display_lcd( " Meteorologica " , 1 , 0 );
					break;
		}

}
