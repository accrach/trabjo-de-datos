#include <iostream>
#include<fstream>
#include<string>
using namespace std;

struct Pieza {
char simbolo; // Define qué tipo de pieza es y su caracter
int x, y; // Su posición dentro del tablero [0, 7] x [0, 7]
};

struct Tablero {
int cantidad_de_piezas; // catidad de piezas.
Pieza *piezas_tablero; // Lista de piezas que tiene el tablero
};

bool movimientoLegal(Tablero& tablero, Pieza& pieza, int a_x, int a_y) {
    if (a_x < 0 || a_x >= 8 || a_y < 0 || a_y >= 8) {
        return false; // El movimiento está fuera del rango del tablero
    }

    // PEÓN
    if (pieza.simbolo == 'P') {
        // El peón puede avanzar una casilla hacia adelante si no hay ninguna pieza en esa posición
        if (a_x == pieza.x && a_y == pieza.y + 1 && tablero.piezas_tablero[a_x + a_y * 8].simbolo == '.') {
            return true;
        }
        // El peón puede moverse diagonalmente para capturar una pieza enemiga
        if ((a_x == pieza.x + 1 || a_x == pieza.x - 1) && a_y == pieza.y + 1 && tablero.piezas_tablero[a_x + a_y * 8].simbolo != '.') {
            return true;
        }
    }

    // TORRE
    if (pieza.simbolo == 'T') {
        // La torre puede moverse horizontal o verticalmente, pero no diagonalmente
        if ((a_x == pieza.x || a_y == pieza.y) && a_x != pieza.x && a_y != pieza.y) {
            return true;
        }
    }

    // CABALLO
    if (pieza.simbolo == 'C') {
        // El caballo se mueve en forma de "L", dos casillas en una dirección y una casilla en la dirección perpendicular
        int dx = a_x - pieza.x;
        int dy = a_y - pieza.y;
        if ((dx == 2 || dx == -2) && (dy == 1 || dy == -1)) {
            return true;
        }
        if ((dx == 1 || dx == -1) && (dy == 2 || dy == -2)) {
            return true;
        }
    }

    // ALFIL
    if (pieza.simbolo == 'A') {
        // El alfil se mueve en diagonal, por lo que el cambio en x debe ser igual al cambio en y
        int dx = a_x - pieza.x;
        int dy = a_y - pieza.y;
        if (dx == dy || dx == -dy) {
            return true;
        }
    }

    // REINA
    if (pieza.simbolo == 'R') {
        // La reina puede moverse como una torre o un alfil
        if ((a_x == pieza.x || a_y == pieza.y) && a_x != pieza.x && a_y != pieza.y) {
            return true; // movimiento de torre
        }
        int dx = a_x - pieza.x;
        int dy = a_y - pieza.y;
        if (dx == dy || dx == -dy) {
            return true; // movimiento de alfil
        }
    }

    // REY Sebastian
    if (pieza.simbolo == 'K') {
        // El rey puede moverse una casilla en cualquier dirección
        int dx = a_x - pieza.x;
        int dy = a_y - pieza.y;
        if ((dx == 1 || dx == -1) && (dy == 1 || dy == -1)) {
            return true;
        }
        if ((dx == 0 || dy == 0) && (dx != 0 || dy != 0)) {
            return true;
        }
    }

    return false; // El movimiento es inválido para la pieza dada
}

bool reyEnJaque( Tablero &tablero){
    for (int i = 0; i< tablero.cantidad_de_piezas; ++i){
        if( tablero.piezas_tablero[i].simbolo == 'X'){ //busca al rey en el tablero
            int reyX = tablero.piezas_tablero[i].x;
            int reyY = tablero.piezas_tablero[i].y;
            for( int j=0; j< tablero.cantidad_de_piezas; ++j){
                if(tablero.piezas_tablero[j].simbolo != 'X' && movimientoLegal(tablero, tablero.piezas_tablero[j], reyX, reyY)){
                    return true;//retorna true si es que una pieza puede atacar al rey
                }
            }
            return false;//retorna false cuando ninguna pieza puede atacar al rey, por ende no hay jaque
        }
    }
    return false;
}

bool tableroEnJaqueMate(Tablero &tablero){ //es para determinar si esta en jaque mate
    if(reyEnJaque(tablero)){
        for (int i=0; i<tablero.cantidad_de_piezas; ++i){//recorre todas las piezas del tablero
            if( tablero.piezas_tablero[i].simbolo == 'X'){//busca al rey y verifica si tiene movimientos legales por hacer
                for( int dx= -1; dx<=1; ++dx){
                    for( int dy= -1; dy<=1; ++dy){
                        if(dx != 0 || dy != 0){
                            int a_x = tablero.piezas_tablero[i].x + dx;
                            int a_y = tablero.piezas_tablero[i].y + dy;
                            if( movimientoLegal(tablero, tablero.piezas_tablero[i], a_x, a_y)){
                                return false;//si el rey tiene un movimiento legal, ya no esta en jaque
                            }
                        }
                    }
                }
                return true;//si el rey no puede hacer un movimento legal para salir del jaque, esta en mate
            }
        }
    }
    return false;// si el rey no esat en jaque, no pude estar en jaquemate
}



        
int main () {

    ifstream Archivo; 
    Archivo.open("tablero.txt");

    if (!Archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    int contador = 0;
    Tablero mitablero;
    while (getline(Archivo, linea)) {

        if (contador == 0){

            mitablero.cantidad_de_piezas=stoi(linea);
            mitablero.piezas_tablero = new Pieza[mitablero.cantidad_de_piezas];
            
        }
        else{

            for (int i = 0; i < linea.length(); i++) {

                if (linea[i] != '.') {
                cout << linea[i];
                mitablero.piezas_tablero[contador-1].simbolo = linea[i];
                mitablero.piezas_tablero[contador-1].x = i;
                mitablero.piezas_tablero[contador-1].y = (contador - 1);

                }

           
            }
        }

        
        contador++;
    }
    if (tableroEnJaqueMate(mitablero)){ //esto en simple pregunta si esta en jaquemate si esque da verdareo dira que si 

        cout<<"SI";
        
    }

    else{
        cout<<"No";
    }

    cout<<endl;
    Archivo.close();
    delete[]mitablero.piezas_tablero;

    
    return 0;
}
