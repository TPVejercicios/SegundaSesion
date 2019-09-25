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

void OrdenarPorFecha(ListaAlquileres& listaAlquileres) {
	sort(listaAlquileres.elementos, &(listaAlquileres.elementos[listaAlquileres.contador]));
	MostrarAlquileres(listaAlquileres);
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
	OrdenarPorFecha(listaAlquileres);

	system("pause");
}
