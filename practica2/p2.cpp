#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Peticion.hpp"
#include "ArbolPeticiones.hpp"

using namespace std;

bool obtenerDatos(ifstream &f, vector<Peticion> *vector, int &n)
{
    //Leer primera línea
    int m, p; //n -> capacidad del tren, m -> número de estaciones, p -> número de pedidos
    f >> n >> m >> p;
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
        //cout << salida << " " << llegada << " " << pasajeros << endl;
        P.setPeticion(salida, llegada, pasajeros);
        vector->push_back(P);
        i++;
    }
    return true;
}

int funcion_poda(vector<Peticion> *v, unsigned int objeto, unsigned int capacidad_ocupada,
                 unsigned int capacidad_total, int U, vector<bool> descartados)
{
    int poda = U;
    int c = capacidad_ocupada;
    for (int i = objeto; i < v->size(); i++)
    {
        if (!descartados[i] && capacidad_ocupada + v->at(i).getPasajeros() <= capacidad_total)
        {
            poda += v->at(i).getBeneficio();
            capacidad_ocupada += v->at(i).getPasajeros();
        }
    }
    return poda;
}

int funcion_cota(vector<Peticion> *v, unsigned int objeto, unsigned int capacidad_ocupada,
                 unsigned int capacidad_total, int ben, vector<bool> descartados)
{
    int beneficio = ben;
    int c = capacidad_ocupada;
    for (int i = objeto; i < v->size(); i++)
    {
        if (c == capacidad_total)
        {
            break;
        }
        if (!descartados[i])
        {
            if (c + v->at(i).getPasajeros() > capacidad_total)
            {
                beneficio += ((double)(capacidad_total - c) / v->at(i).getPasajeros()) * v->at(i).getBeneficio();
                c = capacidad_total;
            }
            else
            {
                c += v->at(objeto).getPasajeros();
                beneficio += v->at(objeto).getBeneficio();
            }
        }
    }
    return beneficio;
}

void ramificacion_poda(ArbolPeticiones a, int capacidad_total, vector<Peticion> *v)
{
    unsigned int nivel = 0;
    int U = a.getEstimacion();
    int beneficio = 0;
    int capacidad_disponible = capacidad_total;
    bool izqFactible;
    priority_queue<ArbolPeticiones, vector<ArbolPeticiones>, LessThanCost> pq;
    //Apilar nodo raíz
    pq.push(a);
    while (!pq.empty())
    {
        //Obtener nodo más prometedor
        ArbolPeticiones actual = pq.top();
        pq.pop();
        if (actual.getCoste() <= U)
        {
            cout << nivel << endl;
            //Expandir nodo (generar 2 hijos, izq cogiendo la petición, dch sin coger la petición)
            int capacidad_tras_anyadir = actual.getCapacidad() - v->at(nivel).getPasajeros();
            nivel = actual.getId_peticion() + 1;
            ArbolPeticiones izq(nivel, v->size()); //Se añade la petición del nodo actual
            izq.setDescartados(actual.getDescartados());
            izqFactible = capacidad_tras_anyadir > 0;
            cout << "U global: " << U << endl;
            cout << "U nodo: " << actual.getEstimacion() << endl;
            cout << "ĉ(actual): " << actual.getCoste() << endl;
            if (izqFactible)
            {
                izq.setCoste(actual.getCoste());
                izq.setEstimacion(actual.getEstimacion());
                izq.setCapacidad(capacidad_tras_anyadir);
            }

            ArbolPeticiones dch(nivel, v->size()); //No se añade la petición del nodo actual
            dch.setDescartados(actual.getDescartados());
            dch.descartar(nivel);
            dch.setCoste(funcion_cota(v, nivel, actual.getCapacidad(), capacidad_total, actual.getCoste(), dch.getDescartados()));
            dch.setEstimacion(funcion_poda(v, nivel, actual.getCapacidad(), capacidad_total, actual.getEstimacion(), dch.getDescartados()));
            dch.setCapacidad(actual.getCapacidad());
            cout << dch.getCoste() << endl
                 << endl;

            //Añadir nodos a la cola de prioridades si cumplen restricciones
            if (nivel == v->size() - 1)
            {
                if (izqFactible)
                {
                    //Caben última petición, hijo izq solución factible
                    if (izq.getCoste() < U)
                    {
                        beneficio = izq.getCoste();
                        U = izq.getEstimacion();
                    }
                }
                else
                {
                    //No caben más, hijo dch solución factible, izq nodo muerto
                    if (dch.getCoste() < U)
                    {
                        beneficio = dch.getCoste();
                        U = dch.getEstimacion();
                    }
                }
            }
            else
            {
                if (izqFactible)
                {
                    //Caben última petición, hijo izq solución factible
                    pq.push(izq);
                    pq.push(dch);
                }
                else
                {
                    //No caben más, hijo dch solución factible, izq nodo muerto
                    pq.push(dch);
                }
            }
        }
        else
        {
            cout << "PODA: " << actual.getId_peticion() << ", U global: " << U << ", cota: " << actual.getCoste() << endl;
        }
    }
    cout << beneficio << endl;
    cout << U << endl;
}

void calcular_solucion(vector<Peticion> *vector, bool *solucion, int capacidad_total)
{
    //Crear el árbol
    ArbolPeticiones ap(-1, vector->size());
    ap.setEstimacion(funcion_poda(vector, 0, 0, capacidad_total, 0, ap.getDescartados()));
    ap.setCoste(funcion_cota(vector, 0, 0, capacidad_total, 0, ap.getDescartados()));
    ap.setCapacidad(capacidad_total);
    cout << ap.getEstimacion() << endl;
    //ramificacion_poda(ap, capacidad_total, vector);
}

/*
struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}


void printTree(ArbolPeticiones *root, Trunk* prev, bool isLeft)
{
    if (root == nullptr)
        return;
    
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getIzq(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->getId_peticion() << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getDer(), trunk, false);
}*/

int main()
{

    ifstream f_entrada;
    f_entrada.open("datos.txt");
    vector<Peticion> *v = new vector<Peticion>();
    int capacidad_tren;
    obtenerDatos(f_entrada, v, capacidad_tren);
    obtenerDatos(f_entrada, v, capacidad_tren);
    obtenerDatos(f_entrada, v, capacidad_tren);
    v->clear();
    obtenerDatos(f_entrada, v, capacidad_tren);
    sort(v->begin(), v->end());
    for (auto i : *v)
    {
        i.mostrarPeticion();
    }

    bool *solucion = (bool *)malloc(size(*v));
    calcular_solucion(v, solucion, capacidad_tren);

    //ArbolPeticiones* a = crear_arbol(vector,0);
    //printTree(a, nullptr, false);
}