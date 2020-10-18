#include <stdlib.h>
#include "Binario.h"
#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include <math.h>
#include "listaSimple.cpp"

using namespace std;
//Prototipo de Funciones
//Prototipos de Funciones
int PrioridadDP(string operador);
int PrioridadAP(string operador);
bool EsOperador(string cadena);
bool EsParentesis(string cadena);
int Operacion(string cadena);
void ArchivoTxT(string cadena, string cadena2);
//Definicion de Funciones

int MostrarPrioridadDP(string cadena){
    string Operadores[7]={"+","-","/","*","^","(",")"};
    int prioridades[7]={1,1,2,2,3,0,0};
    int indice=0;
    while(indice<=6){
        if(cadena==Operadores[indice]){
            break;
        }else{
            indice++;
        }
    }
    return prioridades[indice];
}

int MostrarPrioridadAP(string cadena){
    string Operadores[7]={"+","-","/","*","^","(",")"};
    int prioridades[7]={1,1,2,2,4,5,5};
    int indice=0;
    while(indice<=6){
        if(cadena==Operadores[indice]){
            break;
        }else{
            indice++;
        }
    }
    return prioridades[indice];
}

int Operacion(string cadena){
    string Operadores[5]={"+","-","/","*","^"};
    int valor[5]={1,2,3,4,5};
    int indice=0;
    while(indice<=4){
        if(cadena==Operadores[indice]){
            break;
        }else{
            indice++;
        }
    }
    return valor[indice];
}
bool EsOperador(string cadena){
    string operadores[7]={"+","-","^","(",")","*","/"};
    for (int i=0;i<=6;i++){
        if (cadena==operadores[i]){
            return true;
        }else{
        	continue;
		}
    }
    return false;
}

bool EsParentesis(string cadena){
	string operadores[2]={"(",")"};
    for (int i=0;i<=1;i++){
        if (cadena==operadores[i]){
            return true;
        }else{
        	continue;
		}
    }
    return false;
}

void ArchivoTxT(string cadena, string cadena2){
	ofstream archivo;
	int numero;
	archivo.open("Prioridades.txt", ios::app);
	if(archivo.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	archivo<<"Operación dentro de pila a comparar:    "<<cadena<<"    Valor del operador: "<< MostrarPrioridadDP(cadena)<<endl;
	archivo<<"Operación fuera de pila a comparar:    "<<cadena2<<"    Valor del operador: "<< MostrarPrioridadAP(cadena2)<<endl;
	if(MostrarPrioridadDP(cadena)< MostrarPrioridadAP(cadena2)){
		archivo<<"La prioridad fuera de la Pila es mayor que la prioridad dentro de la Pila"<<endl;
	}else{
		archivo<<"La prioridad fuera de la Pila es menor o igual a la prioridad dentro de la Pila"<<endl;
	}
	archivo<<endl;
}

void ConstruirArbol1(){
	lista pila;
	lista expresion;
	
	
}

int main(){
	
   return 0;
}

