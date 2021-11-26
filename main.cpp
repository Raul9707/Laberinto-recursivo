#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <time.h>
#include <vector>


using namespace std;

const int filas = 14, columnas = 14, cardinalLength = 4, prioridadLength = 3, segundo = 1;
const int filaInicial1= 2, columnaInicial1=2,filaInicial2 = 11, columnaInicial2 = 11;
const int prioridad[3] = {-6,-5,-4};
int puntaje1=0,puntaje2=0;
mutex m;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

struct nodo{
    int info;
    int priority;
};
typedef struct nodo* Casilla;

struct nodo* crearNodo(int informacion, int prioridad)
{
    struct nodo* aux = new struct nodo();
    aux->info = informacion;
    aux->priority = prioridad;
    return aux;
}

Casilla tablero[filas][columnas]={
  {crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(0,-6),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(0,-6),crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo('@',-6),crearNodo(-1,-1),crearNodo(20,-6),crearNodo(-1,-1),crearNodo('D',-6),crearNodo(10,-6),crearNodo('@',-6),crearNodo('@',-6),crearNodo('@',-6),crearNodo(-3,-6),crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(10,-6),crearNodo(-1,-1),crearNodo('@',-6),crearNodo(-1,-1),crearNodo('@',-6),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo('@',-6),crearNodo('@',-6),crearNodo(50,-6), crearNodo(-1,-1),crearNodo('@',-6),crearNodo(-1,-1), crearNodo(-2,-6), crearNodo('@',-6), crearNodo(50,-6), crearNodo('C',-6), crearNodo(0,-6),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(10,-6),crearNodo(-1,-1),crearNodo('C',-6), crearNodo(-1,-1),crearNodo(-2,-6),crearNodo(-1,-1), crearNodo(-1,-1), crearNodo('@',-6), crearNodo(-1,-1), crearNodo(-1,-1), crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo('D',-6),crearNodo(-1,-1),crearNodo('@',-6), crearNodo(-1,-1),crearNodo('@',-6),crearNodo('@',-6), crearNodo(-1,-6), crearNodo(10,-6), crearNodo('@',-6), crearNodo('@',-6), crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-3,-6), crearNodo(-1,-1),crearNodo('@',-6),crearNodo('C',-6), crearNodo('@',-6), crearNodo(10,-6), crearNodo(-1,-1), crearNodo('@',-6), crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(0,-6),crearNodo('D',-6),crearNodo(10,-6),crearNodo('@',-6), crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1), crearNodo(-1,-1), crearNodo(40,-6), crearNodo(-1,-1), crearNodo('@',-6), crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo('@',-6), crearNodo('@',-6),crearNodo('@',-6),crearNodo(-1,-1), crearNodo('C',-6), crearNodo('@',-6), crearNodo(-1,-1), crearNodo('@',-6), crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(10,-6),crearNodo('@',-6),crearNodo('@',-6), crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1), crearNodo('@',-6), crearNodo(-1,-1), crearNodo(-1,-1), crearNodo('D',-6), crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(50,-6),crearNodo(-1,-1),crearNodo('@',-6),crearNodo('@',-6),crearNodo(10,-6),crearNodo(10,-6),crearNodo(50,-6),crearNodo('@',-6),crearNodo(-2,-6),crearNodo('@',-6),crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(-1,-1),crearNodo(20,-6),crearNodo(10,-6),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(-1,-1),crearNodo(9,0)},

  {crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0),crearNodo(9,0)}};

void ImprimirTablero(){

    /*BLACK 0, BLUE 1, GREEN 2, CYAN 3, RED 4, MAGENTA 5,
	BROWN 6, LIGHT GREY 7, DARK GREY 8, LIGHT BLUE 9,
        LIGHT GREEN 10, LIGHT CYAN 11, LIGHT RED 12,
	LIGHT MAGENTA 13, YELLOW 14, WHITE 15, */
// blockea el tablero en orden de quien llega
        m.lock();
        system("cls");
        for(int i = 0; i < filas; i ++){
        for(int j = 0; j < columnas; j++){
        if(tablero[i][j]->info >= 60){
            SetConsoleTextAttribute(h,11);
            cout << (char)tablero[i][j]->info << "\t";
        }
        else{
        if(tablero[i][j]->info >= 10 && tablero[i][j]->info <=50){
            SetConsoleTextAttribute(h,3);
        }
        switch(tablero[i][j]->info){
        case 9:
            SetConsoleTextAttribute(h,5);
            break;
        case 3:
            SetConsoleTextAttribute(h,2);
        case 2:
            SetConsoleTextAttribute(h,14);
        case 1:
            SetConsoleTextAttribute(h,14);
            break;
        case 0:
            SetConsoleTextAttribute(h,15);
            break;
        case -1:
            SetConsoleTextAttribute(h,4);
            break;
        case -2:
            SetConsoleTextAttribute(h,1);
            break;
        case -3:
            SetConsoleTextAttribute(h,7);
        }
         cout << tablero[i][j]->info << "\t";
        }
      }
        cout << endl;
    }
    SetConsoleTextAttribute(h,15);
    m.unlock();
}


void Priorizador(int cardinales[],int posicionActual,int prioridadActual,vector<char> &resultado){

            if((posicionActual == cardinalLength && resultado.size() > 0) || (posicionActual == cardinalLength && prioridadActual == 3)){
            return ;
        }
        else if(posicionActual == cardinalLength && resultado.size() == 0){
            Priorizador(cardinales,posicionActual=0,prioridadActual+1,resultado);
            return;
        }

        if(cardinales[posicionActual] == prioridad[prioridadActual]){
            switch(posicionActual){
            case 0:
                //arriba
                resultado.push_back('U');
                break;
            case 1:
                //abajo
                resultado.push_back('D');
                break;
            case 2:
                //derecha
                resultado.push_back('R');
                break;
            case 3:
                //izquierda
                resultado.push_back('L');
                break;
            }
        }
        Priorizador(cardinales,posicionActual+1,prioridadActual,resultado);
}


char Seleccionador(int cardinales[],int posicionActual,int prioridadActual,vector<char> &resultado){
    resultado.clear();
    Priorizador(cardinales,posicionActual,prioridadActual,resultado);
    srand(time(0));

    if(resultado.size() == 0){
        return 'N';
    }
    cout << endl;
    return resultado[rand() % resultado.size()];
}

void SistemaCardinal(int arriba,int abajo,int derecha,int izquierda,int cardinales[],int posicionActual){
        if(posicionActual == cardinalLength){

            return;
        }
        switch(posicionActual){
        case 0:
            cardinales[posicionActual] = arriba;
            break;
        case 1:
            cardinales[posicionActual] = abajo;
            break;
        case 2:
            cardinales[posicionActual] = derecha;
            break;
        case 3:
            cardinales[posicionActual] = izquierda;
            break;
        }
        SistemaCardinal(arriba,abajo,derecha,izquierda,cardinales,posicionActual+1);
}

void SistemaPisadas(Casilla &arriba,Casilla &abajo,Casilla &derecha,Casilla &izquierda){

    if(arriba->priority == -4){
       arriba->priority = -5;
    }
    else if(abajo->priority == -4){
       abajo->priority = -5;
    }
    else if(derecha->priority == -4){
       derecha->priority = -5;
    }
    else if(izquierda->priority == -4){
       izquierda->priority = -5;
    }

}

int MovimientoRecursivo(int &filaActual,int &columnaActual, int &posicionActual,int &prioridadActual,int &ID_Player,int cardinales[],vector<char> &resultado, int &valorAntiguo){
//int i;

    valorAntiguo = tablero[filaActual][columnaActual]->info;
    if(tablero[filaActual][columnaActual]->info != -3){
    tablero[filaActual][columnaActual]->info = ID_Player;
    tablero[filaActual][columnaActual]->priority = -4;
    }
    else{
        tablero[filaActual][columnaActual]->info = '@';
    }

    if(valorAntiguo >= 10 && valorAntiguo <= 50){
        if(ID_Player == 1)puntaje1 += valorAntiguo;
        else if(ID_Player == 2) puntaje2 += valorAntiguo;
    }
    switch(valorAntiguo){
        case -3:
            if(ID_Player == 1){
                filaActual = filaInicial1; columnaActual = columnaInicial1;
            }
            else if(ID_Player == 2){
                filaActual = filaInicial2; columnaActual = columnaInicial2;
            }
            return MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player,cardinales,resultado,valorAntiguo);
        break;
        case 67:
            if(ID_Player == 1){
                puntaje1 = 0;
            }
            else if(ID_Player == 2){
                puntaje2 = 0;
            }
            break;
        case 68:
            if(ID_Player == 1){
                puntaje1 *= 2;
            }
            else if(ID_Player == 2){
                puntaje2 *= 2;
            }

            break;
    }

    ImprimirTablero();
    cout << "Puntaje jugador nro 1: " << puntaje1 << endl;
    cout << "Puntaje jugador nro 2: " << puntaje2 << endl;
    //detiene los  threads unos cuantos segundos
    if(valorAntiguo == -2) this_thread::sleep_for(chrono::milliseconds(segundo * 4000));
    else if(valorAntiguo == 0) return 0;
    else this_thread::sleep_for(chrono::milliseconds(segundo * 1000));
    system("cls");

    SistemaCardinal(tablero[filaActual-1][columnaActual]->priority,tablero[filaActual+1][columnaActual]->priority,
                   tablero[filaActual][columnaActual+1]->priority,tablero[filaActual][columnaActual-1]->priority,
                   cardinales,posicionActual);
    resultado.push_back(Seleccionador(cardinales,posicionActual,prioridadActual,resultado));
    tablero[filaActual][columnaActual]->info = '@';
     SistemaPisadas(tablero[filaActual-1][columnaActual],tablero[filaActual+1][columnaActual],tablero[filaActual][columnaActual+1],tablero[filaActual][columnaActual-1]);
        switch(resultado[resultado.size()-1]){
        case 'U':
            filaActual --;
            return MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player,cardinales,resultado,valorAntiguo);
            break;
        case 'D':
            filaActual ++;
            return MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player,cardinales,resultado,valorAntiguo);
            break;
        case 'R':
            columnaActual ++;
            return MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player,cardinales,resultado,valorAntiguo);
            break;
        case 'L':
            columnaActual --;
            return MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player,cardinales,resultado,valorAntiguo);
            break;
        }

}



void Player1(){

    int filaActual= filaInicial1,columnaActual = columnaInicial1,posicionActual = 0,prioridadActual = 0, ID_Player1=1, valorAntiguo1 = 0;
    int cardinales[4];
    vector<char> resultado;
    MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player1,cardinales,resultado,valorAntiguo1);

}


void Player2(){

    int filaActual= filaInicial2,columnaActual = columnaInicial2,posicionActual = 0,prioridadActual = 0,ID_Player2=2, valorAntiguo2 = 0;
    int cardinales[4];
    vector<char> resultado;
    MovimientoRecursivo(filaActual,columnaActual,posicionActual,prioridadActual,ID_Player2,cardinales,resultado,valorAntiguo2);

}



int main()
{
    // comienza los threads
    thread player1(Player1);
    thread player2(Player2);
    // Finalizan los threads
    player1.join();
    player2.join();

    return 0;
}
