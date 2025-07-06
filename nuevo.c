#include <stdio.h>
#include <string.h>

#define MAX 100
#define ALPH_SIZE 47

/* prototipos */
void lee_original(char *orig, int *N);
void inicializa_alfabeto(char *alf);
void codificar(char *orig, char *cod, char *alf, int N);
void primera_etapa(char *orig, char *tmp, int N);
void segunda_etapa(char *tmp, char *cod, int N);
void graba_mensaje(char *cod);

int main(){
    char original[MAX];
    char alfabeto[ALPH_SIZE+1];
    char codificado[MAX];
    int N;

    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_mensaje(codificado);

    return 0;
}

/* lee N y mensaje de original.txt (sin espacios entre # y mensaje) */
void lee_original(char *orig, int *N){
    FILE *f = fopen("original.txt","r");
    if(!f){ perror("original.txt"); return; }
    fscanf(f, "%d#", N);
    fgets(orig, MAX, f);
    orig[strcspn(orig,"\r\n")] = '\0';
    fclose(f);
}

/* arma el alfabeto tal como en el enunciado */
void inicializa_alfabeto(char *alf){
    const char temp[ALPH_SIZE+1] =
     "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
     "0123456789!,.:;?-+*/";
    memcpy(alf, temp, ALPH_SIZE+1);
}

/* invoca a primera y segunda etapa */
void codificar(char *orig, char *cod, char *alf, int N){
    char tmp[MAX];
    primera_etapa(orig, tmp, N);
    segunda_etapa(tmp, cod, N);
}

/* Etapa 1: desplazar -N todos los caracteres */
void primera_etapa(char *orig, char *tmp, int N){
    int L = strlen(orig);
    for(int i=0; i<L; i++){
        /* buscar en alfabeto */
        char *p = strchr(alf, orig[i]);
        int idx = (p ? (int)(p - alf) : -1);
        if(idx>=0)
            tmp[i] = alf[(idx - N + ALPH_SIZE) % ALPH_SIZE];
        else
            tmp[i] = orig[i];
    }
    tmp[L] = '\0';
}

/* Etapa 2: sobre la salida de primera, desplazar -N sólo en posiciones múltiplo de 2 (0 incluido) */
void segunda_etapa(char *tmp, char *cod, int N){
    int L = strlen(tmp);
    for(int i=0; i<L; i++){
        if(i % 2 == 0){
            char *p = strchr(alfabeto, tmp[i]);
            int idx = (p ? (int)(p - alfabeto) : -1);
            if(idx>=0)
                cod[i] = alfabeto[(idx - N + ALPH_SIZE) % ALPH_SIZE];
            else
                cod[i] = tmp[i];
        } else {
            cod[i] = tmp[i];
        }
    }
    cod[L] = '\0';
}

/* graba en codificado.txt con formato N#CODIFICADO */
void graba_mensaje(char *cod){
    FILE *f = fopen("codificado.txt","w");
    if(!f){ perror("codificado.txt"); return; }
    /* usamos N#cod */
    fprintf(f, "%d#%s\n", N, cod);
    fclose(f);
}
