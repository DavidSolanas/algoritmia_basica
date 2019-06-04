#include <queue>
#include <iostream>
#include <fstream>
#include "Peticion.hpp"

using namespace std;

bool obtenerDatos(ifstream &f)
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
        P.mostrarPeticion();
        i++;
    }
    return true;
}

int main()
{
    priority_queue<int> q;
    ifstream f_entrada;
    f_entrada.open("datos.txt");
    obtenerDatos(f_entrada);
    //obtenerDatos(f_entrada);
}