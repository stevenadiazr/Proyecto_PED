#include <cstdlib>
#include <iostream>
#include "interfaz.h"

using namespace std;

int main(int argc, char** argv) {
    
    Ventana v;
    
    v.llenarMatriz();
    
    v.ventanaInicio();
    
    v.mostrarMatriz();
    
    return 0;
}
