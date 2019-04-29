#include <iostream>
#include <cstdio>

using namespace std;

long tamanno_fichero(FILE *f)
{
    fseek(f, 0, SEEK_END);
    return ftell(f);
}

/*
 * leer fichero, frecuencias[256], heap de arboles hoja != 0
 *
 */
int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "rb");
    long tam = tammano_fichero(f);
    char *contenido = (char *)malloc(tamanno_fichero(f) + 1);
    fread(contenido, tam, 1, f);
}