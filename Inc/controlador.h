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
    ESTADO_SIM_CERRADO,
    ESTADO_SIM_ABIERTO,
    ESTADO_SIM_ABRIENDO,
    ESTADO_SIM_CERRANDO,
    ESTADO_SIM_REPOSO_INT
} estado_controlador;

/* Events */
typedef enum {
    EVENTO_SIM_BOTON_M1,
    EVENTO_SIM_BOTON_M2,
    EVENTO_SIM_TICK
} evento_controlador;

estado_controlador SIM_evento(estado_controlador current, evento_controlador event);
estado_controlador SIM_iniciar(void);

#endif /* INC_CONTROLADOR_H_ */
