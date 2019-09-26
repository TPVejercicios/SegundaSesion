#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Date.h"

using namespace std;

typedef struct Coche {
	int codigo, precio;
	string marca, modelo;
};

typedef struct Alquiler {
	int codigo, dias;
	Date fecha;
	bool operator<(const Alquiler& m) const {
		return fecha < m.fecha;
	}
};

struct ListaCoches {
	Coche** elementos;
	int tamaño, contador;
};

struct ListaAlquileres {
	Alquiler* elementos;
	int tamaño, contador;
};

//Libera la memoria
void liberar(ListaCoches listaCoches, ListaAlquileres listaAlquileres)
{
	for (int i = 0; i < listaCoches.contador; i++)
	{
		delete listaCoches.elementos[i];
	}

	delete[] listaAlquileres.elementos;
	delete[] listaCoches.elementos;
}

//Muestra en consola la lista de coches
void MostrarCoches(ListaCoches& listaCoches) {
	for (int i = 0; i < listaCoches.contador; i++) {
		cout << listaCoches.elementos[i]->codigo << " " << listaCoches.elementos[i]->precio << " " << listaCoches.elementos[i]->marca << " " << listaCoches.elementos[i]->modelo << endl;
	}
}

//Muestra en consola la lista de alquileres
void MostrarAlquileres(ListaAlquileres& listaAlquileres) {
	for (int i = 0; i < listaAlquileres.contador; i++) {
		cout << listaAlquileres.elementos[i].codigo << " " << listaAlquileres.elementos[i].fecha << " " << listaAlquileres.elementos[i].dias << endl;
	}
}

//Comprueba si un codigo pertenece a un coche existente
Coche *BuscarCoche(int codigo,const ListaCoches& listaCoches) {

	bool encontrado = false;
	Coche *p = nullptr;
	int i = 0;
	while ((!encontrado) && (i < listaCoches.contador)) {
		encontrado = (codigo == listaCoches.elementos[i]->codigo);
		i++;
	}
	i--;
	if (encontrado) {
		p = listaCoches.elementos[i];
		cout << "Coche encontrado. " << endl;
	}
	else {
		cout << "No se ha encontrado. " << endl;
	}

	return p;
}

//Organiza y muestra en consola los alquileres de coches
void GestionarAlquileres(const ListaCoches& listaCoches,const ListaAlquileres& listaAlquileres) {
	Coche *p;
	for (int i = 0; i < listaAlquileres.contador; i++) {
		p = BuscarCoche(listaAlquileres.elementos[i].codigo, listaCoches);
		cout << listaAlquileres.elementos[i].fecha << " ";
		if (p != nullptr){
			cout << p->marca << " " << p->marca << " " << p->modelo << " " << listaAlquileres.elementos[i].dias << " dia(s) por " << listaAlquileres.elementos[i].dias * p->precio <<" euros." << endl;
			}
		else cout << "ERROR: Modelo inexistente" << endl;
		}
}

//Ordena por las fechas de alquiler de menos a mayor
void OrdenarPorFecha(ListaAlquileres& listaAlquileres) {
	sort(listaAlquileres.elementos, &(listaAlquileres.elementos[listaAlquileres.contador]));
}

//Lee los coches de un fichero y los almacena en un array dinámico
bool LecturaCoches(ListaCoches& listaCoches) {
	ifstream lectura;
	lectura.open("coches.txt");
	bool leido = lectura.is_open();
	if (leido) {
		lectura >> listaCoches.contador;
		listaCoches.tamaño = listaCoches.contador + 10;
		listaCoches.elementos = new Coche*[listaCoches.tamaño];
		for (int i = 0; i < listaCoches.contador; i++) {
			listaCoches.elementos[i] = new Coche;
			lectura >> listaCoches.elementos[i]->codigo >> listaCoches.elementos[i]->precio >> listaCoches.elementos[i]->marca >> listaCoches.elementos[i]->modelo;
		}
	}
	lectura.close();
	return leido;
}

//Lee los alquileres de un fichero y los almacena en un array dinámico
bool LecturaAlquileres(ListaAlquileres& listaAlquileres) {
	ifstream lectura;
	lectura.open("rent.txt");
	bool leido = lectura.is_open();
	if (leido) {
		lectura >> listaAlquileres.contador;
		listaAlquileres.tamaño = listaAlquileres.contador + 10;
		listaAlquileres.elementos = new Alquiler[listaAlquileres.tamaño];
		for (int i = 0; i < listaAlquileres.contador; i++) {
			lectura >> listaAlquileres.elementos[i].codigo >> listaAlquileres.elementos[i].fecha >> listaAlquileres.elementos[i].dias;
		}
	}
	lectura.close();
	return leido;
}

//Gestiona la entrada de teclado
int Menu() {
	int op;
	cout << "1. Mostrar Alquileres" << endl;
	cout << "2. Buscar Coche" << endl;
	cout << "0. Salir" << endl;
	cout << "Elige una opcion: ";
	cin >> op;
	while ((op < 0) || (op > 2)) {
		cout << "Opcion no valida. Elige una opcion: ";
		cin >> op;
	}
	return op;

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ListaAlquileres listaAlquileres;
	ListaCoches listaCoches;
	if (LecturaCoches(listaCoches)) cout << "Los coches se han leido correctamente. " << endl;
	else cout << "error de lectura coches" << endl;
	if (LecturaAlquileres(listaAlquileres)) cout << "Los alquileres se han leido correctamente. " << endl;
	else cout << "error de lectura alquileres" << endl;
	cout << "*****************************************" << endl;
	int input;
	string mensaje;
	do {
		cout << mensaje << endl;
		input = Menu();
		system("cls");
		switch (input) {
		case 1: 
			OrdenarPorFecha(listaAlquileres);
			GestionarAlquileres(listaCoches, listaAlquileres);
			break;
		case 2:
			int codigo;
			cout << "Ingrese el codigo del coche. " << endl;
			cin >> codigo;
			Coche *p = BuscarCoche(codigo, listaCoches);
			if (p != nullptr){
				cout << "El coche encontrado es: " << p->marca << " " << p->modelo << endl;
			}
			else{
				cout << "No existe un coche con el codigo: " << codigo << " en rent.txt" << endl;
			}
			break;
		}

	} while (input != 0);

	liberar(listaCoches,listaAlquileres);
}
