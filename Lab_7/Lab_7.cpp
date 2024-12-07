#include <iostream>
#include <fstream> // Para usar ofstream
#include <cstdlib>  // Para usar malloc y free

using namespace std;

// Laboratorio 7 (Nota menor) - POA
// Nombre: Gabriel Rojas

/*
Este programa ha sido realizado como parte de la POA de ayED
*/

// Clase para representar un grafo no dirigido
class Graph {
// Atributos de la clase
private:
                       // Puestos así porque se ve más bonito (solo aquí)
    int** matrix_ad;  // Matriz de adyacencia
    int num_nodes;   // Número de nodos

public:
    // Constructor para inicializar el grafo
    Graph(int n) : num_nodes(n) {
        // Reservar memoria para la matriz de adyacencia
        matrix_ad = new int*[n];
        for (int i = 0; i < n; ++i) {
            matrix_ad[i] = new int[n];
        }
    }

    /* Destructor para liberar memoria
    El "~" significa que es un destructor para la clase. Así como el 
    constructor es un método especial que se llama cuando se crea un objeto, 
    el destructor es un método especial que se llama cuando se destruye un objeto
    */ 
    ~Graph() {
        for (int i = 0; i < num_nodes; ++i) {
        delete[] matrix_ad[i];
        }
        delete[] matrix_ad;
    }

    // Método para leer los datos desde la entrada estándar o usar un ejemplo
    void readGraph(bool flag = false) {
        if (num_nodes == 5 && flag) {
            int example_graph[5][5] = {
                {0, 2, -1, 6, -1},
                {2, 0, 3, 8, 5},
                {-1, 3, 0, -1, 7},
                {6, 8, -1, 0, 9},
                {-1, 5, 7, 9, 0}
            };
            for (int i = 0; i < num_nodes; ++i) {
                for (int j = 0; j < num_nodes; ++j) {
                    matrix_ad[i][j] = example_graph[i][j];
                }
            }
            cout << "Usando matriz de ejemplo para n = 5.\n";
        } else {
            cout << "Ingrese la matriz de distancias (usar -1 para infinito):\n";
            for (int i = 0; i < num_nodes; ++i) {
                for (int j = 0; j < num_nodes; ++j) {
                    cout << "Distancia entre " << i << " y " << j << ": ";
                    cin >> matrix_ad[i][j];
                }
            }
        }
    }

    // Método para generar un archivo Graphviz del grafo original
    void generateOriginalGraph() const {
        ofstream file("original_graph.dot");
        file << "graph G {\n";
        file << "graph [rankdir=LR];\n";
        file << "node [shape=circle style=filled fillcolor=\"#00ff005f\"];\n";

        for (int i = 0; i < num_nodes; ++i) {
            for (int j = i + 1; j < num_nodes; ++j) {
                if (matrix_ad[i][j] != -1) {
                    file << "  " << i << " -- " << j
                         << " [label=\"" << matrix_ad[i][j] << "\"];\n";
                }
            }
        }
        file << "}\n";
        file.close();

        // Generar imagen del grafo original
        cout << "Archivo 'original_graph.dot' generado.\n";
        system("dot -Tpng original_graph.dot -o original_graph.png");
        system("eog original_graph.png");
    }

    // Método para aplicar el algoritmo de Prim y generar el árbol mínimo
    void prim() {

        // Arreglo para saber si un nodo está en U
        bool* inU = new bool[num_nodes];
        
        // Arreglo para almacenar las aristas del árbol mínimo
        int** L = new int*[num_nodes - 1];
        for (int i = 0; i < num_nodes - 1; ++i) {
            L[i] = new int[2];
        }

        // Inicializar los arreglos
        for (int i = 0; i < num_nodes; ++i) inU[i] = false;

        inU[0] = true;  // Nodo inicial
        int uCount = 1;
        int lCount = 0;
        int total_cost = 0;

        // Mientras no se hayan agregado todos los nodos
        while (uCount < num_nodes) {
            int minCost = -1;
            int u = -1, v = -1;

            // Buscar la arista de menor costo (u, v)
            for (int i = 0; i < num_nodes; ++i) {
                // Si el nodo i está en U
                if (inU[i]) {
                    for (int j = 0; j < num_nodes; ++j) {
                        // Si el nodo j no está en U y hay una arista (i, j)
                        if (!inU[j] && matrix_ad[i][j] != -1 && (minCost == -1 || matrix_ad[i][j] < minCost)) {
                            minCost = matrix_ad[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            // Agregar la arista (u, v) al árbol
            if (u != -1 && v != -1) {
                L[lCount][0] = u;
                L[lCount][1] = v;
                ++lCount;

                inU[v] = true;
                ++uCount;

                total_cost += minCost;
            }
        }

        cout << "Aristas seleccionadas (L):\n";
        for (int i = 0; i < lCount; ++i) {
            cout << L[i][0] << " -- " << L[i][1] << "\n";
        }
        cout << "Costo total del árbol abarcador mínimo: " << total_cost << "\n";

        generateGraphCostMin(L, lCount);

        // Libera el arreglo dinámico inU
        delete[] inU; 
        for (int i = 0; i < num_nodes - 1; ++i) {
            // Libera cada subarreglo de L
            delete[] L[i]; 
        }
        delete[] L;
    }

    // Método para generar el archivo Graphviz del árbol de expansión mínima
    void generateGraphCostMin(int** L, int lCount) const {
        cout <<"generando archivo de grafo minimo\n";
        ofstream file("graph_min_cost.dot");
        file << "graph G {\n";
        file << "graph [rankdir=LR];\n";
        file << "node [shape=circle style=filled fillcolor=\"#00ff005f\"];\n"; // Square para diferenciarlo del grafo original
        for (int i = 0; i < lCount; ++i) {
            int u = L[i][0];
            int v = L[i][1];
            int label = matrix_ad[u][v];
            cout << "test " << u << " " << v << " " << label << "\n";
            file << "  " << L[i][0] << " -- " << L[i][1] << " [label=\"" << label <<"\"]" << ";\n";
        }
        file << "}\n";
        file.close();
        cout << "Archivo 'graph_min_cost.dot' generado.\n";

        // Generar imagen del árbol de expansión mínima
        system("dot -Tpng graph_min_cost.dot -o graph_min_cost.png");
        system("eog graph_min_cost.png");
    }
    
    // Método para ver la matriz original
    void seeOriginalMatrix(){
        system("eog original_graph.png");
    }

    // Método para ver la matriz de minimo
    void seeMinimumMatrix(){
        system("eog graph_min_cost.png");
    }
};

void menu(int n){
    int option;
    while(true){
        cout << "Menú:\n";
        cout << "1. Ingresar matriz de distancias manualmente.\n";
        cout << "2. Usar matriz de ejemplo.\n";
        cout << "3. Ver matriz de minimo.\n";
        cout << "4. Ver matriz original.\n";
        cout << "5. Salir.\n";
        cout << "Ingrese una opción: ";
        cin >> option;
        // Opción de salida primero para evitar que se ejecute el resto del código
        if(option == 5){
            cout << "Saliendo...\n";
            return;
        }
        if(option == 1){
            // Se crea un objeto de la clase Graph con n nodos los otros son 5 por ejemplificar
            Graph g(n);
            g.readGraph(false);
            g.generateOriginalGraph();
            g.prim();
        }
        else if(option == 2){
            Graph g(5);
            g.readGraph(true);
            g.generateOriginalGraph();
            g.prim();
        }
        else if(option == 3){
            // Se genera un constructor con 5 nodos para poder entrar al método
            Graph g(5);
            g.seeMinimumMatrix();
        }
        else if(option == 4){
            // Se genera un constructor con 5 nodos para poder entrar al método
            Graph g(5);
            g.seeOriginalMatrix();
        }
        else{
            cout << "Opción no válida.\n";
        }
    
    }
}   

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <número de nodos>\n";
        return 1;
    }

    int n = stoi(argv[1]);
    if (n < 2) {
        cerr << "El número de nodos debe ser mayor o igual a 2.\n";
        return 1;
    }
    
    menu(n);
    
    return 0;
}
