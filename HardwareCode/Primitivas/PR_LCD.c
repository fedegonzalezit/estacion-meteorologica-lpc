/*******************************************************************************************************************************//**
 *
 * @file		PR_LCD.c
 * @brief		Funcion para mostrar por el LCD un mensaje
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

#include "PR_LCD.h"


/**
 \fn		 void Display_lcd( char *msg , char renglon , char posicion )
 \brief 	 Muestra un mensaje en el display LCD
 \param 	 msg:		mensaje a mostrar en el display
 \param 	 renglon:	renglon en el que se va a mostrar el mensaje
 \param 	 posicion:	posicion en el renglon
 \return 	 Posicion final.
 */

void Display_lcd( char *msg , char renglon , char posicion )
{
	unsigned char i ;

	if( renglon )
        posicion = posicion + 0xc0 ;
	else
		posicion = posicion + 0x80 ;

	Dato_LCD( posicion , LCD_CONTROL );                 //comando de posicion e incremento del cursor
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		Dato_LCD( msg[ i ] , LCD_DATA );

}
