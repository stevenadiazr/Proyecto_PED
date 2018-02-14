#ifndef METODOS_REGISTRO_H
#define METODOS_REGISTRO_H
#include "registro.h"
#include<iostream>
#include<cstdlib>
#include<string.h>
#include<fstream>
#include<string>

using namespace std;

//Cuerpos de la clase lista

/***********************************************************************************************************************/

//Inicializacion del constructor vacio
lista::lista(){
    this->pInicio = NULL;
}

/***********************************************************************************************************************/

//Esta funcion se encarga de verificar la existencia del archivo y de guardar los datos en dicho archivo
//De no encontrarse el archivo esta misma lo crea
void lista::escribir(string nombre, int score1, string nombre1, int score2){ // se los quitamos porque lo estamos pidiendo desde el teclado
    ofstream archivo;
    ofstream puntajes;
    //string nombre,nombre1;
    archivo.open("Registro.txt", ios::app);
    puntajes.open("puntajes.txt", ios::app);
    if (archivo.fail() && puntajes.fail()){
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    //Datos jugador 1
    archivo << nombre << endl;
    puntajes<< score1 << endl;
    
    //Datos jugador 2
    archivo << nombre1 << endl;
    puntajes<< score2 << endl;
    
    archivo.close();
    puntajes.close();
}

/***********************************************************************************************************************/

//Esta funcion se encarga de leer los archivos y convertir su contenido a entero para poder validar los datos
void lista::lectura(){ // aca no lleva parametros
    ifstream archivo;
    ifstream puntajes;
    string texto;
    string aux;
    int puntos;
    
    archivo.open("Registro.txt", ios::in);
    puntajes.open("puntajes.txt", ios::in);
    
    if (archivo.fail() && puntajes.fail()){
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    while (!archivo.eof() && !puntajes.eof()){
        getline(archivo, texto);
        getline(puntajes,aux);
        puntos = atoi(aux.c_str());
        //cout << "Nombre: " << texto << "  puntajes: "<<puntos <<endl;
        lista::validar(texto, puntos);
    }
    archivo.close();
    puntajes.close();
}

/***********************************************************************************************************************/

//Esta funcion se encarga de hacer las validaciones correspondientes e ingresar los datos a una estructura dinamica
void lista::validar(string texto, int puntos ){
    //string texto
    //int aux
    nodo *box= new nodo;
    box->texto = texto; // ACA LLAMAR A NOMBRE
    box->puntos = puntos;
	
    nodo *aux=this->pInicio;
    nodo *aux1;
	
    while (aux != NULL && aux->puntos < puntos){
        aux1 = aux;
        aux = aux->sig;
    }
    if (pInicio == aux){
        pInicio = box;
    }
    else {
        aux1->sig = box;
    }
    box->sig = aux;
}    

/***********************************************************************************************************************/

// Estas funciones se encargan de recorrer la lista y guardar los elementos correspondientes a nombre y puntaje dentro 
//de un nuevo archivo de texto
void lista::mostrar()
{
	lista::mostrar_recursivo(this->pInicio);
}
void lista::mostrar_recursivo(nodo *aux)
{
	if(aux)
	{
		lista::mostrar_recursivo(aux->sig);
		cout << "Nombre: "<<aux->texto<<" puntaje: "<<aux->puntos <<endl;
                ofstream archivos;
                archivos.open("arch.txt", ios::app);
                if (archivos.fail() ){
                    cout << "No se Pudo abrir el Archivo";
                    exit(1);   
            }
                archivos << "Nombre: " << aux->texto << ". Puntaje: ";
                archivos << aux->puntos << endl;;
                archivos.close();     
	}
}


#endif /* METODOS_REGISTRO_H */

