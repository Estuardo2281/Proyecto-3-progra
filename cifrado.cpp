#include "cifrado.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string charToString(char c) {
    stringstream ss;
    ss << c;
    return ss.str();
}

string convertirMinusculaNoVocal(char letra, const string& llave) {
    string resultado;
    switch (letra) {
        case 'b': resultado = "m1"; break;
        case 'c': resultado = "m2"; break;
        case 'd': resultado = "m3"; break;
        case 'f': resultado = "m4"; break;
        case 'g': resultado = "m5"; break;
        case 'h': resultado = "m6"; break;
        case 'j': resultado = "m7"; break;
        case 'k': resultado = "m8"; break;
        case 'l': resultado = "m9"; break;
        case 'm': resultado = "m10"; break;
        case 'n': resultado = "m11"; break;
        case 'ñ': resultado = "m12"; break;
        case 'p': resultado = "m13"; break;
        case 'q': resultado = "m14"; break;
        case 'r': resultado = "m15"; break;
        case 's': resultado = "m16"; break;
        case 't': resultado = "m17"; break;
        case 'v': resultado = "m18"; break;
        case 'w': resultado = "m19"; break;
        case 'x': resultado = "m20"; break;
        case 'y': resultado = "m21"; break;
        case 'z': resultado = "m22"; break;
        default: resultado = charToString(letra); break;
    }
    return resultado;
}

string convertirMayusculaNoVocal(char letra, const string& llave) {
    string resultado;
    switch (letra) {
        case 'B': resultado = "g1"; break;
        case 'C': resultado = "g2"; break;
        case 'D': resultado = "g3"; break;
        case 'F': resultado = "g4"; break;
        case 'G': resultado = "g5"; break;
        case 'H': resultado = "g6"; break;
        case 'J': resultado = "g7"; break;
        case 'K': resultado = "g8"; break;
        case 'L': resultado = "g9"; break;
        case 'M': resultado = "g10"; break;
        case 'N': resultado = "g11"; break;
        case 'Ñ': resultado = "g12"; break;
        case 'P': resultado = "g13"; break;
        case 'Q': resultado = "g14"; break;
        case 'R': resultado = "g15"; break;
        case 'S': resultado = "g16"; break;
        case 'T': resultado = "g17"; break;
        case 'V': resultado = "g18"; break;
        case 'W': resultado = "g19"; break;
        case 'X': resultado = "g20"; break;
        case 'Y': resultado = "g21"; break;
        case 'Z': resultado = "g22"; break;
        default: resultado = charToString(letra); break;
    }
    return resultado;
}

string cifrarPalabra(const string& palabra, const string& llave) {
    string resultado;
    for (char letra : palabra) {
        if (isalpha(letra)) {
            if (islower(letra)) {
                if (letra == 'a') resultado += "U1";
                else if (letra == 'e') resultado += "U2";
                else if (letra == 'i') resultado += "U3";
                else if (letra == 'o') resultado += "U4";
                else if (letra == 'u') resultado += "U5";
                else resultado += convertirMinusculaNoVocal(letra, llave);
            } else {
                if (letra == 'A') resultado += "a6";
                else if (letra == 'E') resultado += "a7";
                else if (letra == 'I') resultado += "a8";
                else if (letra == 'O') resultado += "a9";
                else if (letra == 'U') resultado += "a10";
                else resultado += convertirMayusculaNoVocal(letra, llave);
            }
        } else {
            resultado += charToString(letra); // Conserva los caracteres no alfabéticos
        }
    }
    return resultado;
}

string descifrarPalabra(const string& palabra, const string& llave) {
    string resultado;
    // Implementar la lógica para descifrar la palabra
    // ...
    return resultado;
}

void cifrarArchivo(const string& nombreArchivoEntrada, const string& nombreArchivoSalida, const string& llave) {
    ifstream archivoEntrada(nombreArchivoEntrada);
    ofstream archivoSalida(nombreArchivoSalida);
    ofstream archivoOriginal("original.txt");
    ofstream archivoLlave("llave.txt");

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return;
    }

    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return;
    }

    string palabra;
    while (archivoEntrada >> palabra) {
        archivoSalida << cifrarPalabra(palabra, llave) << " ";
        archivoOriginal << palabra << " ";
    }

    archivoLlave << llave;

    archivoEntrada.close();
    archivoSalida.close();
    archivoOriginal.close();
    archivoLlave.close();

    cout << "Cifrado completado. Resultado guardado en " << nombreArchivoSalida << endl;
}

void descifrarArchivo(const string& nombreArchivoEntrada, const string& nombreArchivoSalida, const string& llave) {
    ifstream archivoEntrada(nombreArchivoEntrada);
    ofstream archivoSalida(nombreArchivoSalida);

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return;
    }

    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return;
    }

    string palabra;
    while (archivoEntrada >> palabra) {
        archivoSalida << descifrarPalabra(palabra, llave) << " ";
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Descifrado completado. Resultado guardado en " << nombreArchivoSalida << endl;
}

