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


bool piezaEnJaque( Tablero &tablero, Pieza &pieza){ //es para verificar si la pieza esta en jaque
    for (int i = 0; i < 8; ++i){ 
        for (int j = 0; j < 8; ++j){
            if (tablero.piezas_tablero[i].x != pieza.x || tablero.piezas_tablero[i].y != pieza.y){ // esta condicion se cumple si la pieza actual del
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
}



bool tableroEnJaqueMate(Tablero &tablero){ //es para determinar si esta en jaque mate
	for (int i=0; i<8; ++i){
		for(int j=0; j<8; ++j){
			if(tablero.piezas_tablero[i].simbolo == 'X'){ //Aqui busca al rey
				if(piezaEnJaque(tablero, tablero.piezas_tablero[i])){
					for (int x= -1; x <=1; ++x){
						for(int y=-1; y<=1; ++y){
							if (x != 0 || y != 0){
								int a_x = tablero.piezas_tablero[i].x + x;
								int a_y = tablero.piezas_tablero[i].y + y;
								if (movimientoLegal(tablero, tablero.piezas_tablero[i], a_x, a_y)){
									return false; // si retorna false, el rey tiene como minimo un movimiento legal por hacer
                                }
                            }
                        }
                    }
                    return true; // El rey esta en jaque-mate
                }
            }
        }
    }
    return false; // si no esta en jaque retorna false
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
