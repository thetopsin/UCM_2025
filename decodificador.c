#include <stdio.h>
#include <string.h>

// Alfabeto original usado para codificar/decodificar
char alfabeto[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '!', ',', '.', ':', ';', '?', '-', '+', '*', '/'
};

int largo_alfabeto = 48;

// Devuelve el índice de un carácter en el alfabeto
int buscar_posicion(char c) {
    int i;
    for (i = 0; i < largo_alfabeto; i++) {
        if (alfabeto[i] == c) {
            return i;
        }
    }
    return -1;
}

int main() {
    FILE *in;
    FILE *out;
    int N;
    char linea[200];
    char primera[200];
    char segunda[200];
    int i;
    int pos, nueva_pos;

    in = fopen("codificado.txt", "r");
    out = fopen("decodificado.txt", "w");

    if (!in || !out) {
        printf("No se pudieron abrir los archivos.\n");
        return 1;
    }

    fscanf(in, "%d#", &N); // lee clave
    fgets(linea, 200, in); // lee mensaje codificado
    linea[strcspn(linea, "\n")] = '\0';

    // Revertir segunda etapa
    for (i = 0; linea[i] != '\0'; i++) {
        if (i % 2 == 0) {
            pos = buscar_posicion(linea[i]);
            nueva_pos = (pos + N) % largo_alfabeto;
            primera[i] = alfabeto[nueva_pos];
        } else {
            primera[i] = linea[i];
        }
        primera[i + 1] = '\0';
    }

    // Revertir primera etapa
    for (i = 0; primera[i] != '\0'; i++) {
        pos = buscar_posicion(primera[i]);
        nueva_pos = (pos + N) % largo_alfabeto;
        segunda[i] = alfabeto[nueva_pos];
        segunda[i + 1] = '\0';
    }

    fprintf(out, "%d#%s\n", N, segunda);

    fclose(in);
    fclose(out);

    return 0;
}
