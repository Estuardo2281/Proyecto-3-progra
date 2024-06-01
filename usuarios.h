#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>

// Prototipos de las funciones utilizadas en el main.cpp
void registrarUsuario(const std::string& usuario, const std::string& contrasena, const std::string& llave);
bool verificarUsuario(const std::string& usuario, const std::string& contrasena, const std::string& llave);

#endif // USUARIOS_H

