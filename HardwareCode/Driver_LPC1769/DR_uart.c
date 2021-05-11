/*******************************************************************************************************************************//**
 *
 * @file		DR_uart.c
 * @brief		Descripcion del modulo
 * @date		31 de ago. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_uart.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define 	MAX_TX		500
#define 	MAX_RX		100
#define		I_RX	      2
#define		I_TX	      1
#define 	CTI        	  6

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
uint8_t bufferTX[MAX_TX];
uint8_t bufferRX[MAX_RX];
uint8_t inx_TX_out;
uint8_t inx_TX_in;
uint8_t inx_RX_out;
uint8_t inx_RX_in;
uint8_t fEnviando;

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


//void UART0_IRQHandler (void)
//{
//	unsigned char iir;
//	int aux, dato;
//	do
//	{
//		//IIR es reset por HW, una vez que lo lei se resetea.
//		iir = U0IIR;
//
//		if ( iir & 0x04 ) 							//Data ready
//		{
//			//Display_lcd ("LLEGO msj -UART0", 0 , 0);
//			aux = U0RBR;
//			Push_RX ( aux );   	//guardo en buffer e incremento índice
//									//garantizo el buffer circular
//
//		}
//
//		if ( iir & 0x02 ) //THRE
//		{
//
//
//			aux = Pop_TX ( );
//			if(aux>=0)
//			{
//			U0THR = 0x58;
//			}
//			else
//			{
//				fEnviando=0;
//			}
//			}
//	}
//	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entre a la ISR habia otra
//						     	int. pendiente de atencion: b0=1 (ocurre unicamente si dentro del mismo
//								espacio temporal llegan dos interrupciones a la vez) */
//}

void UART0_IRQHandler (void)
{
	unsigned char iir;
	int aux, dato;

	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U0IIR;



	//		switch(dato)

		switch ( ( iir >> 1) & 0x07  )
		//switch((iir & 0x0E)>>1)
					{
						case (	I_RX ):
										//U0LSR &=~ LSR_RDR;
										dato = U0RBR;
										Push_RX(dato);
										break;
						case ( I_TX ):
										aux = Pop_TX();
										if( aux >=0)
										{
											U0THR = aux;
										}
										else
											fEnviando = 0;
										break;
						case ( CTI ):
										dato = U0RBR;
										Push_RX( dato );
										break;
						default:
										break;
					}
	}while ( ! ( iir & 0x01 ) );/* me fijo si cuando entr‚ a la ISR habia otra
						     	int. pendiente de atenci¢n: b0=1 (ocurre £nicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */

}


void UART0_Inicializacion (void)
{
	//1.- Registro PCONP (0x400FC0C4) - bit 3 en 1 prende la UART:
	PCONP |= 0x01<<3;
	//2.- Registro PCLKSEL0 (0x400FC1A8) - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea CCLK/4:
	PCLKSEL0 &= ~(0x03<<6);	//con un CCLOK=100Mhz, nos queda PCLOCK=25Mhz
	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	U0LCR = 0x00000083;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 9600 baudios:
	U0DLM = 0;
	U0DLL = 0xA3;//0xA3 para 9600
	//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
	//TX1D : PIN ??	-> 		P0[2]	-> PINSEL0: 04:05
	SetPINSEL( TX0 , PINSEL_FUNC1 );
	//RX1D : PIN ??	-> 		P0[3]	-> PINSEL1: 06:07
	SetPINSEL( RX0 , PINSEL_FUNC1 );
	//6.- Registro U1LCR, pongo DLAB en 0:
	U0LCR = 0x03;
	//7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U0IER = 0x03;
	ISER0 |= (1<<5);
}


void Push_RX ( uint8_t dato)
{
	bufferRX[inx_RX_in] = dato;
	inx_RX_in++;
	inx_RX_in %= MAX_RX;

}

int16_t Pop_RX ( void )
{
	int8_t dato = -1;

	if (inx_RX_in != inx_RX_out)
	{
//	return -1;

	dato = bufferRX[inx_RX_out];
	inx_RX_out++;
	inx_RX_out %= MAX_RX;
	}
	return ( uint16_t ) dato;

}

void Push_TX ( uint8_t dato)
{
//	if(fEnviando == 0)
//	{
//		fEnviando = 1;
//		U0THR = dato;
//		return;
//	}
	bufferTX[inx_TX_in] = dato;
	inx_TX_in++;
	inx_TX_in %= MAX_TX;

}


int Pop_TX( void )
{
	int dato = -1;

	if ( inx_TX_in != inx_TX_out )
	{
		dato = bufferTX[inx_TX_out];
		inx_TX_out ++;
		inx_TX_out %= MAX_TX;
	}
	return dato;
}


void Transmitir (char *p )
{
	int i;
	for( i = 0 ; p[i] ; i++ )
		Push_TX( p[i] );

	if(fEnviando == 0)
	{
		fEnviando = 1;
		U0THR = Pop_TX();
		return;
	}
}

void Transmitir_datos (char *p, uint8_t largo)
{
	int i;
	for( i = 0 ; i<largo ; i++ )
		Push_TX( p[i] );

	if(fEnviando == 0)
	{
		fEnviando = 1;
		U0THR = Pop_TX();
		return;
	}
}
