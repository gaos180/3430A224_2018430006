#include "tinyxml2.h"
#include <iostream>


using namespace std;

// para compilar:
// g++ LectorDrugbank.cpp -o LectorXML -ltinyxml2
// [g++] nombre.cpp -o ejecutable -librería añadida

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

int recorrerXML(){
// se genera el elemento xml llamado doc
    tinyxml2::XMLDocument doc;

    // si la carga no es exitosa saldrá el error
    if (doc.LoadFile("archivoDrug.xml") != tinyxml2::XML_SUCCESS) {
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

        // Para leer datos de más profundidad de los fármacos hay que hacer una llamada al data con lo
        // de first Child, para ello sería otro ciclo con while distnto a nullptr

        // verifica si hay targets, en caso de que haya la base de datos está hecha para que solo haya un targets
        tinyxml2::XMLElement* targets = drug->FirstChildElement("targets");
        

        if (targets!=nullptr)
        {
            cout << "Hay targets" << endl;

            // si hay targets habrá al menos un target, pero puede haber más de uno por ello
            tinyxml2::XMLElement* target = targets->FirstChildElement("target");

            // hay que recorrer los target
            while (target != nullptr) {
                const char* targetSpecificDrugName = target->FirstChildElement("name")->GetText();


                cout << "nombre del Target: " << targetSpecificDrugName << endl;
                
                tinyxml2::XMLElement* polypeptide = target->FirstChildElement("polypeptide");
                if (polypeptide != nullptr)
                {   
                    cout << "Hay polipetidos" << endl;
                    const char* targetSpecificDrugPolyptideAminoAcid = polypeptide->FirstChildElement("amino-acid-sequence")->GetText();
                    const char* targetSpecificDrugPolyptideGeneSequence = polypeptide->FirstChildElement("gene-sequence")->GetText();
                    if (targetSpecificDrugPolyptideAminoAcid != nullptr)
                    {
                        cout << "Secuencia aminoacidica del target: " << targetSpecificDrugPolyptideAminoAcid << endl;
                    }
                    if (targetSpecificDrugPolyptideGeneSequence != nullptr)
                    {
                      cout << "Secuencia genetica del target" << targetSpecificDrugPolyptideGeneSequence << endl;
                    }
                }

                target = target->NextSiblingElement("target");
            }

        }else
        {
            // se lee mejor si se piensa que lo está leyendo Gru de mi villano favorito
            cout << "En terminos de targets, no tenemos targets" << endl;
        }
        

        cout << "-------------------" << endl;

        // siguiente elemento hermano, es decir siguiente elemento del mismo tipo
        drug = drug->NextSiblingElement("drug"); // Pasar a la siguiente droga
    }
    return 0;
}



int main() {
    int retorno;
    retorno=recorrerXML();
    return retorno;
}
