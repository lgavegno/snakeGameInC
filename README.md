# Snake Game en C (Consola)

Este es un juego clásico de **Snake** implementado en C para consola. Está diseñado para ejecutarse en sistemas Windows usando la biblioteca `<windows.h>`, y permite guardar los puntajes máximos en un archivo local.

## 🎮 Cómo jugar

- Usa las siguientes teclas para controlar la serpiente:
  - `W`: mover hacia arriba
  - `S`: mover hacia abajo
  - `A`: mover a la izquierda
  - `D`: mover a la derecha
- El objetivo es comer la manzana (`A`) sin chocar contra los bordes o contigo mismo.
- Cada manzana te da **100 puntos**.
- Tienes **3 vidas** por partida.

## 🧱 Características

- Juego de consola con interfaz básica tipo ASCII
- Control de velocidad de juego
- Sistema de puntuación y ranking (guardado en `scores.txt`)
- Soporte para múltiples jugadores
- Gestión de vidas y reinicio tras choque
- Interfaz de menú con 3 opciones:
  1. Iniciar juego
  2. Ver ranking de puntajes
  3. Salir

## 📂 Estructura del proyecto

- `main.c`: código fuente principal
- `scores.txt`: archivo donde se almacenan los puntajes
- `snake.cbp`: archivo del proyecto Code::Blocks
- `snake.layout`: configuración del IDE

## 🛠️ Requisitos

- Sistema operativo: **Windows**
- Compilador: **GCC** (MinGW o Code::Blocks recomendado)
- Librerías utilizadas:
  - `stdio.h`
  - `stdlib.h`
  - `conio.h`
  - `time.h`
  - `windows.h`
  - `string.h`

## 🧪 Compilación

Si usas **Code::Blocks**:
1. Abre `snake.cbp`
2. Compila y ejecuta con F9

Si usas terminal:
```bash
gcc main.c -o snake.exe
snake.exe
````

## 📈 Puntajes

Los puntajes se guardan automáticamente en `scores.txt` al finalizar la partida. Si el jugador ya existe, su puntaje se actualiza solo si mejora el anterior.

## 📸 Captura (simulada)

```
########################################
#                                      #
#                                      #
#              OOOA                    #
#                                      #
#                                      #
#                                      #
########################################
Puntos: 500
Vidas Restantes: 2
```

## 📌 Notas

* El juego se ejecuta solo en Windows debido al uso de `windows.h` y `_getch()`.
* El archivo `scores.txt` se genera automáticamente si no existe.

---

Desarrollado por Leandro Gavegno


