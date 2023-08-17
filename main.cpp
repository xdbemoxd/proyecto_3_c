#include <iostream>
#include "json.h"
#include <fstream>
#include <sstream>
#include <string>
#include "ArbolEnario.h"
#include <list>
using namespace std;

//Benjamin Marroquin 27445292

/*nota importante, donde quiera que se vea jVar y auxJVar, siguen el siguente significado 

jVar= java variables en sus siglas in english XD
auxJVar= java variable helper,  que es auxiliar de variable de java, tu sabes espanglish XD

PostData: si tengo problemas con el camel case, hagamelo saber antes del taller de grafos XD
*/ 

//funciones las cuales me ayuda a obtener los datos necerios y organizarlos para crear el arbolenario
void nodosN( json::jobject jVar, string padre, ArbolEnario<string>* &arbol );
void getNombres( json::jobject jVar, string padre, ArbolEnario<string>* &arbol );
//funcion que utilizo para acomodar el get("nombre") y  el get("apellido")  en una sola cadena del estilo "NombreApellido"
string acomodarCadenas( string cadena1 );
//como la primera cadena tiene "" en get("nombre") y en get("apellido"), esta se las quita para posteriormente, unirlas
string quitarComillas( string cadena );
//funcion utilizada para mostrar el recorrido como sale en el enunciado del proyecto
void mostrarRecorrido(list<string> listaR);
//verifica que el nuevo elemento el cual va a ser agregado, posee una cedula repetida o no
string quitarCedula( string cadena );


int main()
{
	//variable utilizada para abrir el archivo
	ifstream archivo;

	json::jobject jVar;
	json::jobject auxJVar; 
	
	//cadena se usa para guardar como una cadena de caracteres, el contido del archivo 
	string cadena;

	//variable donde guardo el contenido del archivo para luego guardarlo en la variable cadena
	stringstream contenido;

	//arbolN es donde se guarda la modelacion del problema con un arbol enario
	ArbolEnario<string>* arbolN;

	//variable donde guardo el recorrido del arbol
	list<string> listaR;


	archivo.open("entrada.json");

	if (archivo.fail())
	{
		cout<<"no se puede abrir el archivo"<<endl;
	}else
	{	
		//primero almaceno el contenido del archivo con la funcion rdbuf()
		contenido << archivo.rdbuf();
		//luego convierto utilizo str(), para almacenar el contenido en cadena
		cadena=contenido.str();
		//para al final utilizar la funcion parse y crear el objeto json
		jVar=json::jobject::parse( cadena );
	}

	archivo.close();

	//guardo como una cadena de caracteres a los subordinados del objeto principal 
	cadena=jVar.get("subordinados");
	//creo el nuevo objeto json, para los subordinados de el objeto principal
	auxJVar=json::jobject::parse( cadena );
	//aqui guardo el nombre del objeto principal para postriormente agregarlo al nodo raiz
	cadena=quitarComillas( jVar.get("nombre") ) + quitarComillas( jVar.get("apellido") ) + quitarComillas( jVar.get("cedula") );
	//almaceno el dato cadena en el nodo raiz del arbol
	arbolN=new ArbolEnario<string>( cadena );
	
	//aqui verifico que la cadena almacenada en auxJVar, mo sea '[]', en caso de serlo, me causaria problemas con las otras funciones
	if (auxJVar.pretty()!="[]")
	{
		nodosN( auxJVar, cadena, arbolN );
	}


	//impresiones de todos los recorridos
	cout<<"PREORDEN:";
	arbolN->preOrden(listaR);
	mostrarRecorrido(listaR);
	listaR.clear();
	arbolN->inOrden(listaR);
	cout<<"INORDEN:";
	mostrarRecorrido(listaR);
	listaR.clear();
	cout<<"POSTORDEN:";
	arbolN->postOrden(listaR);
	mostrarRecorrido(listaR);
	listaR.clear();
	arbolN->levelOrden(listaR);
	cout<<"NIVELES:";
	mostrarRecorrido(listaR);

	return 0;
}


//la vaiable padre, almacena el nombre del padre, de manera que si el tiene multiples hijo, se haga mas facil obtenerlo 
void nodosN( json::jobject jVar, string padre, ArbolEnario<string>* &arbol )
{
	//si es un vector de json, se ira a la funcion getnombres, para obtener los nombres de todos los hijos, en caso contrario, lo agrega en esta funcion
	if (jVar.is_array())
	{
		getNombres(jVar,padre,arbol);
	}else
	{
		arbol->agregarHijo( padre, jVar.get("nombre") + jVar.get("apellido") + jVar.get("cedula") );
	}
}

//reviso cada uno de los espacios del vector JVar y los almaceno a medida que los voy leyendo
void getNombres( json::jobject jVar, string padre, ArbolEnario<string>* &arbol )
{
	string aux;
	json::jobject auxJVar;

	//ciclo utilizado para leer el vector 
	for (int i = 0; i < jVar.size(); ++i)
	{
		//llamada de la funcio para agregar al hijo
		arbol->agregarHijo( padre, jVar.array(i).get("nombre").as_string() + jVar.array(i).get("apellido").as_string() + jVar.array(i).get("cedula").as_string() );
		
		//verifico que tenga hijos, en caso de tenerlos, debo agregarlo tambien, antes de seguir con los otros
		if (jVar.array(i).get("subordinados").as_string()!="[]")
		{	
			//guardo como una cadena de caracteres lo obtenido, para posteriormente, almacenarlo en un objeto json
			aux=jVar.array(i).get("subordinados").as_string();
			auxJVar=json::jobject::parse(aux);
			//llamo a esta funcion para determinar si es un array
			nodosN( auxJVar, jVar.array(i).get("nombre").as_string() + jVar.array(i).get("apellido").as_string() + jVar.array(i).get("cedula").as_string(), arbol );
		}
	}
}

//funcion utilizada para acomodar las cadenas como lo dictamina el enunciado
string acomodarCadenas( string cadena1 )
{	
	return ( '"' + quitarCedula( cadena1 ) + '"' );
}

//funcion para quitar las comillas de una cadena de caracteres
string quitarComillas( string cadena )
{
	string aux;

	aux=cadena[1];

	for ( int i = 2; i < cadena.size()-1; ++i )
	{
		aux=aux+cadena[i];
	}

	return aux;
}

//muestro el recorrido del arbol, con las pautas propuestas en el enunciado
void mostrarRecorrido( list<string> listaR )
{
	list<string>::iterator it;
	int i=1;

	cout<<"[";
	for ( it = listaR.begin(); it != listaR.end(); ++it )
	{
		cout<<acomodarCadenas(*it);
		i++;

		if ( listaR.size() > 1 && i <= listaR.size() )
		{
			cout<<',';
		}

	}

	cout<<"]"<<endl;
}

string quitarCedula( string cadena )
{
	string auxCadena;
	int i=1;
	auxCadena=cadena[0];

	while(cadena[i]!='1' && cadena[i]!='2' && cadena[i]!='3' && cadena[i]!='4' && cadena[i]!='5' && cadena[i]!='6' && cadena[i]!='7' && cadena[i]!='8' && cadena[i]!='9' && cadena[i]!='0' )
	{
		auxCadena=auxCadena + cadena[i];
		i++;
	}

	return auxCadena;
}