/*******************************************************************************************************************************//**
 *
 * @file		DR_I2C.c
 * @brief		Funciones del I2C
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_I2C.h"
#include "DR_EINT.h"
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
uint8_t MasterBuffer[BUFFER_SIZE], BufferEsclavo[BUFFER_SIZE];
volatile uint32_t IndexEscritura, IndexLectura, Ultimo;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint32_t LargoLectura=0 , LargoEscritura=0;
uint8_t FlagMaster = I2C_IDLE, START_REPEAT, FlagI2C;
uint32_t I2C_Timeout = 0;
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
 \fn  		void I2C0_Inicializacion(void)
 \brief 	Funcion de inicializacion del I2C0
 \param 	void
 \return 	void
 */
void I2C1_Inicializacion(void)
{
		PCONP		|= 	ALIMENTA_I2C1;
		PCLKSEL1	&=  PCLK_I2C1;
		//Aca selecciono que pins voy a usar
		SetPINSEL (0, 0, PINSEL_FUNC3);		//Pin0.0 SDA1
		SetPINSEL (0, 1, PINSEL_FUNC3);		//Pin0.1 SCL1
		SetMODE (0, 0, 2); //Ni pull-up ni pull-down
		SetMODE (0, 1, 2); //Ni pull-up ni pull-down




		/*Limpio bits */
		I2C1CONCLR		|=	0x04;
		I2C1CONCLR		|=	0x08;
		I2C1CONCLR		|=	0x20;
		I2C1CONCLR		|=	0x40;
		/*-------------*/

		/*Eligo SCLL y SCLH Fast Mode*/
		I2C1SCLH		|=	SCLH_SET;			//Seteo el clock nivel alto
		I2C1SCLL		|=	SCLL_SET;			//Seteo el clock nivel bajo



		ISE_I2C1;								//Habilito Interrupciones
		I2C1CONSET		|=  I2EN_ENABLE;		//Activo interfaz I2C
		I2C1CONSET		|=  AA_ENABLE;			//Activo interfaz I2C

}


/**
	\fn 		void I2C0_IRQHandler (void)
	\brief	 	Interrupción de I2C
 	\param 		void
	\return 	void
*/
void I2C1_IRQHandler(void)
{

		I2C_Timeout = 0;

		//Bus Error. Enter not addressed Slave mode and release bus.
		if ((I2C1STAT & 0xFF) == 0x00){

			//1. Write 0x14 to I2CONSET to set the STO and AA bits.
			I2C1CONSET |= 0x14;

			/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR |= 0x08;
		}


		else if ((I2C1STAT & 0xFF) == 0x08){

			/*
			A START condition has been transmitted. Se envía la direccion del esclavo + R/W.*/
			IndexEscritura = 0;
			IndexLectura = 0;
			/*1. Se escribe la direccion del esclavo+R/W en I2C0DAT*/
			I2C1DAT = MasterBuffer[IndexEscritura];
			/*2. Write 0x04 to I2CONSET to set the AA bit.*/
			I2C1CONSET = 0x04;
		    /*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x28;

			FlagMaster = I2C_STARTED;

			IndexEscritura++;

		}


		else if ((I2C1STAT & 0xFF) == 0x10){
			IndexEscritura = 0;
			IndexLectura = 0;
			/* A repeated START condition has been transmitted.
			 * Se envía la direccion del esclavo + R/W.*/
			/*1. Se escribe la direccion del esclavo +R/W en I2C0DAT*/
			I2C1DAT = MasterBuffer[IndexEscritura];
			/*2. Write 0x04 to I2CONSET to set the AA bit.*/
			I2C1CONSET = 0x04;
			/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x28;

			IndexEscritura++;
			//printf ("0x10\n");

		}



		// Estado: Master transmitiendo

		else if ((I2C1STAT & 0xFF) == 0x18){
			/*
			Estado previo: 0x08 o 0x10, Se transmitió la dirección de esclavo
			y se recibió el ACK. Se transmite el primer byte de datos.*/

			if (LargoEscritura == 1)
			{
				I2C1CONSET = I2CONSET_STO;
				FlagMaster = I2C_NO_DATA;
			}

			else{
				/*1. Se carga el I2C0DAT con el primer byte de datos del buffer.*/
				I2C1DAT = MasterBuffer[IndexEscritura];
				/*4. Increment Master Transmit buffer pointer.*/
				IndexEscritura++;
			}
			/*2. Write 0x04 to I2CONSET to set the AA bit.*/
			I2C1CONSET = 0x04;
			/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR  = 0x28;
			//printf ("0x18\n");
		}


		else if ((I2C1STAT & 0xFF) == 0x20){
			/*
			Slave Address + Write has been transmitted,No se ricibio el ACK. Se transmite
			ciondicion de stop.*/

			/*1. Write 0x14 to I2CONSET to set the STO and AA bits.*/
			I2C1CONSET = 0x14;

			/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x28;
		//	printf ("0x20\n");

		}


		else if ((I2C1STAT & 0xFF) == 0x28){
			/*
			Los datos se transmitieron y se recibio el ACK. Si el dato transmitido es el ultimo
			se envía bit de STOP, sino se envía el siguiente byte de datos.*/

			if (IndexEscritura < LargoEscritura)
			{
				/*5. Load I2DAT with next data byte from Master Transmit buffer.*/
				I2C1DAT = MasterBuffer [IndexEscritura];
				/*8. Increment Master Transmit buffer pointer*/
				IndexEscritura++;
				I2C1CONCLR = 0x08;
			}
			else if (START_REPEAT)
			{
				START_REPEAT = 0;
				I2C1CONSET =  0x20;
				MasterBuffer[0] |= 0x01;
				I2C1CONCLR = 0x08;
//				FlagMaster = I2C_REPEATED_START;

			}
			else
			{
				/*2. Write 0x14 to I2CONSET to set the STO and AA bits.*/
				I2C1CONSET = 0x14;
				/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
				I2C1CONCLR = 0x08;
				FlagMaster = I2C_OK;
			}
			//printf ("0x28\n");

		}

		else if ((I2C1STAT & 0xFF) == 0x30){
			/*
			Los datos se transmitieron, No se recibio el ACK. Se transmite condicion de STOP.*/

			/*1. Write 0x14 to I2CONSET to set the STO and AA bits.*/
			I2C1CONSET = 0x14;

			/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x08;

			FlagMaster = I2C_NOACK;
			//printf ("0x30\n");

		}

		else if ((I2C1STAT & 0xFF) == 0x38){
			/*
			Arbitration has been lost during Slave Address + Write or data. The bus has been
			released and not addressed Slave mode is entered. A new START condition will be
			transmitted when the bus is free again.*/

			/*1. Write 0x24 to I2CONSET to set the STA and AA bits.*/
			I2C1CONSET = 0x24;
			/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x08;
			FlagMaster = I2C_LOST;
			//printf ("0x38\n");

		}

		//Estado: Master recibiendo

		else if ((I2C1STAT & 0xFF) == 0x40){
			/*
			Estado anterior: 0x08 o 0x10. Se transmitio dirreccion de esclavo,
			Se recibio ACK. Data will be received and ACK returned.*/

			if ((IndexEscritura)< LargoLectura)
			{
				/*1. Write 0x04 to I2CONSET to set the AA bit.*/
				I2C1CONSET = 0x04;
			}
			else
			{
				I2C1CONCLR = I2CONCLR_AAC;
			}
			/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x08;
			//printf ("0x40\n");

		}


		else if ((I2C1STAT & 0xFF) == 0x48)
		{
			/*
			Se envió dirreción de esclavo, No se recibió ACK. Se envía condicion de STOP*/
			/*1. Write 0x14 to I2CONSET to set the STO and AA bits.*/
			I2C1CONSET = 0x14;

			/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x08;

			FlagMaster = I2C_NACK_ON_ADDRESS;
			//printf ("0x48\n");
		}


		else if ((I2C1STAT & 0xFF) == 0x50)
		{
			/*
			Se recibio dato, Se envió ACK. Se leen los datos de I2DAT. Additional
			data will be received. If this is the last data byte then NOT ACK will be returned,
			otherwise ACK will be returned.*/

			/*1. Read data byte from I2DAT into Master Receive buffer.*/
			BufferEsclavo[IndexLectura++] = I2C1DAT;

			/*2. Decrement the Master data counter, skip to step 5 if not the last data byte.*/
			if (IndexLectura+1 < LargoLectura){
				/* 3. Write 0x0C to I2CONCLR to clear the SI flag and the AA bit.*/
			//	I2C1CONCLR = 0x0C;
				I2C1CONSET = 0x04;
			}else
			{
			/*5. Write 0x04 to I2CONSET to set the AA bit.*/
			//I2C1CONSET = 0x04;
			/*6. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x04;
			}
			I2C1CONCLR = I2CONCLR_SIC;
			//printf ("0x50\n");
		}


		else if ((I2C1STAT & 0xFF) == 0x58)
		{
			/*
			Se recibio datos, No se retorno ACK. Se lee datos de I2DAT. Se envía condicion de STOP.*/

			/*1. Read data byte from I2DAT into Master Receive buffer.*/
			BufferEsclavo[IndexLectura]	= I2C1DAT;
			/*2. Write 0x14 to I2CONSET to set the STO and AA bits.*/
			I2C1CONSET = 0x14;
			/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
			I2C1CONCLR = 0x08;

			FlagMaster = I2C_OK;
			//printf ("0x58\n");
		}



}



/**
	\fn		    uint8_t Motor_I2C ( )
	\brief 		Inicia comunicacion I2C y espera que finalice
 	\param 		void
	\return 	Estado final del I2C
*/

uint8_t Motor_I2C ( )
{
	//Envío bit de start
	I2C1CONSET =  CONSET_STA;

	FlagMaster = OCUPADO;

	while ((FlagMaster == OCUPADO) || (FlagMaster == I2C_STARTED))
	{
		if (I2C_Timeout >= TIMEOUT){
			FlagMaster = ESTADO_TIMEOUT;
			break;
		}
		I2C_Timeout++;
	}

	I2C1CONCLR = I2CONCLR_STAC;

	return (FlagMaster);

}



/**
	\fn		    uint8_t Start_I2C (void)
	\brief 		Inicia comunicacion I2C
 	\param 		void
	\return 	Si se pudo iniciar retorna ON, sino un OFF
*/
uint8_t Start_I2C (void)
{
	uint8_t rVal = OFF;

	I2C_Timeout = 0;


	I2C1CONSET = CONSET_STA;


	//Espero hasta que cambie el flag o hasta que se supere el tiempo limite
	while(1)
	{
		if(FlagMaster == I2C_STARTED)
		{
			rVal = ON;
			break;
		}
		if(I2C_Timeout >= TIMEOUT)
		{
			rVal = OFF;
			break;
		}
		I2C_Timeout++;
	}

  return(rVal);
}


/**
	\fn		    uint8_t Stop_I2C (void)
	\brief 		Finaliza comunicacion I2C
 	\param 		void
	\return 	ON
*/
uint8_t Stop_I2C (void)
{
	I2C1CONSET = CONSET_STO;    //Seteo Stop
	I2C1CONCLR = I2CONCLR_SIC;  //Limpio flag

	//Espero hasta que se detiene
	while(I2C1CONSET & I2CONSET_STO);

  return ON;
}
