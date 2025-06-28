#include "header.h"
#include <iostream>
#include <fstream>
using namespace std;

// Función para agregar estudiante (CREATE)
void agregarEstudiante() {
    Estudiante e;
    cout << "Nombre (sin espacios): ";
    cin >> e.nombre;
    cout << "Carnet: ";
    cin >> e.carnet;
    cout << "Edad: ";
    cin >> e.edad;

    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << e.nombre << " " << e.carnet << " " << e.edad << endl;
        archivo.close();
        cout << "Estudiante agregado correctamente.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para mostrar estudiantes (READ)
void mostrarEstudiantes() {
    ifstream archivo("estudiantes.txt");
    Estudiante e;

    if (archivo.is_open()) {
        cout << "\n--- Lista de Estudiantes ---\n";
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            cout << "Nombre: " << e.nombre 
                 << ", Carnet: " << e.carnet
                 << ", Edad: " << e.edad << endl;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// -----------------------------
// 👇 TU TAREA: Completa esta función (UPDATE)
void modificarEstudiante() {
    string carnetBuscar;
    cout << "Ingresa el carnet del estudiante a modificar: ";
    cin >> carnetBuscar;

    ifstream archivoEntrada("estudiantes.txt");  // Abrimos archivo original
    ofstream archivoTemporal("temp.txt");        // Archivo temporal para guardar los cambios

    bool encontrado = false;
    Estudiante est;

    while (archivoEntrada >> est.nombre >> est.carnet >> est.edad) {
        if (est.carnet == carnetBuscar) {
            encontrado = true;
            cout << "Estudiante encontrado.\n";
            cout << "Nombre actual: " << est.nombre << ", Edad: " << est.edad << endl;

            cout << "Nuevo nombre (actual: " << est.nombre << "): ";
            cin >> est.nombre; 

            cout << "Nuevo carnet (actual: " << est.carnet << "): ";
            cin >> est.carnet;

            cout << "Nueva edad (actual: " << est.edad << "): ";
            cin >> est.edad;
        }

        // Guarda ya sea los datos nuevos o sin modificar
        archivoTemporal << est.nombre << " " << est.carnet << " " << est.edad << endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    remove("estudiantes.txt");               // Se borra el archivo viejo
    rename("temp.txt", "estudiantes.txt");   // Renombro el nuevo archivo

    if (encontrado)
        cout << "Estudiante modificado correctamente.\n";
    else
        cout << "Estudiante con carnet " << carnetBuscar << " no encontrado.\n";
}

    // Debes permitir actualizar nombre, carnet y/o edad
    // de un estudiante identificado por su carnet.
    // Puedes usar o no manejo de archivos.
    // Si lo implementas con archivos correctamente, obtendrás **2 puntos extra**.

// -----------------------------

// Función para eliminar estudiante (DELETE)
void eliminarEstudiante() {
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");
    Estudiante e;
    string buscado;
    bool eliminado = false;

    cout << "Ingrese carnet a eliminar: ";
    cin >> buscado;

    if (archivo.is_open() && temp.is_open()) {
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            if (e.carnet == buscado) {
                eliminado = true;               // No se copia: se “borra”
            } else {
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");

        if (eliminado)
            cout << "Estudiante eliminado correctamente.\n";
        else
            cout << "Carnet no encontrado.\n";
    } else {
        cout << "Error abriendo los archivos.\n";
    }
}
