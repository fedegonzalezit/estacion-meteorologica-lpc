/*******************************************************************************************************************************//**
 *
 * @file		DR_I2C.h
 * @brief		Macros y prototipos  del driver
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_I2C_H_
#define DR_I2C_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_PLL.h"
#include "DR_EINT.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//Registros I2C-0
#define		I2C0	( ( __RW uint32_t * ) 0x4001C000 )

#define		I2C0CONSET			I2C0[0] 	//!<Control Set Register: Se escribe con un 1, un 0 no hace efecto
#define		I2C0STAT			I2C0[1]		//!<Status Register
#define		I2C0DAT				I2C0[2]		//!<Data Register: Mientras el maestro o el esclavo transmiten, los datos se escriben en este registro
#define		I2C0ADR0			I2C0[3]		//!<Direccion Esclavo Registro 0: Contiene los 7 bits de direccion. Solo se utiliza en modo esclavo. El bit menos significativo determina si un esclavo responde a la direccion llamada
#define		I2C0SCLH			I2C0[4]		//!<SCH Register: Determines the high time of the I2C clock.
#define		I2C0SCLL			I2C0[5]		//!<SCL Register: Determines the low time of the I2C clock.
#define		I2C0CONCLR			I2C0[6]		//!<Registro de control: Clear. Con un 1 se borra el bit correspondiente en el registro
#define		I2C0MMCTRL			I2C0[7]		//!<Monitor mode control register.
#define		I2C0ADR1			I2C0[8]		//!<Direccion Esclavo Registro 1.
#define		I2C0ADR2			I2C0[9]		//!<Direccion de Esclavo Registro 2.
#define		I2C0ADR3			I2C0[10]	//!<Direccion de esclavo Registro 3.
#define		I2C0DATA_BUFFER 	I2C0[11]	//!<Registro de datos del buffer.
#define		I2C0MASK0			I2C0[12]	//!<I2C Slave address mask register 0. Determina coincidencia en el registro de direccion
#define		I2C0MASK1			I2C0[13]	//!<I2C Slave address mask register 1.
#define		I2C0MASK2			I2C0[14]	//!<I2C Slave address mask register 2.
#define		I2C0MASK3			I2C0[15]	//!<I2C Slave address mask register 2.



//Registros I2C-1
#define		I2C1	( ( __RW uint32_t * ) 0x4005C000 )

#define		I2C1CONSET			I2C1[0] 	//!<Control Set Register: Se escribe con un 1, un 0 no hace efecto
#define		I2C1STAT			I2C1[1]		//!<Status Register
#define		I2C1DAT				I2C1[2]		//!<Data Register: Mientras el maestro o el esclavo transmiten, los datos se escriben en este registro
#define		I2C1ADR0			I2C1[3]		//!<Direccion Esclavo Registro 0: Contiene los 7 bits de direccion. Solo se utiliza en modo esclavo. El bit menos significativo determina si un esclavo responde a la direccion llamada
#define		I2C1SCLH			I2C1[4]		//!<SCH Register: Determines the high time of the I2C clock.
#define		I2C1SCLL			I2C1[5]		//!<SCL Register: Determines the low time of the I2C clock.
#define		I2C1CONCLR			I2C1[6]		//!<Registro de control: Clear. Con un 1 se borra el bit correspondiente en el registro
#define		I2C1MMCTRL			I2C1[7]		//!<Monitor mode control register.
#define		I2C1ADR1			I2C1[8]		//!<Direccion Esclavo Registro 1.
#define		I2C1ADR2			I2C1[9]		//!<Direccion de Esclavo Registro 2.
#define		I2C1ADR3			I2C1[10]	//!<Direccion de esclavo Registro 3.
#define		I2C1DATA_BUFFER	    I2C1[11]	//!<Registro de datos del buffer.
#define		I2C1MASK0			I2C1[12]	//!<I2C Slave address mask register 0. Determina coincidencia en el registro de direccion
#define		I2C1MASK1			I2C1[13]	//!<I2C Slave address mask register 1.
#define		I2C1MASK2			I2C1[14]	//!<I2C Slave address mask register 2.
#define		I2C1MASK3			I2C1[15]	//!<I2C Slave address mask register 2.



//Registros I2C-3
#define		I2C3	( ( __RW uint32_t * ) 0x4001C000 )

#define		I2C3CONSET			I2C3[0] 	//!<Control Set Register: Se escribe con un 1, un 0 no hace efecto
#define		I2C3STAT			I2C3[1]		//!<Status Register
#define		I2C3DAT				I2C3[2]		//!<Data Register: Mientras el maestro o el esclavo transmiten, los datos se escriben en este registro
#define		I2C3ADR0			I2C3[3]		//!<Direccion Esclavo Registro 0: Contiene los 7 bits de direccion. Solo se utiliza en modo esclavo. El bit menos significativo determina si un esclavo responde a la direccion llamada
#define		I2C3SCLH			I2C3[4]		//!<SCH Register: Determines the high time of the I2C clock.
#define		I2C3SCLL			I2C3[5]		//!<SCL Register: Determines the low time of the I2C clock.
#define		I2C3CONCLR			I2C3[6]		//!<Registro de control: Clear. Con un 1 se borra el bit correspondiente en el registro
#define		I2C3MMCTRL			I2C3[7]		//!<Monitor mode control register.
#define		I2C3ADR1			I2C3[8]		//!<Direccion Esclavo Registro 1.
#define		I2C3ADR2			I2C3[9]		//!<Direccion de Esclavo Registro 2.
#define		I2C3ADR3			I2C3[10]	//!<Direccion de esclavo Registro 3.
#define		I2C3DATA_BUFFER		I2C3[11]	//!<Registro de datos del buffer.
#define		I2C3MASK0			I2C3[12]	//!<I2C Slave address mask register 0. Determina coincidencia en el registro de direccion
#define		I2C3MASK1			I2C3[13]	//!<I2C Slave address mask register 1.
#define		I2C3MASK2			I2C3[14]	//!<I2C Slave address mask register 2.
#define		I2C3MASK3			I2C3[15]	//!<I2C Slave address mask register 2.



//Registro de configuracion de pin I2C para pin 0.27 y 0.28 -- Pag 119.
#define		I2CPADCFG	( ( __RW uint32_t * ) 0x4002C07C )


//Defines

#define		ALIMENTA_I2C0		0x00000080		//Enciente bit de alimentacion de I2C0
#define		ALIMENTA_I2C1		0x00080000		//Enciente bit de alimentacion de I2C1
#define		ALIMENTA_I2C2		0x04000000		//Enciende bit de alimentacion de I2C2
#define		PCLK_I2C0			~(0x03<<14)		//Selecciono fuente de clock CLCK/4 (25Mhz) para I2C0 (USAR PCLKSEL0)
#define		PCLK_I2C1			0x0000003F		//Selecciono fuente de clock CLCK/4 (25Mhz) para I2C1 (USAR PCLKSEL1)
#define		PCLK_I2C2			~(0x03<<20)		//Selecciono fuente de clock CLCK/4 (25Mhz) para I2C2 (USAR PCLKSEL1)
#define		I2EN_ENABLE			0x00000040		//Pone en 1 el bit 6 I2EN
#define		AA_ENABLE			0x00000004		//Pone en 1 el bit 2 Assert acknowledge flag.
#define		SCLL_SET			0x00000080
#define		SCLH_SET			0x00000080
#define		BUFFER_SIZE			64
#define     I2CONSET_STO        (0x1<<4)		//Bit de stop
#define		CONSET_STO			0x00000010		//Pone un 1 en bit de STOP
#define		CONSET_STA			0x00000020		//Pone un 1 en bit de START
#define		TIMEOUT				0x0000FFFF
#define		I2CONCLR_STAC		(0x01<<5)
#define	 	I2CONCLR_SIC        (0x01<<3)
#define     I2CONCLR_AAC        (0x01<<2)
#define		APAGADO				0
#define		ENVIANDO			1
#define		RECIBIENDO			2


//Estados FlagMaster
#define		I2C_IDLE				0
#define     I2C_OK              	12
#define     I2C_LOST            	1
#define     I2C_NOACK           	2
#define		I2C_NO_DATA		    	3
#define		I2C_NACK_ON_ADDRESS		4
#define		I2C_STARTED				5
#define		OCUPADO					6
#define		ESTADO_TIMEOUT			7
#define     I2C_REPEATED_START  	8


/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void I2C1_Inicializacion(void);

uint8_t Motor_I2C (void);
uint8_t Start_I2C (void);
uint8_t Stop_I2C (void);

#endif /* TEMPLATE_H_ */
