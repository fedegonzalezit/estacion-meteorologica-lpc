/*******************************************************************************************************************************//**
 *
 * @file		Driver_display_7segm.c
 * @brief		Módulo que contiene el driver de barrido de display
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_7seg.h"
#include "DR_gpio.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define    dg0       0,19    // DIGITO 6 P0.19 exp 5
#define    dg1       1,20   // DIGITO 5 P1.20 exp 4
#define    dg2       1,23   // DIGITO 4 P1.23 exp 3
#define    dg3       4,28   // DIGITO 3 P4.28 exp 2
#define    dg4       1,29   //DIGITO 2 P1.29 exp1
#define    dg5       2,7    //DIGITO 1 P2.7 exp0


#define    seg_a        3,26 //P3.26 exp6
#define    seg_b        1,18//P1.18 exp15
#define    seg_c        1,21// P1.21 exp14
#define    seg_d        1,24// P1.24 exp13
#define    seg_e        1,27// P1.27 exp12
#define    seg_f        3,25// P3.25  exp11
#define    seg_g        0,20// P0.20  exp10

#define    seg_dp        1,19// P1.19  exp9

#define    DIGITO_0           0
#define    DIGITO_1           1
#define    DIGITO_2           2
#define    DIGITO_3           3
#define    DIGITO_4           4
#define    DIGITO_5           5

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
uint8_t Digito_Display[ N_DIGITOS ];//!< 	Digitos del display

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
 \fn  void BarridoDisplay( void )
 \brief Barrido de Display
 \param void
 \return void
 */
void BarridoDisplay( void )
{
    uint8_t auxiliar;
    static uint8_t    Indice_Display = 0;

    SetPIN (dg0,OFF);//SET_PIN(digito0,OFF);
    SetPIN (dg1,OFF);
    SetPIN (dg2,OFF);
    SetPIN (dg3,OFF);
    SetPIN (dg4,OFF);
    SetPIN (dg5,OFF);

    auxiliar = Digito_Display[Indice_Display];

    SetPIN (seg_a,(auxiliar & (uint8_t)0x01));
    SetPIN (seg_b,(( auxiliar >> 1 ) & (uint8_t)0x01));
    SetPIN (seg_c,(( auxiliar >> 2 ) & (uint8_t)0x01));
    SetPIN (seg_d,(( auxiliar >> 3 ) & (uint8_t)0x01));
    SetPIN (seg_e,(( auxiliar >> 4 ) & (uint8_t)0x01));
    SetPIN (seg_f,(( auxiliar >> 5 ) & (uint8_t)0x01));
    SetPIN (seg_g,(( auxiliar >> 6 ) & (uint8_t)0x01));
    SetPIN (seg_dp,(( auxiliar >> 7 ) & (uint8_t)0x01));

    switch( Indice_Display)
    {
        case DIGITO_0:
        	SetPIN (dg0,ON); break;
        case DIGITO_1:
        	SetPIN (dg1,ON); break;
        case DIGITO_2:
        	SetPIN (dg2,ON); break;
        case DIGITO_3:
        	SetPIN (dg3,ON); break;
        case DIGITO_4:
        	SetPIN (dg4,ON); break;
        case DIGITO_5:
        	SetPIN (dg5,ON); break;
    }


    // Incremento el indice del display
    Indice_Display++;
    Indice_Display %= N_DIGITOS;
}

void Inicializar_Display ( void )
{
	SetDIR ( dg0,SALIDA);
	SetDIR ( dg1,SALIDA);
	SetDIR ( dg2,SALIDA);
	SetDIR ( dg3,SALIDA);
	SetDIR ( dg4,SALIDA);
	SetDIR ( dg5,SALIDA);

	SetDIR ( seg_a,SALIDA);
	SetDIR ( seg_b,SALIDA);
	SetDIR ( seg_c,SALIDA);
	SetDIR ( seg_d,SALIDA);
	SetDIR ( seg_e,SALIDA);
	SetDIR ( seg_f,SALIDA);
	SetDIR ( seg_g,SALIDA);
	SetDIR ( seg_dp,SALIDA);// dp de la placa exp 2
}
