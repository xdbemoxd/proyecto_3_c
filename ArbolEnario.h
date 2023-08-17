#ifndef ArbolEnario_H_
#define ArbolEnario_H_

#include <list>
#include "NodoA.h"
#include <iostream>
using namespace std;

template <class Tipo>
class ArbolEnario
{
	private:
		NodoA<Tipo>* raiz;

		void buscarPadre(NodoA<Tipo>* actual,Tipo padre,Tipo hijo,bool &band);
		void agregarHijo(NodoA<Tipo>* actual,Tipo hijo);
		void recorridoInOrden(NodoA<Tipo>* actual,list<Tipo> &lista,string padre);
		list< NodoA<Tipo>* > obtenerHijos(NodoA<Tipo>* padre);
		void recorridoPreOrden(NodoA<Tipo>* actual,list<Tipo> &lista);
		void recorridoLevelOrden(NodoA<Tipo>* actual,list<Tipo> &lista);
		void recorridoPostOrden(NodoA<Tipo>* actual,list<Tipo> &lista);
		void recorridoInOrdenDerecha(NodoA<Tipo>* actual,list<Tipo> &lista,string padre);
		bool elementoRepetido(Tipo elemento,list<Tipo> lista);
	public:
		ArbolEnario();
		ArbolEnario(Tipo Dato);
		void agregarHijo(Tipo padre,Tipo hijo);
		Tipo obtenerDatoRaiz();
		void inOrden(list<Tipo> &lista);
		void postOrden(list<Tipo> &lista);
		void preOrden(list<Tipo> &lista);
		void levelOrden(list<Tipo> &lista);
		void mostrarArbol();
		bool esSemilla();
};

template<class Tipo>
ArbolEnario<Tipo>::ArbolEnario()
{
	this->raiz=NULL;
}

template<class Tipo>
ArbolEnario<Tipo>::ArbolEnario( Tipo Dato )
{
	this->raiz=new NodoA<Tipo>( Dato );
}

template<class Tipo>
Tipo ArbolEnario<Tipo>::obtenerDatoRaiz()
{
	return this->raiz->obtenerDato();
}

template<class Tipo>
void ArbolEnario<Tipo>::agregarHijo( Tipo padre, Tipo hijo )
{
	NodoA<Tipo>* nuevo=new NodoA<Tipo>( hijo );
	bool band=false;

	if ( this->raiz->obtenerHijoIzquierdo() == NULL && padre == this->raiz->obtenerDato() )
	{
		this->raiz->modificarHijoIzquierdo( nuevo );	
	}else
	{
		if ( this->raiz->obtenerDato() == padre )
		{
			this->agregarHijo( this->raiz->obtenerHijoIzquierdo(), hijo );
		}else
		{
			if ( this->raiz->obtenerHijoIzquierdo() != NULL )
			{
				this->buscarPadre( raiz->obtenerHijoIzquierdo(), padre, hijo, band );
			}
		}
	}
}

template<class Tipo>
void ArbolEnario<Tipo>::buscarPadre( NodoA<Tipo>* actual, Tipo padre, Tipo hijo, bool &band )
{
	if  ( actual->obtenerDato() == padre )
	{
		band=true;
		if ( actual->obtenerHijoIzquierdo() == NULL )
		{
			NodoA<Tipo>* nuevo=new NodoA<Tipo>( hijo );
			actual->modificarHijoIzquierdo( nuevo );
		}else
		{
			if ( actual->obtenerHijoIzquierdo() != NULL )
			{
				this->agregarHijo( actual->obtenerHijoIzquierdo(), hijo );
			}
		}
	}
	

	if ( actual->obtenerHijoIzquierdo() != NULL && band != true )
	{
		this->buscarPadre( actual->obtenerHijoIzquierdo(), padre, hijo, band );
	}

	if ( actual->obtenerHijoDerecho() != NULL && band != true )
	{
		this->buscarPadre( actual->obtenerHijoDerecho(), padre, hijo, band );
	}
}

template<class Tipo>
void ArbolEnario<Tipo>::agregarHijo( NodoA<Tipo>* actual, Tipo hijo )
{
	NodoA<Tipo>* nuevo=new NodoA<Tipo>( hijo );

	while( actual->obtenerHijoDerecho() != NULL )
	{
		actual=actual->obtenerHijoDerecho();
	}

	actual->modificarHijoDerecho( nuevo );
}

template<class Tipo>
void ArbolEnario<Tipo>::inOrden( list<Tipo> &lista )
{
	if ( !this->esSemilla() )
	{
		this->recorridoInOrden( this->raiz->obtenerHijoIzquierdo(), lista, this->obtenerDatoRaiz() );
	}else
	{
		lista.push_back( this->obtenerDatoRaiz() );
	}
	
}

template<class Tipo>
void ArbolEnario<Tipo>::recorridoInOrden( NodoA<Tipo>* actual, list<Tipo> &lista, string padre )
{

	if ( actual->obtenerHijoIzquierdo() != NULL )
	{
		this->recorridoInOrden( actual->obtenerHijoIzquierdo(), lista, actual->obtenerDato() );
		
		if( actual->obtenerHijoDerecho() == NULL )
		{
			lista.push_back( actual->obtenerDato() );
		}

	}

	if ( actual->obtenerHijoDerecho() != NULL )
	{
		this->recorridoInOrdenDerecha(actual,lista,padre);
	}

	if ( actual->obtenerHijoDerecho() == NULL && actual->obtenerHijoIzquierdo() == NULL && actual!=NULL)
	{
		lista.push_back( actual->obtenerDato() );
		
	}	
}

template<class Tipo>
void ArbolEnario<Tipo>::recorridoInOrdenDerecha( NodoA<Tipo>* actual, list<Tipo> &lista, string padre )
{
	if( !elementoRepetido(actual->obtenerDato(),lista) )
	{
		lista.push_back( actual->obtenerDato() );
	}
	if( !elementoRepetido(padre,lista) )
	{
		lista.push_back( padre );
	}
	actual=actual->obtenerHijoDerecho();

	while( actual != NULL )
	{

		if ( actual->obtenerHijoIzquierdo() != NULL )
		{
			this->recorridoInOrden( actual->obtenerHijoIzquierdo(), lista, actual->obtenerDato() );	
		}

		if( !elementoRepetido(actual->obtenerDato(),lista) )
		{
			lista.push_back( actual->obtenerDato() );
		}	
		actual=actual->obtenerHijoDerecho();
	}
}

template<class Tipo>
bool ArbolEnario<Tipo>::elementoRepetido(Tipo elemento,list<Tipo> lista)
{
	bool aux=false;

	while( !lista.empty() && !aux ) 
	{
		if (lista.front()==elemento)
		{
			aux=true;
		}
		lista.pop_front();
	}

	return aux;
}

template<class Tipo>
list< NodoA<Tipo>* > ArbolEnario<Tipo>::obtenerHijos( NodoA<Tipo>* padre )
{
	list<NodoA<Tipo>*> hijos;
	NodoA<Tipo>* aux=padre->obtenerHijoIzquierdo();

	while( aux != NULL )
	{
		hijos.push_back( aux );
		aux=aux->obtenerHijoDerecho();
	}

	return hijos;
}

template<class Tipo>
void ArbolEnario<Tipo>::mostrarArbol()
{
	NodoA<Tipo>* actual=this->raiz;
	list<NodoA<Tipo>*> listaNodo;

	if ( actual->obtenerHijoIzquierdo() != NULL )
	{
		listaNodo=this->obtenerHijos( actual );
	}
	
	while( !listaNodo.empty() )
	{
		actual=listaNodo.front();
		cout<<actual->obtenerDato()<<" ";
		if ( actual->obtenerHijoIzquierdo() != NULL )
		{
			listaNodo.push_back( actual->obtenerHijoIzquierdo() );
		}
		listaNodo.pop_front();
	}
}

template<class Tipo>
void ArbolEnario<Tipo>::preOrden( list<Tipo> &lista )
{
	lista.push_back( this->obtenerDatoRaiz() );
	
	if ( !this->esSemilla() )
	{
		this->recorridoPreOrden( this->raiz->obtenerHijoIzquierdo(), lista );
	}
}

template<class Tipo>
void ArbolEnario<Tipo>::recorridoPreOrden( NodoA<Tipo>* actual, list<Tipo> &lista )
{
	lista.push_back( actual->obtenerDato() );

	if ( actual->obtenerHijoIzquierdo() != NULL )
	{
		this->recorridoPreOrden( actual->obtenerHijoIzquierdo(), lista );
	}

	if ( actual->obtenerHijoDerecho() != NULL )
	{
		this->recorridoPreOrden( actual->obtenerHijoDerecho(), lista );
	}
}

template<class Tipo>
void ArbolEnario<Tipo>::levelOrden( list<Tipo> &lista )
{
	lista.push_back( this->obtenerDatoRaiz() );
	if ( !this->esSemilla() )
	{
		this->recorridoLevelOrden( this->raiz->obtenerHijoIzquierdo(), lista );
	}
	
}

template<class Tipo>
void ArbolEnario<Tipo>::recorridoLevelOrden( NodoA<Tipo>* actual, list<Tipo> &lista )
{
	list<NodoA<Tipo>*> listaNodo;

	listaNodo.push_back( actual );

	while( !listaNodo.empty() )
	{

		while( actual != NULL )
		{	
			lista.push_back( actual->obtenerDato() );
			if ( actual->obtenerHijoIzquierdo() != NULL )
			{
				listaNodo.push_back( actual->obtenerHijoIzquierdo() );
			}
			actual=actual->obtenerHijoDerecho();

		}
		listaNodo.pop_front();
		if ( !listaNodo.empty() )
		{
			actual=listaNodo.front();
		}
	}
}

template<class Tipo>
void ArbolEnario<Tipo>::postOrden( list<Tipo> &lista )
{
	if ( !this->esSemilla() )
	{
		this->recorridoPostOrden( this->raiz->obtenerHijoIzquierdo(), lista );
	}
	
	lista.push_back( this->obtenerDatoRaiz() );
}

template<class Tipo>
void ArbolEnario<Tipo>::recorridoPostOrden( NodoA<Tipo>* actual, list<Tipo> &lista )
{
	if ( actual->obtenerHijoIzquierdo() != NULL )
	{
		this->recorridoPostOrden( actual->obtenerHijoIzquierdo(), lista );
	}

	lista.push_back( actual->obtenerDato() );

	if ( actual->obtenerHijoDerecho() != NULL )
	{
		this->recorridoPostOrden( actual->obtenerHijoDerecho(), lista );
	}
}

template<class Tipo>
bool ArbolEnario<Tipo>::esSemilla()
{
	return this->raiz->esHoja();
}
#endif