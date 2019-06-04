#include <queue>
#include <iostream>
#include <fstream>
#include <list>
#include "Peticion.hpp"

using namespace std;

bool obtenerDatos(ifstream &f, list<Peticion>* lista)
{
    //Leer primera línea
    int n, m, p; //n -> capacidad del tren, m -> número de estaciones, p -> número de pedidos
    f >> n >> m >> p;
    cout << n << " " << m << " " << p << endl;
    if (n == 0 && m == 0 && p == 0)
    {
        return false;
    }
    int i = 1;
    int salida, llegada, pasajeros;
    Peticion P;
    while (i <= p)
    {
        f >> salida >> llegada >> pasajeros;
        cout << salida << " " << llegada << " " << pasajeros << endl;
        P.setPeticion(salida, llegada, pasajeros);
        lista->push_back(P);
        i++;
    }
    return true;
}

int main()
{
    ifstream f_entrada;
    f_entrada.open("datos.txt");
    list<Peticion>* lista = new list<Peticion>();
    obtenerDatos(f_entrada, lista);
    lista->sort(operator>);
    for (Peticion p : *lista){
        p.mostrarPeticion();
    }
}