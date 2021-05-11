/*******************************************************************************************************************************//**
 *
 * @file		PR_24LC256.c
 * @brief
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Inicializacion.h"
#include "PR_24LC256.h"
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
 \fn 		 uint16_t BuscarFinal(void)
 \brief 	 Busca la posicion del primer byte libre y la devuelve (Leyendo los dos primeros bytes)
 \param		 void
 \return 	 Posicion del primer byte libre
 */
uint16_t BuscarFinal (void)
{

	uint16_t aux1, aux2;
	uint16_t largo;


	aux1 = LeerByte_LC_256(0x00, 0x00);
	aux2 = LeerByte_LC_256(0x00, 0x01);

	largo = aux1<<8 | aux2;

	return (largo);
}


/**
 \fn		 uint16_t Insertar_Memoria_bytes (char *cadena, uint16_t posicion, uint8_t largo)
 \brief 	 Inserta una cadena de bytes en una posicion de la memoria
 \param 	 cadena: cadena a guardar en la memoria
 \param 	 posicion: Posicion donde ingresar cadena
 \param 	 largo: largo de la cadena
 \return 	 Posicion final.
 */
uint16_t Insertar_Memoria_bytes (char *cadena, uint16_t posicion,uint8_t largo)
{
	uint16_t Address_High, Address_Low;
	char cadena1[64], cadena2[64];
	uint8_t i, j;

	Address_High = posicion / 256;

	Address_Low = posicion%256;

	//Memoria llena?
	if (Address_High > 0x7F)
	{
		return -1;
	}

	//Si me paso de pagina tengo que dividirlo en 2
	if (posicion%64+largo > 64)
	{
			for (i=0; i<(64-(posicion%64)); i++)
			{
				cadena1[i] = cadena[i];
			}

			EscribirBytes(Address_High, Address_Low, cadena1,i);
			for (j=0; j<=largo-i; j++)
			{
				cadena2[j] = cadena[i+j];
			}

			Address_High = (posicion+i)/256;
			Address_Low = (posicion+i)%256;
			EscribirBytes (Address_High, Address_Low, cadena2, j);

	}
	else
	{
		EscribirBytes (Address_High, Address_Low, cadena, largo);
	}
	return (posicion+largo);

}

/**
 \fn		 uint16_t Insertar_Memoria_cadena (char *cadena, uint16_t posicion)
 \brief 	 Inserta una cadena de caracteres en una posicion de la memoria
 \param 	 cadena: cadena a guardar en la memoria
 \param 	 posicion: Posicion donde ingresar cadena
 \return 	 Posicion final.
 */
uint16_t Insertar_Memoria_cadena (char *cadena, uint16_t posicion)
{
	uint16_t Address_High, Address_Low, largo;
	char cadena1[64], cadena2[64];
	uint8_t i, j;

	Address_High = posicion / 256;

	Address_Low = posicion%256;

	//Memoria llena?
	if (Address_High >= 0x7F)
	{
		return -1;
	}

	//largo de la cadena hasta \r
	for (largo = 0; cadena[largo] != '\0'; largo++);

	//Si me paso de pagina tengo que dividirlo en 2
	if (posicion%64+largo > 64)
	{
			for (i=0; i<(64-(posicion%64)); i++)
			{
				cadena1[i] = cadena[i];
			}

			EscribirMemoria (Address_High, Address_Low, cadena1);
			for (j=0; j<=largo-i; j++)
			{
				cadena2[j] = cadena[i+j];
			}

			Address_High = (posicion+i)/256;
			Address_Low = (posicion+i)%256;
			EscribirMemoria (Address_High, Address_Low, cadena2);

	}
	else
	{
		EscribirMemoria (Address_High, Address_Low, cadena);
	}
	return (posicion+largo);

}

/**
 \fn		 void LeerPagina (uint16_t Pagina)
 \brief 	 Lee una pagina
 \param 	 Pagina: pagina que quiero leer
 \return 	 void
 */
void LeerPagina (uint16_t Pagina)
{
	uint8_t Address_High, Address_Low;
	uint16_t posicion;

	posicion = Pagina*64;
	Address_High = posicion / 256;
	Address_Low = posicion%256;
	LeerMemoria (Address_High, Address_Low);

}


/**
 \fn		 void Cambiar_ultimaposicion (uint16_t final)
 \brief		 Actualiza el valor de la ultima posicion
 \param 	 final:	el nuevo valor que quiero que tome
 \return 	 void
 */
void Cambiar_ultimaposicion (uint16_t final)
{
	char cadena[3];

	cadena [0] = (char)(final>>8);
	cadena [1] = (char)(final&0xFF);

	EscribirBytes(0x00, 0x00, cadena, 2);
}
