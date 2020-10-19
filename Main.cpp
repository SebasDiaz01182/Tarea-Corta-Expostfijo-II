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
#include "listaSimple.hpp"
#include "NodoBinario.h"
#include "ListaSimplePostfijo.hpp"

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

void PreordenR(NodoBinario *R){
    
    if(R==NULL){
        return;
    }else{
        cout<<R->valor<<" -> ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InordenR(pnodo R){

    if(R==NULL){
        return;
    }else{
        InordenR(R->Hizq);
        cout<<R->valor<<" -> ";
        InordenR(R->Hder);
    }
}

void PostordenRec(pnodo R, listaP& postfijo){

    if(R==NULL){
        return;
    }else{
        PostordenRec(R->Hizq , postfijo);
        PostordenRec(R->Hder , postfijo);
        cout<<R->valor<<" -> ";
        postfijo.InsertarFinal(R->valor);
    }
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
	cout<<"Archivo#1"<<endl;
	cout<<"Expresion original: "<<endl;
	lista pila;
	lista expresion;
	ifstream archivo;
    string texto;
    ofstream archivoSalida;
    archivoSalida.open("Prioridades.txt", ios::app);
    if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	archivo.open("Arch1.txt",ios::in);
	archivoSalida<<"-----Archivo#1-----"<<endl;
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		cout<<texto;
    		if(EsOperador(texto)){
    			if(pila.ListaVacia()){
    				pnodo nuevo = new NodoBinario(texto);
    				pila.InsertarInicio(nuevo);
				}
				else{
					if(texto ==")"){
						
	    				int cont= 0;
	    				pnodoSimp recorrerP = pila.primero;
	    				while(recorrerP != NULL){
	    					if(EsParentesis(recorrerP->valor->valor)){
	    						cont++;
	    						break;
							}else{
								pnodo raiz = new NodoBinario(recorrerP->valor->valor);
			    				raiz->Hder = expresion.primero->valor;
			    				raiz->Hizq = expresion.primero->siguiente->valor;
			    				expresion.BorrarInicio();
			    				expresion.BorrarInicio();
			    				expresion.InsertarInicio(raiz);
								//AGREGAR A LA EXPRESION
								cont++;
								recorrerP= recorrerP->siguiente;
							}
						}while(cont!=0){
							pila.BorrarInicio();
							cont--;
						}
					}else{
						ArchivoTxT(pila.primero->valor->valor,texto);
						if(MostrarPrioridadDP(pila.primero->valor->valor)<MostrarPrioridadAP(texto)){
							pnodo nuevo = new NodoBinario(texto);
							pila.InsertarInicio(nuevo);
						}
						else{
							pnodo raiz = new NodoBinario(pila.primero->valor->valor);
							pila.BorrarInicio();
							raiz->Hder = expresion.primero->valor;
		    				raiz->Hizq = expresion.primero->siguiente->valor;
		    				expresion.BorrarInicio();
		    				expresion.BorrarInicio();
		    				expresion.InsertarInicio(raiz);
		    				pnodo nuevo = new NodoBinario(texto);
		    				pila.InsertarInicio(nuevo);
						}
					}
				}
			}
			else{
				//Si no es operador
				pnodo nuevo = new NodoBinario(texto);
				expresion.InsertarInicio(nuevo);
			}
		}
		if(!pila.ListaVacia()){
			pnodo raiz = new NodoBinario(pila.primero->valor->valor);
			pila.BorrarInicio();
			raiz->Hder = expresion.primero->valor;
			raiz->Hizq = expresion.primero->siguiente->valor;
			expresion.BorrarInicio();
			expresion.BorrarInicio();
			expresion.InsertarInicio(raiz);
			
			//--------------------------------------------------------------------------
		}
	
	}
	cout<<endl;
	cout<<"Inorden: "<<endl;
	InordenR(expresion.primero->valor);
	cout<<endl;
	cout<<"Preorden: "<<endl;
	PreordenR(expresion.primero->valor);
	cout<<endl;
	cout<<"Postorden: "<<endl;
	listaP post1;
	PostordenRec(expresion.primero->valor, post1);
	cout<<endl;
	listaP ListaNumeros;
    pnodoP punteroE=post1.primero;
    bool flag=false;    
    while (punteroE!=NULL){     
        if(EsOperador(punteroE->valor)){
            if(ListaNumeros.largoLista()>=3){
                flag=true;
            }else{
                flag=false;
            }
            float num1=atof((ListaNumeros.primero->siguiente->valor).c_str());
            float num2=atof((ListaNumeros.primero->valor).c_str());    //ListaNumeros=[]/ListaNumeros=[]
            int operacion=Operacion(punteroE->valor);
            switch (operacion){
                case 1:
                {
				float resultado=num1+num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
                if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
				}
                break;
                
                case 2:
                {
                float resultado=num1-num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
            	if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
                }
                break;
                
                case 3:
                {	
                if(num2==0){
                	cout<<"Evaluacion: "<<endl;
                    cout<<"Error, no se puede dividir por cero"<<endl;
                    goto division;
                    break;
                }else{
                    float resultado=num1/num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                    break;
                }
            	}
                case 4:
                {
                 float resultado =num1*num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                }
                
                break;
                
                case 5:
                {
                float resultado=pow(num1,num2);
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                     }
                    else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                }

                break;
            }
            
        }
        else{
            ListaNumeros.InsertarInicio(punteroE->valor);
            punteroE=punteroE->siguiente;
        }
    }
    cout<<"Evaluacion: "<<endl;
    ListaNumeros.Mostrar();
division:
	cout<<endl;	
}


void ConstruirArbol2(){
	cout<<endl;cout<<endl;
	cout<<"Archivo#2"<<endl;
	cout<<"Expresion original: "<<endl;
	lista pila;
	lista expresion;
	ifstream archivo;
    string texto;
    ofstream archivoSalida;
    archivoSalida.open("Prioridades.txt", ios::app);
    if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	archivo.open("Arch2.txt",ios::in);
	archivoSalida<<"-----Archivo#2-----"<<endl;
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		cout<<texto;
    		if(EsOperador(texto)){
    			if(pila.ListaVacia()){
    				pnodo nuevo = new NodoBinario(texto);
    				pila.InsertarInicio(nuevo);
				}
				else{
					if(texto ==")"){
						
	    				int cont= 0;
	    				pnodoSimp recorrerP = pila.primero;
	    				while(recorrerP != NULL){
	    					if(EsParentesis(recorrerP->valor->valor)){
	    						cont++;
	    						break;
							}else{
								pnodo raiz = new NodoBinario(recorrerP->valor->valor);
			    				raiz->Hder = expresion.primero->valor;
			    				raiz->Hizq = expresion.primero->siguiente->valor;
			    				expresion.BorrarInicio();
			    				expresion.BorrarInicio();
			    				expresion.InsertarInicio(raiz);
								//AGREGAR A LA EXPRESION
								cont++;
								recorrerP= recorrerP->siguiente;
							}
						}while(cont!=0){
							pila.BorrarInicio();
							cont--;
						}
					}else{
						ArchivoTxT(pila.primero->valor->valor,texto);
						if(MostrarPrioridadDP(pila.primero->valor->valor)<MostrarPrioridadAP(texto)){
							pnodo nuevo = new NodoBinario(texto);
							pila.InsertarInicio(nuevo);
						}
						else{
							pnodo raiz = new NodoBinario(pila.primero->valor->valor);
							pila.BorrarInicio();
							raiz->Hder = expresion.primero->valor;
		    				raiz->Hizq = expresion.primero->siguiente->valor;
		    				expresion.BorrarInicio();
		    				expresion.BorrarInicio();
		    				expresion.InsertarInicio(raiz);
		    				pnodo nuevo = new NodoBinario(texto);
		    				pila.InsertarInicio(nuevo);
						}
					}
				}
			}
			else{
				//Si no es operador
				pnodo nuevo = new NodoBinario(texto);
				expresion.InsertarInicio(nuevo);
			}
		}
		if(!pila.ListaVacia()){
			pnodo raiz = new NodoBinario(pila.primero->valor->valor);
			pila.BorrarInicio();
			raiz->Hder = expresion.primero->valor;
			raiz->Hizq = expresion.primero->siguiente->valor;
			expresion.BorrarInicio();
			expresion.BorrarInicio();
			expresion.InsertarInicio(raiz);
			
			//--------------------------------------------------------------------------
		}
	
	}
	cout<<endl;
	cout<<"Inorden: "<<endl;
	InordenR(expresion.primero->valor);
	cout<<endl;
	cout<<"Preorden: "<<endl;
	PreordenR(expresion.primero->valor);
	cout<<endl;
	listaP post2;
	cout<<"Postorden: "<<endl;
	PostordenRec(expresion.primero->valor, post2);
	cout<<endl;
	listaP ListaNumeros;
    pnodoP punteroE=post2.primero;
    bool flag=false;    
    while (punteroE!=NULL){     
        if(EsOperador(punteroE->valor)){
            if(ListaNumeros.largoLista()>=3){
                flag=true;
            }else{
                flag=false;
            }
            float num1=atof((ListaNumeros.primero->siguiente->valor).c_str());
            float num2=atof((ListaNumeros.primero->valor).c_str());    //ListaNumeros=[]/ListaNumeros=[]
            int operacion=Operacion(punteroE->valor);
            switch (operacion){
                case 1:
                {
				float resultado=num1+num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
                if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
				}
                break;
                
                case 2:
                {
                float resultado=num1-num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
            	if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
                }
                break;
                
                case 3:
                {	
                if(num2==0){
                	cout<<"Evaluacion: "<<endl;
                    cout<<"Error, no se puede dividir por cero"<<endl;
                    goto division;
                    break;
                }else{
                    float resultado=num1/num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                    break;
                }
            	}
                case 4:
                {
                 float resultado =num1*num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                }
                
                break;
                
                case 5:
                {
                float resultado=pow(num1,num2);
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                     }
                    else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                }

                break;
            }
            
        }
        else{
            ListaNumeros.InsertarInicio(punteroE->valor);
            punteroE=punteroE->siguiente;
        }
    }
    cout<<"Evaluacion: "<<endl;
    ListaNumeros.Mostrar();
division:
	cout<<endl;	
}

void ConstruirArbol3(){
	cout<<endl;cout<<endl;
	cout<<"Archivo#3"<<endl;
	cout<<"Expresion original: "<<endl;
	lista pila;
	lista expresion;
	ifstream archivo;
    string texto;
    ofstream archivoSalida;
    archivoSalida.open("Prioridades.txt", ios::app);
    if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	archivoSalida<<"-----Archivo#3-----"<<endl;
	archivo.open("Arch3.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		cout<<texto;
    		if(EsOperador(texto)){
    			if(pila.ListaVacia()){
    				pnodo nuevo = new NodoBinario(texto);
    				pila.InsertarInicio(nuevo);
				}
				else{
					if(texto ==")"){
						
	    				int cont= 0;
	    				pnodoSimp recorrerP = pila.primero;
	    				while(recorrerP != NULL){
	    					if(EsParentesis(recorrerP->valor->valor)){
	    						cont++;
	    						break;
							}else{
								pnodo raiz = new NodoBinario(recorrerP->valor->valor);
			    				raiz->Hder = expresion.primero->valor;
			    				raiz->Hizq = expresion.primero->siguiente->valor;
			    				expresion.BorrarInicio();
			    				expresion.BorrarInicio();
			    				expresion.InsertarInicio(raiz);
								//AGREGAR A LA EXPRESION
								cont++;
								recorrerP= recorrerP->siguiente;
							}
						}while(cont!=0){
							pila.BorrarInicio();
							cont--;
						}
					}else{
						ArchivoTxT(pila.primero->valor->valor,texto);
						if(MostrarPrioridadDP(pila.primero->valor->valor)<MostrarPrioridadAP(texto)){
							pnodo nuevo = new NodoBinario(texto);
							pila.InsertarInicio(nuevo);
						}
						else{
							pnodo raiz = new NodoBinario(pila.primero->valor->valor);
							pila.BorrarInicio();
							raiz->Hder = expresion.primero->valor;
		    				raiz->Hizq = expresion.primero->siguiente->valor;
		    				expresion.BorrarInicio();
		    				expresion.BorrarInicio();
		    				expresion.InsertarInicio(raiz);
		    				pnodo nuevo = new NodoBinario(texto);
		    				pila.InsertarInicio(nuevo);
						}
					}
				}
			}
			else{
				//Si no es operador
				pnodo nuevo = new NodoBinario(texto);
				expresion.InsertarInicio(nuevo);
			}
		}
		if(!pila.ListaVacia()){
			pnodo raiz = new NodoBinario(pila.primero->valor->valor);
			pila.BorrarInicio();
			raiz->Hder = expresion.primero->valor;
			raiz->Hizq = expresion.primero->siguiente->valor;
			expresion.BorrarInicio();
			expresion.BorrarInicio();
			expresion.InsertarInicio(raiz);
			
			//--------------------------------------------------------------------------
		}
	
	}
	cout<<endl;
	cout<<"Inorden: "<<endl;
	InordenR(expresion.primero->valor);
	cout<<endl;
	cout<<"Preorden: "<<endl;
	PreordenR(expresion.primero->valor);
	cout<<endl;
	listaP post3;
	cout<<"Postorden: "<<endl;
	PostordenRec(expresion.primero->valor, post3);
	cout<<endl;
	listaP ListaNumeros;
    pnodoP punteroE=post3.primero;
    bool flag=false;    
    while (punteroE!=NULL){     
        if(EsOperador(punteroE->valor)){
            if(ListaNumeros.largoLista()>=3){
                flag=true;
            }else{
                flag=false;
            }
            float num1=atof((ListaNumeros.primero->siguiente->valor).c_str());
            float num2=atof((ListaNumeros.primero->valor).c_str());    //ListaNumeros=[]/ListaNumeros=[]
            int operacion=Operacion(punteroE->valor);
            switch (operacion){
                case 1:
                {
				float resultado=num1+num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
                if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
				}
                break;
                
                case 2:
                {
                float resultado=num1-num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
            	if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
                }
                break;
                
                case 3:
                {	
                if(num2==0){
                	cout<<"Evaluacion: "<<endl;
                    cout<<"Error, no se puede dividir por cero"<<endl;
                    goto division;
                    break;
                }else{
                    float resultado=num1/num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                    break;
                }
            	}
                case 4:
                {
                 float resultado =num1*num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                }
                
                break;
                
                case 5:
                {
                float resultado=pow(num1,num2);
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                     }
                    else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                }

                break;
            }
            
        }
        else{
            ListaNumeros.InsertarInicio(punteroE->valor);
            punteroE=punteroE->siguiente;
        }
    }
    cout<<"Evaluacion: "<<endl;
    ListaNumeros.Mostrar();
division:
	cout<<endl;	
	
}

void ConstruirArbol4(){
	cout<<endl;cout<<endl;
	cout<<"Archivo#4"<<endl;
	cout<<"Expresion original: "<<endl;
	lista pila;
	lista expresion;
	ifstream archivo;
    string texto;
    ofstream archivoSalida;
    archivoSalida.open("Prioridades.txt", ios::app);
    if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}archivoSalida<<"-----Archivo#4-----"<<endl;
	archivo.open("Arch4.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		cout<<texto;
    		if(EsOperador(texto)){
    			if(pila.ListaVacia()){
    				pnodo nuevo = new NodoBinario(texto);
    				pila.InsertarInicio(nuevo);
				}
				else{
					if(texto ==")"){
						
	    				int cont= 0;
	    				pnodoSimp recorrerP = pila.primero;
	    				while(recorrerP != NULL){
	    					if(EsParentesis(recorrerP->valor->valor)){
	    						cont++;
	    						break;
							}else{
								pnodo raiz = new NodoBinario(recorrerP->valor->valor);
			    				raiz->Hder = expresion.primero->valor;
			    				raiz->Hizq = expresion.primero->siguiente->valor;
			    				expresion.BorrarInicio();
			    				expresion.BorrarInicio();
			    				expresion.InsertarInicio(raiz);
								//AGREGAR A LA EXPRESION
								cont++;
								recorrerP= recorrerP->siguiente;
							}
						}while(cont!=0){
							pila.BorrarInicio();
							cont--;
						}
					}else{
						ArchivoTxT(pila.primero->valor->valor,texto);
						if(MostrarPrioridadDP(pila.primero->valor->valor)<MostrarPrioridadAP(texto)){
							pnodo nuevo = new NodoBinario(texto);
							pila.InsertarInicio(nuevo);
						}
						else{
							pnodo raiz = new NodoBinario(pila.primero->valor->valor);
							pila.BorrarInicio();
							raiz->Hder = expresion.primero->valor;
		    				raiz->Hizq = expresion.primero->siguiente->valor;
		    				expresion.BorrarInicio();
		    				expresion.BorrarInicio();
		    				expresion.InsertarInicio(raiz);
		    				pnodo nuevo = new NodoBinario(texto);
		    				pila.InsertarInicio(nuevo);
						}
					}
				}
			}
			else{
				//Si no es operador
				pnodo nuevo = new NodoBinario(texto);
				expresion.InsertarInicio(nuevo);
			}
		}
		if(!pila.ListaVacia()){
			pnodo raiz = new NodoBinario(pila.primero->valor->valor);
			pila.BorrarInicio();
			raiz->Hder = expresion.primero->valor;
			raiz->Hizq = expresion.primero->siguiente->valor;
			expresion.BorrarInicio();
			expresion.BorrarInicio();
			expresion.InsertarInicio(raiz);
			
			//--------------------------------------------------------------------------
		}
	
	}
	cout<<endl;
	cout<<"Inorden: "<<endl;
	InordenR(expresion.primero->valor);
	cout<<endl;
	cout<<"Preorden: "<<endl;
	PreordenR(expresion.primero->valor);
	cout<<endl;
	listaP post4;
	cout<<"Postorden: "<<endl;
	PostordenRec(expresion.primero->valor, post4);
	cout<<endl;
	listaP ListaNumeros;
    pnodoP punteroE=post4.primero;
    bool flag=false;    
    while (punteroE!=NULL){     
        if(EsOperador(punteroE->valor)){
            if(ListaNumeros.largoLista()>=3){
                flag=true;
            }else{
                flag=false;
            }
            float num1=atof((ListaNumeros.primero->siguiente->valor).c_str());
            float num2=atof((ListaNumeros.primero->valor).c_str());    //ListaNumeros=[]/ListaNumeros=[]
            int operacion=Operacion(punteroE->valor);
            switch (operacion){
                case 1:
                {
				float resultado=num1+num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
                if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
				}
                break;
                
                case 2:
                {
                float resultado=num1-num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
            	if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
                }
                break;
                
                case 3:
                {	
                if(num2==0){
                	cout<<"Evaluacion: "<<endl;
                    cout<<"Error, no se puede dividir por cero"<<endl;
                    goto division;
                    break;
                }else{
                    float resultado=num1/num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                    break;
                }
            	}
                case 4:
                {
                 float resultado =num1*num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                }
                
                break;
                
                case 5:
                {
                float resultado=pow(num1,num2);
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                     }
                    else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                }

                break;
            }
            
        }
        else{
            ListaNumeros.InsertarInicio(punteroE->valor);
            punteroE=punteroE->siguiente;
        }
    }
    cout<<"Evaluacion: "<<endl;
    ListaNumeros.Mostrar();
division:
	cout<<endl;	
	
}

void ConstruirArbol5(){
	cout<<endl;cout<<endl;
	cout<<"Archivo#5"<<endl;
	cout<<"Expresion original: "<<endl;
	lista pila;
	lista expresion;
	ifstream archivo;
    string texto;
    ofstream archivoSalida;
    archivoSalida.open("Prioridades.txt", ios::app);
    if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	archivoSalida<<"-----Archivo#5-----"<<endl;
	archivo.open("Arch5.txt",ios::in);
    if (archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    else{
    	while(!archivo.eof()){
    		getline(archivo,texto);
    		cout<<texto;
    		if(EsOperador(texto)){
    			if(pila.ListaVacia()){
    				pnodo nuevo = new NodoBinario(texto);
    				pila.InsertarInicio(nuevo);
				}
				else{
					if(texto ==")"){
						
	    				int cont= 0;
	    				pnodoSimp recorrerP = pila.primero;
	    				while(recorrerP != NULL){
	    					if(EsParentesis(recorrerP->valor->valor)){
	    						cont++;
	    						break;
							}else{
								pnodo raiz = new NodoBinario(recorrerP->valor->valor);
			    				raiz->Hder = expresion.primero->valor;
			    				raiz->Hizq = expresion.primero->siguiente->valor;
			    				expresion.BorrarInicio();
			    				expresion.BorrarInicio();
			    				expresion.InsertarInicio(raiz);
								//AGREGAR A LA EXPRESION
								cont++;
								recorrerP= recorrerP->siguiente;
							}
						}while(cont!=0){
							pila.BorrarInicio();
							cont--;
						}
					}else{
						ArchivoTxT(pila.primero->valor->valor,texto);
						if(MostrarPrioridadDP(pila.primero->valor->valor)<MostrarPrioridadAP(texto)){
							pnodo nuevo = new NodoBinario(texto);
							pila.InsertarInicio(nuevo);
						}
						else{
							pnodo raiz = new NodoBinario(pila.primero->valor->valor);
							pila.BorrarInicio();
							raiz->Hder = expresion.primero->valor;
		    				raiz->Hizq = expresion.primero->siguiente->valor;
		    				expresion.BorrarInicio();
		    				expresion.BorrarInicio();
		    				expresion.InsertarInicio(raiz);
		    				pnodo nuevo = new NodoBinario(texto);
		    				pila.InsertarInicio(nuevo);
						}
					}
				}
			}
			else{
				//Si no es operador
				pnodo nuevo = new NodoBinario(texto);
				expresion.InsertarInicio(nuevo);
			}
		}
		if(!pila.ListaVacia()){
			pnodo raiz = new NodoBinario(pila.primero->valor->valor);
			pila.BorrarInicio();
			raiz->Hder = expresion.primero->valor;
			raiz->Hizq = expresion.primero->siguiente->valor;
			expresion.BorrarInicio();
			expresion.BorrarInicio();
			expresion.InsertarInicio(raiz);
			
			//--------------------------------------------------------------------------
		}
	
	}
	cout<<endl;
	cout<<"Inorden: "<<endl;
	InordenR(expresion.primero->valor);
	cout<<endl;
	cout<<"Preorden: "<<endl;
	PreordenR(expresion.primero->valor);
	cout<<endl;
	listaP post5;
	cout<<"Postorden: "<<endl;
	PostordenRec(expresion.primero->valor, post5);
	cout<<endl;
	listaP ListaNumeros;
    pnodoP punteroE=post5.primero;
    bool flag=false;    
    while (punteroE!=NULL){     
        if(EsOperador(punteroE->valor)){
            if(ListaNumeros.largoLista()>=3){
                flag=true;
            }else{
                flag=false;
            }
            float num1=atof((ListaNumeros.primero->siguiente->valor).c_str());
            float num2=atof((ListaNumeros.primero->valor).c_str());    //ListaNumeros=[]/ListaNumeros=[]
            int operacion=Operacion(punteroE->valor);
            switch (operacion){
                case 1:
                {
				float resultado=num1+num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
                if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
				}
                break;
                
                case 2:
                {
                float resultado=num1-num2;
                stringstream ss;
                ss<<resultado;
                string valor =ss.str();
                ListaNumeros.BorrarInicio();
            	ListaNumeros.BorrarInicio();
            	if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                }
                else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                }
                }
                break;
                
                case 3:
                {	
                if(num2==0){
                	cout<<"Evaluacion: "<<endl;
                    cout<<"Error, no se puede dividir por cero"<<endl;
                    goto division;
                    break;
                }else{
                    float resultado=num1/num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                    break;
                }
            	}
                case 4:
                {
                 float resultado =num1*num2;
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                    else{
                        ListaNumeros.InsertarFinal(valor);
            	        punteroE=punteroE->siguiente;    
                    }
                }
                
                break;
                
                case 5:
                {
                float resultado=pow(num1,num2);
                    stringstream ss;
                    ss<<resultado;
                    string valor =ss.str();
                    ListaNumeros.BorrarInicio();
            		ListaNumeros.BorrarInicio();
            		if(flag){
                    ListaNumeros.InsertarInicio(valor);
            	    punteroE=punteroE->siguiente;    
                     }
                    else{
                    ListaNumeros.InsertarFinal(valor);
            	    punteroE=punteroE->siguiente;    
                    }
                }

                break;
            }
            
        }
        else{
            ListaNumeros.InsertarInicio(punteroE->valor);
            punteroE=punteroE->siguiente;
        }
    }
    cout<<"Evaluacion: "<<endl;
    ListaNumeros.Mostrar();
division:
	cout<<endl;	
	
}


int main(){
	ConstruirArbol1();
	ConstruirArbol2();
	ConstruirArbol3();
	ConstruirArbol4();
	ConstruirArbol5();
   return 0;
}
