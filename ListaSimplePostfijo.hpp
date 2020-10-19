
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include <math.h>
using namespace std;

//Clase nodo
class nodoP { //clase NODO
	
   public:
    nodoP(string v) // 20 Tiene diferente cantidad de parametros, diferente tipos. Mismo nombre de la clase
    {
       valor = v;//20
       siguiente = NULL;
    }

 
    nodoP(string v, nodoP * signodoP) // 2 dirprimero direccion de memoria
    {
       valor = v;//2
       siguiente = signodoP;//primero
    }


    public: //atributos
    string valor; // tipo entero. Ej clase estudiante nombre,dir,tel,siguente
    nodoP *siguiente; // tipo de la clase, clase autoreferencia. Direccion 
    
        
   friend class listaP; // telefono, son amigas lista con la clase. Solo los metodos, constructores

};
typedef nodoP *pnodoP; //alias redefinir los punteros

class listaP {
   public:
    listaP()
	{
      primero=NULL;   	
    	
	}
    ~listaP();
    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos (string v, int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Mostrar();
    void Primero();
	void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
    void invertir();
    void lectura();
      
   public:
    pnodoP primero; 
   
};
  
listaP::~listaP() //Destructor
{
   pnodoP aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
  
}

int listaP::largoLista(){ //largo
    int cont=0;

    pnodoP aux; //nodo *aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void listaP::InsertarInicio(string v)
{
   if (ListaVacia())
     primero = new nodoP(v);
   else
     primero=new nodoP (v,primero);
}
 
void listaP::InsertarFinal(string v)
{
   if (ListaVacia())
     primero = new nodoP(v);
   else
     { pnodoP aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoP(v);
      }    
}

void listaP::InsertarPos(string v, int pos) 
{
   if (ListaVacia())
     primero = new nodoP(v);
   else{
        if(pos <=1){                     //InsertarInicio(v);
          pnodoP nuevo = new nodoP(v);
          nuevo->siguiente= primero;
          primero= nuevo;     
        }      
        else
		{
        	if (pos>=largoLista())
			   InsertarFinal(v);
			else
			{
			
             pnodoP aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodoP nuevo= new nodoP(v); //1 NODO
             nuevo->siguiente=aux->siguiente; // 2 Nuevo con el valor siguiente 20
             aux->siguiente=nuevo;// 3 aux con nuevo
            }
             
        }
        }
}
      
void listaP::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoP aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }
                
              pnodoP temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void listaP::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else
   {
        if (primero->siguiente == NULL)
		{
        	    pnodoP temp=primero;
                primero= NULL;
                delete temp;
        }
		else
		{

                pnodoP aux = primero;
                primero=primero->siguiente;                
                delete aux;
        }
   }
}



void listaP:: borrarPosicion(int pos){
     if(ListaVacia()){
              cout << "Lista vacia" <<endl;
    }else{
         if((pos>largoLista())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==1){
        primero=primero->siguiente;
        }else{
          int cont=2;
            pnodoP aux=  primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            aux->siguiente=aux->siguiente->siguiente;
            }
        }
     }

}
 

void listaP::Mostrar()
{
   nodoP *aux;
   if (primero== NULL)
       cout << "No hay elementos";  
   else
   {
   		aux = primero;
		while(aux) 
		{
		    cout << aux->valor ;
		    aux = aux->siguiente;
		}
		cout << endl;
   }
}

