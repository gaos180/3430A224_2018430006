#include "tinyxml2.h"
#include <iostream>


using namespace std;

// para compilar:
// g++ LectorXML.cpp -o LectorXML -ltinyxml2
// [g++] nombre.cpp -o ejecutable -librería añadida

int main() {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("archivo.xml") != tinyxml2::XML_SUCCESS) {
        cerr << "Error al cargar el archivo XML" << endl;
        return -1;
    }

    tinyxml2::XMLElement* catalogo = doc.FirstChildElement("catalogo");
    if (catalogo == nullptr) {
        cerr << "No se encontró el elemento catalogo" << endl;
        return -1;
    }

    tinyxml2::XMLElement* libro = catalogo->FirstChildElement("libro");
    while (libro != nullptr) {
        const char* titulo = libro->FirstChildElement("titulo")->GetText();
        const char* autor = libro->FirstChildElement("autor")->GetText();
        const char* precio = libro->FirstChildElement("precio")->GetText();

        cout << "Título: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Precio: " << precio << endl;
        cout << "-------------------" << endl;

        libro = libro->NextSiblingElement("libro"); // Pasar al siguiente libro
    }

    return 0;
}
