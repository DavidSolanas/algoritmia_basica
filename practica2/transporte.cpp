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

/**
 * Obtiene los datos del fichero de entrada. La primera línea corresponde con 3 enteros,
 * el primero la capacidad total del tren (n), el segundo el número de estaciones (m) y el
 * tercero el número de pedidos (p). A partir de esa línea las p siguientes líneas están
 * compuestas de tres enteros. El primero indica la estación de salida (salida), el segundo
 * la estación de llegada (llegada) y el último el número de pasajeros de ese pedido (pasajeros).
 * Si al leer la primera línea se lee la secuencia 0 0 0, indica que no hay más datos que leer y
 * devuelve FALSE, en caso contrario devuelve TRUE otra recogida de datos para otro problema distinto.
 * Las peticiones se van guardando en el vector [vector].
 */
bool obtenerDatos(ifstream &f, vector<Peticion> *vector, int &n, int &m)
{
    //n -> capacidad del tren, m -> número de estaciones, p -> número de pedidos
    int p;
    //Leer primera línea
    f >> n >> m >> p;
    if (n == 0 && m == 0 && p == 0)
    {
        //No hay más datos en el fichero
        return false;
    }
    int i = 1;
    int salida, llegada, pasajeros;
    Peticion P;
    while (i <= p)
    {
        //Leer petición
        f >> salida >> llegada >> pasajeros;
        //Crear petición
        P.setPeticion(salida, llegada, pasajeros);
        //Guardar petición
        vector->push_back(P);
        i++;
    }
    //Hay más datos en el fichero
    return true;
}

/**
 * v: Vector de peticiones ordenado por número de pasajeros / distancia del trayecto
 * objeto: Índice a partir del cual considerar siguientes peticiones
 * capacidad_ocupada: Vector de capacidad ocupada por estación
 * capacidad_total: Capacidad total del tren
 * beneficio_actual: Beneficio actual calculado
 * Calcula el beneficio resultante de llenar lo máximo posible el tren
 * a partir de las peticiones restantes
 */
void completar_pedidos(vector<Peticion> *v, int objeto, vector<int> &capacidad_ocupada,
                       int capacidad_total, int &beneficio_actual)
{
    for (int i = objeto; i < v->size(); i++)
    {
        int pasajeros = v->at(i).getPasajeros();
        //Para cada estación de la petición calcula el beneficio resultante de añadir
        //los pasajeros posibles al tren
        for (int j = v->at(i).getEstacionSalida(); j < v->at(i).getEstacionLlegada(); j++)
        {
            if (capacidad_ocupada[j] + pasajeros > capacidad_total)
            {
                //Los pasajeros + la capacidad ocupada en la estación supera
                //la capacidad del tren, se actualiza la capacidad ocupada y el beneficio
                //se calcula como el número de pasajeros que caben en el tren + el
                //beneficio actual
                beneficio_actual -= capacidad_total - capacidad_ocupada[j];
                capacidad_ocupada[j] = capacidad_total;
            }
            else
            {
                //Los pasajeros + la capacidad ocupada en la estación no supera
                //la capacidad del tren, se actualiza la capacidad ocupada y el beneficio
                //se calcula como el número de pasajeros de la petición + el beneficio actual
                beneficio_actual -= pasajeros;
                capacidad_ocupada[j] += pasajeros;
            }
        }
    }
}

/**
 * capacidad_total: Capacidad total del tren
 * capacidad_ocupada: Vector de capacidad ocupada por estación
 * salida: Estación de salida del viaje
 * llegada: Estación de llegada del viaje
 * pasajeros: Número de pasajeros asociados al viaje
 * Devuelve true si para toda estación la capacidad ocupada + los pasajeros del viaje no
 * sobrepasa la capacidad total del tren, devuelve false en caso contrario
 */
bool caben_pasajeros(int capacidad_total, vector<int> capacidad_ocupada, int salida, int llegada, int pasajeros)
{
    for (int i = salida; i < llegada; i++)
    {
        if (capacidad_ocupada[i] + pasajeros > capacidad_total)
            return false;
    }
    return true;
}

/**
 * v: Vector de peticiones ordenado por número de pasajeros / distancia del trayecto
 * objeto: Índice a partir del cual considerar siguientes peticiones
 * capacidad_total: Capacidad total del tren
 * descartados: Vector de booleanos que indica que peticiones han sido descartadas
 * capacidad_ocuapada: Vector de capacidad ocupada por estación
 * Calcula el valor de poda
 */
int funcion_poda(vector<Peticion> *v, unsigned int objeto,
                 unsigned int capacidad_total, vector<bool> descartados, vector<int> capacidad_ocupada)
{
    int poda = 0;
    vector<int> c = capacidad_ocupada;

    //Calcula la poda desde la primera petición hasta la petición objeto
    for (int i = 0; i <= objeto; i++)
    {
        //Comprueba si la petición ha sido descartada, si lo ha sido se ignora
        if (!descartados[i])
        {
            int salida = v->at(i).getEstacionSalida();
            int llegada = v->at(i).getEstacionLlegada();
            int pasajeros = v->at(i).getPasajeros();
            //Comprueba si para cada estación de la petición caben los pasajeros
            //solicitados en el tren
            bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                           llegada, pasajeros);
            if (aceptar)
            {
                //Se actualiza el valor de poda y la capacidad ocupada del tren en cada estación
                poda += v->at(i).getBeneficio();
                for (int i = salida; i < llegada; i++)
                {
                    c[i] += pasajeros;
                }
            }
        }
    }

    //Calcula la poda desde la petición objeto + 1 hasta el final de peticiones
    for (int i = objeto + 1; i < v->size(); i++)
    {
        int salida = v->at(i).getEstacionSalida();
        int llegada = v->at(i).getEstacionLlegada();
        int pasajeros = v->at(i).getPasajeros();
        //Comprueba si para cada estación de la petición caben los pasajeros
        //solicitados en el tren
        bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                       llegada, pasajeros);
        if (aceptar)
        {
            //Se actualiza el valor de poda y la capacidad ocupada del tren en cada estación
            poda += v->at(i).getBeneficio();
            for (int i = salida; i < llegada; i++)
            {
                c[i] += pasajeros;
            }
        }
    }
    return poda;
}

/**
 * v: Vector de peticiones ordenado por número de pasajeros / distancia del trayecto
 * objeto: Índice a partir del cual considerar siguientes peticiones
 * capacidad_total: Capacidad total del tren
 * descartados: Vector de booleanos que indica que peticiones han sido descartadas
 * capacidad_ocuapada: Vector de capacidad ocupada por estación
 * Calcula el valor de cota (coste estimado)
 */
int funcion_cota(vector<Peticion> *v, unsigned int objeto,
                 unsigned int capacidad_total, vector<bool> descartados, vector<int> capacidad_ocupada)
{
    int beneficio = 0;
    vector<int> c = capacidad_ocupada;
    bool parar = false;
    //Calcula el coste desde la primera petición hasta la petición objeto
    for (int i = 0; i <= objeto && !parar; i++)
    {
        //Comprueba si la petición ha sido descartada, si lo ha sido se ignora
        if (!descartados[i])
        {
            int salida = v->at(i).getEstacionSalida();
            int llegada = v->at(i).getEstacionLlegada();
            int pasajeros = v->at(i).getPasajeros();
            //Comprueba si para cada estación de la petición caben los pasajeros
            //solicitados en el tren
            bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                           llegada, pasajeros);
            if (!aceptar)
            {
                //No caben todos los pasajeros, completar capacidad y actualizar beneficio
                completar_pedidos(v, i, c, capacidad_total, beneficio);
                parar = true;
            }
            else
            {
                //Se actualiza el valor de poda y la capacidad ocupada del tren en cada estación
                beneficio += v->at(i).getBeneficio();
                for (int i = salida; i < llegada; i++)
                {
                    c[i] += pasajeros;
                }
            }
        }
    }

    //Calcula el coste desde la petición objeto + 1 hasta el final de peticiones
    for (int i = objeto + 1; i < v->size() && !parar; i++)
    {
        int salida = v->at(i).getEstacionSalida();
        int llegada = v->at(i).getEstacionLlegada();
        int pasajeros = v->at(i).getPasajeros();
        //Comprueba si para cada estación de la petición caben los pasajeros
        //solicitados en el tren
        bool aceptar = caben_pasajeros(capacidad_total, c, salida,
                                       llegada, pasajeros);
        if (!aceptar)
        {
            //No caben todos los pasajeros, completar capacidad y actualizar beneficio
            completar_pedidos(v, i, c, capacidad_total, beneficio);
            parar = true;
        }
        else
        {
            //Se actualiza el valor de poda y la capacidad ocupada del tren en cada estación
            beneficio += v->at(i).getBeneficio();
            for (int i = salida; i < llegada; i++)
            {
                c[i] += pasajeros;
            }
        }
    }
    return beneficio;
}

/**
 * capacidad_total: Capacidad total del tren
 * capacidad_ocupada: Vector de capacidad ocupada por estación
 * Devuelve true si para toda estación la capacidad ocupada no
 * sobrepasa la capacidad total del tren, devuelve false en caso contrario
 */
bool es_factible(int capacidad_total, vector<int> capacidad_ocupada)
{
    for (int i : capacidad_ocupada)
    {
        if (i > capacidad_total)
            return false;
    }
    return true;
}

/**
 * a: Nodo raíz para iniciar la búsqueda
 * capacidad_total: Capacidad total del tren
 * v: Vector de peticiones ordenado por número de pasajeros / distancia del trayecto
 * n_paradas: Número total de estaciones
 * fuerzaBruta: Indica si utilizar el algoritmo de ramificación y poda o de fuerza bruta para calcular la solución
 * Dado el vector de peticiones, calcula el máximo ingreso total.
 */
int ramificacion_poda(NodoPeticion a, int capacidad_total, vector<Peticion> *v, int n_paradas, bool fuerzaBruta)
{
    //Indica la petición a tratar
    unsigned int nivel = 0;
    //Representa el valor mínimo de poda (que a su vez es el beneficio máximo en negativo)
    int U = a.getEstimacion();
    //Indica si tras añadir una petición se ha sobrepasado el límite de capacidad del tren o no
    bool izqFactible;
    //Cola de prioridades que ordena de forma ascendiente los nodos según la función de cota
    priority_queue<NodoPeticion, vector<NodoPeticion>, LessThanCost> pq;
    //Apilar nodo raíz
    pq.push(a);
    //Repetir mientras haya nodos en la cola de prioridades
    while (!pq.empty())
    {
        //Obtener nodo más prometedor (el que tenga una función de cota menor)
        NodoPeticion actual = pq.top();
        //Eliminar nodo de la cola de prioridades
        pq.pop();
        //Comprobar si hay que podar el nodo o no (si su función de cota supera el valor mínimo de poda -> PODAR)
        //Si fuerzaBruta es TRUE nunca habrá poda, solo será TRUE si el usuario ejecuta el programa con el flag
        // -fb
        if (fuerzaBruta || actual.getCoste() <= U)
        {
            //Expandir nodo (generar 2 hijos, izq cogiendo la petición, dch sin coger la petición)
            nivel = actual.getId_peticion() + 1;
            //Añade los pasajeros de la petición a las estaciones correspondientes
            vector<int> capacidad_tras_anyadir = actual.getCapacidad();
            for (int i = v->at(nivel).getEstacionSalida(); i < v->at(nivel).getEstacionLlegada(); i++)
            {
                capacidad_tras_anyadir[i] += v->at(nivel).getPasajeros();
            }

            //Crear el hijo izquierdo -> Hijo resultante tras elegir la petición actual
            NodoPeticion izq(nivel, v->size(), n_paradas);
            //Se copia el vector de descartados del nodo actual
            izq.setDescartados(actual.getDescartados());
            //Se comprueba si tras añadir todos los pasajeros de la petición actual al tren
            //se sobrepasa el límite del tren en alguna estación
            izqFactible = es_factible(capacidad_total, capacidad_tras_anyadir);
            //Si no se ha sobrepasado el límite se actualizan los valores del hijo de su función
            //de cota, su función de poda y su capacidad ocupada tras añadir la petición actual.
            //Si se ha sobrepasado el límite, el hijo izquierdo nunca será añadido a la cola de
            //prioridades ni se tendrá en cuenta si es una hoja, ya que no puede dar lugar a una
            //solución.
            if (izqFactible)
            {
                //Actualizar el valor de la función de cota
                izq.setCoste(actual.getCoste());
                //Actualizar el valor de la función de poda
                izq.setEstimacion(actual.getEstimacion());
                //Actualizar la capacidad ocupada tras añadir la petición
                izq.setCapacidad(capacidad_tras_anyadir);
            }

            //Crear el hijo derecho -> Hijo resultante tras no elegir la petición actual
            NodoPeticion dch(nivel, v->size(), n_paradas);
            //Se copia el vector de descartados del nodo actual y se descarta la
            //última petición tratada
            dch.setDescartados(actual.getDescartados());
            dch.descartar(nivel);

            //Actualizar el valor de la función de cota
            dch.setCoste(funcion_cota(v, nivel, capacidad_total, dch.getDescartados(), dch.getCapacidad()));
            //Actualizar el valor de la función de poda
            dch.setEstimacion(funcion_poda(v, nivel, capacidad_total, dch.getDescartados(), dch.getCapacidad()));
            //Mantener la capacidad ocupada que había previamente
            dch.setCapacidad(actual.getCapacidad());

            //Añadir nodos a la cola de prioridades si cumplen restricciones
            if (nivel == v->size() - 1)
            {
                //Los hijos del nodo actual son hojas
                if (izqFactible)
                {
                    //Cabe la última petición, hijo izq solución factible, si su función
                    //de cota es menor que el valor mínimo de poda actual se actualiza
                    if (izq.getCoste() <= U)
                    {
                        U = izq.getEstimacion();
                    }
                }
                else
                {
                    //No caben más, hijo dch solución factible, izq nodo muerto, si la función
                    //de cota del hijo dch es menor que el valor mínimo de poda actual se actualiza
                    if (dch.getCoste() <= U)
                    {
                        U = dch.getEstimacion();
                    }
                }
            }
            else
            {
                //Los hijos del nodo actual no son hojas, añadirlos a la cola de prioridades
                if (izqFactible)
                {
                    //Cabe última petición, añadir hijos izq y dch, ya que ambos pueden llevar
                    //a la solución
                    pq.push(izq);
                    pq.push(dch);
                }
                else
                {
                    //No cabe la última petición, añadir hijo dch ya que puede llevar a la solución
                    //y matar al hijo izq ya que no es una solución posible
                    pq.push(dch);
                }
            }
        }
    }
    return -U;
}

/**
 * vector: Vector de peticiones ordenado por número de pasajeros / distancia del trayecto
 * capacidad_total: Capacidad total del tren
 * n_paradas: Número total de estaciones
 * f: Fichero de salida para escribir el resultado obtenido
 * fuerzaBruta: Indica si utilizar el algoritmo de ramificación y poda o de fuerza bruta para calcular la solución
 * Crea el nodo raíz y calcula sus funciones de cota y de poda, y resuelve el problema, calculando
 * el tiempo de ejecución del algoritmo que resuelve el problema y escribiendo en el fichero de salida
 * f el beneficio máximo obtenido y el tiempo de ejecución en segundos.
 */
void calcular_solucion(vector<Peticion> *vector, int capacidad_total, int n_paradas, ofstream &f, bool fuerzaBruta)
{
    clock_t t_start = clock();
    int ben = 0;
    if (vector->size() > 0)
    {
        //Crear el nodo raíz
        NodoPeticion ap(-1, vector->size(), n_paradas);
        //Cálculo de la función de poda del nodo
        ap.setEstimacion(funcion_poda(vector, 0, capacidad_total, ap.getDescartados(), ap.getCapacidad()));
        //Cálculo de la función de cota del nodo
        ap.setCoste(funcion_cota(vector, 0, capacidad_total, ap.getDescartados(), ap.getCapacidad()));
        //Ejecución del algoritmo y obtención del resultado
        ben = ramificacion_poda(ap, capacidad_total, vector, n_paradas, fuerzaBruta);
    }
    clock_t t_end = clock();
    //Escribir en el fichero de salida los resultados obtenidos
    f << ben << " " << (double)(t_end - t_start) / CLOCKS_PER_SEC << endl;
}

/**
 * Ejecuta el comando transporte. El primer parámetro corresponde al fichero de entrada
 * donde se obtienen los datos del problema, el segundo parámetro corresponde al fichero
 * generado con los resultados obtenidos del mismo.
 */
int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        bool fuerzaBruta = argc == 4 && string(argv[3]) == "-fb";
        ifstream f_entrada;
        ofstream f_salida;
        f_entrada.open(string(argv[1]));
        if (f_entrada.is_open())
        {
            f_salida.open(string(argv[2]));
            vector<Peticion> *v = new vector<Peticion>();
            int capacidad_tren, n_paradas;
            //Al obtener los datos, v contendrá las peticiones, capacidad_tren,
            //la capacidad total y n_paradas el número de estaciones total
            while (obtenerDatos(f_entrada, v, capacidad_tren, n_paradas))
            {
                //Ordenar las peticiones según número_pasajeros/distancia del trayecto
                sort(v->begin(), v->end());
                calcular_solucion(v, capacidad_tren, n_paradas, f_salida, fuerzaBruta);
                //Borrar el vector de peticiones para incluir las nuevas
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
        cerr << "Numero de argumentos incorrecto: transporte <nombre_fichero_entrada> <nombre_fichero_salida> [-fb]" << endl;
    }
}