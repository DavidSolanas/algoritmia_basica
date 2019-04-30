#include <iostream>
#include <cstdio>

using namespace std;

/**
 * Devuelve el tamaño del fichero f en Bytes.
 */
long tamanno_fichero(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);
    return tam;
}

/**
 * Lee el contenido del vector de caracteres y almacena
 * en el vector frecuencias el número de apariciones de 
 * cada carácter en dicho vector. La posición de un carácter
 * en el vector frecuencias vendrá determinado por su código ASCII
 */
void calcular_frecuencias(char *datos, int *frecuencias)
{
    int indice = 0;
    while (datos[indice] != '\0')
    {
        cout << indice << ": " << (int)datos[indice] << endl;
        frecuencias[datos[indice]]++;
        indice++;
    }
}

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "rb");
    long tam = tamanno_fichero(f);
    char *contenido = (char *)malloc(tam + 1);
    fread(contenido, tam, 1, f);

    // Creación del array e inicialización a 0
    int frecuencias[256] = {0};
    calcular_frecuencias(contenido, frecuencias);
    for (int i = 0; i < 256; i++)
    {
        cout << i << ": " << frecuencias[i] << endl;
    }
    cout << endl;
}