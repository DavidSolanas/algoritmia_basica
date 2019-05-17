#include <iostream>
#include <queue>
#include <bitset>

using namespace std;

class Arbol_caracteres
{
private:
    unsigned char caracter;
    unsigned int frecuencia;
    Arbol_caracteres* der;
    Arbol_caracteres* izq;
public:
    Arbol_caracteres(unsigned char a, unsigned int f);
    Arbol_caracteres(Arbol_caracteres* i, Arbol_caracteres* d);
    Arbol_caracteres(Arbol_caracteres* i);
    ~Arbol_caracteres();
    unsigned int getFrecuencia();
    unsigned char getCaracter();
    Arbol_caracteres* getIzq();
    Arbol_caracteres* getDer();
    void setCaracter (unsigned char c);
    void setFrecuencia (unsigned int f);
    void setDer (Arbol_caracteres* d);
    void setIzq (Arbol_caracteres* i);
    unsigned int escribir_arbol_fichero (ofstream& f);
    void escribir_arbol(); //debug
};

Arbol_caracteres::Arbol_caracteres(unsigned char a, unsigned int f)
{
    der=nullptr;
    izq=nullptr;
    caracter=a;
    frecuencia=f;
}

Arbol_caracteres::Arbol_caracteres(Arbol_caracteres* i, Arbol_caracteres* d){
    der=d;
    izq=i;
    caracter=0;
    frecuencia= d->frecuencia + i->frecuencia;
}

Arbol_caracteres::Arbol_caracteres(Arbol_caracteres* i){
    der=nullptr;
    izq=i;
    caracter=0;
    frecuencia= i->frecuencia;
}

Arbol_caracteres::~Arbol_caracteres()
{
    if (izq!=nullptr){
        delete(izq);
        delete(der);
    }
}

unsigned int Arbol_caracteres:: getFrecuencia(){
    return frecuencia;
}

unsigned char Arbol_caracteres:: getCaracter(){
    return caracter;
}

Arbol_caracteres* Arbol_caracteres::getIzq(){
    return izq;
}

Arbol_caracteres* Arbol_caracteres::getDer(){
    return der;
}

void Arbol_caracteres::setCaracter (unsigned char c){
    this->caracter=c;
}

void Arbol_caracteres::setFrecuencia (unsigned int f){
    this->frecuencia=f;
}

void Arbol_caracteres::setDer (Arbol_caracteres* d){
    this->der=d;
}
    
void Arbol_caracteres::setIzq (Arbol_caracteres* i){
    this->izq=i;
}

unsigned int Arbol_caracteres::escribir_arbol_fichero (ofstream& f){
    queue<Arbol_caracteres*>* cola = new queue<Arbol_caracteres*>();
    cola->push(this);
    unsigned int i = 0;
    while(!cola->empty()){
        Arbol_caracteres* a = cola->front();
        cola->pop();
        unsigned char caracter = a->getCaracter();
        bool esHoja = a->izq == nullptr;
        f.write(reinterpret_cast<char*>(&caracter), sizeof(unsigned char));
        f.write(reinterpret_cast<char*>(&esHoja), sizeof(bool));
        if (a->izq != nullptr){
            cola->push(a->getIzq());
        }
        if (a->der != nullptr){
            cola->push(a->getDer());
        }
        i++;
    }
    return i;
}

void Arbol_caracteres::escribir_arbol(){
    if (der!=nullptr && izq!=nullptr){
        der->escribir_arbol();
        izq->escribir_arbol();
    }
    else if (izq!=nullptr){
        izq->escribir_arbol();
    }
    else if (der!=nullptr){
        der->escribir_arbol();
    }
    else{
        cout << bitset<8>(caracter)<<": "<<frecuencia<<endl;
    }
}