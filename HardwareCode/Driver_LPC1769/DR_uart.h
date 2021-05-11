/*******************************************************************************************************************************//**
 *
 * @file		DR_uart.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		31 de ago. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DR_UART_H_
#define DR_UART_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_PLL.h"
#include "DR_gpio.h"
#include "DR_EINT.h"
#include "DR_pinsel.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//!< /////////////		UARTs		///////////////////////////
//0x40010000UL : Registro de recepcion de la UART0:
#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )

#define		U0RBR		DIR_UART0[0]	// Registro de Recepción RBR
#define		U0THR		DIR_UART0[0]	// Registro de Transmisión THR
#define		U0DLL		DIR_UART0[0]	// Parte baja del divisor de la UART0:
#define		U0IER		DIR_UART0[1]	// Registro de Habilitación de interrupciones de la UART0:
#define		U0DLM		DIR_UART0[1]	// Parte Alta del divisor de la UART0:
#define		U0IIR		DIR_UART0[2]	// Registro de Identificación de interrupciones de la UART0:
#define		U0LCR		DIR_UART0[3]	// Line CONTROL Register de la UART0:
#define		U0LSR		DIR_UART0[5]	// Line STATUS Register de la UART0:

//Macros UART0
#define		U0DLAB_OFF	(U0LCR & 0xEF)
#define		U0DLAB_ON	(U0LCR | 0x80)


//0x40010000UL : Registro de recepcion de la UART1:
#define		DIR_UART1		( ( __RW uint32_t  * ) 0x40010000UL )

#define		U1RBR		DIR_UART1[0]
#define		U1THR		DIR_UART1[0]
#define		U1DLL		DIR_UART1[0]
#define		U1IER		DIR_UART1[1]
#define		U1DLM		DIR_UART1[1]
#define		U1IIR		DIR_UART1[2]
#define		U1LCR		DIR_UART1[3]
#define		U1LSR		DIR_UART1[5]

#define 	LSR_RDR		0x01
//Comunicación serie
#define 	TX0			0, 2	//Tx de la UART0
#define 	RX0			0, 3	//Rx de la UART0

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Push_RX (uint8_t dato);
int16_t Pop_RX ( void);
void UART0_Inicializacion (void);
int Pop_TX( void );
void Push_TX ( uint8_t dato);
void Transmitir (char *p );
void Transmitir_datos (char *p, uint8_t largo);

#endif /* DR_UART_H_ */
