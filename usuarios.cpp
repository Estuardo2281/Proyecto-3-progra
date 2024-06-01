#include "usuarios.h"
#include "cifrado.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void registrarUsuario(const string& usuario, const string& contrasena, const string& llave) {
    ofstream archivoUsuarios("acceso.txt", ios::app);
    if (!archivoUsuarios.is_open()) {
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return;
    }

    archivoUsuarios << usuario << " " << cifrarPalabra(contrasena, llave) << endl;
    archivoUsuarios.close();
    cout << "Usuario registrado con éxito." << endl;
}

bool verificarUsuario(const string& usuario, const string& contrasena, const string& llave) {
    ifstream archivoUsuarios("acceso.txt");
    if (!archivoUsuarios.is_open()) {
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return false;
    }

    string usuarioArchivo, contrasenaArchivo;
    while (archivoUsuarios >> usuarioArchivo >> contrasenaArchivo) {
        if (usuarioArchivo == usuario && contrasenaArchivo == cifrarPalabra(contrasena, llave)) {
            archivoUsuarios.close();
            return true;
        }
    }

    archivoUsuarios.close();
    return false;
}

