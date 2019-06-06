/*********************************************************
 * Fichero transporte.cpp
 * Práctica 2 Algoritmia Básica
 * Autores: Diego Martínez Baselga      735969
 *          David Solanas Sanz          738630
 *********************************************************/

#include <queue>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "Peticion.hpp"
#include "NodoPeticion.hpp"

using namespace std;

bool obtenerDatos(ifstream &f, vector<Peticion> *vector, int &n, int &m)
{
    //n -> capacidad del tren, m -> número de estaciones, p -> número de pedidos
    int p;
    //Leer primera línea
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
        P.setPeticion(salida, llegada, pasajeros);
        vector->push_back(P);
        i++;
    }
    return true;
}

void completar_pedidos(vector<Peticion> *v, int objeto, vector<int> &capacidad_ocupada,
                       int capacidad_total, int &beneficio_actual)
{
    for (int i = objeto; i < v->size(); i++)
    {
        int pasajeros = v->at(i).getPasajeros();
        for (int j = v->at(i).getEstacionSalida(); j < v->at(i).getEstacionLlegada(); j++)
        {
            if (capacidad_ocupada[j] + pasajeros > capacidad_total)
            {
                beneficio_actual -= capacidad_total - capacidad_ocupada[j];
                capacidad_ocupada[j] = capacidad_total;
            }
            else
            {
                beneficio_actual -= pasajeros;
                capacidad_ocupada[j] += pasajeros;
            }
        }
    }
}

bool caben_pasajeros(int capacidad_total, vector<int> capacidad_ocupada, int salida, int llegada, int pasajeros)
{
    for (int i = salida; i < llegada; i++)
    {
        if (capacidad_ocupada[i] + pasajeros > capacidad_total)
            return false;
    }
    return true;
}

int funcion_poda(vector<Peticion> *v, unsigned int objeto,
                 unsigned int capacidad_total, vector<bool> descartados, vector<int> capacidad_ocupada)
{
    int poda = 0;
    vector<int> c = capacidad_ocupada;

    for (int i = 0; i <= objeto; i++)
    {
        if (!descartados[i])
        {
            int salida = v->at(i).getEstacionSalida();
            int llegada = v->at(i).getEstacionLlegada();
            int pasajeros = v->at(i).getPasajeros();
            bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                           llegada, pasajeros);
            if (aceptar)
            {
                poda += v->at(i).getBeneficio();
                for (int i = salida; i < llegada; i++)
                {
                    c[i] += pasajeros;
                }
            }
        }
    }

    for (int i = objeto + 1; i < v->size(); i++)
    {
        int salida = v->at(i).getEstacionSalida();
        int llegada = v->at(i).getEstacionLlegada();
        int pasajeros = v->at(i).getPasajeros();
        bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                       llegada, pasajeros);
        if (aceptar)
        {
            poda += v->at(i).getBeneficio();
            for (int i = salida; i < llegada; i++)
            {
                c[i] += pasajeros;
            }
        }
    }
    return poda;
}

int funcion_cota(vector<Peticion> *v, unsigned int objeto,
                 unsigned int capacidad_total, int ben, vector<bool> descartados, vector<int> capacidad_ocupada)
{
    int beneficio = 0;
    vector<int> c = capacidad_ocupada;
    bool parar = false;
    for (int i = 0; i <= objeto && !parar; i++)
    {
        if (!descartados[i])
        {
            int salida = v->at(i).getEstacionSalida();
            int llegada = v->at(i).getEstacionLlegada();
            int pasajeros = v->at(i).getPasajeros();
            bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                           llegada, pasajeros);
            if (!aceptar)
            {

                completar_pedidos(v, i, c, capacidad_total, beneficio);
                parar = true;
            }
            else
            {
                beneficio += v->at(i).getBeneficio();
                for (int i = salida; i < llegada; i++)
                {
                    c[i] += pasajeros;
                }
            }
        }
    }
    for (int i = objeto + 1; i < v->size() && !parar; i++)
    {
        int salida = v->at(i).getEstacionSalida();
        int llegada = v->at(i).getEstacionLlegada();
        int pasajeros = v->at(i).getPasajeros();
        bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                       llegada, pasajeros);
        if (!aceptar)
        {
            completar_pedidos(v, i, c, capacidad_total, beneficio);
            parar = true;
        }
        else
        {
            beneficio += v->at(i).getBeneficio();
            for (int i = salida; i < llegada; i++)
            {
                c[i] += pasajeros;
            }
        }
    }
    return beneficio;
}

bool es_factible(int capacidad_total, vector<int> capacidad_ocupada)
{
    for (bool i : capacidad_ocupada)
    {
        if (i > capacidad_total)
            return false;
    }
    return true;
}

int ramificacion_poda(NodoPeticion a, int capacidad_total, vector<Peticion> *v, int n_paradas)
{
    unsigned int nivel = 0;
    int U = a.getEstimacion();
    int beneficio = 0;
    int capacidad_disponible = capacidad_total;
    bool izqFactible;
    priority_queue<NodoPeticion, vector<NodoPeticion>, LessThanCost> pq;
    //Apilar nodo raíz
    pq.push(a);
    while (!pq.empty())
    {
        //Obtener nodo más prometedor
        NodoPeticion actual = pq.top();
        pq.pop();
        if (actual.getCoste() <= U)
        {
            //Expandir nodo (generar 2 hijos, izq cogiendo la petición, dch sin coger la petición)
            nivel = actual.getId_peticion() + 1;
            vector<int> capacidad_tras_anyadir = actual.getCapacidad();
            for (int i = v->at(nivel).getEstacionSalida(); i < v->at(nivel).getEstacionLlegada(); i++)
            {
                capacidad_tras_anyadir[i] += v->at(nivel).getPasajeros();
            }

            NodoPeticion izq(nivel, v->size(), n_paradas); //Se añade la petición del nodo actual
            izq.setDescartados(actual.getDescartados());
            izqFactible = es_factible(capacidad_total, capacidad_tras_anyadir);
            if (izqFactible)
            {
                izq.setCoste(actual.getCoste());
                izq.setEstimacion(actual.getEstimacion());
                izq.setCapacidad(capacidad_tras_anyadir);
            }

            NodoPeticion dch(nivel, v->size(), n_paradas); //No se añade la petición del nodo actual
            dch.setDescartados(actual.getDescartados());
            dch.descartar(nivel);

            dch.setCoste(funcion_cota(v, nivel, capacidad_total, actual.getCoste(), dch.getDescartados(), dch.getCapacidad()));
            dch.setEstimacion(funcion_poda(v, nivel, capacidad_total, dch.getDescartados(), dch.getCapacidad()));
            dch.setCapacidad(actual.getCapacidad());

            //Añadir nodos a la cola de prioridades si cumplen restricciones
            if (nivel == v->size() - 1)
            {
                if (izqFactible)
                {
                    //Caben última petición, hijo izq solución factible
                    if (izq.getCoste() <= U)
                    {
                        beneficio = izq.getCoste();
                        U = izq.getEstimacion();
                    }
                }
                else
                {
                    //No caben más, hijo dch solución factible, izq nodo muerto
                    if (dch.getCoste() <= U)
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
    }
    return -U;
}

void calcular_solucion(vector<Peticion> *vector, int capacidad_total, int n_paradas, ofstream &f)
{
    clock_t t_start = clock();
    int ben = 0;
    if (vector->size() > 0)
    {
        //Crear el árbol
        NodoPeticion ap(-1, vector->size(), n_paradas);
        ap.setEstimacion(funcion_poda(vector, 0, capacidad_total, ap.getDescartados(), ap.getCapacidad()));
        ap.setCoste(funcion_cota(vector, 0, capacidad_total, 0, ap.getDescartados(), ap.getCapacidad()));
        ;
        ben = ramificacion_poda(ap, capacidad_total, vector, n_paradas);
    }
    clock_t t_end = clock();
    f << ben << " " << (double)(t_end - t_start) / CLOCKS_PER_SEC << endl;
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        ifstream f_entrada;
        ofstream f_salida;
        f_entrada.open(string(argv[1]));
        if (f_entrada.is_open())
        {
            f_salida.open(string(argv[2]));
            vector<Peticion> *v = new vector<Peticion>();
            int capacidad_tren, n_paradas;
            while (obtenerDatos(f_entrada, v, capacidad_tren, n_paradas))
            {
                sort(v->begin(), v->end());
                calcular_solucion(v, capacidad_tren, n_paradas, f_salida);
                v->clear();
            }
        }
        else
        {
            cerr << "No se ha podido abrir el fichero " << argv[1] << endl;
        }
    }
    else
    {
        cerr << "Numero de argumentos incorrecto: transporte <nombre_fichero_entrada> <nombre_fichero_salida>" << endl;
    }
}