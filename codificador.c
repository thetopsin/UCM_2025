#include <stdio.h>
#include <string.h>

#define MAX 200
#define ALFABETOLEN 47

void inicializa_alfabeto(char *);
int buscar_posicion(char , char *);
void lee_original(char *, int *);
void primera_etapa(char *, char *, int, char *);
void codificar(char *, char *, char *, int);
void graba_mensaje(char *, int);

int main() {
    char alfabeto[ALFABETOLEN];
    char mensaje[MAX];
    char codificado[MAX];
    int N;

    inicializa_alfabeto(alfabeto);
    lee_original(mensaje, &N);
    codificar(mensaje, codificado, alfabeto, N);
    graba_mensaje(codificado, N);

    return 0;
}

void inicializa_alfabeto(char *alfabeto) {
    const char caracteres[] = {
        'A','B','C','D','E','F','G','H','I','J','K','L',
        'M','N','O','P','Q','R','S','T','U','V','W','X',
        'Y','Z',' ','0','1','2','3','4','5','6','7','8','9',
        '!',',','.',':',';','?','-','+','*','/'
    };
    memcpy(alfabeto, caracteres, ALFABETOLEN);
}

int buscar_posicion(char c, char *alfabeto) {
    int i;
    for (i = 0; i < ALFABETOLEN; i++) {
        if (alfabeto[i] == c) {
            return i;
        }
    }
    return -1;
}

void lee_original(char *mensaje, int *N) {
    FILE *in = fopen("original.txt", "r");
    if (!in) return;

    fscanf(in, "%d#", N);
    fgets(mensaje, MAX, in);
    mensaje[strcspn(mensaje, "\n")] = '\0';

    fclose(in);
}

void primera_etapa(char *mensaje, char *etapa1, int N, char *alfabeto) {
    int i, pos, nueva_pos;
    for (i = 0; mensaje[i] != '\0'; i++) {
        pos = buscar_posicion(mensaje[i], alfabeto);
        if (pos != -1) {
            nueva_pos = (pos - N + ALFABETOLEN) % ALFABETOLEN;
            etapa1[i] = alfabeto[nueva_pos];
        } else {
            etapa1[i] = mensaje[i];
        }
    }
    etapa1[i] = '\0';
}

/*void segunda_etapa(char *etapa1, char *codificado, int N, char *alfabeto) {
    int i, pos, nueva_pos;
    for (i = 0; etapa1[i] != '\0'; i++) {
        if (i % 2 == 0) {
            pos = buscar_posicion(etapa1[i], alfabeto);
            if (pos != -1) {
                nueva_pos = (pos - N + ALFABETOLEN) % ALFABETOLEN;
                codificado[i] = alfabeto[nueva_pos];
            } else {
                codificado[i] = etapa1[i];
            }
        } else {
            codificado[i] = etapa1[i];
        }
    }
    codificado[i] = '\0';
}*/

void codificar(char *mensaje, char *codificado, char *alfabeto, int N) {
    char etapa1[MAX];
    primera_etapa(mensaje, codificado, N, alfabeto);
    /*segunda_etapa(etapa1, codificado, N, alfabeto);*/
}

void graba_mensaje(char *codificado, int N) {
    FILE *out = fopen("codificado.txt", "w");
    if (!out) return;

    fprintf(out, "%d#%s\n", N, codificado);

    fclose(out);
}