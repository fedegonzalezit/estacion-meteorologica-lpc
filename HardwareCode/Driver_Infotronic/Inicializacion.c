
/*******************************************************************************************************************************//**
 *
 * @file		Inicializacion.c
 * @brief		Inicializaciones del Kit de Info II Infotronic
 * @date		23/03/16
 * @author		Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Inicializacion.h"
#include "Infotronic.h"

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
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
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
 \fn  void Inicializar ( void )
 \brief funcion principal
 \param void
 \return void
 */
void Inicializacion ( void )
{
	//!< Infotronic
	SetDIR( RELAY1 , SALIDA );
	SetDIR( RELAY2 , SALIDA );
	SetDIR( RELAY3 , SALIDA );
	SetDIR( RELAY4 , SALIDA );

	RELAYS_OFF ();

	//SetPIN(RELAY1, ON );

	Inicializar_Fecha ();

	//SetDIR (1, 18, SALIDA); // Selecciono Puerto 1,18 (DHT11MCU) para enviar datos a dht
	//inicializarLeds ();
	InicializarTeclado( );
	//Inicializar_Display ( );
	//inicializarRGB ();


	//!< LPC1769
	InitPLL();					//Configuro en primer lugar el PLL:Estabiliza el oscilador interno del micro en 100MHz
	SysTick_Inicializacion ( );
	UART0_Inicializacion ();
	EXT0_Inicializacion ( );
	Inic_ADC(  );
	InicTimer0( );
	I2C1_Inicializacion( );
	Inicializar_LCD ();
	BMP180_init ( );

}

void RELAYS_OFF (void)
{
	SetPIN ( RELAY1 , OFF );
	SetPIN ( RELAY2 , OFF );
	SetPIN ( RELAY3 , OFF );
}


