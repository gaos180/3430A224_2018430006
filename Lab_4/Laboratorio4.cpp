#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root = nullptr;

    // Metodo recursivo privado para insertar un nodo en el arbol binario de busqueda
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posicion vacia
            return createNode(data);
        }

        if (data < node->info) {
            // Insertar en el subarbol izquierdo
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // Insertar en el subarbol derecho
            node->right = insertNode(node->right, data);
        } else {
            // El dato ya esta en el arbol
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }


    // Metodo recursivo privado para imprimir el arbol en preorden
    void printPreOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " "; // Imprimir el dato del nodo actual
        printPreOrder(node->left);  // Recorrer el subarbol izquierdo
        printPreOrder(node->right); // Recorrer el subarbol derecho
    }
    // Metodo recursivo privado para imprimir el arbol en Inorden
    void printInOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);  // Recorrer el subarbol izquierdo
        cout << node->info << " "; // Imprimir el dato del nodo actual
        printInOrder(node->right); // Recorrer el subarbol derecho
    }
    // Metodo recursivo privado para imprimir el arbol en prostorden
    void printPostOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printPostOrder(node->left);  // Recorrer el subarbol izquierdo
        printPostOrder(node->right); // Recorrer el subarbol derecho
        cout << node->info << " "; // Imprimir el dato del nodo actual
    }

    // Metodo recursivo privado para la búsqueda de un valor 
    bool search(Node* root, int dato){
        if (root == nullptr)
        {
            return false;  // Retorna falso cuando no hay
        }else if (root -> info == dato)
        {
            return true;  // Retorna verdadero cuando lo encuentra
        }else if (dato < root->info)
        {
            return search(root->left, dato); // Revisa el lado izquierdo (subarbol)
        }else{
            return search(root->right, dato); // Revisa el lado derecho (subarbol)
        }
    }

    // Elimina el nodo
    Node* deleteNode(Node* root, int key){
        if (root == nullptr)
        {
            return root;
        }
        if(key < root->info){  
            root->left = deleteNode(root->left, key);
        } else if (key > root -> info)
        {
            root->right = deleteNode(root->right, key);
        }else{
            if (root ->left == nullptr)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }else if (root -> right == nullptr)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            Node* temp = root -> right;
            while (temp->left != nullptr)
            {
                temp = temp -> left;
            }
            root ->info = temp -> info;
            root->right = deleteNode(root->right, temp->info);
            
        }
        return root;
        
    }

public:
    Arbol() : root(nullptr) {}

    // Metodo publico para insertar un nodo en el arbol
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Metodo publicos para imprimir el arbol
    void printPreOrder() const {
        printPreOrder(root);
        cout << endl;
    }

    void printInOrder() const {
        printInOrder(root);
        cout << endl;
    }
    void printPostOrder() const {
        printPostOrder(root);
        cout << endl;
    }

    // Método público para buscar el dato
    void search(int data){
        if (search(root, data))
        {
            cout << "Se encontro el dato" << endl;
        }else
        {
            cout << "No se encontro el dato" << endl;
        }
    }

    // Se encarga de buscar el dato a eliminar y eliminarlo
    void deleteInTree(int data){
        if (search(root, data)) // Usa la función de buscar
        {
            cout << "Se encontro el dato, se eliminará" << endl;
            deleteNode(root, data);

        }else
        {
            cout << "No se encontro el dato" << endl;
        }
    }

    // Encargado de modificar el arbol, eliminar un nodo y agregar otro
    void modTree(int dataBefore, int dataAfter){  // Dato antes y dato después de la modificación
        if (!search(root, dataAfter)) // Si no está el dato que se ingresará se avanzará
        {
            if(search(root, dataBefore)){ // Si está el dato que se eliminará se prosigue
                // A pesar que ambos tengan validaciones, estas son solo si ocurre su caso
                // por lo que deben de cumplirse ambos casos para que se realice
                deleteInTree(dataBefore);
                insert(dataAfter);
            }else
            {
            cout << "No se encontro el dato que se iba a eliminar" << endl;
            }
        }else
        {
            cout << "Se encontro el dato que se iba a agregar" << endl;

        }
    }

    // recorre el arbol para añadir los nodos en el formato adecuado a graphviz
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << to_string(node->info) << "->" << to_string(node->left->info) << ";" << endl;
            } else {
                string cadena = "\""+ to_string(node->info) + "i\"";
                fp << cadena << "[shape=point];" << endl;
                fp << to_string(node->info) << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << to_string(node->info)  << "->" << to_string(node->right->info) << ";" << endl;
            } else {
                string cadena = "\"" + to_string(node->info) + "d\"";
                fp << cadena << "[shape=point];" << endl;
                fp << to_string(node->info) << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

    // Generar y mostrar la visualizacion del arbol
    void visualize() {
        ofstream fp("grafo.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo grafo.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=\"#FBFF76\"];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del arbol
        system("dot -Tpng -o grafo.png grafo.txt");
        system("eog grafo.png");
    }

};

// Verifica si la opción es un int o un float
bool verificarOpcion(float opcion){
    int opcionInt = static_cast<int>(opcion); // Transforma a int sin redondear
    return (opcion == opcionInt);
}

// Insertar en el arbol lo consultará hasta que él número a insertar sea el adecuado en entero
void insertar(Arbol arbol){
    float numero_a_insertar = 0.1;
    try
    {
        // lo hace hasta que el número insertado sea verdadero
        do
        {
            cout << "Ingrese un número entero para insertar en el arbol" << endl;
            cin >> numero_a_insertar;
        } while (!verificarOpcion(numero_a_insertar));
        
    }
    catch(const exception& e)
    {
        cout << "Por favor ingrese un valor adecuado" << endl;
        cerr << e.what() << endl;
    }
    
    arbol.insert(numero_a_insertar);    

}

void buscar(Arbol arbol){
    float numero_a_buscar = 0.1;
    try
    {
        // lo hace hasta que el número ingresado un entero
        do
        {
            cout << "Ingrese un número entero para buscarlo en el arbol" << endl;
            cin >> numero_a_buscar;
        } while (!verificarOpcion(numero_a_buscar));
        
    }
    catch(const exception& e)
    {
        cout << "Por favor ingrese un valor adecuado" << endl;
        cerr << e.what() << endl;
    }
    
    arbol.search(numero_a_buscar);

}

void modificar(Arbol arbol){
    float numero_a_eliminar = 0.1;
    float numero_a_ingresar = 0.1;
    try
    {
        // lo hace hasta que el número ingresado sea un entero
        do
        {
            cout << "Ingrese el número entero a modificar del arbol" << endl;
            cin >> numero_a_eliminar;
        } while (!verificarOpcion(numero_a_eliminar));
        do
        {
            cout << "Ingrese el número entero que se colocará ahora" << endl;
            cin >> numero_a_ingresar;
        } while (!verificarOpcion(numero_a_ingresar));
        
    }
    catch(const exception& e)
    {
        cout << "Por favor ingrese un valor adecuado" << endl;
        cerr << e.what() << endl;
    }
    
    arbol.modTree(numero_a_eliminar, numero_a_ingresar);

}

void eliminar(Arbol arbol){
    float numero_a_eliminar = 0.1;
    try
    {
        // lo hace hasta que el número ingresado sea un entero
        do
        {
            cout << "Ingrese un número entero para elimnarlo del arbol" << endl;
            cin >> numero_a_eliminar;
        } while (!verificarOpcion(numero_a_eliminar));
        
    }
    catch(const exception& e)
    {
        cout << "Por favor ingrese un valor adecuado" << endl;
        cerr << e.what() << endl;
    }
    
    arbol.deleteInTree(numero_a_eliminar);

}


void menu(Arbol arbol){
    float opcion;

    while (true)
    {   
        try
        {
            // Menú
            cout<< "Menú del arbol" << endl;
            cout<< "[0] Salir" << endl;
            cout<< "[1] Insertar un valor" << endl;
            cout<< "[2] Búsqueda de un valor" << endl;
            cout<< "[3] Modificación de un valor" << endl;
            cout<< "[4] Eliminar un valor" << endl;
            cout<< "[5] Visualizar árbol en una imagen" << endl;
            cout<< "[6] Visualizar árbol en PreOrder" << endl;
            cout<< "[7] Visualizar árbol en InOrder" << endl;
            cout<< "[8] Visualizar árbol en PostOrder" << endl;
            cin >> opcion;

            if (verificarOpcion(opcion))
            {   
                // se usa un if masivo debido a que switch puede dar problemas para cerrar el ciclo (while true)
                if (opcion == 0)
                {
                    cout << "Saliendo del menú, tenga un buen día" << endl; // Para los demás valores
                    break;
                }else if (opcion == 1)
                {
                    insertar(arbol);
                }else if (opcion == 2)
                {
                    buscar(arbol);
                }else if (opcion == 3)
                {
                    modificar(arbol);
                }else if (opcion == 4)
                {
                    eliminar(arbol);
                }else if (opcion == 5)
                {
                    arbol.visualize();    
                }else if (opcion == 6)
                {
                    arbol.printPreOrder();
                }else if (opcion == 7)
                {
                    arbol.printInOrder();
                }else if (opcion == 8)
                {
                    arbol.printPostOrder();
                }else{
                    cout << "Por favor ingrese un valor adecuado" << endl; // Para los demás valores
                }
            
            }else
            {
                cout << "Por favor ingrese un valor adecuado" << endl;
            }
        }
        catch(const exception& e)
        {
            cout << endl;
            cerr << e.what() << endl;
            cout << "Por favor ingrese un valor adecuado" << endl;
        }
    }
}

int main() {
    Arbol arbol;

    // Insertar numeros en el arbol usando el metodo insert
    arbol.insert(120);
    arbol.insert(87);
    arbol.insert(140);
    arbol.insert(43);
    arbol.insert(99);
    arbol.insert(130);
    arbol.insert(22);
    arbol.insert(65);
    arbol.insert(93);
    arbol.insert(135);
    arbol.insert(56);
    
    // Imprimir el arbol en preorden, Inorden y postorder
    cout << "Recorrido en preorden: ";
    arbol.printPreOrder();
    cout << "\nRecorrido en inorden: ";
    arbol.printInOrder();
    cout << "\nRecorrido en postorden: ";
    arbol.printPostOrder();

    // Búsqueda ambos casos, está y no está
    arbol.search(22);
    arbol.search(-2);

    // Visualizar con eog
    arbol.visualize();

    // Modificar el arbol
    arbol.modTree(22, 20);

    // Volver a visualizar para ver la modificación
    arbol.visualize();

    menu(arbol);
    

    
    
    
    return 0;
}