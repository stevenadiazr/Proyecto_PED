#include "interfaz.h"
#include "Metodos_registro.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>

using namespace std;

/***********************************************************************************************************************/

//Inicializacion de variables globales
lista lista; 
int cont=0, turno=1, x, puntajex=0, puntaje0=0, contEmpate=0;
string user1, user2;

/***********************************************************************************************************************/

//Funcion Jugadores
//Esta funcion guarda las cadenas de caracteres en las variables creadas anteriormente
void Ventana:: Jugadores(){ 
    cout<<"Ingrese el nombre del jugador #1:\n";
    getline(cin, user1);
    cout<<"Ingrese el nombre del jugador #2:\n";
    getline(cin, user2);
    cout<<"Nombres almacenados de forma exitosa!"<<endl;
}

/***********************************************************************************************************************/

//Funcion Ventana
//Esta funcion se encarga de inicializar los punteros de SDL en nulo, ademas inicializa SDL 
Ventana::Ventana(){
    
    this->window=nullptr; 
    this->wSurface=nullptr;
    this->isRunning=true; 
    
    this->imagen1=nullptr;
    this->imagen2=nullptr;
    this->fondo=nullptr;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    this->window= SDL_CreateWindow("X-0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 510, 510, SDL_WINDOW_SHOWN);
}

/***********************************************************************************************************************/

// En esta funcion se encuentran los eventos de introduccionde nombres de usuario
//de top 10, ayuda o simplemente iniciar el juego
void Ventana::ventanaInicio(void){
    SDL_Event ev;
    this-> wSurface=SDL_GetWindowSurface(this->window);
   
    this->inicio=IMG_Load("Pantalla de inicio.jpg");
    colocarImagen(0, 0, inicio);
    
    
    while(this->isRunning==true)
    {
        while(SDL_PollEvent(&ev)!=0)
        {
            //EVENTO DE CIERRE DE VENTANA
            if (ev.type==SDL_QUIT)
            {
                this->isRunning=false;
            }
            //COSAS DE BOTON XD
            else if (ev.type==SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.button=SDL_BUTTON_LEFT)
                {
                    if (ev.button.y >= 340 && ev.button.x >= 340){
                        
                        //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                        Jugadores();
                        ventanaAviso();
                    }
                    else if (ev.button.x >= 190 && ev.button.y >= 340 && ev.button.x < 300){
//                        if (cont < 2){
                        //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                        system("gnome-open Aiuda.pdf");
                    }
                    else if (ev.button.x >= 0 && ev.button.y >= 340 && ev.button.x < 150){
                        //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                        lista.lectura();
                        lista.mostrar();
                        system("gnome-open arch.txt");

                    }
                }
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }
   
    
    SDL_DestroyWindow(this->window);
    this->window= NULL;
   

    correrJuego();
}

/***********************************************************************************************************************/

//Esta funcion carga las imagenes de tablero, x y 0 pero ademas contiene los eventos y condiciones necesarias
// para el funcionamiento correcto del juego
void Ventana::correrJuego() {

    SDL_Event ev;

    this-> wSurface = SDL_GetWindowSurface(this->window);

    this->fondo = IMG_Load("tablero.jpg");
    this->imagen1 = IMG_Load("0-tablero.png");
    this->imagen2 = IMG_Load("x-tablero.png");

    Ventana::colocarImagen(0, 0, fondo);

    SDL_UpdateWindowSurface(this->window);

    while (this->isRunning == true) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                this->isRunning = false;
            } else if (cont != 9) {
                if (ev.type == SDL_MOUSEBUTTONDOWN) {
                    if (ev.button.button = SDL_BUTTON_LEFT) {
                        //cout << "x: " << ev.button.x << endl << "y: " << ev.button.y << endl;
                        if (ev.button.x >= 0 && ev.button.y >= 0 && ev.button.x < 40 && ev.button.y < 45) {
                            //cout << "x" << ev.button.x << endl << "y" << ev.button.y << endl;
                            //cout << "Boton de reinicio" << endl;
                            llenarMatriz();
                            cont = 0;
                            turno = 1;
                            correrJuego();
                        } else if (ev.button.x >= 0 && ev.button.y >= 45 && ev.button.x < 40 && ev.button.y < 85) {
                            //cout << "x" << ev.button.x << endl << "y" << ev.button.y << endl;
                            //cout << "Boton de boton de menu" << endl;
                            llenarMatriz();
                            cont = 0;
                            turno = 1;
                            lista.escribir(user1, puntajex, user2, puntaje0);
                            ventanaInicio();
                            Jugadores();
                        } else if (this->M[ev.button.y / 170][ev.button.x / 170] == 4 && turno == 0) {
                            M[ev.button.y / 170][ev.button.x / 170] = 0;
                            Ventana::colocarImagen((ev.button.y / 170)*170, (ev.button.x / 170)*170, this->imagen1);
                            turno = 1;
                            cont++;
                            x = juegoGanado();
                            if (x == 1)
                                this->isRunning = false;
                        } else if (this->M[ev.button.y / 170][ev.button.x / 170] == 4 && turno == 1) {
                            Ventana::colocarImagen((ev.button.y / 170)*170, (ev.button.x / 170)*170, this->imagen2);
                            M[ev.button.y / 170][ev.button.x / 170] = 1;
                            turno = 0;
                            cont++;
                            x = juegoGanado();
                            if (x == 1)
                                this->isRunning = false;
                        }
                    }
                }
            } else {
                ventanaEmpate();
                cout << "Juego finalizado, empate." << endl;
                this->isRunning = false;
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }

    SDL_DestroyWindow(this->window);
    this->window = NULL;
    SDL_Quit();
}

/***********************************************************************************************************************/

//Esta funcion recibe 3 parametros : coordenada en x, coordenada en y y la imagen
void Ventana::colocarImagen(int x, int y, SDL_Surface*imagen){
    SDL_Rect destination;
    destination.x=y;
    destination.y=x;
    SDL_BlitSurface(imagen, NULL, this->wSurface, &destination);
}

/***********************************************************************************************************************/

//Esta funcion llena la matriz con el numero 4, este numero indica que esa casilla esta vacia
void Ventana::llenarMatriz(){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            M[i][j]=4;
        }
    }
}

/***********************************************************************************************************************/

//esta funcion revisa las posiciones necesarias para ganar  tanto en posicion diagonal vertical u horizontal
int Ventana::juegoGanado(){
    this-> wSurface=SDL_GetWindowSurface(this->window);

    //JUEGO EN DIAGONAL PARA EQUIS
    if (this->M[0][0] == 1 && this->M[1][1] == 1 && this->M[2][2] == 1 || this->M[0][2] == 1 && this->M[1][1] == 1 && this->M[2][0] == 1) {
        ventanaGanaX();
        return 1;
    }
    else
    {
        // TRES EQUIS EN FILA
        if (this->M[0][0] == 1 && this->M[0][1] == 1 && this->M[0][2] == 1 || this->M[1][0] == 1 && this->M[1][1] == 1 && this->M[1][2] == 1 || this->M[2][0] == 1 && this->M[2][1] == 1 && this->M[2][2] == 1) {
            ventanaGanaX();
            return 1;
        }
        else
        {
            //TRES EQUIS EN COLUMNA
            if (this->M[0][0] == 1 && this->M[1][0] == 1 && this->M[2][0] == 1 || this->M[0][1] == 1 && this->M[1][1] == 1 && this->M[2][1] == 1 ||this->M[0][2] == 1 && this->M[1][2] == 1 && this->M[2][2] == 1) 
            {
                ventanaGanaX();
                return 1;
            }
            else
            {
                //**********************************************************************************************************************************************************************************************************************************************************************
                //JUEGO EN DIAGONAL PARA CERO
                if (this->M[0][0] == 0 && this->M[1][1] == 0 && this->M[2][2] == 0 || this->M[0][2] == 0 && this->M[1][1] == 0 && this->M[2][0] == 0)
                {
                    ventanaGana0();
                    return 1;
                }
                else
                {
                    // TRES CEROS EN FILA
                    if (this->M[0][0] == 0 && this->M[0][1] == 0 && this->M[0][2] == 0 || this->M[1][0] == 0 && this->M[1][1] == 0 && this->M[1][2] == 0 || this->M[2][0] == 0 && this->M[2][1] == 0 && this->M[2][2] == 0)
                    {
                        ventanaGana0();
                        return 1;
                    }
                    else
                    {
                        //TRES CEROS EN COLUMNA
                        if (this->M[0][0] == 0 && this->M[1][0] == 0 && this->M[2][0] == 0 || this->M[0][1] == 0 && this->M[1][1] == 0 && this->M[2][1] == 0 ||this->M[0][2] == 0 && this->M[1][2] == 0 && this->M[2][2] == 0) 
                        {
                            ventanaGana0();
                            return 1;
                        }
                        else 
                        {
                            cout << "Jugada realizada" << endl;
                        }
                    }
                }
            }
        }
    }
}

/***********************************************************************************************************************/

// esta funcion recorre la matriz mostrando el contenido de cada casilla
void Ventana::mostrarMatriz(){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cout<<M[i][j]<<" ";
        }
    }
}

/***********************************************************************************************************************/

//esta ventana se dezpliega unicamente cuando la x resulta ganadora en una partida
//al ejecutarse suma un punto a las x
void Ventana::ventanaGanaX(){
    puntajex++;
    
    
    SDL_Event ev;
    
    this-> wSurface=SDL_GetWindowSurface(this->window);
    
    
    this->ganaX = IMG_Load("X-win.jpg");

    Ventana::colocarImagen(0 ,0 , ganaX);
   
    while(this->isRunning==true)
    {
        while(SDL_PollEvent(&ev)!=0)
        {
            //EVENTO DE CIERRE DE VENTANA
            if (ev.type==SDL_QUIT)
            {
                this->isRunning=false;
            }
            else
            {
                if (ev.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (ev.button.button=SDL_BUTTON_LEFT)
                    {
                       // cout <<"x: "<<ev.button.x << endl<<"y: "<< ev.button.y<<endl;
                        if (ev.button.x >= 425 && ev.button.y > 440)
                        {
                            if (puntajex >= 2)
                            {
                                ventanaResultados(puntajex, puntaje0, contEmpate);
                                lista.escribir(user1, puntajex, user2, puntaje0);
                            }
                            else
                            {
                                //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                                //cout << "Boton de reinicio" << endl;
                                llenarMatriz();
                                cont=0;
                                turno=1;
                                correrJuego();
                            }
                            
                        }
                        else if (ev.button.x >= 350 && ev.button.y > 440 && ev.button.x < 425)
                        {
                            //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                            //cout << "Boton de boton de menu" << endl;
                            llenarMatriz();
                            cont=0;
                            turno=1;
                            ventanaResultados(puntajex, puntaje0, contEmpate);
                        }
                    }
                }
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }
   
    SDL_DestroyWindow(this->window);
    this->window= NULL;

}

/***********************************************************************************************************************/

//esta ventana se dezpliega unicamente cuando los 0 resultan ganadores en una partida
//al ejecutarse suma un punto a los 0
void Ventana::ventanaGana0(){
    
    puntaje0++;
    
    
    SDL_Event ev;
    
    this-> wSurface=SDL_GetWindowSurface(this->window);
    
    this->gana0 = IMG_Load("0-win.jpg");

    Ventana::colocarImagen(0 ,0 , gana0);
   
    while(this->isRunning==true)
    {
        while(SDL_PollEvent(&ev)!=0)
        {
            //EVENTO DE CIERRE DE VENTANA
            if (ev.type==SDL_QUIT)
            {
                this->isRunning=false;
            }
            else
            {
                if (ev.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (ev.button.button=SDL_BUTTON_LEFT)
                    {
                        //cout <<"x: "<<ev.button.x << endl<<"y: "<< ev.button.y<<endl;
                        if (ev.button.x >= 425 && ev.button.y > 440)
                        {
                            if (puntaje0 >= 2)
                            {
                                ventanaResultados(puntajex, puntaje0, contEmpate);
                                lista.escribir(user1, puntajex, user2, puntaje0);
                            }
                            else
                            {
                                //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                                //cout << "Boton de reinicio" << endl;
                                llenarMatriz();
                                cont=0;
                                turno=1;
                                correrJuego();
                            }
                        }
                        else if (ev.button.x >= 350 && ev.button.y > 440 && ev.button.x < 425)
                        {
                            //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                            //cout << "Boton de boton de menu" << endl;
                            llenarMatriz();
                            cont=0;
                            turno=1;
                            cout << puntaje0 << endl;
                            ventanaResultados(puntajex, puntaje0, contEmpate);
                        }
                    }
                }
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }
   
    SDL_DestroyWindow(this->window);
    this->window= NULL;
   
}

/***********************************************************************************************************************/

//esta ventana se dezpliega unicamente cuando nadie resulta ganador en una partida
//al ejecutarse suma un punto al contador de empate
void Ventana::ventanaEmpate(){
    contEmpate++;
    
    
    SDL_Event ev;
    
    this-> wSurface=SDL_GetWindowSurface(this->window);
    
    
    this->empate = IMG_Load("empate.jpg");

    Ventana::colocarImagen(0 ,0 , empate);
   
    while(this->isRunning==true)
    {
        while(SDL_PollEvent(&ev)!=0)
        {
            //EVENTO DE CIERRE DE VENTANA
            if (ev.type==SDL_QUIT)
            {
                this->isRunning=false;
            }
            else
            {
                if (ev.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (ev.button.button=SDL_BUTTON_LEFT)
                    {
                        //cout <<"x: "<<ev.button.x << endl<<"y: "<< ev.button.y<<endl;
                        if (contEmpate>=5){
                            ventanaResultados(puntajex, puntaje0, contEmpate);
                            lista.escribir(user1, puntajex, user2, puntaje0);
                        }
                        else if (ev.button.x >= 425 && ev.button.y > 440)
                        {
                            //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                            //cout << "Boton de reinicio" << endl;
                            llenarMatriz();
                            cont=0;
                            turno=1;
                            correrJuego();
                        }
                        else if (ev.button.x >= 350 && ev.button.y > 440 && ev.button.x < 425)
                        {
                            //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                            //cout << "Boton de boton de menu" << endl;
                            llenarMatriz();
                            cont=0;
                            turno=1;
                            ventanaResultados(puntajex, puntaje0, contEmpate);
                        }
                    }
                }
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }

    SDL_DestroyWindow(this->window);
    this->window= NULL;
   
}

/***********************************************************************************************************************/

//En esta ventana se crea un aviso que le indica a cada jugador la pieza con la que jugara
//En esta ventana solo existe un evento de click el cual permite pasar a la siguiente pantalla
void Ventana::ventanaAviso (void){
    SDL_Event ev;
    
    this-> wSurface=SDL_GetWindowSurface(this->window);
    
    this->aviso = IMG_Load("aviso.jpg");
    Ventana::colocarImagen(0 ,0 , aviso);
    
     while(this->isRunning==true)
    {
        while(SDL_PollEvent(&ev)!=0)
        {
            //EVENTO DE CIERRE DE VENTANA
            if (ev.type==SDL_QUIT)
            {
                this->isRunning=false;
            }
            else
            {
                if (ev.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (ev.button.button=SDL_BUTTON_LEFT)
                    {
                        //cout <<"x: "<<ev.button.x << endl<<"y: "<< ev.button.y<<endl;
                        if (ev.button.x >= 230 && ev.button.y > 310 && ev.button.x < 300 && ev.button.y < 380)
                        {
                            //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                            //cout << "Iniciando partida." << endl;
                            llenarMatriz();
                            cont=0;
                            turno=1;
                            puntajex=puntaje0=contEmpate=0;
                            correrJuego();
                        }
                    }
                }
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }

    SDL_DestroyWindow(this->window);
    this->window= NULL;
   
}

/***********************************************************************************************************************/

//En esta ventana se muestran los resultados finales del juego
// Esta funcion recibe como parametros el puntaje de las x, el puntaje de los 0 y el contador de empates
void Ventana::ventanaResultados (int puntajex, int puntaje0, int contEmpate){
    SDL_Event ev;
  
    this->resultados = IMG_Load("resultados.jpg");
    Ventana::colocarImagen(0 ,0 , resultados);
    
    // Seleccion de imagen para puntaje jugador 1 (x)
    
    this->pointx0=IMG_Load("0puntox.jpg");
    this->pointx1=IMG_Load("1puntox.jpg");
    this->pointx2=IMG_Load("2puntox.jpg");
    this->pointx3=IMG_Load("3puntox.jpg");
    this->pointx4=IMG_Load("4puntox.jpg");
    this->pointx5=IMG_Load("5puntox.jpg");
   
    
    switch (puntajex){
        case 0:
            Ventana::colocarImagen(100,0, pointx0);
            break;
        case 1:
            Ventana::colocarImagen(100,0, pointx1);
            break;
        case 2:
            Ventana::colocarImagen(100,0, pointx2);
            break;
        case 3:
            Ventana::colocarImagen(100,0, pointx3);
            break;
        case 4:
            Ventana::colocarImagen(100,0, pointx4);
            break;
        case 5:
            Ventana::colocarImagen(100,0, pointx5);
            break;
    }
    
    // Seleccion de imagen para puntaje jugador 2 (0)
    
    this->point00=IMG_Load("0punto0.jpg");
    this->point01=IMG_Load("1punto0.jpg");
    this->point02=IMG_Load("2punto0.jpg");
    this->point03=IMG_Load("3punto0.jpg");
    this->point04=IMG_Load("4punto0.jpg");
    this->point05=IMG_Load("5punto0.jpg");
    
    switch (puntaje0){
        case 0:
            Ventana::colocarImagen(200,0, point00);
            break;
        case 1:
            Ventana::colocarImagen(200,0, point01);
            break;
        case 2:
            Ventana::colocarImagen(200,0, point02);
            break;
        case 3:
            Ventana::colocarImagen(200,0, point03);
            break;
        case 4:
            Ventana::colocarImagen(200,0, point04);
            break;
        case 5:
            Ventana::colocarImagen(200,0, point05);
            break;
    }
    
    // Seleccion de imagen en caso de empate
    
    this->empate0=IMG_Load("empatenulo.jpg");
    this->empate1=IMG_Load("empate1.jpg");
    this->empate2=IMG_Load("empate2.jpg");
    this->empate3=IMG_Load("empate3.jpg");
    this->empate4=IMG_Load("empate4.jpg");
    this->empate5=IMG_Load("empate5.jpg");
    
    switch (contEmpate){
        case 0:
            Ventana::colocarImagen(300,0, empate0);
            break;
        case 1:
            Ventana::colocarImagen(300,0, empate1);
            break;
        case 2:
            Ventana::colocarImagen(300,0, empate2);
            break;
        case 3:
            Ventana::colocarImagen(300,0, empate3);
            break;
        case 4:
            Ventana::colocarImagen(300,0, empate4);
            break;
        case 5:
            Ventana::colocarImagen(300,0, empate5);
            break;
    }
    
     while(this->isRunning==true)
    {
        while(SDL_PollEvent(&ev)!=0)
        {
            //EVENTO DE CIERRE DE VENTANA
            if (ev.type==SDL_QUIT)
            {
                this->isRunning=false;
            }
            else
            {
                if (ev.type==SDL_MOUSEBUTTONDOWN)
                {
                    if (ev.button.button=SDL_BUTTON_LEFT)
                    {
                        //cout <<"x: "<<ev.button.x << endl<<"y: "<< ev.button.y<<endl;
                        if (ev.button.x >= 425 && ev.button.y > 440)
                        {
                            //cout<<"x"<<ev.button.x<<endl<<"y"<<ev.button.y<<endl;
                            //cout << "Boton de menu" << endl;
                            llenarMatriz();
                            cont=0;
                            turno=1;
                            
                            lista.escribir(user1, puntajex, user2, puntaje0);
                            puntajex=puntaje0=contEmpate=0;
                            ventanaInicio();
                            Jugadores();
                        }
                    }
                }
            }
        }
        SDL_UpdateWindowSurface(this->window);
    }

    SDL_DestroyWindow(this->window);
    this->window= NULL;

}

/***********************************************************************************************************************/
