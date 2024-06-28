//Biblioteca para o pacman

#ifndef LEMES_H
#define LEMES_H

typedef struct Cacador {
    Vector2 position;
    Vector2 direction;
} Cacador;

void ChangeDirection(Cacador *cacador) {
    int randomDirection = GetRandomValue(0, 3);
    switch(randomDirection) {
        case 0: cacador->direction = (Vector2){ 1, 0 }; break;  // Right
        case 1: cacador->direction = (Vector2){ -1, 0 }; break; // Left
        case 2: cacador->direction = (Vector2){ 0, 1 }; break;  // Down
        case 3: cacador->direction = (Vector2){ 0, -1 }; break; // Up
    }
}


#endif