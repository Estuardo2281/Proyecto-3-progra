#ifndef CIFRADO_H
#define CIFRADO_H

#include <string>

// Declaraci�n de la funci�n cifrarPalabra
std::string cifrarPalabra(const std::string& palabra, const std::string& llave);

// Declaraci�n de la funci�n cifrarArchivo
void cifrarArchivo(const std::string& archivoEntrada, const std::string& archivoSalida, const std::string& llave);

#endif // CIFRADO_H

