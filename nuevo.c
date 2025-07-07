#include <stdio.h>
#include <string.h>

#define TAM 100

void lee_original(char *, int *);
void inicializa_alfabeto(char *);
void codificar(char *, char *, char *, int);
void primera_etapa(char *, char *, int, char *);
void segunda_etapa(char *, char *, int, char *);
void graba_mensaje(char *, int);

// Inicializa el alfabeto según el enunciado
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,. :;?-+*/");
}

// Busca la posición de un carácter en el alfabeto
int buscar_posicion(char c, char *alfabeto) {
    for (int i = 0; i < strlen(alfabeto); i++) {
        if (alfabeto[i] == c)
            return i;
    }
    return -1;
}

void lee_original(char *mensaje, int *N) {
    FILE *archivo = fopen("original.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir original.txt\n");
        return;
    }
    fscanf(archivo, "%d#", N);
    fgets(mensaje, TAM, archivo);
    mensaje[strcspn(mensaje, "\n")] = '\0'; // Eliminar salto de línea
    fclose(archivo);
}

void primera_etapa(char *original, char *etapa1, int N, char *alfabeto) {
    int len_alf = strlen(alfabeto);
    for (int i = 0; i < strlen(original); i++) {
        int pos = buscar_posicion(original[i], alfabeto);
        int nueva_pos = (pos - N + len_alf) % len_alf;
        etapa1[i] = alfabeto[nueva_pos];
    }
    etapa1[strlen(original)] = '\0';
}

void segunda_etapa(char *etapa1, char *etapa2, int N, char *alfabeto) {
    int len_alf = strlen(alfabeto);
    for (int i = 0; i < strlen(etapa1); i++) {
        int pos = buscar_posicion(etapa1[i], alfabeto);
        if (i % 2 == 0) { // múltiplo de 2 (0 también cuenta)
            int nueva_pos = (pos - N + len_alf) % len_alf;
            etapa2[i] = alfabeto[nueva_pos];
        } else {
            etapa2[i] = etapa1[i];
        }
    }
    etapa2[strlen(etapa1)] = '\0';
}

void codificar(char *original, char *codificado, char *alfabeto, int N) {
    char etapa1[TAM];
    primera_etapa(original, etapa1, N, alfabeto);
    segunda_etapa(etapa1, codificado, N, alfabeto);
}

void graba_mensaje(char *mensaje_codificado, int N) {
    FILE *archivo = fopen("codificado.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo crear codificado.txt\n");
        return;
    }
    fprintf(archivo, "%d#%s", N, mensaje_codificado);
    fclose(archivo);
}

int main() {
    char original[TAM];
    char alfabeto[TAM];
    char codificado[TAM];
    int N;

    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_mensaje(codificado, N);

    return 0;
}