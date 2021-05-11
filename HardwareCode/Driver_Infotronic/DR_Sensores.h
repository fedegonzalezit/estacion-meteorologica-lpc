/*******************************************************************************************************************************//**
 *
 * @file		DR_Sensores.h
 * @brief		Macros, tipos, prototipos del driver
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_Sensores_H_
#define DR_Sensores_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Infotronic.h"
#include "DR_timer0123.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		DHT11		2,8  		// Expansión 16
//#define		DHT11		1,18  		// Expansión 15
#define		BUFFER_SIZE						64
#define		BMP180_REGISTRO_CONTROL			0xF4
#define		BMP180_TEMPERATURA				0x2E
#define		BMP180_REGISTRO_RESULTADO1		0xF6
#define		BMP180_REGISTRO_RESULTADO2		0xF7
#define		BMP180_ADDRESS					0xEE
#define		READ_BIT         				0x01
#define		BMP180_COMMAND_PRESSURE0 		0x34
#define		BMP180_COMMAND_PRESSURE1 		0x74
#define		BMP180_COMMAND_PRESSURE2 		0xB4
#define		BMP180_COMMAND_PRESSURE3 		0xF4
#define		DATO_TEMPERATURA				0
#define		DATO_PRESION					1
#define		DATO_ALTURA						2
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint8_t MasterBuffer[BUFFER_SIZE];
extern uint8_t BufferEsclavo[BUFFER_SIZE];
extern uint32_t LargoLectura;
extern uint32_t LargoEscritura;
extern uint8_t FlagMaster;
extern uint8_t START_REPEAT;
/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

void LeerBit (uint32_t frec);
void BMP180_init (void);
long  BMP180_Presion (void);
uint16_t  BMP180_Temperatura (void);
uint8_t Start_Temperatura (void);
uint16_t Get_Temperatura (void);
uint8_t BMP180_I2C_Write (uint8_t *datos, uint8_t largo);
uint8_t Start_pressure (void);
uint16_t Get_pressure (void);
short Leer_BMP180_I2C_short (uint8_t Address_High, uint8_t Address_Low);
unsigned short Leer_BMP180_I2C_Ushort (uint8_t Address_High, uint8_t Address_Low);
uint8_t BMP180_I2C_Read (uint8_t Address_High, uint8_t Address_Low, uint8_t largo);
long BMP180_Sealevel(long P, long A);


#endif /* TEMPLATE_H_ */
