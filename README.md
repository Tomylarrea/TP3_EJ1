### Ejercicio 1

Crear el firmware de un controlador para un portón automático (como los de cocheras), junto con un simulador de portón para poder probarlo. Es decir, se asemeja a realizar dos proyectos distintos dentro del mismo microcontrolador, implementando dos módulos, cada uno controlado por una máquina de estados.

**El sistema se compone de:**

- Un módulo controlador, que posee cuatro entradas y dos salidas:
  - Un botón único para comandarlo (BC).
  - Un sensor de fin de carrera para la apertura (FC1).
  - Un sensor de fin de carrera para el cierre (FC2).
  - Un haz infrarrojo que detiene el movimiento si es interrumpido (BI).
  - Dos salidas para accionar el motor en uno u otro sentido (M1, M2). El motor se activa por nivel (no por pulso), es decir, se mueve mientras la línea correspondiente esté activa.

- Un módulo simulador de portón, que posee dos entradas y dos salidas:
  - Dos entradas para emular el accionamiento del motor (M1, M2).
  - Dos salidas que emulan los finales de carrera (FC1, FC2).

**El funcionamiento de los módulos respeta los siguientes puntos:**

- **Para el controlador:**
  - Al encender, se leen los sensores de fin de carrera para determinar la posición inicial del portón.
  - Si ninguno está activado, al presionar el botón el portón se cerrará.
  - Si alguno está activado, al presionar el botón el portón se moverá hacia el otro extremo.
  - El movimiento se detiene si se interrumpe el haz infrarrojo, tanto en apertura como en cierre. Para reanudar, el haz debe liberarse y se debe volver a presionar el botón, continuando en el mismo sentido.

- **Para el emulador de portón:**
  - El portón tarda 4 segundos en ir de un fin de carrera al otro.
  - Ambas máquinas de estados se ejecutan cada 10 ms.

**Consignas:**

1. Implementar el módulo de portón como una máquina de estados utilizando pulsadores en M1 y M2, y LEDs para FC1 y FC2. Considerar, si se desea, los estados: ABIERTO, CERRADO, ABRIENDO, CERRANDO, REPOSO_INTERMEDIO.
2. Implementarlo como librería.
3. Implementar el módulo controlador como una máquina de estados, conectado al módulo de portón.
4. Implementarlo como librería.
5. Describir el tipo de arquitectura de firmware utilizada (superloop, foreground/background, time-triggered), fundamentando la elección.
6. Implementar la temporización o alguna de las entradas mediante interrupciones (si no se hizo previamente), evitando problemas de concurrencia con las máquinas de estado y explicando el funcionamiento.
