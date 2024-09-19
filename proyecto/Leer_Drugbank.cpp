#include "tinyxml2.h"
#include <iostream>


using namespace std;

/*
se carga los datos de los archivos xml de la siguiente forma
<drugbank>
    <drug>
        <drugbank-id>
        </drugbank-id>
        <description>
        </description>
    </drug>
</drugbank>

se ve si está el primer elemento
luego se divide en otros elementos para poder hacer los valores de drugbank se recorran

es como si se generara un listado de los listados cada vez que se hace una drug

de esta manera aún si se tiene que son muchos que se llaman igual se ven guiados por la jerarquía
de los elementos

*/



int main() {
    // se genera el elemento xml llamado doc
    tinyxml2::XMLDocument doc;

    // si la carga no es exitosa saldrá el error
    if (doc.LoadFile("full_database.xml") != tinyxml2::XML_SUCCESS) {
        cerr << "Error al cargar el archivo XML" << endl;
        return -1;
    }


    // le damos el primer elemento dueño de los demás, en este caso es drugbank
    tinyxml2::XMLElement* drugbankData = doc.FirstChildElement("drugbank");
    if (drugbankData == nullptr) {
        cerr << "No se encontró el elemento drugbankData" << endl;
        return -1;
    }

    // se carga el elemento de drugas y se asigna, estando dentro de la data de drugbank
    tinyxml2::XMLElement* drug = drugbankData->FirstChildElement("drug");
    while (drug != nullptr) {
        // datos de interes
        const char* drugbankID = drug->FirstChildElement("drugbank-id")->GetText();
        const char* name = drug->FirstChildElement("name")->GetText();
        const char* description = drug->FirstChildElement("description")->GetText();

        // que se impriman estos datos de interes
        cout << "drugbankID: " << drugbankID << endl;
        cout << "nombre: " << name << endl;
        cout << "Descripcion: " << description << endl;
        cout << "-------------------" << endl;

        // siguiente elemento hermano, es decir siguiente elemento del mismo tipo
        drug = drug->NextSiblingElement("drug"); // Pasar al siguiente libro
    }

    return 0;
}
