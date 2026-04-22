/*
 * simulador.h
 *
 *  Created on: 19 abr 2026
 *      Author: tomyl
 */

#ifndef INC_SIMULADOR_H_
#define INC_SIMULADOR_H_

#include <stdint.h>

extern uint8_t M1; // Botón para abrir
extern uint8_t M2; // Botón para cerrar
extern uint8_t FC2, FC1;
extern uint16_t t;

/* States */
typedef enum {
    STATE_ABRIENDO,
    STATE_CERRANDO,
    STATE_ABIERTO,
    STATE_CERRADO,
    STATE_REPOSO_INT
} Estado_simulador;

/* Events */
typedef enum {
    EVENT_TICK
} FSMEvent;

Estado_simulador simulador_porton(Estado_simulador current, FSMEvent event);
Estado_simulador iniciar_porton(void);

#endif /* INC_SIMULADOR_H_ */
