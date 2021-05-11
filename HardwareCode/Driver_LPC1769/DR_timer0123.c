/*******************************************************************************************************************************//**
 *
 * @file		DR_timer0123.c
 * @brief		Descripcion del modulo
 * @date		5 de jul. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_timer0123.h"
#include "DR_PLL.h"
#include "DR_EINT.h"
#include "DR_gpio.h"
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
uint32_t ContadorTimer0 = 0;
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
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 5 de jul. de 2016
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
/**
 \fn  void InicTimeo0 (void)
 \brief Inicializa timer 0 para trabajar en captura del canal 0 generando interrupciones
 \author CATEDRA INFO2
 \date: - Nov2012
 \param  void
 \return void
*/
void InicTimer0(void){
	//SetPINSEL( 1 , 26 , 3 );			//!< SW13 P1.26 como CAP0.0
	//SetMODE( 1 , 26 , 0 );			//!< Configurar pin mode como pull up para P1.26

	PCONP		|= ALIMENTA_T0;			//!< Habilitar Timer 0
	PCLKSEL0 	|= PCLK_T0;				//!< Clock for timer PCLK = CCLK Selecciono clock 100MHz

	T0PR = 100;	//0,000001 s = 1us
	T0MR0 = 1500000;		//1,5s
	T0MR1 = 1518000;	 	//18ms
//	T0MR2 = 1018050;		//30uS




//	T0PR 		= PREESCALER;			//!< Configura presscaler para generar un pulso para contar por segundo
//	T0MR0 		= MATCH00;				//!< Configuro los pulsos del match 0
	T0MCR 		&= CLR_MTCH_CONFIG;		//!< Pongo en cero los bits de control de match
	T0MCR 		|= MATCH0_INT;			//!< Configuro match 0 para interrumpir
	T0MCR 		|= MATCH1_INT_RST;			//!< Configuro match 1 para interrumpir
//	T0MCR 		|= MATCH2_INT_RST;			//!< Configuro match 2 para interrumpir y resetear timer
//	T0MCR 		|= MATCH3_INT_RST;		//!< Configuro match 3 para interrumpir y resetear timer
//	T0CTCR 		&= TIMER_COUNTER_CLR;	//!< Cuenta pulsos de CAP0.0
	//T0CTCR 		|= COUNTER;				//!< Contador de pulsos falling edge en P1.26
	T0TCR 		&= CLEAR_RST_EN;		//!< Limpio bits de control de reset y encendido del timer
	T0TCR 		|= TIMER_OFFyRST;		//!< Apago y reseteo el temporizador
	T0TCR 		&= TIMER_RST_OFF;		//!< Limpio bit de control de reset
	T0TCR 		|= TIMER_ON;			//!< Enciendo timer
	ISER0 		|= INT_TO_EN;  			//!< Habilito Interrupcion TIMER0
}



void TIMER0_IRQHandler (void)
{

	//Pasaron dos segundos: Entra por match0 Tira abajo la linea hasta el proximo Match
	if(T0IR & MR0)
	{
		SetDIR (DHT11, SALIDA);
//		printf ("MR0: %d\n", T0TC);
	    SetPIN (DHT11, OFF);
		//interrumpio match 0 !!!
		T0IR |= MR0; 					//!< Borro flag del Match 0
	}


	//Pasaron 18ms: Entra por match1 Levanta la linea hasta el proximo match
	if(T0IR & MR1)
	{
//		printf ("MR1: %d\n", T0TC);
		SetPIN (DHT11, ON);
		SetDIR (DHT11, ENTRADA);
		//interrumpio match 0 !!!
		T0IR |= MR1; 					//!< Borro flag del Match 0
	}



}
