#include "tinyxml2.h"
#include <iostream>
#include <unordered_set> // Permite hash table, así almacenar valores unicos mejor
#include <string>
#include <libpq-fe.h>
#include <string>




using namespace std;

// para compilar:
// g++ -o rellenandoTargetAll RellenandoBaseConTargetsAll.cpp -ltinyxml2 -lpq -I/usr/include/postgresql

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



// Conectando con la base de datos
void connectDB(PGconn* &conn) {
    conn = PQconnectdb("dbname=druggraph user=drug_user password=pasta-base");
    if (PQstatus(conn) == CONNECTION_BAD) {
        cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Connected to database successfully!" << endl;
    }
}

// Insertar en drug (IDs como VARCHAR)
void insertDrug(PGconn *conn, const string &drug_id, const string &name) {
    string query = "INSERT INTO drug (drug_id, name) VALUES ('" + drug_id + "', '" + name + "');";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        cerr << "Insert failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Drug inserted successfully!" << endl;
    }
    PQclear(res);
}

// Insertar en target (IDs como VARCHAR)
void insertTarget(PGconn *conn, const string &target_id, const string &name, const string &sequence) {
    // query normal para agregar con insert
    // string query = "INSERT INTO target (target_id, name, amino_acid_sequence) VALUES ('" + target_id + "', '" + name + "', '" + sequence + "');";
    
    // query para insertar si no existe
    // ejemplo: SELECT insertar_usuario('Juan Pérez', 'juan@example.com');
    string query = "SELECT insertar_target('" + target_id + "', '" + name + "', '" + sequence + "');";
    
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        //cerr << "Insert failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Target inserted successfully!" << endl;
    }
    PQclear(res);
}

void insertTargetAll(PGconn *conn, const string &target_id, const string &name) {
    
    string query = "SELECT insertar_target('" + target_id + "', '" + name + "');";
    
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        //cerr << "Insert failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Target inserted successfully!" << endl;
    }
    PQclear(res);
}


// Seleccionar todos los registros de la tabla drug
void selectDrugs(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM drug;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        cerr << "Select failed: " << PQerrorMessage(conn) << endl;
    } else {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            cout << "Drug ID: " << PQgetvalue(res, i, 0) << ", Name: " << PQgetvalue(res, i, 1) << endl;
        }
    }
    PQclear(res);
}

// Seleccionar un solo registro de la tabla drug por ID
void selectDrug(PGconn *conn, const string &drug_id) {
    string query = "SELECT drug_id, name FROM drug WHERE drug_id = '" + drug_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            cout << "Drug ID: " << PQgetvalue(res, i, 0) << ", Name: " << PQgetvalue(res, i, 1) << endl;
        }
    } else {
        cerr << "Select failed: " << PQerrorMessage(conn) << endl;
    }
    PQclear(res);
}

// Seleccionar todos los registros de la tabla target
void selectTargets(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM target;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        cerr << "Select failed: " << PQerrorMessage(conn) << endl;
    } else {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            cout << "Target ID: " << PQgetvalue(res, i, 0) << ", Name: " << PQgetvalue(res, i, 1)
                      << ", Amino Acid Sequence: " << PQgetvalue(res, i, 2) << endl;
        }
    }
    PQclear(res);
}

// Actualizar un registro en drug por ID
void updateDrug(PGconn *conn, const string &drug_id, const string &new_name) {
    string query = "UPDATE drug SET name = '" + new_name + "' WHERE drug_id = '" + drug_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        cerr << "Update failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Drug updated successfully!" << endl;
    }
    PQclear(res);
}

// Actualizar un registro en target por ID
void updateTarget(PGconn *conn, const string &target_id, const string &new_name) {
    string query = "UPDATE target SET name = '" + new_name + "' WHERE target_id = '" + target_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        cerr << "Update failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Target updated successfully!" << endl;
    }
    PQclear(res);
}

// Eliminar un registro de la tabla drug por ID
void deleteDrug(PGconn *conn, const string &drug_id) {
    string query = "DELETE FROM drug WHERE drug_id = '" + drug_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        cerr << "Delete failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Drug deleted successfully!" << endl;
    }
    PQclear(res);
}

// Eliminar un registro de la tabla target por ID
void deleteTarget(PGconn *conn, const string &target_id) {
    string query = "DELETE FROM target WHERE target_id = '" + target_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        cerr << "Delete failed: " << PQerrorMessage(conn) << endl;
    } else {
        cout << "Target deleted successfully!" << endl;
    }
    PQclear(res);
}


int recorrerXML(){

    // conectando con la base de datos    
    PGconn *conn = nullptr;
    connectDB(conn);

// se genera el elemento xml llamado doc
    tinyxml2::XMLDocument doc;
    
    //unordered_set<string> targets_unicos;
    // hash table sin orden, el orden no importa porque estará en la base de datos así como salga el id (no)

    // si la carga no es exitosa saldrá el error


    // archivoDrug.xml prueba
    // full_database.xml base de datos


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
        //const char* name = drug->FirstChildElement("name")->GetText();
        //const char* description = drug->FirstChildElement("description")->GetText();

        // que se impriman estos datos de interes
        //cout << "drugbankID: " << drugbankID << endl;
        //cout << "nombre: " << name << endl;
        //cout << "Descripcion: " << description << endl;

        // Para leer datos de más profundidad de los fármacos hay que hacer una llamada al data con lo
        // de first Child, para ello sería otro ciclo con while distnto a nullptr

        // verifica si hay targets, en caso de que haya la base de datos está hecha para que solo haya un targets
        tinyxml2::XMLElement* targets = drug->FirstChildElement("targets");

        if (targets!=nullptr)
        {
            //cout << "Hay targets" << endl;

            // si hay targets habrá al menos un target, pero puede haber más de uno por ello
            tinyxml2::XMLElement* target = targets->FirstChildElement("target");

            // hay que recorrer los target
            while (target != nullptr) {
                
                const char* targetSpecificTargetName = target->FirstChildElement("name")->GetText();
                //cout << "nombre del Target: " << targetSpecificTargetName << endl;
                const char* targetSpecificTargetID = target->FirstChildElement("id")->GetText();
                
                //targets_unicos.insert(targetSpecificTargetID);
                insertTargetAll(conn, targetSpecificTargetID, targetSpecificTargetName);

                tinyxml2::XMLElement* polypeptide = target->FirstChildElement("polypeptide");
                //       <id>BE0000048</id>
                if (polypeptide != nullptr)
                {   
                    //cout << "Hay polipetidos" << endl;
                    const char* targetSpecificTargetPolyptideAminoAcid = polypeptide->FirstChildElement("amino-acid-sequence")->GetText();
                    const char* targetSpecificTargetPolyptideGeneSequence = polypeptide->FirstChildElement("gene-sequence")->GetText();
                    if (targetSpecificTargetPolyptideAminoAcid != nullptr)
                    {
                        //cout << "Secuencia aminoacidica del target: " << targetSpecificTargetPolyptideAminoAcid << endl;
                        //cout << targetSpecificTargetID << " | " << targetSpecificTargetName << " | " << targetSpecificTargetPolyptideAminoAcid << endl;
                        // void insertTarget(PGconn *conn, const string &target_id, const string &name, const string &sequence) {
                        insertTarget(conn, targetSpecificTargetID, targetSpecificTargetName, targetSpecificTargetPolyptideAminoAcid);
                    }
                    if (targetSpecificTargetPolyptideGeneSequence != nullptr)
                    {
                    //cout << "Secuencia genetica del target" << targetSpecificTargetPolyptideGeneSequence << endl;
                    }
                }
                target = target->NextSiblingElement("target");
            }

        }else
        {
            // se lee mejor si se piensa que lo está leyendo Gru de mi villano favorito
            cout << "En terminos de targets, no tenemos targets" << endl;
        }
        


        // siguiente elemento hermano, es decir siguiente elemento del mismo tipo
        drug = drug->NextSiblingElement("drug"); // Pasar a la siguiente droga
    }

    /*
    cout << "Cantidad de targets:" << targets_unicos.size() << endl;    


    
    for (auto it = targets_unicos.begin(); it != targets_unicos.end(); ++it) {
        string target = *it;
        cout << target << endl;
    }
    */

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));  

        PQfinish(conn);
        exit(1);
    }

    PQfinish(conn);



    return 0;
}


int main() {

    int retorno;
    retorno=recorrerXML();
    return retorno;

    /*
    // Insertar un nuevo fármaco
    insertDrug(conn, "D001", "Aspirin");

    // Insertar un nuevo target
    insertTarget(conn, "T001", "Protein A", "MKTAYIAKQRQISFVKSHFSRQLEERLGLIEVQYAG...");

    // Mostrar todos los fármacos
    selectDrugs(conn);

    // Mostrar todos los targets
    selectTargets(conn);

    deleteDrug(conn, "D001");

    deleteTarget(conn, "T001");

    // Mostrar todos los fármacos
    selectDrugs(conn);

    // Mostrar todos los targets
    selectTargets(conn);

    // Cerrar la conexión
    PQfinish(conn);
    return 0;
    */
   return 0;
}
