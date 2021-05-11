/*******************************************************************************************************************************//**
 *
 * @file		AP_Estacion.h
 * @brief		Macros, tipos , prototipos de la aplicacion
 * @date		2016
 * @author		Gonzalez Itzik, Sivilotti
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef APLICACION_AP_ESTACION_H_
#define APLICACION_AP_ESTACION_H_


#include "Inicializacion.h"

#define		ACTUALIZADA			1
#define		INICIO				0x00
#define		FECHA1				0x06
#define		FECHA2				0x01
#define		CARGAR_FECHA		0x02
#define		ENVIAR_MEMO			0x03
#define		FREC1				0x04
#define		ENVIAR_MEMORIA		0x04
#define		ENVIAR_MEMORIA_2	0x05
#define		LEER_FREC			0x05
#define		SET_FREC			0x07

typedef struct Dates
{
	uint8_t dia;
	uint8_t mes;
	uint16_t anio;
	uint8_t hora;
	uint8_t min;
	uint8_t seg;
}Date;
extern uint16_t final;
extern char BufferMemoria[64];

void rellenar_fecha (void);
void RecibiendoDatos(void);
void PedirFecha (void);
void maquina_estado (void);
void Seleccion_Teclas (void);
void Fecha_AutoIncremento (void);
void Inicializar_Fecha (void);
void get_fecha(void);
void get_hora(void);
void get_temperatura(void);
void get_humedad(void);
void get_presion(void);

#endif /* APLICACION_AP_ESTACION_H_ */
