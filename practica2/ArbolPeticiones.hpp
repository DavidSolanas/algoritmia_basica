/**
 * Fichero ArbolPeticiones.h
 * Práctica 1 Algoritmia Básica
 * Autores: Diego Martínez Baselga      735969
 *          David Solanas Sanz          738630
 */
#include <iostream>
#include <queue>
#include <bitset>

using namespace std;

//Árbol de Huffman
class ArbolPeticiones
{
private:
    // byte correspondiente con el nodo del árbol (indefinido si no es hoja)
    unsigned char caracter;
    // frecuencia de aparición de los caracteres del árbol
    unsigned int coste;
    unsigned int estimacion;
    unsigned int id_peticion;
    // hijo derecho
    ArbolPeticiones* der;
    // hijo izquierdo
    ArbolPeticiones* izq;
public:
    /**
     * Crea el árbol correspondiente al byte a con frecuencia f
     */
    ArbolPeticiones(unsigned char a, unsigned int f);

    /**
     * Crea el árbol correspondiente a la fusión del árbol i con el d.
     * i pasa a ser el hijo izquierdo y d el derecho
     */
    ArbolPeticiones(ArbolPeticiones* i, ArbolPeticiones* d);

    /**
     * Devuelve el árbol de caracteres formado por un árbol con hijo i.
     * Utilizado en ficheros con solo un byte o bytes iguales
     */
    ArbolPeticiones(ArbolPeticiones* i);

    /**
     * Libera el espacio del arbol de caracteres
     */
    ~ArbolPeticiones();

    /**
     * Devuelve la suma de frecuencias de aparición de los caracteres 
     * pertenecientes al arbol
     */
    unsigned int getCoste();
    unsigned int getId_peticion();
    unsigned int getEstimacion();

    /**
     * Devuelve el hijo izquierdo de la raíz del árbol
     */
    ArbolPeticiones* getIzq();

    /**
     * Devuelve el hijo derecho de la raíz del árbol
     */
    ArbolPeticiones* getDer();

    /**
     * Asigna c como byte correspondiente con la raíz del árbol
     */
    void setCoste (unsigned int c);

    /**
     * Asigna f como frecuencia correspondiente con la raíz del árbol
     */
    void setEstimacion (unsigned int e);
    void setId_peticion (unsigned int i);

    /**
     * Asigna d como hijo derecho de la raíz del árbol
     */
    void setDer (ArbolPeticiones* d);

    /**
     * Asigna i como hijo izquierdo de la raíz del árbol
     */
    void setIzq (ArbolPeticiones* i);

    /**
     * Asigna d como hijo derecho de la raíz del árbol
     */
    unsigned int escribir_arbol_fichero (ofstream& f);
    void escribir_arbol(); //debug
};



ArbolPeticiones::~ArbolPeticiones()
{
    if (izq!=nullptr){
        delete(izq);
        delete(der);
    }
}

unsigned int ArbolPeticiones:: getCoste(){
    return coste;
}

unsigned int ArbolPeticiones::getId_peticion(){
    return id_peticion;
}

unsigned int ArbolPeticiones::getEstimacion(){
    return estimacion;
}

ArbolPeticiones* ArbolPeticiones::getIzq(){
    return izq;
}

ArbolPeticiones* ArbolPeticiones::getDer(){
    return der;
}



void ArbolPeticiones::setDer (ArbolPeticiones* d){
    this->der=d;
}
    
void ArbolPeticiones::setIzq (ArbolPeticiones* i){
    this->izq=i;
}

void ArbolPeticiones::setCoste (unsigned int c){
    this->coste=c;
}

void ArbolPeticiones::setEstimacion (unsigned int e){
    this->estimacion=e;
}

void ArbolPeticiones::setId_peticion (unsigned int i){
    this->id_peticion=i;
}