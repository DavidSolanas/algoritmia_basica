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
    int getEstacionSalida();
    int getEstacionLlegada();
    int getPasajeros();
    int getBeneficio();
    int getPenalizacion();
    void mostrarPeticion();
    bool operator<(Peticion p);
    bool operator>(Peticion p);
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
int Peticion::getEstacionSalida()
{
    return estacion_salida;
}
int Peticion::getEstacionLlegada()
{
    return estacion_llegada;
}
int Peticion::getPasajeros()
{
    return num_pasajeros;
}
int Peticion::getBeneficio()
{
    return num_pasajeros * (estacion_llegada - estacion_salida);
}
int Peticion::getPenalizacion()
{
    return -getBeneficio();
}
void Peticion::mostrarPeticion()
{
    cout << "Salida: " << estacion_salida << ", ";
    cout << "Llegada: " << estacion_llegada << ", ";
    cout << "Pasajeros: " << num_pasajeros << ", ";
    cout << "Beneficio: " << getBeneficio() << endl;
}

bool Peticion::operator<(Peticion p)
{
    return this->getPenalizacion() < p.getPenalizacion();
}

bool Peticion::operator>(Peticion p)
{
    return this->getPenalizacion() > p.getPenalizacion();
}
