#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define WIDTH 40
#define HEIGHT 20


typedef struct {
    int x, y;
} Posicion;

typedef struct {
    Posicion pos[100];
    int length;
    char direccion;
} Snake;

typedef struct {
    Posicion pos;
} Manzana;

typedef struct {
    char nombre[50];
    int puntos;
    int vidas;
} Player;

typedef struct {
    char nombre[50];
    int puntos;
} Score;

Snake snake;
Manzana apple;
Player player;
Score scores[100];
int numScores = 0;

void iniciarJuego() {
    snake.length = 1;
    snake.direccion = 'd';
    snake.pos[0].x = WIDTH/2;
    snake.pos[0].y = HEIGHT/2;

    player.puntos = 0;
    player.vidas = 3;

    srand(time(NULL));
    generarManzana();
}
//--------------------------------------------------
void generarManzana() {
    int valido = 0;
    while (!valido) {  // validacion de acierto de manzana
        valido = 1;
        apple.pos.x = rand()%(WIDTH-2)+1;
        apple.pos.y = rand()%(HEIGHT-2)+1;
        for (int i = 0; i < snake.length; i++) {
            if (snake.pos[i].x == apple.pos.x && snake.pos[i].y == apple.pos.y) {
                valido = 0;
                break;
            }
        }
    }
}
//--------------------------------------------------
void dibujarJuego() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y==0 || y==HEIGHT -1 || x==0 || x==WIDTH -1) {
                printf("#");
            } else {
                int isSnake = 0;
                for (int i = 0; i < snake.length; i++) {
                    if (snake.pos[i].x == x && snake.pos[i].y == y) {
                        printf("O");
                        isSnake=1;
                        break;
                    }
                }
                if (!isSnake) {
                    if (apple.pos.x == x && apple.pos.y == y) {
                        printf("A");
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("Puntos: %d\n", player.puntos);
    printf("Vidas Restantes: %d\n", player.vidas);
}
//--------------------------------------------------
void movSnake() {
    for (int i = snake.length-1; i > 0; i--) {
        snake.pos[i] = snake.pos[i-1];
    }

    switch (snake.direccion) {
        case 'a':
            snake.pos[0].x--;
            break;
        case 'd':
            snake.pos[0].x++;
            break;
        case 'w':
            snake.pos[0].y--;
            break;
        case 's':
            snake.pos[0].y++;
            break;
    }
}
//--------------------------------------------------
int verifChoque() {
    if (snake.pos[0].x < 1 || snake.pos[0].x >= WIDTH-1 || snake.pos[0].y < 1 || snake.pos[0].y >= HEIGHT-1) {
        player.vidas--;
        if (player.vidas > 0) {
            snake.length = 1;
            snake.pos[0].x = WIDTH/2;
            snake.pos[0].y = HEIGHT/2;
            return 0;
        } else {
            return 1;
        }
    }

    for (int i = 1; i < snake.length; i++) {
        if (snake.pos[0].x == snake.pos[i].x && snake.pos[0].y == snake.pos[i].y) {
            player.vidas--;
            if (player.vidas > 0) {
                snake.length = 1;
                snake.pos[0].x = WIDTH / 2;
                snake.pos[0].y = HEIGHT / 2;
                return 0;
            } else {
                return 1;
            }
        }
    }
    return 0;
}
//--------------------------------------------------
int comerManzana() {
    if (snake.pos[0].x == apple.pos.x && snake.pos[0].y == apple.pos.y) {
        snake.length++;
        player.puntos += 100;
        generarManzana();
        return 1;
    }
    return 0;
}
//--------------------------------------------------
void mostrarMenu() {
    system("cls");
    printf("************** Indicaciones del juego: **************\n");
       printf("Tecla w : desplazamiento hacia arriba \n");
       printf("Tecla s : desplazamiento hacia abajo \n");
       printf("Tecla d : giro a la derecha \n");
       printf("Tecla a : giro a la izquierda \n");
    printf("*****************************************************\n");

    printf("1. Iniciar Juego\n");
    printf("2. Ver Ranking de Puntajes\n");
    printf("3. Salir\n");
    printf("Seleccione una opcion: ");
}
//--------------------------------------------------
void guardarPuntuacion() {
    FILE *archivo;
    archivo = fopen("scores.txt", "a");  // Abre el archivo en modo añadir

    if (archivo == NULL) {
        printf("Error al abrir el archivo de puntajes.\n");
        return;
    }

    int encontrado = 0;
    for (int i = 0; i < numScores; i++) {
        if (strcmp(scores[i].nombre, player.nombre) == 0) {
            // Si el jugador ya existe, actualiza su puntaje si es mayor
            if (player.puntos > scores[i].puntos) {
                scores[i].puntos = player.puntos;
                encontrado = 1;
            }
        }
    }

    // Si no se encontró al jugador en la lista lo añade
    if (!encontrado) {
        strcpy(scores[numScores].nombre, player.nombre);
        scores[numScores].puntos = player.puntos;
        numScores++;
    }

    // Escribe todos los puntajes en el archivo
    for (int i = 0; i < numScores; i++) {
        fprintf(archivo, "%s %d\n", scores[i].nombre, scores[i].puntos);
    }

    fclose(archivo);
}
//--------------------------------------------------

void cargaPuntos() {
    FILE *archivo;
    archivo = fopen("scores.txt", "r");

    if (archivo == NULL) {
        printf("No hay puntajes guardados.\n");
        return;
    }

    printf("*****   Ranking de Puntajes:   *****\n");
    printf("Nombre\tPuntaje\n");

    while (fscanf(archivo, "%s %d", scores[numScores].nombre, &scores[numScores].puntos) != EOF) {
        printf("%s\t%d\n", scores[numScores].nombre, scores[numScores].puntos);
        numScores++;
    }

    fclose(archivo);
}
//--------------------------------------------------
int main() {
    int option;
    cargaPuntos();  // Carga los puntajes al inicio

    while (1) {
        mostrarMenu();
        option = getch();
        if (option == '1') {
            system("cls");
            printf("Ingrese su nombre: ");
            fgets(player.nombre, sizeof(player.nombre), stdin);
            strtok(player.nombre, "\n");  // Remueve el salto de línea al final
            iniciarJuego();
            int gameOver = 0;
            while (!gameOver) {
                dibujarJuego();
                if (_kbhit()) {
                    char ch = _getch();
                    if ((ch == 'a' || ch == 'A') && (snake.direccion != 'd')){
                        snake.direccion = 'a';
                    }

                    if ((ch == 'd' || ch == 'D') && (snake.direccion != 'a')){
                        snake.direccion = 'd';
                    }

                    if ((ch == 'w' || ch == 'W') && (snake.direccion != 's')){
                        snake.direccion = 'w';
                    }

                    if ((ch == 's' || ch == 'S') && (snake.direccion != 'w')){
                        snake.direccion = 's';
                    }

                }
                movSnake();
                if (verifChoque()) {
                    printf("Game Over! Puntaje: %d\n", player.puntos);
                    gameOver = 1;
                }
                comerManzana();
                Sleep(100); // Controla la velocidad del juego
            }
            guardarPuntuacion();  // Guardar puntaje al finalizar el juego
            printf("Presione cualquier tecla para volver al menu...\n");
            getch();
        } else if (option == '2') {
            system("cls");
            cargaPuntos();
            printf("Presione cualquier tecla para volver al menu...\n");
            getch();
        } else if (option == '3') {
            break;
        }
    }

    return 0;
}
