/*******************************************************************************************************************************//**
 *
 * @file		PuertaCorrediza.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		13 de abr. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef PUERTACORREDIZA_H_
#define PUERTACORREDIZA_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_gpio.h"
#include "Infotronic.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	O1_OFF				SetPIN( RELAY1 , OFF )
#define 	O1_ON				SetPIN( RELAY1 , ON )
#define 	O2_OFF				SetPIN( RELAY2 , OFF )
#define 	O2_ON				SetPIN( RELAY2 , ON )
#define 	O3_OFF				SetPIN( RELAY3 , OFF )
#define 	O3_ON				SetPIN( RELAY3 , ON )
#define 	O4_OFF				SetPIN( RELAY4 , OFF )
#define 	O4_ON				SetPIN( RELAY4 , ON )


//Encendido y apagado de leds de la expansion para el ejercicio del parcial
#define 	EXP1_OFF				SetPIN( 2, 7 , OFF )
#define 	EXP1_ON				SetPIN( 2, 7 , ON )
#define 	EXP2_OFF				SetPIN( 1, 29 , OFF )
#define 	EXP2_ON				SetPIN( 1, 29 , ON )
#define 	EXP3_OFF				SetPIN( 4, 28 , OFF )
#define 	EXP3_ON				SetPIN( 4, 28 , ON )

#define 	T0					PrgTimer[0]
#define 	T1					PrgTimer[1]
#define 	T2					PrgTimer[2]
#define 	T3					PrgTimer[3]
#define 	T4					PrgTimer[4]
#define 	T5					PrgTimer[5]
#define 	T6					PrgTimer[6]
#define 	T7					PrgTimer[7]
#define 	T8					PrgTimer[8]

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define 	TRUE  		1
#define 	FALSE  		0

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint32_t	PrgTimer[];
extern uint16_t Tiempos[];

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

#endif /* PUERTACORREDIZA_H_ */
