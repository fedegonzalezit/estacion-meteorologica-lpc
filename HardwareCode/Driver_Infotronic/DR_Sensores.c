/*******************************************************************************************************************************//**
 *
 * @file		DR_Sensores.c
 * @brief		Inicializacion de sensores
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Sensores.h"
#include <stdio.h>
#include <math.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define			DTHSalida		SetDIR (DTH11, SALIDA);
#define			DTHEntrada		SetDIR (DTH11, ENTRADA);
#define			DatoDTH			GetPIN (DTH11, 1);
#define			DTH_ON			SetPIN (DTH11, ON);
#define			DTH_OFF			SetPIN (DTH11, OFF);


/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
short AC1, AC2, AC3, B1, B2, MB, MC, MD;
unsigned short AC4, AC5, AC6;
long T, p, altitude;
int oss = 0;

long UT, UP,X1, X1_1, X1_2, X2, X3, B5, B6, B3;
unsigned long B4, B7;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint8_t CheckSum=0;
uint8_t Temp_byte = 0, Temp_byte2 = 0, H_byte=0, H_byte2=0;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
uint32_t bufferDHT = 0;
uint8_t fRecibiendo = 0;

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
 \fn 		void RellenarDHT (uint32_t frec)
 \brief 	Rellena el bufferDHT segun la frecuencia del pulso
 \param 	valor de frecuencia del pulso
 \return 	void
 */

void LeerBit (uint32_t frec){
static uint8_t i=0, j=0, bit=0;

		if ((frec >= 78) && (frec <= 90)) //Respuesta del DHT, comienza a recibir datos
		{
			bit = 0;
		}

		if (bit < 32){
			if ((frec <= 30) && (frec >= 20)){ 		//< Si la frecuencia esta entre 30uS y 20uS Se pone un 0
				(bufferDHT) &= ~(0x01<<(31-i));
				i++;
				bit++;
			}
			if ((frec >= 65) && (frec <= 75)){  		//Si la frec esta entre 65uS y 75uS se pone un 1
				(bufferDHT) |= (0x01<<(31-i));
				i++;
				bit++;
			}
		}

		if (bit >= 32 && bit < 40){
			if ((frec >= 65) && (frec <= 75)){  		//Si la frec esta entre 65uS y 75uS se pone un 1
				(CheckSum) |= (0x01<<(8-j));
				j++;
				bit++;
			}
			if ((frec <= 30) && (frec >= 20)){ 		//< Si la frecuencia esta entre 30uS y 24uS Se pone un 0
				(CheckSum) &= ~(0x01<<(8-j));
				j++;
				bit++;
			}
		}

		if (bit >= 40){


			if (((((bufferDHT>>8 & 0xFF) +  (bufferDHT>>24 & 0xFF)) & 0xFF) == CheckSum)&& (CheckSum != 0)){
				H_byte = (bufferDHT>>24 & 0xFF);
				H_byte2 = (bufferDHT>>16 & 0xFF);
				Temp_byte = (bufferDHT>>8 & 0xFF);
				Temp_byte2 = (bufferDHT & 0xFF);

			}

			i = 0;
			j = 0;
			bufferDHT = 0;
			CheckSum = 0;

		}

}


/**
 \fn 		void BMP180_init (void)
 \brief 	Inicializar parametros de BMP180
 \param 	void
 \return 	void
 */
void BMP180_init (void)
{

    //Read Calibration Data from E2PROM of the BMP180
	AC1 = Leer_BMP180_I2C_short (0xAA, 0xAB);
	AC2 = Leer_BMP180_I2C_short (0xAC, 0xAD);
	AC3 = Leer_BMP180_I2C_short (0xAE, 0xAF);
	AC4 = Leer_BMP180_I2C_Ushort (0xB0, 0xB1);
	AC5 = Leer_BMP180_I2C_Ushort (0xB2, 0xB3);
	AC6 = Leer_BMP180_I2C_Ushort (0xB4, 0xB5);
	B1 = Leer_BMP180_I2C_short (0xB6, 0xB7);
	B2 = Leer_BMP180_I2C_short (0xB8, 0xB9);
	MB = Leer_BMP180_I2C_short (0xBA, 0xBB);
	MC = Leer_BMP180_I2C_short (0xBC, 0xBD);
	MD = Leer_BMP180_I2C_short (0xBE, 0xBF);


}

/**
 \fn		 uint16_t BMP180_Temperatura (void)
 \brief		 Funcion que utiliza el usuario para pedir temperatura del BMP180
 \param 	 void
 \return 	 temperatura
 */

uint16_t  BMP180_Temperatura (void){

		//Read uncompensated temperature value
		UT = Get_Temperatura ( );
		//Calculate true temperatura
		X1_1 = (UT - AC6);
		X1_2 = X1_1*AC5;
		X1 = X1_2/32768;
		X2 = MC * 2048 / (X1+MD);
		B5 = X1 + X2;
		T = (B5 + 8)/16;

		return T;
}

/**
 \fn 		uint16_t BMP180_Presion (void)
 \brief 	Funcion que utiliza el usuario para pedir Presion del BMP180
 \param 	void
 \return 	presion
 */

long  BMP180_Presion (void){
		//Empiezo a calcular presion
		UP = Get_pressure ( );
		//Calculate true pressure
		B6 = B5 - 4000;
		X1 = (B2 * (B6 * B6/4096))/2048;
		X2 = AC2 * B6 / 2048;
		X3 = X1 + X3;
		B3 = (((AC1*4+X3)<<oss)+2)/4;
		X1 = AC3 * B6 / 8192;
		X2 = (B1 * (B6 * B6/4096))/65536;
		X3 = ((X1 + X2)+2)/4;
		B4 = AC4 * (unsigned long)(X3 + 32768 )/32768;
		B7 = ((unsigned long)UP -B3)*(50000>>oss);
		if (B7<0x80000000){p = (B7*2)/B4;}
		else{
			p = (B7/B4) * 2;
		}
		X1 = (p/256) * (p/256);
		X1 = (X1*3038)/65536;
		X2 = (-7357 * p)/65536;
		p = p+ (X1 + X2 + 3791)/16;

		return p;
}


/**
 \fn 		uint8_t Start_Temperatura (void)
 \brief 	Avisa al BMP180 que quiero pedir tempertura
 \param 	void
 \return	Ultimo estado del I2C
 */

uint8_t Start_Temperatura (void)
{

	LargoLectura = 0;
	LargoEscritura = 3;
	MasterBuffer[0] = BMP180_ADDRESS;
	MasterBuffer[1] = BMP180_REGISTRO_CONTROL;
	MasterBuffer[2] = BMP180_TEMPERATURA;

	return (Motor_I2C ( ));
}



/**
 \fn 		uint8_t Get_Temperatura (void)
 \brief 	Toma dato de temperatura
 \param 	void
 \return	Ultimo estado del I2C
 */
uint16_t Get_Temperatura (void)
{
uint16_t resultado;

    MasterBuffer[0] = BMP180_ADDRESS;
    MasterBuffer[1] = BMP180_REGISTRO_RESULTADO1;
    MasterBuffer[2] = BMP180_REGISTRO_RESULTADO2;

    LargoLectura = 2;
	START_REPEAT = ON;
	Motor_I2C ( );

	resultado = ((BufferEsclavo[0]<<8) | BufferEsclavo[1]);

	//resultado = BMP180_I2C_Read (BMP180_REGISTRO_RESULTADO, 2);
	return resultado;
	//Se toman los datos de buffer Esclavo

}


/**
 \fn 		uint8_t uint8_t BMP180_I2C_Write (uint8_t *datos, uint8_t largo)
 \brief 	Escribe en el BMP180
 \param 	datos: datos a escribir, Largo: Largo de escritura
 \return	Ultimo estado del I2C
 */

uint8_t BMP180_I2C_Write (uint8_t *datos, uint8_t largo)
{
	uint32_t i = 0;
	LargoEscritura = largo + 1;
	LargoLectura = 0;

	MasterBuffer[0] = BMP180_ADDRESS;
	for (i=0; i<largo; i++){
		MasterBuffer[i+1] = datos[i];
	}
	Motor_I2C ( );

	return Motor_I2C ( );

}

/**
 \fn 		uint8_t BMP180_I2C_Read (uint8_t direccion, uint8_t largo)
 \brief 	Lee del BMP180
 \param 	direccion: direccion a leer, Largo: Largo de lectura
 \return	Ultimo estado del I2C

 */

uint8_t BMP180_I2C_Read (uint8_t Address_High, uint8_t Address_Low, uint8_t largo)
{

	LargoEscritura = 3;
	LargoLectura = largo;
	MasterBuffer[0] = BMP180_ADDRESS;
	MasterBuffer[1]	= Address_High;
	MasterBuffer[2] = Address_Low;
	START_REPEAT = ON;


	return Motor_I2C ( );

}

/**
 \fn 		uint8_t Start_pressure (void)
 \brief 	Avisa al BMP180 que quiero pedir tempertura
 \param 	void
 \return	Ultimo estado del I2C
 */

uint8_t Start_pressure (void)
{

	LargoEscritura = 3;
	LargoLectura = 0;
	MasterBuffer[0] = BMP180_ADDRESS;
	MasterBuffer[1] = BMP180_REGISTRO_CONTROL;
	MasterBuffer[2] = BMP180_COMMAND_PRESSURE0;


	return (Motor_I2C ( ));
}

/**
 \fn 		uint8_t Get_pressure (void)
 \brief 	Toma dato de presion
 \param		void
 \return	Ultimo estado del I2C
 */
uint16_t Get_pressure (void)
{
	uint16_t resultado;
	LargoEscritura = 2;
	LargoLectura = 3;
	MasterBuffer[0] = BMP180_ADDRESS;
	MasterBuffer[1] = BMP180_REGISTRO_RESULTADO1;
	MasterBuffer[2] = BMP180_REGISTRO_RESULTADO2;
	START_REPEAT = ON;

	Motor_I2C ( );

	resultado = ((BufferEsclavo[0]<<8) | BufferEsclavo[1]);

	return resultado;
}


/**
 \fn 		short Leer_BMP180_I2C_short (uint8_t Address_High, uint8_t Address_Low)
 \brief 	Se utiliza para inicializar los parametros del BMP180
 \param		Adress_High: direccion de memoria con datos de calibracion(High)
 \param		Adress_Low:  direccion de memoria con datos de calibracion(Low)
 \return	Parametro de calibracion
 */
short Leer_BMP180_I2C_short (uint8_t Address_High, uint8_t Address_Low)
{
	short parametro;

	if (BMP180_I2C_Read (Address_High, Address_Low, 2) == I2C_OK){
		parametro = (short)BufferEsclavo[0]<<8 | (short)BufferEsclavo[1];
		if (parametro & 0x8000) parametro |= 0xFFFF0000;
		return parametro;
	}
	return 0;
}


/**
 \fn 		unsigned short Leer_BMP180_I2C_Ushort (uint8_t Address_High, uint8_t Address_Low)
 \brief 	Se utiliza para inicializar los parametros del BMP180
 \param		Adress_High: direccion de memoria con datos de calibracion(High)
 \param		Adress_Low:  direccion de memoria con datos de calibracion(Low)
 \return	Parametro de calibracion
 */
unsigned short Leer_BMP180_I2C_Ushort (uint8_t Address_High, uint8_t Address_Low)
{
	short parametro;

	if (BMP180_I2C_Read (Address_High, Address_Low, 2) == I2C_OK){
		parametro = (((unsigned short)BufferEsclavo[0]<<8) | (unsigned short)BufferEsclavo[1]);
		return parametro;
	}
	return 0;
}
