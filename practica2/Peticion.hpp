/*********************************************************
 * Fichero Peticion.hpp
 * Práctica 2 Algoritmia Básica
 * Autores: Diego Martínez Baselga      735969
 *          David Solanas Sanz          738630
 *********************************************************/

#include <iostream>

using namespace std;

/**
 * Petición de viaje
 */
class Peticion
{
private:
    //Indica la estación de salida del viaje
    int estacion_salida;

    //Indica la estación de llegada del viaje
    int estacion_llegada;

    //Indica el número de pasajeros que incluye la petición
    int num_pasajeros;

public:
    /**
     * Crea una petición vacía
     */
    Peticion();

    /**
     * Crea una petición y asigna salida como estación de salida,
     * llegada como estación de llegada y pasajeros como el
     * número de pasajeros de la petición
     */
    Peticion(int salida, int llegada, int pasajeros);

    /**
     * Asigna salida como estación de salida,
     * llegada como estación de llegada y pasajeros como el
     * número de pasajeros de la petición
     */
    void setPeticion(int salida, int llegada, int pasajeros);

    /**
     * Asigna salida como estación de salida de la petición
     */
    void setEstacionSalida(int salida);

    /**
     * Asigna llegada como estación de llegada de la petición
     */
    void setEstacionLlegada(int llegada);

    /**
     * Asigna pasajeros como el número de pasajeros de la petición
     */
    void setPasajeros(int pasajeros);

    /**
     * Devuelve la estación de salida de la petición
     */
    int getEstacionSalida() const;

    /**
     * Devuelve la estación de llegada de la petición
     */
    int getEstacionLlegada() const;

    /**
     * Devuelve el número de pasajeros de la petición
     */
    int getPasajeros() const;

    /**
     * Devuelve la distancia del trayecto, calculado como:
     * estación de llegada - estación de salida
     */
    int getDistancia() const;

    /**
     * Devuelve el beneficio obtenido con la petición (en signo negativo),
     * calculado como: número de pasajeros * distancia
     */
    int getBeneficio() const;

    /**
     * Muestra por pantalla la información relativa a la petición con el formato:
     * "Salida: [estacion_salida], Llegada: [estacion_llegada],
     * Pasajeros: [num_pasajeros], Beneficio: [num_pasajeros*distancia]"
     */
    void mostrarPeticion();

    /**
     * Define el operador < para comparar dos peticiones. Una petición será menor
     * que otra si el número de pasajeros / distancia del trayecto es
     * menor que el de la otra petición
     */
    bool operator<(const Peticion &p);

    /**
     * Define el operador > para comparar dos peticiones. Una petición será mayor
     * que otra si el número de pasajeros / distancia del trayecto es
     * mayor que el de la otra petición
     */
    bool operator>(const Peticion &p);
};

Peticion::Peticion()
{
    estacion_salida = -1;
    estacion_llegada = -1;
    num_pasajeros = -1;
}

Peticion::Peticion(int salida, int llegada, int pasajeros)
{
    estacion_salida = salida;
    estacion_llegada = llegada;
    num_pasajeros = pasajeros;
}

void Peticion::setPeticion(int salida, int llegada, int pasajeros)
{
    estacion_salida = salida;
    estacion_llegada = llegada;
    num_pasajeros = pasajeros;
}

void Peticion::setEstacionSalida(int salida)
{
    estacion_salida = salida;
}

void Peticion::setEstacionLlegada(int llegada)
{
    estacion_llegada = llegada;
}

void Peticion::setPasajeros(int pasajeros)
{
    num_pasajeros = pasajeros;
}

int Peticion::getEstacionSalida() const
{
    return estacion_salida;
}

int Peticion::getEstacionLlegada() const
{
    return estacion_llegada;
}

int Peticion::getDistancia() const
{
    return this->estacion_llegada - this->estacion_salida;
}

int Peticion::getPasajeros() const
{
    return num_pasajeros;
}

int Peticion::getBeneficio() const
{
    return -num_pasajeros * (estacion_llegada - estacion_salida);
}

void Peticion::mostrarPeticion()
{
    cout << "Salida: " << estacion_salida << ", ";
    cout << "Llegada: " << estacion_llegada << ", ";
    cout << "Pasajeros: " << num_pasajeros << ", ";
    cout << "Beneficio: " << getBeneficio() << endl;
}

bool Peticion::operator<(const Peticion &p)
{
    return this->getPasajeros() / this->getDistancia() > p.getPasajeros() / p.getDistancia();
}

bool Peticion::operator>(const Peticion &p)
{
    return this->getPasajeros() / this->getDistancia() > p.getPasajeros() / p.getDistancia();
}

bool operator<(const Peticion &p1, const Peticion &p2)
{
    return p1.getPasajeros() / p1.getDistancia() < p2.getPasajeros() / p2.getDistancia();
}