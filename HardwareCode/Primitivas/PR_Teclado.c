/*******************************************************************************************************************************//**
 *
 * @file		PR_Teclado.c
 * @brief		Descripcion del modulo
 * @date		8 de jun. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_Teclado.h"

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
	\fn  uint8_t GetKey ( void )
	\brief Trae del buffer de teclado el codigo de la tecla pulsada
 	\author Ing. Marcelo Trujillo
 	\date 8 de jun. de 2016
 	\param void
	\return Codigo de tecla  o NO_KEY
*/
uint8_t GetKey ( void )
{
	uint8_t aux, p;
	aux = Tecla;
	p = aux;

	if(p==03)
	{
		Tecla = NO_KEY;
	}

	return aux;
}
