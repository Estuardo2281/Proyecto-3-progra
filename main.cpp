#include "usuarios.h"
#include "cifrado.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// Declaración de la función reproducirAudio
void reproducirAudio(const string& palabra);

struct Nodo {
    string palabra;
    string italiano;
    string frances;
    string aleman;
    string ingles;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};

class Arbol {
public:
    Arbol() : raiz(nullptr) {}

    void insertar(const string& palabra, const string& italiano, const string& frances, const string& aleman, const string& ingles) {
        raiz = insertar(raiz, palabra, italiano, frances, aleman, ingles);
    }

    void eliminar(const string& palabra) {
        raiz = eliminar(raiz, palabra);
    }

    void mostrar() const {
        int contador = 1;
        mostrar(raiz, contador);
    }

    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo.c_str());
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string palabra, italiano, frances, aleman, ingles;
            getline(ss, palabra, ',');
            getline(ss, italiano, ',');
            getline(ss, frances, ',');
            getline(ss, aleman, ',');
            getline(ss, ingles, ',');
            insertar(palabra, italiano, frances, aleman, ingles);
        }
        archivo.close();
    }

    void guardarEnArchivo(const string& nombreArchivo) const {
        ofstream archivo(nombreArchivo.c_str());
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }
        guardarEnArchivo(raiz, archivo);
        archivo.close();
    }

    void buscarYMostrar(const string& palabra) const {
        Nodo* nodo = buscar(raiz, palabra);
        if (nodo != nullptr) {
            cout << "Palabra: " << nodo->palabra << ", Italiano: " << nodo->italiano
                 << ", Francés: " << nodo->frances << ", Alemán: " << nodo->aleman
                 << ", Inglés: " << nodo->ingles << endl;
                   // Concatenar las traducciones en una cadena separada por comas
        string traducciones = nodo->italiano + "," + nodo->frances + "," + nodo->aleman + "," + nodo->ingles;
        // Reproducir las traducciones como audio
        reproducirAudio(traducciones);
        } else {
            cout << "La palabra no se encuentra en el árbol." << endl;
        }
    }

private:
    Nodo* raiz;

    Nodo* nuevoNodo(const string& palabra, const string& italiano, const string& frances, const string& aleman, const string& ingles) {
        Nodo* nodo = new Nodo();
        nodo->palabra = palabra;
        nodo->italiano = italiano;
        nodo->frances = frances;
        nodo->aleman = aleman;
        nodo->ingles = ingles;
        nodo->izquierda = nodo->derecha = nullptr;
        nodo->altura = 1;
        return nodo;
    }

    int altura(Nodo* nodo) {
        return nodo ? nodo->altura : 0;
    }

    int balance(Nodo* nodo) {
        return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
    }

    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izquierda;
        Nodo* T2 = x->derecha;
        x->derecha = y;
        y->izquierda = T2;
        y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
        x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->derecha;
        Nodo* T2 = y->izquierda;
        y->izquierda = x;
        x->derecha = T2;
        x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
        y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
        return y;
    }

    Nodo* insertar(Nodo* nodo, const string& palabra, const string& italiano, const string& frances, const string& aleman, const string& ingles) {
        if (nodo == nullptr) {
            return nuevoNodo(palabra, italiano, frances, aleman, ingles);
        }
        if (palabra < nodo->palabra) {
            nodo->izquierda = insertar(nodo->izquierda, palabra, italiano, frances, aleman, ingles);
        } else if (palabra > nodo->palabra) {
            nodo->derecha = insertar(nodo->derecha, palabra, italiano, frances, aleman, ingles);
        } else {
            return nodo;
        }
        nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
        int balanceNodo = balance(nodo);
        if (balanceNodo > 1 && palabra < nodo->izquierda->palabra) {
            return rotarDerecha(nodo);
        }
        if (balanceNodo < -1 && palabra > nodo->derecha->palabra) {
            return rotarIzquierda(nodo);
        }
        if (balanceNodo > 1 && palabra > nodo->izquierda->palabra) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
        }
        if (balanceNodo < -1 && palabra < nodo->derecha->palabra) {
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
        }
        return nodo;
    }

    Nodo* eliminar(Nodo* raiz, const string& palabra) {
        if (raiz == nullptr) return nullptr;

        if (palabra < raiz->palabra) {
            raiz->izquierda = eliminar(raiz->izquierda, palabra);
        } else if (palabra > raiz->palabra) {
            raiz->derecha = eliminar(raiz->derecha, palabra);
        } else {
            if ((raiz->izquierda == nullptr) || (raiz->derecha == nullptr)) {
                Nodo* temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;
                if (temp == nullptr) {
                    temp = raiz;
                    raiz = nullptr;
                } else {
                    *raiz = *temp;
                }
                delete temp;
            } else {
                Nodo* temp = minValorNodo(raiz->derecha);
                raiz->palabra = temp->palabra;
                raiz->derecha = eliminar(raiz->derecha, temp->palabra);
            }
        }

        if (raiz == nullptr) return raiz;

        raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));
        int balanceNodo = balance(raiz);

        if (balanceNodo > 1 && balance(raiz->izquierda) >= 0) {
            return rotarDerecha(raiz);
        }
        if (balanceNodo > 1 && balance(raiz->izquierda) < 0) {
            raiz->izquierda = rotarIzquierda(raiz->izquierda);
            return rotarDerecha(raiz);
        }
        if (balanceNodo < -1 && balance(raiz->derecha) <= 0) {
            return rotarIzquierda(raiz);
        }
        if (balanceNodo < -1 && balance(raiz->derecha) > 0) {
            raiz->derecha = rotarDerecha(raiz->derecha);
            return rotarIzquierda(raiz);
        }

        return raiz;
    }

    Nodo* minValorNodo(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual->izquierda != nullptr) actual = actual->izquierda;
        return actual;
    }

    Nodo* buscar(Nodo* nodo, const string& palabra) const {
        if (nodo == nullptr || nodo->palabra == palabra) {
            return nodo;
        }
        if (palabra < nodo->palabra) {
            return buscar(nodo->izquierda, palabra);
        } else {
            return buscar(nodo->derecha, palabra);
        }
    }

    void mostrar(Nodo* nodo, int& contador) const {
        if (nodo != nullptr) {
            mostrar(nodo->izquierda, contador);
            cout << contador << ". " << nodo->palabra << ": " << nodo->italiano << ", "
                 << nodo->frances << ", " << nodo->aleman << ", " << nodo->ingles << endl;
            contador++;
            mostrar(nodo->derecha, contador);
        }
    }

    void guardarEnArchivo(Nodo* nodo, ofstream& archivo) const {
        if (nodo != nullptr) {
            archivo << nodo->palabra << "," << nodo->italiano << "," << nodo->frances << ","
                    << nodo->aleman << "," << nodo->ingles << endl;
            guardarEnArchivo(nodo->izquierda, archivo);
            guardarEnArchivo(nodo->derecha, archivo);
        }
    }
};

void registrarUsuario() {
    string usuario, contrasena;
    cout << "Ingrese el nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese la contraseña: ";
    cin >> contrasena;

    registrarUsuario(usuario, contrasena, "llave_predeterminada");
}

bool iniciarSesion() {
    string usuario, contrasena;
    cout << "Ingrese el nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese la contraseña: ";
    cin >> contrasena;

    return verificarUsuario(usuario, contrasena, "llave_predeterminada");
}

void cargarHistorial(map<string, int>& historial) {
    ifstream archivo("historial.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string palabra;
            int contador;
            ss >> palabra >> contador;
            historial[palabra] = contador;
        }
        archivo.close();
    }
}

void guardarHistorial(const map<string, int>& historial) {
    ofstream archivo("historial.txt");
    if (archivo.is_open()) {
        for (const auto& par : historial) {
            archivo << par.first << " " << par.second << endl;
        }
        archivo.close();
    }
}
// Función para reproducir audio
void reproducirAudio(const string& palabra ) {
 // Creamos el comando para reproducir el audio utilizando espeak
    string comando = "espeak \"" + palabra + "\"";
    // Ejecutamos el comando utilizando system
    system(comando.c_str());
    }
    
int main() {
    Arbol arbol;
    string nombreArchivo = "archivo.txt";

    ifstream archivoUsuarios("credenciales.txt");
    if (!archivoUsuarios) {
        ofstream crearArchivoUsuarios("credenciales.txt");
        crearArchivoUsuarios.close();
    }

    int opcion;
    bool sesionIniciada = false;

    while (!sesionIniciada) {
        cout << "1. Registrarse\n2. Iniciar sesión\nSeleccione una opción: ";
        cin >> opcion;
        if (opcion == 1) {
            registrarUsuario();
        } else if (opcion == 2) {
            sesionIniciada = iniciarSesion();
            if (!sesionIniciada) {
                cout << "Credenciales incorrectas. Intente de nuevo.\n";
            }
        } else {
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    arbol.cargarDesdeArchivo(nombreArchivo);

    map<string, int> historial;
    cargarHistorial(historial);

do {
    cout << "1. Insertar palabra\n";
    cout << "2. Eliminar palabra\n";
    cout << "3. Mostrar palabras\n";
    cout << "4. Buscar palabra\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;
	system("cls");
    if (opcion == 1) {
        string palabra, italiano, frances, aleman, ingles;
        cout << "Ingrese la palabra en español: ";
        cin >> palabra;
        cout << "Ingrese la palabra en italiano: ";
        cin >> italiano;
        cout << "Ingrese la palabra en francés: ";
        cin >> frances;
        cout << "Ingrese la palabra en alemán: ";
        cin >> aleman;
        cout << "Ingrese la palabra en inglés: ";
        cin >> ingles;
        arbol.insertar(palabra, italiano, frances, aleman, ingles);
		system("PAUSE");
        system("cls");
		    
	} else if (opcion == 2) {
        string palabra;
        cout << "Ingrese la palabra en español a eliminar: ";
        cin >> palabra;
        arbol.eliminar(palabra);
        system("PAUSE");
        system("cls");
        
    } else if (opcion == 3) {
        arbol.mostrar();
        system("PAUSE");
        system("cls");
        
    } else if (opcion == 4) {
        string palabra;
        cout << "Ingrese la palabra en español a buscar: ";
        cin >> palabra;
        arbol.buscarYMostrar(palabra);
        reproducirAudio(palabra);

        if (historial.find(palabra) != historial.end()) {
            historial[palabra]++;
        } else {
            historial[palabra] = 1;
        }

        cout << "Historial de búsquedas:" << endl;
        for (const auto& par : historial) {
            cout << par.first << " " << par.second << endl;
        }
        system("PAUSE");
        system("cls");
    }
} while (opcion != 5);


    guardarHistorial(historial);

    return 0;
}

