#ifndef REGISTRO_H
#define REGISTRO_H

#include<iostream>
#include<cstdlib>
#include<string.h>
#include<fstream>
#include<string>

using namespace std;

struct nodo{
    string texto;
    int puntos;
    nodo *sig;
};


class lista {
private:
    nodo *pInicio;
public:
    lista();
    void escribir(string, int, string, int);
    void lectura();
    void validar(string, int);
    //funcion para mostrar
    void mostrar();
    void mostrar_recursivo(nodo *);
};

#endif /* REGISTRO_H */

