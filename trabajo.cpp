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

bool movimientoLegal( Tablero& tablero, Pieza& pieza, int a_x, int a_y) { //es para verificar si el movimiento es legal
    return true;
};


bool piezaEnJaque( Tablero& tablero, Pieza& pieza){ //es para verificar si la pieza esta en jaque
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



bool tableroEnJaqueMate(Tablero& tablero){ //es para determinar si esta en jaque mate
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
}
