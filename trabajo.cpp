#include <iostream>
#include<fstream>
#include<string>
using namespace std;

struct Pieza {
char simbolo; // Define qué tipo de pieza es y su caracter
int x, y; // Su posición dentro del tablero [0, 7] x [0, 7]
};

struct Tablero {
Pieza* piezas_tablero; // Lista de piezas que tiene el tablero
};

bool tableroEnJaqueMate(Tablero &tablero){ //es para determinar si esta en jaque mate
};


bool movimientoLegal( Tablero &tablero, Pieza& pieza, int nueva_x, int nuevo_y){ //es para verificar si el movimiento es legal
};


bool piezaEnJaque( Tablero &tablero, Pieza &pieza){ //es para verificar si la pieza esta en jaque
    for (int i = 0; i < 8; ++i) 
    {
        for (int j = 0; j < 8; ++j) 
        {
            if (tablero.piezas_tablero[i].x != pieza.x || tablero.piezas_tablero[i].y != pieza.y) // esta condicion se cumple si la pieza actual del
            { 
                                                                                                     // tablero no tiene las mismas coordenadas que la pieza
                                                                                                     // que se esta verificando y a su vez comprueba si la
                                                                                                     // pieza puede atacar a la pieza dada
                if (movimientoLegal(tablero, tablero.piezas_tablero[i], pieza.x, pieza.y)) {
                    return true; // retorna que la pieza esta en jaque
        }
      }
    }
  }
  return false; // retorna que la pieza no esta en jaque
};
        
int main () {

    int n = 0;

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

            n = stoi(linea);
            mitablero.piezas_tablero = new Pieza[n];
            

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

    Archivo.close();
    
    return 0;