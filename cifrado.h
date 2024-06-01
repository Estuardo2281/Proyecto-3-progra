#ifndef CIFRADO_H
#define CIFRADO_H

#include <string>

// Declaración de la función cifrarPalabra
std::string cifrarPalabra(const std::string& palabra, const std::string& llave);

// Declaración de la función cifrarArchivo
void cifrarArchivo(const std::string& archivoEntrada, const std::string& archivoSalida, const std::string& llave);

#endif // CIFRADO_H

