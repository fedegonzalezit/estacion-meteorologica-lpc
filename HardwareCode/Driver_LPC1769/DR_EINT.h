/*******************************************************************************************************************************//**
 *
 * @file		DR_EINT.c
 * @brief		Interrupciones externas
 * @date		Fecha de creacion del archivo 09-06-16
 * @author		Marcelo, Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_EINT_H_
#define DR_EINT_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_pinsel.h"
#include "DR_Sensores.h"
#include "DR_timer0123.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
//0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( ( uint32_t * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (  uint32_t * ) 0xE000E180UL )


//Registros ISER: Para habilitar las Interupciones Se activan con 1 Escribiendo un 0 no hace nada
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]
#define		ISE_EINT3	ISER[0] |= (0x00000001 << 21)  //ISER0->bit21 pongo un 1 en el bit 21 para habilitar la INT EINT3
#define     ISE_EINT2	ISER[0] |= (0x00000001 << 20)  //ISER0->bit20 pongo un 1 en el bit 20 para habilitar la INT EINT2
#define     ISE_EINT1	ISER[0] |= (0x00000001 << 19)  //ISER0->bit19 pongo un 1 en el bit 19 para habilitar la INT EINT1
#define     ISE_EINT0	ISER[0] |= (0x00000001 << 18)  //ISER0->bit18 pongo un 1 en el bit 18 para habilitar la INT EINT1
#define		ISE_ADC		ISER[0] |= (0x00000001 << 22)
#define		ISE_I2C1	ISER[0] |= (0x00000001 << 11)

// Registro EXTMODE : Para seleccionar si la ISR Externa activa por flanco ó nivel
#define		EXTMODE 		( (uint32_t  * ) 0x400FC148 )
#define		EXTMODE3_F		EXTMODE[0] |= 0x00000001 << 3  // EINT3 por flanco
#define		EXTMODE2_F		EXTMODE[0] |= 0x00000001 << 2  // EINT2 por flanco
#define		EXTMODE1_F		EXTMODE[0] |= 0x00000001 << 1  // EINT1 por flanco
#define		EXTMODE0_F		EXTMODE[0] |= 0x00000001       // EINT0 por flanco

// Registro EXTPOLAR : selecciona Polaridad del EXTMODE
#define    EXTPOLAR        ( (uint32_t  * ) 0x400FC14C )
#define    EXTPOLAR3_P      EXTPOLAR[0] |= 0X00000001 << 3 // Flanco ó Nivel Positivo
#define    EXTPOLAR2_P      EXTPOLAR[0] |= 0X00000001 << 2 // Flanco ó Nivel Positivo
#define    EXTPOLAR1_P      EXTPOLAR[0] |= 0X00000001 << 1 // Flanco ó Nivel Positivo
#define    EXTPOLAR0_P      EXTPOLAR[0] |= 0X00000001      // Flanco ó Nivel Positivo


//Registros ICER: Para deshabilitar las Interupciones Se desactivan con 1 Escribiendo un 0 no hace nada
//Registros ICER:

#define		ICER0		ICER[0]
#define		ICER1		ICER[1]
#define		ICE_EINT3	ICER0 |= (0x00000001 << 21) // deshabilito a EINT3
#define		ICE_EINT2	ICER0 |= (0x00000001 << 20) // deshabilito a EINT2
#define		ICE_EINT1	ICER0 |= (0x00000001 << 19) // deshabilito a EINT1
#define		ICE_EINT0	ICER0 |= (0x00000001 << 18) // deshabilito a EINT0
#define		ICE_ADC		ICER0 |= (0x00000001 << 22)


#define		EXTINT 		( (uint32_t  * ) 0x400FC140UL ) // Reg de Flags para limpiar la ISR

#define		CLR_EINT3		EXTINT[0] |= 0x00000001 << 3 // bajo el flag de EINT3
#define		CLR_EINT2		EXTINT[0] |= 0x00000001 << 2 // bajo el flag de EINT2
#define		CLR_EINT1		EXTINT[0] |= 0x00000001 << 1 // bajo el flag de EINT1
#define		CLR_EINT0		EXTINT[0] |= 0x00000001      // bajo el flag de EINT0


//Registros de control de interrupciones por GPIO
#define		INTGPIO		( ( uint32_t * ) 0x40028090 )

#define		IO0IntEnR		INTGPIO[0]		// Habilita interrupción puerto0 por flanco ascendente
#define		IO0IntEnF		INTGPIO[1]		// Habilita interrupción puerto0 por flanco descendente
#define		IO2IntEnR		INTGPIO[8]		// Habilita interrupción puerto2 por flanco ascendente
#define		IO2IntEnF		INTGPIO[9]		// Habilita interrupción puerto2 por flanco descendente

//Registros de status de interrupciones por GPIO
#define		INTSTATUS		( ( uint32_t * ) 0x40028080 )


#define		IOIntStatus		INTSTATUS [0]		// Estado de interrupción
#define		IO0IntStatR		INTSTATUS [1]		// Estado interrupción por flanco ascendente
#define		IO0IntStatF		INTSTATUS [2]		// Estado interrupción por flanco descendente
#define		IO0IntClear		INTSTATUS [3]		// Limpiar interrupción


#define		IO2IntStatR		INTSTATUS [9]		// Estado interrupción por flanco ascendente
#define		IO2IntStatF		INTSTATUS [10]		// Estado interrupción por flanco descendente
#define		IO2IntClr		INTSTATUS [11]		// Limpiar interrupción




/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint32_t ContadorTimer0;
/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void EXT0_Inicializacion( void );
void Emergency_STOP (void);

#endif /* DR_EINT_H_ */
