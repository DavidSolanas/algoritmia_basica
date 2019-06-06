/**
 * Fichero ArbolPeticiones.h
 * Práctica 1 Algoritmia Básica
 * Autores: Diego Martínez Baselga      735969
 *          David Solanas Sanz          738630
 */
#include <iostream>
#include <vector>

using namespace std;

//Árbol de Huffman
class ArbolPeticiones
{
private:
    vector<int> capacidad_restante;
    // frecuencia de aparición de los caracteres del árbol
    int coste;
    int estimacion;
    int id_peticion;
    vector<bool> descartados;
    // hijo derecho
    ArbolPeticiones *der;
    // hijo izquierdo
    ArbolPeticiones *izq;

public:
    ArbolPeticiones(int id, int size, int n_paradas);

    /**
     * Crea el árbol correspondiente al byte a con frecuencia f
     */

    /**
     * Crea el árbol correspondiente a la fusión del árbol i con el d.
     * i pasa a ser el hijo izquierdo y d el derecho
     */
    ArbolPeticiones(ArbolPeticiones *i, ArbolPeticiones *d);

    /**
     * Devuelve el árbol de caracteres formado por un árbol con hijo i.
     * Utilizado en ficheros con solo un byte o bytes iguales
     */
    ArbolPeticiones(ArbolPeticiones *i);

    /**
     * Libera el espacio del arbol de caracteres
     */
    ~ArbolPeticiones();

    /**
     * Devuelve la suma de frecuencias de aparición de los caracteres 
     * pertenecientes al arbol
     */
    int getCoste() const;
    int getId_peticion();
    vector<int> getCapacidad();
    int getEstimacion();
    vector<bool> getDescartados();

    /**
     * Devuelve el hijo izquierdo de la raíz del árbol
     */
    ArbolPeticiones *getIzq();

    /**
     * Devuelve el hijo derecho de la raíz del árbol
     */
    ArbolPeticiones *getDer();

    /**
     * Asigna c como byte correspondiente con la raíz del árbol
     */
    void setCoste(int c);

    /**
     * Asigna f como frecuencia correspondiente con la raíz del árbol
     */
    void setEstimacion(int e);
    void setId_peticion(unsigned int i);
    void setCapacidad(vector<int> v);
    void setDescartados(vector<bool> e);
    void descartar(int indice);

    /**
     * Asigna d como hijo derecho de la raíz del árbol
     */
    void setDer(ArbolPeticiones *d);

    /**
     * Asigna i como hijo izquierdo de la raíz del árbol
     */
    void setIzq(ArbolPeticiones *i);

    /**
     * Asigna d como hijo derecho de la raíz del árbol
     */
    unsigned int escribir_arbol_fichero(ofstream &f);
    void escribir_arbol(); //debug
};

ArbolPeticiones::ArbolPeticiones(int id, int size, int n_paradas)
{
    this->coste = INT32_MAX;
    this->estimacion = INT32_MAX;
    this->id_peticion = id;
    this->der = nullptr;
    this->izq = nullptr;
    this->descartados.resize(size);
    this->capacidad_restante.resize(n_paradas);
}

ArbolPeticiones::~ArbolPeticiones()
{
    if (izq != nullptr)
    {
        //delete(izq);
        //delete(der);
    }
}

int ArbolPeticiones::getCoste() const
{
    return coste;
}

vector<int> ArbolPeticiones::getCapacidad()
{
    return capacidad_restante;
}

int ArbolPeticiones::getId_peticion()
{
    return id_peticion;
}

int ArbolPeticiones::getEstimacion()
{
    return estimacion;
}

vector<bool> ArbolPeticiones::getDescartados()
{
    return descartados;
}

ArbolPeticiones *ArbolPeticiones::getIzq()
{
    return izq;
}

ArbolPeticiones *ArbolPeticiones::getDer()
{
    return der;
}

void ArbolPeticiones::setDer(ArbolPeticiones *d)
{
    this->der = d;
}

void ArbolPeticiones::setIzq(ArbolPeticiones *i)
{
    this->izq = i;
}

void ArbolPeticiones::setCoste(int c)
{
    this->coste = c;
}

void ArbolPeticiones::setEstimacion(int e)
{
    this->estimacion = e;
}

void ArbolPeticiones::setId_peticion(unsigned int i)
{
    this->id_peticion = i;
}

void ArbolPeticiones::setCapacidad(vector<int> v)
{
    this->capacidad_restante = v;
}

void ArbolPeticiones::setDescartados(vector<bool> v)
{
    this->descartados = v;
}

void ArbolPeticiones::descartar(int indice)
{
    this->descartados[indice] = true;
}

struct LessThanCost
{
    bool operator()(const ArbolPeticiones &lhs, const ArbolPeticiones &rhs) const
    {
        return lhs.getCoste() > rhs.getCoste();
    }
};