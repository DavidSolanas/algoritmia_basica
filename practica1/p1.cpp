#include <iostream>
#include <cstdio>
#include "Monticulo_arboles.h"

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
void calcular_frecuencias(unsigned char *datos, unsigned int *frecuencias)
{
    int indice = 0;
    while (datos[indice] != '\0')
    {
        frecuencias[datos[indice]]++;
        indice++;
    }
}

void inicializar_monticulo (Monticulo_arboles* monticulo, unsigned int* frecuencias){
    for (int i = 0; i<256; i++){
        if (frecuencias[i] != 0){
            //cout << (int)i << endl;
            monticulo->insertar(new Arbol_caracteres(i, frecuencias[i]));
        }
    }
}

Arbol_caracteres* huffman (unsigned int* frecuencias){
    //int i = 0;
    
    Monticulo_arboles* monticulo = new Monticulo_arboles();
    inicializar_monticulo (monticulo, frecuencias);
    if (monticulo->terminado()){
        Arbol_caracteres* a = monticulo->borrar_primero();
        monticulo->insertar(new Arbol_caracteres(a));
    }
    //monticulo->escribir_monticulo();
    //cout << "Antes del bucle" << endl;
    //i=0;
    while (!monticulo->terminado()){
       // monticulo->escribir_monticulo();
        //cout << i << "prim" << endl;
        Arbol_caracteres* a = monticulo->borrar_primero();
       // monticulo->escribir_monticulo();
       // cout << i << "seg" << endl;
        //a->escribir_arbol();
        Arbol_caracteres* b = monticulo->borrar_primero();
        //cout << i << "ter" << endl;
        //b->escribir_arbol();
        monticulo->insertar(new Arbol_caracteres(a, b));
        //cout << i << "cua" << endl;
        //i++;
    }
    
   /* 
    cout << "ARBOL A:"<<endl;
    Arbol_caracteres* a = monticulo->borrar_primero();
    cout << "arbol(primero)"<<endl;
    a->escribir_arbol();
    cout << "ARBOL B:"<<endl;
    Arbol_caracteres* b = monticulo->borrar_primero();
    cout << "arbol(primero)"<<endl;
    b->escribir_arbol();*/
    return monticulo->borrar_primero();
}
//SI ES UN ARBOL DE UN SOLO COMPONENTE NO TIENE POR QUE PETAR
void clacular_codigos (Arbol_caracteres* a, string codigos[], string cadena){
    if (a->getIzq()==nullptr){
        //Hoja, árbol compuesto solo por un caracter
        codigos[a->getCaracter()] = cadena;
    }
    else if (a->getDer() == nullptr){
        //Caso en el que el árbol está compuesto por solo una letra (un nodo y una hoja)
        clacular_codigos(a->getIzq(), codigos, cadena + '0');
    }
    else{
        clacular_codigos(a->getIzq(), codigos, cadena + '0');
        clacular_codigos(a->getDer(), codigos, cadena + '1');
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1){
        FILE *f = fopen(argv[1], "rb");
        long tam = tamanno_fichero(f);
        unsigned char *contenido = (unsigned char *)malloc(tam + 1);
        fread(contenido, tam, 1, f);
        // Creación del array e inicialización a 0
        unsigned int frecuencias[256] = {0};
        calcular_frecuencias(contenido, frecuencias);
        Arbol_caracteres* arbol = huffman(frecuencias);
        string codigos[256];
        cout<<"Antes"<<endl;
        clacular_codigos(arbol, codigos, "");
        cout<<"despues"<<endl;
        for (int i = 0; i<256; i++){
            cout<<(unsigned char)i<<": "<< codigos[i]<<endl;
        }
    }
    else {
        cout << "Inutil" << endl;
    }
}