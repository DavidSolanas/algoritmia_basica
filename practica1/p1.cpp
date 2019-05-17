#include <iostream>
#include <fstream>
#include "Monticulo_arboles.h"
#include <bitset>
#include <cstring>

using namespace std;

/**
 * Devuelve el tamaño del fichero f en Bytes.
 */
int tamanno_fichero(ifstream& f)
{
    f.clear();
    f.seekg (0, f.end);
    int tam = f.tellg();
    f.seekg (0, f.beg);
    return tam;
}

/**
 * Lee el contenido del vector de caracteres y almacena
 * en el vector frecuencias el número de apariciones de 
 * cada carácter en dicho vector. La posición de un carácter
 * en el vector frecuencias vendrá determinado por su código ASCII
 */
void calcular_frecuencias(unsigned char *datos, unsigned int *frecuencias, int n)
{
    for (int i = 0; i < n; i++)
    {
        frecuencias[datos[i]]++;
    }
    cout << "FRECUENCIAS"<<endl;
    for (int i = 0; i< 256; i++){
        if (frecuencias[i]>0){
            cout << i << ": "<<frecuencias[i]<<endl;
        }
    }
}

void inicializar_monticulo (Monticulo_arboles* monticulo, unsigned int* frecuencias){
    for (int i = 0; i<256; i++){
        if (frecuencias[i] != 0){
            monticulo->insertar(new Arbol_caracteres(i, frecuencias[i]));
        }
    }
}

Arbol_caracteres* huffman (unsigned int* frecuencias){
    Monticulo_arboles* monticulo = new Monticulo_arboles();
    inicializar_monticulo (monticulo, frecuencias);
    if (monticulo->terminado()){
        Arbol_caracteres* a = monticulo->borrar_primero();
        monticulo->insertar(new Arbol_caracteres(a));
    }
    cout <<"holaaa"<<endl;
    if (monticulo->vacio()){
        return nullptr;
    }
    else{
        while (!monticulo->terminado()){
            Arbol_caracteres* a = monticulo->borrar_primero();
            Arbol_caracteres* b = monticulo->borrar_primero();
            monticulo->insertar(new Arbol_caracteres(a, b));
        }
        return monticulo->borrar_primero();
    }
}
//SI ES UN ARBOL DE UN SOLO COMPONENTE NO TIENE POR QUE PETAR
void clacular_codigos (Arbol_caracteres* a, string codigos[], string cadena){
    if (a!=nullptr){
        cout<<"Calculando codigos..."<<endl;
        if (a->getIzq()==nullptr){
            cout <<"hoja: "<<a->getCaracter()<<endl;
            codigos[a->getCaracter()] = cadena;
        }
        else if (a->getDer() == nullptr){
            cout <<"entramos aqui no?"<<endl;
            //Caso en el que el árbol está compuesto por solo una letra (un nodo y una hoja)
            clacular_codigos(a->getIzq(), codigos, cadena + '0');
        }
        else{
            clacular_codigos(a->getIzq(), codigos, cadena + '0');
            clacular_codigos(a->getDer(), codigos, cadena + '1');
        }
    }
}

uint8_t escribir_codigo (unsigned char* contenido, int tam, string codigos[], 
                            ofstream & f_salida){
    //debug
    ofstream debug;
    debug.open("c_codigos");
    string codigo = "";
    cout <<"A PARTIR DE AQUI"<<endl;
    cout <<"tam:"<<tam<<endl;
    for (int i = 0; i<tam; i++){
        codigo += codigos[contenido[i]];
        //cout << "codigo: "<<codigo<<endl;
        if (codigo.length() >= 8){
            char byte;
            for (int j = 0; j<8; j++){
                if(codigo[8-j-1] == '0'){
                    byte &= ~(1 << j);
                }
                else{
                    byte |= 1 << j;
                }
            }
            f_salida.write(&byte, sizeof(byte));
            //cout << bitset<8> (byte)<<endl;
            debug << bitset<8> (byte) << endl;
            codigo = codigo.substr(8);
        }
    }
    uint8_t resto = 0;
    if (codigo.length()>0){
        cout<<"tendriamos que entrar aqui"<<endl;
        char byte=0;
        for (int j = 0; j<codigo.length(); j++){
            if(codigo[j] == '0'){
                byte &= ~(1 << 8-j-1);
            }
            else{
                byte |= 1 << 8-j-1;
            }
        }
        f_salida.write(&byte, sizeof(byte));
        //cout<<bitset<8>(byte)<<endl;
        debug<<bitset<8>(byte)<<endl;
        resto = codigo.length();
    }
    cout<<(int)resto<<endl;
    debug<<(int)resto<<endl;
    return resto;
}

//if num_nodos = 0,1,2
Arbol_caracteres* leer_arbol (ifstream& f, unsigned int num_nodos){
    Arbol_caracteres* arboles = (Arbol_caracteres *)malloc(num_nodos*sizeof(Arbol_caracteres));
    unsigned char car;
    bool esHoja[num_nodos];
    queue<Arbol_caracteres*>* cola = new queue<Arbol_caracteres*>;
    for (int i = 0; i<num_nodos; i++){
        f.read(reinterpret_cast<char*>(&car), sizeof(unsigned char));
        f.read(reinterpret_cast<char*>(&esHoja[i]), sizeof(bool));
        arboles[i].setCaracter(car);
        cola->push(&arboles[i]);
    }
    cola->pop();
    for (int i = 0; i<num_nodos; i++){
        if (!cola->empty() && !esHoja[i]){
            arboles[i].setIzq(cola->front());
            cola->pop();
            if (!cola->empty()){
                arboles[i].setDer(cola->front());
                cola->pop();
            }
            else{
                arboles[i].setDer(nullptr);
            }
        }
        else{
            arboles[i].setIzq(nullptr);
            arboles[i].setDer(nullptr);
        }
    }
    return arboles;
}

unsigned char* descifrar (Arbol_caracteres* arbol, unsigned char* codigo, int n, 
                    uint8_t bits_extra, int tam_original){
    
    ofstream debug;
    debug.open ("d_codigos");
    Arbol_caracteres* aux = arbol;
    aux->escribir_arbol();
    unsigned char* texto = (unsigned char*) malloc(tam_original);
    int k = 0;
    for (int i = 0; i<n-1; i++){
        char c = codigo[i];
        cout <<bitset<8>(c)<<endl;
        debug <<bitset<8>(c)<<endl;
        for (int j = 7; j>=0; j--){
            if((c >> j) & 1){
                aux=aux->getDer();
            }
            else{
                aux=aux->getIzq();
            }
            if (aux->getIzq()==nullptr){
                texto[k++]=aux->getCaracter();
                aux=arbol;
            }
        }
    }
    char c = codigo[n-1];
    cout << bitset<8> (c)<<endl;
    debug <<bitset<8>(c)<<endl;
    cout << (int)bits_extra<<endl;
    debug << (int)bits_extra<<endl;
    cout << texto<<endl;
    for (int j = 7; j>7-bits_extra; j--){
        if((c >> j) & 1){
            aux=aux->getDer();
        }
        else{
            aux=aux->getIzq();
        }
        if (aux->getIzq()==nullptr){
            texto[k++]=aux->getCaracter();
            aux=arbol;
        }
    }    
    cout << texto <<endl;
    return texto;
}

void comprimir(char* nom_fichero){
        ifstream f_entrada;
        f_entrada.open(nom_fichero, ios::binary);
        int tam = tamanno_fichero(f_entrada);
        unsigned char *contenido = (unsigned char *)malloc(tam);
        f_entrada.read((char*)contenido, tam);
        f_entrada.close();
        // Creación del array e inicialización a 0
        unsigned int frecuencias[256] = {0};
        calcular_frecuencias(contenido, frecuencias, tam);
        cout <<"hola1"<<endl;
        Arbol_caracteres* arbol = huffman(frecuencias);
        string codigos[256];
        cout <<"hola1"<<endl;
        clacular_codigos(arbol, codigos, "");
        for (int i = 0; i < 256; i++){
            if (codigos[i]!=""){
                cout<<i<<"->"<<codigos[i]<<endl;
            }
        }
        ofstream f_salida;
        f_salida.open(string(nom_fichero) + ".huf", ios::binary);
        //Espacio para el número de bits añadidos al final que no forman parte
        //de la cadena original y para el número de nodos del árbol
        f_salida.seekp(sizeof(uint8_t)+sizeof(unsigned int)+sizeof(int));
        cout <<"hola3"<<endl;
        unsigned int num_nodos = 0;
        if (arbol != nullptr){
            cout << "hay que entrar aquiiiiiii"<<endl;
            arbol->escribir_arbol();
            num_nodos = arbol->escribir_arbol_fichero(f_salida);
        }
        cout <<"hola4"<<endl;
        uint8_t bits_extra = escribir_codigo (contenido, tam, codigos, f_salida);
        cout <<"hola5"<<endl;
        f_salida.seekp(0);
        f_salida.write(reinterpret_cast<char*>(&bits_extra), sizeof(uint8_t));
        f_salida.write(reinterpret_cast<char*>(&num_nodos), sizeof(unsigned int));
        f_salida.write(reinterpret_cast<char*>(&tam), sizeof(int));
        f_salida.close();
}


void descomprimir (string nom_fichero){
    string nom_salida = nom_fichero.substr(0, nom_fichero.length()-4);
    ifstream f;
    f.open(nom_fichero, ios::binary);
    int tam = tamanno_fichero(f);
    uint8_t bits_extra;
    f.read(reinterpret_cast<char*>(&bits_extra), sizeof(uint8_t));
    unsigned int num_nodos;
    f.read(reinterpret_cast<char*>(&num_nodos), sizeof(unsigned int));
    int tam_original;
    f.read(reinterpret_cast<char*>(&tam_original), sizeof(int));
    Arbol_caracteres* arbol = leer_arbol (f, num_nodos);
    int location = f.tellg();
    unsigned char *codigo = (unsigned char *)malloc(tam-location);
    f.read((char*)codigo, tam-location);
    f.close();
    unsigned char* contenido = descifrar (arbol, codigo, tam-location, bits_extra, tam_original);
    ofstream f_salida;
    f_salida.open("hola", ios::binary);
    f_salida.write((char*)contenido, tam_original);
    //char* contenido_char = (char*)malloc(contenido.length()+1);
    //f_salida.write(reinterpret_cast<char*>(contenido_char), sizeof(contenido.length()));
    f_salida.close();
}

int main(int argc, char *argv[])
{
    if (argc > 2){
        if (string(argv[1])== "-c"){
            comprimir(argv[2]);
        }
        else if (string(argv[1])== "-d"){
            descomprimir(string(argv[2]));
        }
        else {
            cout << "Opcion invalida: huf [-c|-d] <nombre_fichero>"<<endl;
        }
    }
    else {
        cout << "Numero de argumentos incorrecto: huf [-c|-d] <nombre_fichero>"<<endl;
    }
}