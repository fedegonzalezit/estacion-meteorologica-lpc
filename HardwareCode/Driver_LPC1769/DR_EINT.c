 /*******************************************************************************************************************************//**
 *
 * @file		DR_EINT.c
 * @brief		Interrupciones externas
 * @date		Fecha de creacion del archivo 09-06-16
 * @author		Marcelo, Trujillo
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** INCLUDES
  **********************************************************************************************************************************/
#include "DR_EINT.h"
#include "Inicializacion.h"
#include "PR_Timer.h"
#include <stdio.h>

 /***********************************************************************************************************************************
  *** DEFINES PRIVADOS AL MODULO
  **********************************************************************************************************************************/
#define		EINT0_PIN		2,10
 #define    FLAG_EINT3      EXTINT[0] & (0x00000001 << 3)

 /***********************************************************************************************************************************
  *** MACROS PRIVADAS AL MODULO
  **********************************************************************************************************************************/
#define		KEY2			2,13
 /***********************************************************************************************************************************
  *** TIPOS DE DATOS PRIVADOS AL MODULO
  **********************************************************************************************************************************/
volatile uint32_t frecuenciaDHT;
//static uint32_t frecVector[256], i=0;
 /***********************************************************************************************************************************
  *** TABLAS PRIVADAS AL MODULO
  **********************************************************************************************************************************/

 /***********************************************************************************************************************************
  *** VARIABLES GLOBALES PUBLICAS
  **********************************************************************************************************************************/
extern uint8_t fMarcha;

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
 void EXT0_Inicializacion(void)
{


	 // Debo Haber configurado los pines (como GPIO) de las entradas que usaré como GPIO Interrupt

	 // ISR de los GPIO  Se comparte con la EINT3
	// SE puede vincular al mismo tiempo las INTEXT 3 EINT3 y la GPIO

	// SetDIR (DHT11, ENTRADA); // Selecciono el pin p2[8] como entrada

	 IO2IntEnF |= 0x00000001<<8;  // habilito al pin P2[8]para que genere una ISR por flanco negativo
	 IO2IntEnR |= 0x00000001<<8;  // habilito al pin P2[8]para que genere una ISR por flanco positivo




//	 SetPINSEL( EINT0_PIN , PINSEL_FUNC1 ); 	// Configuro el P2[10] (SW1) para que trabaje como EINT0 esto debe hacerse con
//	                                     	 	// la Interr deshabilitada Pag 25
//	 EXTMODE0_F;                         		// Configuro la interrupcion externa 0 por flanco
//                                         	 	// EXTPOLAR0_P; // si quiero por flanco positivo debo cambiarlo en EXTPOLAR
	 ISE_EINT3;                      	 		// Habilito Interrupcion Externa 0
}


void EINT3_IRQHandler(void)
{

	// Interrumple si cambia de estado el pin conectado al DHT y tomo
  	if (IOIntStatus & 0x04) // La interrup vino por algún bit de P2?
       {
  		  //Interrumpe por flanco Ascendente
	  	  if((IO2IntStatR >> 8) & 0x01)// Fue el P2[8] Expansion 16?
	  	  {
	  		  frecuenciaDHT = T0TC;
	  		  IO2IntClr |= 0x00000001<<8; // apago el flag del P2[8]
	  	  }


  		  //Interrumpe por flanco descendente
	  	  if((IO2IntStatF >> 8) & 0x01)// Fue el P2[8] Expansion 16?
	  	  {
	  		  frecuenciaDHT =  T0TC - frecuenciaDHT; //diferencia entre el contador en cada pulso
	  		  LeerBit (frecuenciaDHT); //Envío la frecuencia en us
	  		  IO2IntClr |= 0x00000001<<8; // apago el flag del P2[8]
	  	  }



    }

}

