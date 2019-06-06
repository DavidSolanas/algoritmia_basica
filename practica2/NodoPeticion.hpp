/**
 * Fichero NodoPeticion.h
 * Práctica 1 Algoritmia Básica
 * Autores: Diego Martínez Baselga      735969
 *          David Solanas Sanz          738630
 */
#include <vector>

using namespace std;

//Árbol de Huffman
class NodoPeticion
{
private:
    vector<int> capacidad_restante;
    // frecuencia de aparición de los caracteres del árbol
    int coste;
    int estimacion;
    int id_peticion;
    vector<bool> descartados;

public:
    NodoPeticion(int id, int size, int n_paradas);

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
};

NodoPeticion::NodoPeticion(int id, int size, int n_paradas)
{
    this->coste = INT32_MAX;
    this->estimacion = INT32_MAX;
    this->id_peticion = id;
    this->descartados.resize(size);
    this->capacidad_restante.resize(n_paradas);
}

int NodoPeticion::getCoste() const
{
    return coste;
}

vector<int> NodoPeticion::getCapacidad()
{
    return capacidad_restante;
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
    this->capacidad_restante = v;
}

void NodoPeticion::setDescartados(vector<bool> v)
{
    this->descartados = v;
}

void NodoPeticion::descartar(int indice)
{
    this->descartados[indice] = true;
}

struct LessThanCost
{
    bool operator()(const NodoPeticion &lhs, const NodoPeticion &rhs) const
    {
        return lhs.getCoste() > rhs.getCoste();
    }
};