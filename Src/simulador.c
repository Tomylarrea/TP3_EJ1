/*
 * simulador.c
 *
 *  Created on: 19 abr 2026
 *      Author: tomyl
 */


#include <simulador.h>
#include "main.h"
#include <stdint.h>
uint16_t t = 0;
uint8_t FC1 = 0;
uint8_t FC2 = 0;



/* Process event and execute actions */
Estado_simulador simulador_porton(Estado_simulador current, FSMEvent event) {
    Estado_simulador next = current;
    switch (current) {
        case STATE_ABRIENDO:
            if (event == EVENT_TICK && (t >= 400)) {
                next = STATE_ABIERTO;
                break;
            }
            if (event == EVENT_TICK && (M1 == 0)) {
                next = STATE_REPOSO_INT;
                break;
            }
            if (event == EVENT_TICK && (t <= 399 && M1 == 1)) {
                t = t +1;
                next = STATE_ABRIENDO;
                break;
            }
            break;
        case STATE_CERRANDO:
            if (event == EVENT_TICK && (M2 == 0)) {
                next = STATE_REPOSO_INT;
                break;
            }
            if (event == EVENT_TICK && (t == 0)) {
                next = STATE_CERRADO;
                break;
            }
            if (event == EVENT_TICK && (t > 0 && M2 == 1)) {
                t = t - 1;
                next = STATE_CERRANDO;
                break;
            }
            break;
        case STATE_ABIERTO:
            if (event == EVENT_TICK && (M2 == 1 && M1 == 0)) {
                FC1 = 0;
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
                next = STATE_CERRANDO;
                break;
            }
            break;
        case STATE_CERRADO:
            if (event == EVENT_TICK && (M1 == 1)) {
                FC2 = 0;
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
                next = STATE_ABRIENDO;
                break;
            }
            break;
        case STATE_REPOSO_INT:
            if (event == EVENT_TICK && (M2 == 1 && M1 == 0)) {
                next = STATE_CERRANDO;
                break;
            }
            if (event == EVENT_TICK && (M1 == 1)) {
                next = STATE_ABRIENDO;
                break;
            }
            break;
        default: break;
    }

    if (next != current) {
        switch (next) {
            case STATE_ABIERTO:
                FC1 = 1;
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
                break;
            case STATE_CERRADO:
                FC2 = 1;
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
                break;
            default: break;
        }
    }
    return next;
}

/* Initialize FSM */
Estado_simulador iniciar_porton(void) {
    Estado_simulador initial = STATE_CERRADO;
    t = 0;
    FC2 = 1;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    FC1 = 0;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    return initial;
}
