#include <stdio.h>

#define TAM 5

int main() {
    int lista[TAM] = {10, 20, 30, 40, 50};
    int indice = 0;

    // Simular avanzar circularmente
    for (int i = 0; i < 10; i++) {
        printf("Avanzar: lista[%d] = %d\n", indice, lista[indice]);
        indice = (indice + 1) % TAM; // si pasa el final, vuelve al inicio
    }

    // Ahora simular retroceder circularmente
    indice = 0;
    for (int i = 0; i < 10; i++) {
        printf("Retroceder: lista[%d] = %d\n", indice, lista[indice]);
        indice = (indice - 1 + TAM) % TAM; // si va a -1, vuelve al final
    }

    return 0;
}
