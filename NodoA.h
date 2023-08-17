#ifndef NodoA_H_
#define NodoA_H_
#include <iostream>
using namespace std;

template <class Tipo>
class NodoA
{
	private:
		
		Tipo dato;
		NodoA<Tipo>* hijoIzquierdo;
		NodoA<Tipo>* hijoDerecho;

	public:
		NodoA();
		NodoA(Tipo NuevoDato);

		Tipo obtenerDato();

		void modificarDato( Tipo NuevoDato );

		NodoA<Tipo>* obtenerHijoIzquierdo();

		NodoA<Tipo>* obtenerHijoDerecho();

		void modificarHijoIzquierdo( NodoA<Tipo>* NuevoHijoIzquierdo );

		void modificarHijoDerecho( NodoA<Tipo>* NuevoHijoDerecho );

		bool esHoja();
	
};

template <class Tipo>
NodoA<Tipo>::NodoA()
{
	this->hijoDerecho=NULL;
	this->hijoIzquierdo=NULL;
}

template <class Tipo>
NodoA<Tipo>::NodoA(Tipo NuevoDato)
{
	this->dato=NuevoDato;
	this->hijoDerecho=NULL;
	this->hijoIzquierdo=NULL; 
}

template <class Tipo>
Tipo NodoA<Tipo>::obtenerDato()
{
	return (this->dato);
}

template <class Tipo>
void NodoA<Tipo>::modificarDato( Tipo nuevoDato )
{
	this->dato=nuevoDato;
}

template <class Tipo>
NodoA<Tipo>* NodoA<Tipo>::obtenerHijoIzquierdo()
{
	return (this->hijoIzquierdo);
}

template <class Tipo>
NodoA<Tipo>* NodoA<Tipo>::obtenerHijoDerecho()
{
	return (this->hijoDerecho);
}

template <class Tipo>
void NodoA<Tipo>::modificarHijoIzquierdo( NodoA<Tipo>* nuevoHijoIzquierdo )
{
	this->hijoIzquierdo=nuevoHijoIzquierdo;
}

template <class Tipo>
void NodoA<Tipo>::modificarHijoDerecho( NodoA<Tipo>* nuevoHijoDerecho )
{
	this->hijoDerecho=nuevoHijoDerecho;
}

template <class Tipo>
bool NodoA<Tipo>::esHoja()
{
	bool aux=false;

	if (this->hijoIzquierdo==NULL && this->hijoDerecho==NULL)
	{
		aux=true;
	}

	return aux;
}

#endif