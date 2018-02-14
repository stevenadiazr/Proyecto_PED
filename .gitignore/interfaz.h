#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <iostream>
#include <cstring>
#include <string.h>
#include <SDL2/SDL_surface.h>


using namespace std;

class Ventana {
private:
    int M[3][3];
    bool isRunning; 
    //Variables para interfaz
    SDL_Window * window;
    SDL_Surface * wSurface;
    //Textos
    TTF_Font*fuente;
    //insercion de imagenes
    SDL_Surface*imagen1;
    SDL_Surface*imagen2;
    SDL_Surface*fondo;
    SDL_Surface*inicio;
    SDL_Surface*ganaX;
    SDL_Surface*gana0;
    SDL_Surface*empate;
    SDL_Surface*aviso;
    SDL_Surface*resultados;
    SDL_Surface*pointx0;
    SDL_Surface*pointx1;
    SDL_Surface*pointx2;
    SDL_Surface*pointx3;
    SDL_Surface*pointx4;
    SDL_Surface*pointx5;
    SDL_Surface*point00;
    SDL_Surface*point01;
    SDL_Surface*point02;
    SDL_Surface*point03;
    SDL_Surface*point04;
    SDL_Surface*point05;
    SDL_Surface*empate0;
    SDL_Surface*empate1;
    SDL_Surface*empate2;
    SDL_Surface*empate3;
    SDL_Surface*empate4;
    SDL_Surface*empate5;
public:
    Ventana();
    void ventanaInicio (void);
    void ventanaGanaX (void);
    void ventanaGana0 (void);
    void ventanaEmpate(void);
    void ventanaAviso (void);
    void ventanaResultados (int, int, int);
    void correrJuego();
    void llenarMatriz();
    void colocarImagen(int, int, SDL_Surface*);
    int juegoGanado(void);
    void Jugadores(void);
    void mostrarMatriz(void);
    
};



#endif /* INTERFAZ_H */

