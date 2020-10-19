#ifndef _NODOBINARIO_H
#define	_NODOBINARIO_H
#include<string.h>
#include<string>
using namespace std;
class NodoBinario {
   public:

    NodoBinario(string num, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig=NULL, NodoBinario *ant=NULL):
        Hizq(izq), Hder(der), valor(num), siguiente(sig), anterior(ant), FB(0) {}
	/*
	NodoBinario(string v){
		valor = v;
		Hder = NULL;
		Hizq = NULL;
		siguiente = NULL;
		anterior = NULL;
	}
	*/

    string valor;
    int FB;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;

    friend class Pila;
    friend class Binario;

    void InsertaBinario(string num);
};

typedef NodoBinario *pnodo;
typedef NodoBinario *pNodoBinario;

#endif	

