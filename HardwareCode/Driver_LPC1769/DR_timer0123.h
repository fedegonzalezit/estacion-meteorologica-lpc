/*******************************************************************************************************************************//**
 *
 * @file		DR_timer0123.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 de jul. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DR_TIMER0123_H_
#define DR_TIMER0123_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//!<-----------------------------------------------------------------------------
//!<Timers
//!<-----------------------------------------------------------------------------
//!< Timer 0
#define		TIMER0 		( ( __RW uint32_t  * ) 0x40004000 )
#define		T0IR		TIMER0[0]
#define		T0TCR		TIMER0[1]
#define		T0TC		TIMER0[2]
#define		T0PR		TIMER0[3]
#define		T0PC		TIMER0[4]
#define		T0MCR		TIMER0[5]
#define		T0MR0		TIMER0[6]
#define		T0MR1		TIMER0[7]
#define		T0MR2		TIMER0[8]
#define		T0MR3		TIMER0[9]
#define		T0CCR		TIMER0[10]
#define		T0CR0		TIMER0[11]
#define		T0CR1		TIMER0[12]

#define		_T0EMR	( ( __RW uint32_t  * ) 0x4000403CUL )
#define		T0EMR	_T0EMR[0]

#define		_T0CTCR	( ( __RW uint32_t  * ) 0x40004070UL )
#define		T0CTCR	_T0CTCR[0]

//!< Timer 1
#define		TIMER1 		( ( __RW uint32_t  * ) 0x40008000UL )
#define		T1IR		TIMER1[0]
#define		T1TCR		TIMER1[1]
#define		T1TC		TIMER1[2]
#define		T1PR		TIMER1[3]
#define		T1PC		TIMER1[4]
#define		T1MCR		TIMER1[5]
#define		T1MR0		TIMER1[6]
#define		T1MR1		TIMER1[7]
#define		T1MR2		TIMER1[8]
#define		T1MR3		TIMER1[9]
#define		T1CCR		TIMER1[10]
#define		T1CR0		TIMER1[11]
#define		T1CR1		TIMER1[12]

#define		_T1EMR	( ( __RW uint32_t  * ) 0x4000803CUL )
#define		T1EMR	_T1EMR[0]

#define		_T1CTCR	( ( __RW uint32_t  * ) 0x40008070UL )
#define		T1CTCR	_T1CTCR[0]

//!< Timer 2
#define		TIMER2 		( ( __RW uint32_t  * ) 0x40090000UL )
#define		T2IR		TIMER2[0]
#define		T2TCR		TIMER2[1]
#define		T2TC		TIMER2[2]
#define		T2PR		TIMER2[3]
#define		T2PC		TIMER2[4]
#define		T2MCR		TIMER2[5]
#define		T2MR0		TIMER2[6]
#define		T2MR1		TIMER2[7]
#define		T2MR2		TIMER2[8]
#define		T2MR3		TIMER2[9]
#define		T2CCR		TIMER2[10]
#define		T2CR0		TIMER2[11]
#define		T2CR1		TIMER2[12]

#define		_T2EMR	( ( __RW uint32_t  * ) 0x4009003CUL )
#define		T2EMR	_T2EMR[0]

#define		_T2CTCR	( ( __RW uint32_t  * ) 0x40090070UL )
#define		T2CTCR	_T2CTCR[0]

//!< Timer 3
#define		TIMER3 		( ( __RW uint32_t  * ) 0x40094000UL )
#define		T3IR		TIMER3[0]
#define		T3TCR		TIMER3[1]
#define		T3TC		TIMER3[2]
#define		T3PR		TIMER3[3]
#define		T3PC		TIMER3[4]
#define		T3MCR		TIMER3[5]
#define		T3MR0		TIMER3[6]
#define		T3MR1		TIMER3[7]
#define		T3MR2		TIMER3[8]
#define		T3MR3		TIMER3[9]
#define		T3CCR		TIMER3[10]
#define		T3CR0		TIMER3[11]
#define		T3CR1		TIMER3[12]

#define		_T3EMR	( ( __RW uint32_t  * ) 0x4009403CUL )
#define		T3EMR	_T3EMR[0]

#define		_T3CTCR	( ( __RW uint32_t  * ) 0x40094070UL )
#define		T3CTCR	_T3CTCR[0]

#define ALIMENTA_T0			0x00000002
#define ALIMENTA_T1			0x00000004
#define PCLK_T0				0x00000004
#define PCLK_T1				~(0x00000030)
#define PREESCALER			0x00
#define TIMER_CAPT0			0xFFFFFFF0
#define RESET_CAPT0			0xFFFFFFF8
#define CAPT0_INT_FE		0x00000006
#define INT_TO_EN			0x00000002
#define CLEAR_RST_EN		0xFFFFFFFC
#define TIMER_OFFyRST		0x00000002
#define TIMER_RST_OFF		0xFFFFFFFD
#define TIMER_ON			0x00000001
#define MATCH00				450000
#define MATCH01				6
#define TIMER				0xFFFFFFFC
#define TIMER_COUNTER_CLR	0xFFFFFFF0
#define COUNTER				0x00000002

#define CLR_MTCH_CONFIG		0xFFFFF000
#define MATCH0_INT			0x00000001
#define MATCH0_INT_RST		0x00000003
#define MATCH1_INT			0x00000008
#define MATCH1_INT_RST		0x00000018
#define MATCH2_INT			0x00000040
#define MATCH2_INT_RST		0x000000C0
#define MATCH3_INT			0x00000200
#define MATCH3_INT_RST		0x00000600


#define MR0					0x01
#define MR1					0x02
#define MR2					0x04
#define MR3					0x08
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
void InicTimer0(void);

#endif /* DR_TIMER0123_H_ */
