#include "Arbol_caracteres.h"


class Monticulo_arboles
{
private:
    int ultimo;
    Arbol_caracteres* vector[256];
    
public:
    Monticulo_arboles();
   // ~Monticulo_arboles();
    void insertar(Arbol_caracteres* a);
    Arbol_caracteres* borrar_primero();
    bool terminado();
    void escribir_monticulo(); //debug
    Arbol_caracteres* borrar_primero_v(); //debug
};

Monticulo_arboles::Monticulo_arboles()
{
    ultimo = -1;
    for (int i = 0; i<256; i++){
        vector[i]=nullptr;
    }
}

/*Monticulo_arboles::~Monticulo_arboles()
{
    for (int i=0; i<=ultimo; i++){
        delete(vector[i]);
    }
}*/

void Monticulo_arboles:: insertar(Arbol_caracteres* a){
    int i = ++ultimo;
    //cout<<"ultimo: "<< ultimo<<endl;
    while (i!=0 && vector [(i-1)/2] -> getFrecuencia() > a -> getFrecuencia()){
        vector[i] = vector [(i-1)/2];
        i=(i-1)/2;
    }
    vector[i] = a;
}

Arbol_caracteres* Monticulo_arboles::borrar_primero(){
    if (ultimo == -1){
        cout << "NOOOOOO TIENE QUE SALIR" << endl;
        return nullptr;
    }
    else{
        Arbol_caracteres* a = vector[0];
        //cout << "primero:"<<endl;
       // a->escribir_arbol();
        Arbol_caracteres* b = vector[ultimo--];
        //cout << "ultimo:"<<endl;
        //b->escribir_arbol();
        int i = 0;
        bool finalizar = false;
        while (ultimo >= 2*i +1 && !finalizar)
        {
            if (ultimo == 2*i + 1 && vector [ultimo]->getFrecuencia() < b->getFrecuencia()){
                vector[i] = vector[ultimo];
                i = ultimo;
            }
            else if (vector[2*i+1]->getFrecuencia() < vector[2*i+2]->getFrecuencia() && 
                        vector[2*i+1]->getFrecuencia() < b->getFrecuencia()){
                vector[i] = vector[2*i+1];
                i = 2*i+1;
            }
            else if (vector[2*i+2]->getFrecuencia() < b->getFrecuencia()){
                vector[i] = vector[2*i+2];
                i = 2*i+2;
            }
            else{
                finalizar = true;
            }
        }   
        vector[i]=b;     
        return a;
    }
}

bool Monticulo_arboles:: terminado(){
    return ultimo==0;
}

void Monticulo_arboles::escribir_monticulo(){
    for (int i = 0; i<=ultimo; i++){
        vector[i]->escribir_arbol();
    }
}

Arbol_caracteres* Monticulo_arboles::borrar_primero_v(){
    if (ultimo == -1){
        cout << "NOOOOOO TIENE QUE SALIR" << endl;
        return nullptr;
    }
    else{
        Arbol_caracteres* a = vector[0];
        cout << "primero:"<<endl;
        a->escribir_arbol();
        Arbol_caracteres* b = vector[ultimo--];
        cout << "ultimo:"<<endl;
        b->escribir_arbol();
        int i = 0;
        bool finalizar = false;
        cout << "valor ultimo: "<<ultimo<<endl;
        while (ultimo >= 2*i +1 && !finalizar)
        {
            cout << "Indice: " <<i << endl;
            if (i==86){
                if (vector[2*i+1]==nullptr){
                    cout<<"primero"<<endl;
                }
                else if (vector[2*i+2]==nullptr){
                    cout<<"segundo"<<endl;
                }
                else if (b==nullptr){
                    cout<<"tercero"<<endl;
                }
                else{
                    ultimo == 2*i + 1 && vector [ultimo]->getFrecuencia() < b->getFrecuencia();
                    cout<<"ninguno"<<endl;
                    cout<< vector[2*i+1]->getFrecuencia()<<endl;
                    cout<<"a"<<endl;
                    cout<<vector[2*i+2]->getFrecuencia()<<endl;
                    cout<<"b"<<endl;
                    cout<<b->getFrecuencia()<<endl;
                    cout<<"c"<<endl;
                    vector[2*i+1]->getFrecuencia() < vector[2*i+2]->getFrecuencia(); 
                    cout<<"d"<<endl;
                    vector[2*i+1]->getFrecuencia() < b->getFrecuencia();
                    cout<<"f"<<endl;
                    vector[2*i+1]->getFrecuencia() < vector[2*i+2]->getFrecuencia() && 
                    vector[2*i+1]->getFrecuencia() < b->getFrecuencia();
                    cout<<"ninguno"<<endl;
                    vector[2*i+2]->getFrecuencia() < b->getFrecuencia();
                    cout<<"ninguno"<<endl;


                }
            }
            if (ultimo == 2*i + 1 && vector [ultimo]->getFrecuencia() < b->getFrecuencia()){
                cout<<"primero"<<endl;
                vector[i] = vector[ultimo];
                i = ultimo;
            }
            else if (vector[2*i+1]->getFrecuencia() < vector[2*i+2]->getFrecuencia() && 
                        vector[2*i+1]->getFrecuencia() < b->getFrecuencia()){
                cout<<"segundo"<<endl;
                vector[i] = vector[2*i+1];
                i = 2*i+1;
            }
            else if (vector[2*i+2]->getFrecuencia() < b->getFrecuencia()){
                cout<<"tercero"<<endl;
                vector[i] = vector[2*i+2];
                i = 2*i+2;
            }
            else{
                finalizar = true;
            }
        }   
        cout << "salimos del bucle"<<endl;
        vector[i]=b;   
        cout << "fin de la funcion"<<endl;  
        return a;
    }
}