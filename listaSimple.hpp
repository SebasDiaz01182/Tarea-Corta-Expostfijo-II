#include <iostream>
#include "NodoBinario.h"
using namespace std;

class nodo { 
	
   public:
    nodo(pnodo v) 
    {
       valor = v;
       siguiente = NULL;
    }

 
    nodo(pnodo v, nodo * signodo) 
    {
       valor = v;
       siguiente = signodo;
    }

   public: 
    pnodo valor; 
    nodo *siguiente;
            
   friend class lista;
   friend class NodoBinario;
   friend class Binario;

};
typedef nodo *pnodoSimp; 

class lista {
   public:
    lista()
	{
      primero=NULL;   	
    	
	}
    ~lista();
    void InsertarInicio(pnodo v);
    void InsertarFinal(pnodo v);
    void InsertarPos (pnodo v, int pos);
    bool ListaVacia() { return primero == NULL; } 
    void Imprimir();
    void Mostrar();
    void Primero();
	void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
      
   public:
    pnodoSimp primero; // nodo *primero; tipo nodo tiene derechoi direccionar un nodo
   
};
  
lista::~lista() //Destructor
{
   pnodoSimp aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
  
}

int lista::largoLista(){ //largo
    int cont=0;

    pnodoSimp aux; //nodo *aux;
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

void lista::InsertarInicio(pnodo v)
{
   if (ListaVacia())
     primero = new nodo(v);
   else
     primero=new nodo (v,primero);
}
 
void lista::InsertarFinal(pnodo v)
{
   if (ListaVacia())
     primero = new nodo(v);
   else
     { pnodoSimp aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(v);
      }    
}

void lista::InsertarPos(pnodo v, int pos) 
{
   if (ListaVacia())
     primero = new nodo(v);
   else{
        if(pos <=1){                     //InsertarInicio(v);
          pnodoSimp nuevo = new nodo(v);
          nuevo->siguiente= primero;
          primero= nuevo;     
        }      
        else
		{
        	if (pos>=largoLista())
			   InsertarFinal(v);
			else
			{
			
             pnodoSimp aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodoSimp nuevo= new nodo(v); //1 NODO
             nuevo->siguiente=aux->siguiente; // 2 Nuevo con el valor siguiente 20
             aux->siguiente=nuevo;// 3 aux con nuevo
            }
             
        }
        }
}
      
void lista::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoSimp aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }
                
              pnodoSimp temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void lista::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else
   {
        if (primero->siguiente == NULL)
		{
        	    pnodoSimp temp=primero;
                primero= NULL;
                delete temp;
        }
		else
		{

                pnodoSimp aux = primero;
                primero=primero->siguiente;                
                delete aux;
        }
   }
}



void lista:: borrarPosicion(int pos){
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
            pnodoSimp aux=  primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            aux->siguiente=aux->siguiente->siguiente;
            }
        }
     }

}
 

void lista::Mostrar()
{
   nodo *aux;
   if (primero== NULL)
       cout << "No hay elementos";  
   else
   {
   
       
   		aux = primero;
		while(aux) 
		{
		    cout << aux->valor->valor<< "-> ";
		    aux = aux->siguiente;
		}
		cout << endl;
   }
}



