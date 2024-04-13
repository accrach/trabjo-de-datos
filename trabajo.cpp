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

bool tableroEnJaqueMate(Tablero& tablero) {
    if (reyEnJaque(tablero)) {
        for (int i = 0; i < tablero.cantidad_de_piezas; ++i) {
            if (tablero.piezas_tablero[i].simbolo == 'X') {
                int reyX = tablero.piezas_tablero[i].x;
                int reyY = tablero.piezas_tablero[i].y;

                // Verificar movimientos legales del rey
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int a_x = reyX + dx;
                        int a_y = reyY + dy;
                        if (movimientoLegal(tablero, tablero.piezas_tablero[i], a_x, a_y)) {
                            // El rey tiene al menos un movimiento legal disponible, por lo que no está en jaque mate
                            return false;
                        }
                    }
                }

                // Si el rey no tiene movimientos legales disponibles, está en jaque mate
                return true;
            }
        }
    }
    return false; // Si el rey no está en jaque, no puede estar en jaque mate
}


        
int main () {

 Tablero mitablero;
    ifstream archivo;
    archivo.open("tablero.txt");

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1; // error
    }

    string linea;
    int num_linea = 0;
    int n = 0;

    while (getline(archivo, linea)) { // lee el archivo 
        if (num_linea == 0) {        // condcion para que la primera linea leea la cantida de piezas
            mitablero.cantidad_de_piezas = stoi(linea);
            mitablero.piezas_tablero = new Pieza[mitablero.cantidad_de_piezas];
        }
        else {
            int longitud_linea = linea.length();
            for (int i = 0; i < longitud_linea; i++) { //guarda la informacion de cada pieza
                if (linea[i] != '.') {
                    mitablero.piezas_tablero[n].simbolo = linea[i];
                    mitablero.piezas_tablero[n].x = num_linea - 1; // Fila
                    mitablero.piezas_tablero[n].y = i; // Columna
                    n++;
                }
            }
        }
        num_linea++;
    }
    
    if (tableroEnJaqueMate(mitablero)){ //esto en simple pregunta si esta en jaquemate si esque da verdareo dira que si 

        cout<<"SI";
        
    }

    else{
        cout<<"No";
    }

    cout<<endl;
    archivo.close();
    delete[] mitablero.piezas_tablero;

    
    return 0;
}
