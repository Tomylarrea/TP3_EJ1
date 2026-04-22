/*
 * controlador.h
 *
 *  Created on: 22 abr 2026
 *      Author: tomyl
 */

#ifndef INC_CONTROLADOR_H_
#define INC_CONTROLADOR_H_

#include <stdint.h>

extern uint8_t BI;



/* States */
typedef enum {
    ESTADO_CONT_CERRADO,
    ESTADO_CONT_ABIERTO,
    ESTADO_CONT_ABRIENDO,
    ESTADO_CONT_CERRANDO,
    ESTADO_CONT_REPOSO_INT
} estado_controlador;

/* Events */
typedef enum {
	EVENTO_CONT_BC,
    EVENTO_CONT_TICK
} evento_controlador;

estado_controlador CONT_evento(estado_controlador current, evento_controlador event);
estado_controlador CONT_iniciar(void);

#endif /* INC_CONTROLADOR_H_ */
