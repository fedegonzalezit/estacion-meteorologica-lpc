/*******************************************************************************************************************************//**
 *
 * @file		DR_SysTick.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		4 de may. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DR_SYSTICK_H_
#define DR_SYSTICK_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_Sensores.h"
#include "AP_Estacion.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		SEGUNDO		400
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
//!< 0xE000E010UL: Registro de control del SysTick:
#define 	SYSTICK		( (systick_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK->_STCTRL

	#define	ENABLE			SYSTICK->bits._ENABLE
	#define	TICKINT			SYSTICK->bits._TICKINT
	#define	CLKSOURCE		SYSTICK->bits._CLKSOURCE
	#define	COUNTFLAG		SYSTICK->bits._COUNTFLAG

#define		STRELOAD	SYSTICK->_STRELOAD
#define		STCURR		SYSTICK->_STCURR
#define		STCALIB		SYSTICK->_STCALIB

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
//!< /////////////		SYSTICK		///////////////////////////
//!< Tipo de dato específico para manejar el SYSTICK
typedef struct
{
	union{
		__RW uint32_t _STCTRL;
		struct{
			__RW uint32_t _ENABLE:1;
			__RW uint32_t _TICKINT:1;
			__RW uint32_t _CLKSOURCE:1;
			__RW uint32_t _RESERVED0:13;
			__RW uint32_t _COUNTFLAG:1;
			__RW uint32_t _RESERVED1:15;
		}bits;
	};
	__RW uint32_t _STRELOAD;
	__RW uint32_t _STCURR;
	__R uint32_t  _STCALIB;
}systick_t;



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint8_t Flag_T;
extern uint8_t Flag_Espera;
extern uint16_t tiempo;
extern uint32_t espera_parametros;
extern uint8_t Flag_timeout;
extern uint8_t timer_timeout;
extern uint8_t Flag_memoria;
/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void SysTick_Inicializacion ( void );

#endif /* DR_SYSTICK_H_ */
