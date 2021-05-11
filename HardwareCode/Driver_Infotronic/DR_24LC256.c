/*******************************************************************************************************************************//**
 *
 * @file		DR_24LC256.c
 * @brief		Driver para el funcionamiento de la memoria 24LC256
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_24LC256.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define		SIZE_BUFFER		64
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
char BufferMemoria[64];
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
 \fn 		uint8_t EscribirMemoria_byte (uint8_t address1, uint8_t address2, uint8_t data)
 \brief		Escribe 1 byte en una direccion especifica de la memoria
 \param		adress1: direccion mas significativa de memoria
 \param		adress2: direccion menos significativa de memoria
 \return	Ultimo estado del I2C
 */
uint8_t EscribirMemoria_byte (uint8_t address1, uint8_t address2, uint8_t data)
{

	MasterBuffer[0] = 0xA0;  //Direccion con bit de escritura
	MasterBuffer[1] = address1;
	MasterBuffer[2] = address2;

	MasterBuffer[3] = data;

	LargoEscritura = 4;

	return (Motor_I2C ( ));
}

/**
 \fn 		uint8_t LeerMemoria (uint8_t Address_High, uint8_t Address_Low)
 \brief		Lee la memoria a partir de la direccione enviada
 \param		Adress_High: Direccion mas significativa de memoria
 \param		Adress_Low: Direccion menos significativa de memoria
 \return	0
 */
uint8_t LeerMemoria (uint8_t Address_High, uint8_t Address_Low)
{
	int i;
	MasterBuffer[0] = (LC_Address);
	MasterBuffer[1] = Address_High;
	MasterBuffer[2] = Address_Low;
	LargoEscritura = 3;
	LargoLectura = 64;
	START_REPEAT=1;

	Motor_I2C ();

	for (i=0; i<64; i++)
	{
		BufferMemoria[i] = BufferEsclavo[i];

	}
	return 0;
}

/**
 \fn 		uint8_t LeerByte_LC_256 (uint8_t Adress_High, uint8_t Adress_Low)
 \brief		Lee el byte de memoria de la direccion enviada
 \param		Adress_High: Direccion mas significativa de memoria
 \param		Adress_Low: Direccion menos significativa de memoria
 \return	Byte leido
 */
uint8_t LeerByte_LC_256 (uint8_t Adress_High, uint8_t Adress_Low)
{
uint8_t dato;
	MasterBuffer[0] = 0xA0;  //Direccion de memoria
	MasterBuffer[1] = Adress_High;
	MasterBuffer[2] = Adress_Low;
	LargoEscritura = 3;
	LargoLectura = 1;
	START_REPEAT = ON;

	Motor_I2C ( );

	dato = BufferEsclavo[0];

	return dato;

}

/**
 \fn 		void EscribirMemoria(uint8_t Address_Comienzo_High, Address_Comienzo_Low, char *cadena)
 \brief		Escribe una cadena de caracteres en una posicion especifica de memoria
 \param		Adress_Comienzo_High: direccion mas significativa
 \param		Adress_Comienzo_Low: direccion menos significativa
 \param		cadena: cadena que quiero escribir
 \return	void
 */

void EscribirMemoria(uint8_t Address_Comienzo_High,uint8_t Address_Comienzo_Low, char *cadena)
{
	uint16_t i;
	MasterBuffer[0] = LC_Address;
	MasterBuffer[1] = Address_Comienzo_High;
	MasterBuffer[2] = Address_Comienzo_Low;

	for (i=0; cadena[i]!='\0'; i++)
	{
		MasterBuffer[i+3] = cadena[i];
	}

	LargoEscritura = i+3;
	Motor_I2C ( );
}

/**
 \fn 		void EscribirBytes(uint8_t Address_Comienzo_High,uint8_t Address_Comienzo_Low, char *datos, uint8_t largo)
 \brief		Escribe una cadena de bytes en una posicion especifica de memoria
 \param		Adress_Comienzo_High: direccion mas significativa
 \param		Adress_Comienzo_Low: direccion menos significativa
 \param		datos: bytes que quiero escribir
 \param		largo: largo de la cadena que escribo
 \return	void
 */
void EscribirBytes(uint8_t Address_Comienzo_High,uint8_t Address_Comienzo_Low, char *datos, uint8_t largo)
{
	uint16_t i;
	MasterBuffer[0] = LC_Address;
	MasterBuffer[1] = Address_Comienzo_High;
	MasterBuffer[2] = Address_Comienzo_Low;

	for (i=0; i<largo; i++)
	{
		MasterBuffer[i+3] = datos[i];
	}

	LargoEscritura = i+3;
	Motor_I2C ( );
}
