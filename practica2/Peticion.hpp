#include <iostream>

using namespace std;

class Peticion
{
private:
    int estacion_salida;
    int estacion_llegada;
    int num_pasajeros;

public:
    Peticion();
    Peticion(int salida, int llegada, int pasajeros);
    void setPeticion(int salida, int llegada, int pasajeros);
    void setEstacionSalida(int salida);
    void setEstacionLlegada(int llegada);
    void setPasajeros(int pasajeros);
    int getEstacionSalida() const;
    int getEstacionLlegada() const;
    int getPasajeros() const;
    int getDistancia() const;
    int getBeneficio() const;
    void mostrarPeticion();
    bool operator<(const Peticion &p);
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
    return -num_pasajeros * (estacion_llegada - estacion_salida + 1);
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