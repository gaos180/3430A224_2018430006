#include <fstream>
#include <iostream>
using namespace std;

struct Node {
    string info;
    Node* left;
    Node* right;
};


// forma de concatenar strings: variable = "Hola " +to_string(i);

// Crear un nuevo nodo
Node* createNode(const string& data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root;

public:
    // Constructor de la clase Arbol
    Arbol(Node* node) : root(node) {}

    // Recorrer el arbol en preorden y escribir en el archivo
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = node->info + "i";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = node->info + "d";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

    // Generar y mostrar la visualizacion del arbol
    void visualize() {
        ofstream fp("arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del arbol
        system("dot -Tpng -o arbol.png arbol.txt");
        system("eog arbol.png");
    }
};

int main() {
    Node *root = NULL;
    root = createNode("est_1");
    
    root->left = createNode("est_2");
    root->right = createNode("est_3");

    root->left->left = createNode("est_4");
    root->left->right = createNode("est_5");

    root->right->left = createNode("est_6");
    root->right->right = createNode("est_7");

    root->right->right->left = createNode("est_8");
    root->left->left->right = createNode("est_9");

    Arbol arbol(root);

    arbol.visualize();

    return 0;
}