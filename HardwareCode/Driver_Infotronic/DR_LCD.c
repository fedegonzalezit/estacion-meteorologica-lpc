/*******************************************************************************************************************************//**
 *
 * @file		DR_LCD.c
 * @brief		Driver del display LCD
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

#include "DR_LCD.h"

void Inicializar_LCD (void)
{
	unsigned int i,j;
	SetPINSEL ( LCD_D4 , FUNCION_GPIO);
	SetPINSEL ( LCD_D5 , FUNCION_GPIO);
	SetPINSEL ( LCD_D6 , FUNCION_GPIO);
	SetPINSEL ( LCD_D7 , FUNCION_GPIO);
	SetPINSEL ( LCD_RS , FUNCION_GPIO);
	SetPINSEL ( LCD_BF , FUNCION_GPIO);
	SetPINSEL ( LCD_E  , FUNCION_GPIO);

	SetDIR ( LCD_D4 , SALIDA);
	SetDIR ( LCD_D5 , SALIDA);
	SetDIR ( LCD_D6 , SALIDA);
	SetDIR ( LCD_D7 , SALIDA);
	SetDIR ( LCD_RS , SALIDA);
	SetDIR ( LCD_BF , ENTRADA);
	SetDIR ( LCD_E  , SALIDA);

	// Inicializacion del LCD => en D7-D4; envio comando (RS=0), 0x3 tres veces c/demora

	for( i = 0 ; i < 3 ; i++ )
	{
		LCD_E_OFF;
		for ( j = 0 ; j < 500000 ; j++ );       //300000
		LCD_DATO(1,1,0,0);

		LCD_RS_OFF;
		LCD_E_ON;

		for( j = 0 ; j < 10000 ; j++ );          //4500

		LCD_E_OFF;
	}

	LCD_E_OFF;

	//envio comando (RS=0), 0x2 una vez c/demora

	for ( j = 0 ; j < 500000 ; j++ );           // 300000

	LCD_DATO(0,1,0,0);

	LCD_RS_OFF;
	LCD_E_ON;

	for( j = 0 ; j < 10000 ; j++ );             //4500

	LCD_E_OFF;

	// A partir de aca pasa a 4 bits
	Dato_LCD( 0x28 , LCD_CONTROL );
	Dato_LCD( 0x08 , LCD_CONTROL);	// display OFF
	Dato_LCD( 0x01 , LCD_CONTROL);	// clear display
	for( j = 0 ; j < 10000 ; j++ );	//delay por la instruccion clear display
	Dato_LCD( 0x06 , LCD_CONTROL);	// programo el LCD para mis necesidades
	Dato_LCD( 0x0C , LCD_CONTROL);	// display ON,sin cursor y blinking OFF del cursor

}

void Dato_LCD ( unsigned char data , unsigned char control )        // envio parte alta y luego parte baja
{
	int q , i = 1;
	int data_d4,data_d5,data_d6,data_d7;

	do
	{
		data_d4 = ( data >> ( 0 + i * 4 ) ) & 0x01 ;
		data_d5 = ( data >> ( 1 + i * 4 ) ) & 0x01 ;
		data_d6 = ( data >> ( 2 + i * 4 ) ) & 0x01 ;
		data_d7 = ( data >> ( 3 + i * 4 ) ) & 0x01 ;

		LCD_DATO(data_d4,data_d5,data_d6,data_d7);

		if( control == LCD_CONTROL )
			LCD_RS_OFF;
		else
			LCD_RS_ON;

		LCD_E_ON;
		for( q = 0 ; q < 400 ; q++ );
		LCD_E_OFF;
		for( q = 0 ; q < 14000 ; q++ );
	}
	while ( i-- );
}

