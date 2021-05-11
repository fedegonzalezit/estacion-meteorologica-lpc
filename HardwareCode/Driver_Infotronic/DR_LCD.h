/*
 * DR_LCD.h
 *
 *  Created on: 29 de oct. de 2016
 *      Author: fede
 */
#include "Inicializacion.h"

#ifndef DRIVER_INFOTRONIC_DR_LCD_H_
#define DRIVER_INFOTRONIC_DR_LCD_H_

#define		LCD_D4			0,5		//PORT0.5
#define		LCD_D5			0,10	//PORT0.10
#define		LCD_D6			2,4		//PORT2.4
#define		LCD_D7			2,5		//PORT2.5
#define		LCD_RS			2,6		//PORT2.6
#define		LCD_BF			1,28	//PORT1.28
#define		LCD_E			0,4		//PORT0.4

#define		LCD_E_OFF				SetPIN (LCD_E , 0)
#define		LCD_E_ON				SetPIN (LCD_E , 1)
#define		LCD_RS_OFF				SetPIN (LCD_RS , 0)
#define		LCD_RS_ON				SetPIN (LCD_RS , 1)
#define		LCD_DATO(d4,d5,d6,d7)	SetPIN (LCD_D4 , d4);SetPIN(LCD_D5, d5);SetPIN(LCD_D6  ,d6);SetPIN(LCD_D7, d7)

#define		LCD_CONTROL		1
#define		LCD_DATA		0


void Inicializar_LCD (void);
void Dato_LCD ( unsigned char data , unsigned char control );

#endif /* DRIVER_INFOTRONIC_DR_LCD_H_ */
