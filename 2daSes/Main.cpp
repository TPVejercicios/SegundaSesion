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
	Coche* elementos;
	int tamaño, contador;
};

struct ListaAlquileres {
	Alquiler* elementos;
	int tamaño, contador;
};


void MostrarCoches(ListaCoches& listaCoches) {
	for (int i = 0; i < listaCoches.contador; i++) {
		cout << listaCoches.elementos[i].codigo << " " << listaCoches.elementos[i].precio << " " << listaCoches.elementos[i].marca << " " << listaCoches.elementos[i].modelo << endl;
	}
}

void MostrarAlquileres(ListaAlquileres& listaAlquileres) {
	for (int i = 0; i < listaAlquileres.contador; i++) {
		cout << listaAlquileres.elementos[i].codigo << " " << listaAlquileres.elementos[i].fecha << " " << listaAlquileres.elementos[i].dias << endl;
	}
}

int *BuscarCoche(int codigo, ListaCoches& listaCoches) {
	bool encontrado = false;
	int *p = nullptr;
	int i = -1;
	while ((!encontrado) && (i < listaCoches.contador)) {
		i++;
		if (codigo == listaCoches.elementos[i].codigo) encontrado = true;
	}
	if (encontrado) {
		//p = listaCoches.elementos[i];
		cout << "Si que lo encuentra" << endl;
	}
	else cout << "No encuentra" << endl;

	return p;
}

void MostrarAlquileres2(ListaCoches& listaCoches, ListaAlquileres& listaAlquileres) {
	int *p;
	for (int i = 0; i < listaAlquileres.contador; i++) {
		BuscarCoche(listaAlquileres.elementos[i].codigo, listaCoches);
		cout << listaAlquileres.elementos[i].fecha << " ";
		/*if (p != nullptr){
			cout << listaCoches.elementos[p].marca << " " << listaCoches.elementos[p].modelo << " " << listaAlquileres.elementos[i].dias << " dia(s) por " << listaAlquileres.elementos[i].dias * listaCoches.elementos[p].precio << endl;
			}*/
		//else
		cout << "ERROR: Modelo inexistente" << endl;
		}
}

void OrdenarPorFecha(ListaAlquileres& listaAlquileres) {
	sort(listaAlquileres.elementos, &(listaAlquileres.elementos[listaAlquileres.contador]));
}

bool LecturaCoches(ListaCoches& listaCoches) {
	ifstream lectura;
	lectura.open("coches.txt");
	bool leido = lectura.is_open();
	if (leido) {
		lectura >> listaCoches.contador;
		listaCoches.tamaño = listaCoches.contador + 10;
		listaCoches.elementos = new Coche[listaCoches.tamaño];
		for (int i = 0; i < listaCoches.contador; i++) {
			lectura >> listaCoches.elementos[i].codigo >> listaCoches.elementos[i].precio >> listaCoches.elementos[i].marca >> listaCoches.elementos[i].modelo;
		}
	}
	lectura.close();
	return leido;
}

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
	ListaAlquileres listaAlquileres;
	ListaCoches listaCoches;
	if (LecturaCoches(listaCoches)) MostrarCoches(listaCoches);
	else cout << "error de lectura coches";
	cout << endl << endl;
	if (LecturaAlquileres(listaAlquileres)) MostrarAlquileres(listaAlquileres);
	else cout << "error de lectura alquileres";
	cout << endl << endl;
	int op;
	do {
		op = Menu();
		switch (op) {
		case 1: 
			OrdenarPorFecha(listaAlquileres);
			MostrarAlquileres2(listaCoches, listaAlquileres);
			break;
		case 2:
			//BuscarCoche();
			//Mostrar Ese Coche
			break;
		}

	} while (op != 0);
	system("pause");
}
