# Controlador de Portón Automático con Simulador

## Descripción del sistema

Este proyecto implementa el firmware de un controlador para un portón automático de cochera, junto con un simulador del portón que permite probarlo dentro del mismo microcontrolador (STM32F103C8T6). El sistema está compuesto por dos módulos independientes, cada uno modelado como una máquina de estados finitos (FSM), que se comunican entre sí a través de variables compartidas.

El **módulo simulador** representa el comportamiento físico del portón. Recibe como entradas las señales de motor M1 y M2, y expone como salidas los finales de carrera FC1 (apertura) y FC2 (cierre). El portón tarda 400 ticks en recorrer el trayecto completo entre un extremo y el otro, lo que equivale a 4 segundos con una cadencia de ejecución de 10 ms. Los estados que modela son: `ABRIENDO`, `CERRANDO`, `ABIERTO`, `CERRADO` y `REPOSO_INT`.

El **módulo controlador** implementa la lógica de comando del portón. Recibe como entradas un botón único (BC), los sensores de fin de carrera FC1 y FC2 provistos por el simulador, y un haz infrarrojo de seguridad (BI). Sus salidas son las señales M1 y M2 que alimentan al simulador. Los estados que modela son: `ABRIENDO`, `CERRANDO`, `ABIERTO`, `CERRADO` y `REPOSO_INT`.

El comportamiento del controlador respeta las siguientes reglas: al presionar BC desde el estado cerrado, el portón comienza a abrir; desde el estado abierto, comienza a cerrar. Si el haz infrarrojo se interrumpe durante el movimiento, el portón se detiene en un estado de reposo intermedio, y solo retoma el movimiento en el mismo sentido al liberar el haz y volver a presionar el botón. La posición inicial se determina al encender el sistema leyendo el estado de los finales de carrera.

Ambas FSMs se ejecutan cada 10 ms, sincronizadas por un timer de hardware.

---

## Arquitectura de firmware

La arquitectura utilizada es **Foreground/Background**.

En este esquema, el programa se divide en dos niveles de ejecución. El **background** es el bucle principal (`while(1)` en `main`), que contiene toda la lógica de la aplicación. El **foreground** está compuesto por las rutinas de servicio de interrupción (ISR), que responden a eventos del hardware de forma asincrónica.

En este proyecto, el timer TIM1 se configura para generar una interrupción cada 10 ms. La ISR correspondiente (`HAL_TIM_PeriodElapsedCallback`) únicamente levanta un flag de tipo `volatile uint8_t`. El loop principal verifica ese flag en cada iteración y, cuando está activo, ejecuta la siguiente secuencia: lectura de entradas físicas (BC y BI), procesamiento del controlador, procesamiento del simulador, y bajada del flag.

### Justificación de la elección

Esta arquitectura fue elegida por tres razones principales.

En primer lugar, garantiza una **cadencia temporal predecible**. Ambas FSMs deben ejecutarse cada 10 ms según el enunciado, y el timer de hardware asegura ese período de forma precisa e independiente del tiempo de ejecución del loop.

En segundo lugar, **evita problemas de concurrencia**. La ISR no accede a las variables de estado ni invoca las FSMs directamente; su única responsabilidad es señalizar mediante el flag. Toda la lógica de las FSMs se ejecuta íntegramente en el contexto del background, lo que elimina la posibilidad de condiciones de carrera. El uso de `volatile` en la declaración del flag garantiza que el compilador no optimice su lectura, asegurando la correcta comunicación entre los dos contextos de ejecución.

En tercer lugar, la **complejidad del sistema no justifica una arquitectura más elaborada**. Un esquema time-triggered aportaría estructura adicional para gestionar múltiples tareas con distintos períodos, pero en este caso ambas FSMs comparten la misma cadencia de 10 ms, por lo que un scheduler simple no agrega valor y sí agrega complejidad innecesaria. Un superloop sin interrupciones, por su parte, no garantizaría el período de ejecución ante cualquier variación en el tiempo de procesamiento.

El esquema foreground/background representa, en este contexto, la solución más simple que cumple correctamente con todos los requisitos del sistema.
