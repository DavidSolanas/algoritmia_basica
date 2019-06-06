/*********************************************************
 * Fichero NodoPeticion.hpp
 * Práctica 2 Algoritmia Básica
 * Autores: Diego Martínez Baselga      735969
 *          David Solanas Sanz          738630
 *********************************************************/
#include <vector>

using namespace std;

/**
 * Nodo de una petición concreta
 */
class NodoPeticion
{
private:
    //Vector de enteros que indica la capacidad ocupada en cada estación de dicho nodo
    vector<int> capacidad_ocupada;

    //Valor de la función de cota de dicho nodo
    int coste;

    //Valor de la función de poda de dicho nodo
    int estimacion;

    //Id que corresponde a la iésima petición del conjunto de peticiones
    int id_peticion;

    //Vector de booleanos que indica que peticiones han sido descartadas (true)
    vector<bool> descartados;

public:
    /**
     * Crea un nodo con id_petición [id], inicializa el vector de capacidad ocupada
     * a 0 de [1..n_paradas] e inicializa el vector de descartados a false de [1..size] 
     */
    NodoPeticion(int id, int size, int n_paradas);

    /**
     * Devuelve el valor de la función de cota del nodo
     */
    int getCoste() const;

    /**
     * Devuelve el índice de petición del nodo
     */
    int getId_peticion();

    /**
     * Devuelve un vector de enteros que corresponde a la 
     * capacidad ocupada en cada estación
     */
    vector<int> getCapacidad();

    /**
     * Devuelve el valor de la función de poda del nodo
     */
    int getEstimacion();

    /**
     * Devuelve un vector de booleanos que corresponde a las
     * peticiones que han sido descartadas
     */
    vector<bool> getDescartados();

    /**
     * Asigna c como el nuevo valor de la función de cota del nodo
     */
    void setCoste(int c);

    /**
     * Asigna e como el nuevo valor de la función de poda del nodo
     */
    void setEstimacion(int e);

    /**
     * Asigna i como el nuevo id_peticion del nodo
     */
    void setId_peticion(unsigned int i);

    /**
     * Asigna v como el nuevo vector de capacidad ocuapada del nodo
     */
    void setCapacidad(vector<int> v);

    /**
     * Asigna d como el nuevo vector de peticiones descartadas del nodo
     */
    void setDescartados(vector<bool> d);

    /**
     * Marca la petición i-ésima como descartada
     */
    void descartar(int i);
};

NodoPeticion::NodoPeticion(int id, int size, int n_paradas)
{
    this->coste = INT32_MAX;
    this->estimacion = INT32_MAX;
    this->id_peticion = id;
    //Reserva size posiciones e inicializa el vector a false
    this->descartados.resize(size);
    //Reserva n_paradas posiciones e inicializa el vector a 0
    this->capacidad_ocupada.resize(n_paradas);
}

int NodoPeticion::getCoste() const
{
    return coste;
}

vector<int> NodoPeticion::getCapacidad()
{
    return capacidad_ocupada;
}

int NodoPeticion::getId_peticion()
{
    return id_peticion;
}

int NodoPeticion::getEstimacion()
{
    return estimacion;
}

vector<bool> NodoPeticion::getDescartados()
{
    return descartados;
}

void NodoPeticion::setCoste(int c)
{
    this->coste = c;
}

void NodoPeticion::setEstimacion(int e)
{
    this->estimacion = e;
}

void NodoPeticion::setId_peticion(unsigned int i)
{
    this->id_peticion = i;
}

void NodoPeticion::setCapacidad(vector<int> v)
{
    this->capacidad_ocupada = v;
}

void NodoPeticion::setDescartados(vector<bool> d)
{
    this->descartados = d;
}

void NodoPeticion::descartar(int i)
{
    this->descartados[i] = true;
}

/**
 * Struct que define el operador de comparación entre dos objetos
 * NodoPeticion
 */
struct LessThanCost
{
    bool operator()(const NodoPeticion &lhs, const NodoPeticion &rhs) const
    {
        return lhs.getCoste() > rhs.getCoste();
    }
};