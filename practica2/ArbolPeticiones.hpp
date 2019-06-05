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
    int capacidad_restante;
    // frecuencia de aparición de los caracteres del árbol
    int coste;
    int coste_sin_anyadir;
    int estimacion;
    int estimacion_sin_anyadir;
    int id_peticion;
    // hijo derecho
    ArbolPeticiones* der;
    // hijo izquierdo
    ArbolPeticiones* izq;
public:
    ArbolPeticiones(int id);

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
    int getCoste() const;
    unsigned int getId_peticion();
    int getCapacidad();
    int getEstimacion();
    int getEstimacion_Sin_Anyadir();
    int getCoste_Sin_Anyadir();

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
    void setCoste (int c);

    /**
     * Asigna f como frecuencia correspondiente con la raíz del árbol
     */
    void setEstimacion (int e);
    void setId_peticion (unsigned int i);
    void setCapacidad(int e);
    void setEstimacion_Sin_Anyadir(int e);
    void setCoste_Sin_Anyadir(int c);

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

ArbolPeticiones::ArbolPeticiones(int id){
    this->coste = INT32_MAX;
    this->estimacion = INT32_MAX;
    this->id_peticion = id;
    this->der = nullptr;
    this->izq = nullptr;
    
}

ArbolPeticiones::~ArbolPeticiones()
{
    if (izq!=nullptr){
        //delete(izq);
        //delete(der);
    }
}

int ArbolPeticiones:: getCoste() const{
    return coste;
}

int ArbolPeticiones:: getCapacidad(){
    return capacidad_restante;
}

unsigned int ArbolPeticiones::getId_peticion(){
    return id_peticion;
}

int ArbolPeticiones::getEstimacion(){
    return estimacion;
}

int ArbolPeticiones::getEstimacion_Sin_Anyadir(){
    return estimacion_sin_anyadir;
}

int ArbolPeticiones::getCoste_Sin_Anyadir(){
    return coste_sin_anyadir;
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

void ArbolPeticiones::setCoste (int c){
    this->coste=c;
}

void ArbolPeticiones::setEstimacion (int e){
    this->estimacion=e;
}

void ArbolPeticiones::setId_peticion (unsigned int i){
    this->id_peticion=i;
}

void ArbolPeticiones::setCapacidad(int e){
    this->capacidad_restante = e;
}

void ArbolPeticiones::setCoste_Sin_Anyadir(int c){
    this->coste_sin_anyadir = c;
}

void ArbolPeticiones::setEstimacion_Sin_Anyadir(int e){
    this->estimacion_sin_anyadir = e;
}


struct LessThanCost
{
  bool operator()(const ArbolPeticiones& lhs, const ArbolPeticiones& rhs) const
  {
    return lhs.getCoste() > rhs.getCoste();
  }
};