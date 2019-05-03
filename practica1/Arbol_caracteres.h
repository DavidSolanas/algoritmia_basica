#include <iostream>

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
        cout << caracter<<": "<<frecuencia<<endl;
    }
}