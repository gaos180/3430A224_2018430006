#include <iostream>
#include <libpq-fe.h>
#include <string>

// compilar y cargar
// g++ -o conectando conectando.cpp -lpq -I/usr/include/postgresql
// ./drug_program


void connectDB(PGconn* &conn) {
    conn = PQconnectdb("dbname=druggraph user=drug_user password=pasta-base");
    if (PQstatus(conn) == CONNECTION_BAD) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Connected to database successfully!" << std::endl;
    }
}

// Insertar en drug (IDs como VARCHAR)
void insertDrug(PGconn *conn, const std::string &drug_id, const std::string &name) {
    std::string query = "INSERT INTO drug (drug_id, name) VALUES ('" + drug_id + "', '" + name + "');";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Drug inserted successfully!" << std::endl;
    }
    PQclear(res);
}

// Insertar en target (IDs como VARCHAR)
void insertTarget(PGconn *conn, const std::string &target_id, const std::string &name, const std::string &sequence) {
    std::string query = "INSERT INTO target (target_id, name, amino_acid_sequence) VALUES ('" + target_id + "', '" + name + "', '" + sequence + "');";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Insert failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Target inserted successfully!" << std::endl;
    }
    PQclear(res);
}

// Seleccionar todos los registros de la tabla drug
void selectDrugs(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM drug;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Select failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            std::cout << "Drug ID: " << PQgetvalue(res, i, 0) << ", Name: " << PQgetvalue(res, i, 1) << std::endl;
        }
    }
    PQclear(res);
}

// Seleccionar un solo registro de la tabla drug por ID
void selectDrug(PGconn *conn, const std::string &drug_id) {
    std::string query = "SELECT drug_id, name FROM drug WHERE drug_id = '" + drug_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            std::cout << "Drug ID: " << PQgetvalue(res, i, 0) << ", Name: " << PQgetvalue(res, i, 1) << std::endl;
        }
    } else {
        std::cerr << "Select failed: " << PQerrorMessage(conn) << std::endl;
    }
    PQclear(res);
}

// Seleccionar todos los registros de la tabla target
void selectTargets(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM target;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Select failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            std::cout << "Target ID: " << PQgetvalue(res, i, 0) << ", Name: " << PQgetvalue(res, i, 1)
                      << ", Amino Acid Sequence: " << PQgetvalue(res, i, 2) << std::endl;
        }
    }
    PQclear(res);
}

// Actualizar un registro en drug por ID
void updateDrug(PGconn *conn, const std::string &drug_id, const std::string &new_name) {
    std::string query = "UPDATE drug SET name = '" + new_name + "' WHERE drug_id = '" + drug_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Update failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Drug updated successfully!" << std::endl;
    }
    PQclear(res);
}

// Actualizar un registro en target por ID
void updateTarget(PGconn *conn, const std::string &target_id, const std::string &new_name) {
    std::string query = "UPDATE target SET name = '" + new_name + "' WHERE target_id = '" + target_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Update failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Target updated successfully!" << std::endl;
    }
    PQclear(res);
}

// Eliminar un registro de la tabla drug por ID
void deleteDrug(PGconn *conn, const std::string &drug_id) {
    std::string query = "DELETE FROM drug WHERE drug_id = '" + drug_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Delete failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Drug deleted successfully!" << std::endl;
    }
    PQclear(res);
}

// Eliminar un registro de la tabla target por ID
void deleteTarget(PGconn *conn, const std::string &target_id) {
    std::string query = "DELETE FROM target WHERE target_id = '" + target_id + "';";
    PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Delete failed: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Target deleted successfully!" << std::endl;
    }
    PQclear(res);
}

int main() {
    PGconn *conn = nullptr;
    connectDB(conn);
    
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
}
