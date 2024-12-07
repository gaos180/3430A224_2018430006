#include <stdlib.h>
#include <iostream>
#include <climits> // permite el uso de INT_MAX
#include <fstream>

// para randoms
#include <cstdlib>
#include <ctime>

/*
 * g++ Lab_6.cpp -o matriz_lab6
 * su ejecución es con
 * ./matriz [numero]
 * así se hace el tamaño de la matriz
 */

using namespace std;

// Usar INT_MAX me permite colocarle el máximo en caso de al arreglo.
// Ya que c no permite no definir el tamaño de un arreglo antes
void leer_nodos (string vector[], int n) {
  int i;
  int inicio = 97; // usa ascii desde el 97 para abcd...etc.
  
  for (i=0; i<n; i++) {
    vector[i] = inicio+i;
  }
}

void imprimir_vector_entero(int vector[], int n) {
    int i;
    for (i=0; i<n; i++) {
        printf ("D[%d]: %d ", i, vector[i]);
    }
    printf ("\n");
}

// inicializa un vector. recibe el vector como un puntero.
void inicializar_vector_caracter (string *vector, int n) {
    int col;
  
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = ' ';
    }
}

// imprime un vector. recibe el vector como un puntero.
void imprimir_vector_caracter(string *vector, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "|" << "vector[" << i << "]: " << vector[i] << "|";
    }
    cout << endl;
}

// inicializa matriz nxn. recibe puntero a la matriz.
void inicializar_matriz_enteros (int **matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = -1;
        }
    }
}

void cambio_random_matriz_enteros(int **matriz, int n) {
    srand(time(NULL));
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            if (col == fila )
            {
                matriz[fila][col] = 0;
            }else{
                int valor_aleatorio1 = rand() % 2;
                if (valor_aleatorio1 == 0)
                {
                    int valor_aleatorio = rand() % 100 + 1;
                    matriz[fila][col] = valor_aleatorio;
                }else{
                    matriz[fila][col] = -1;
                }
                
            }
        }
    }
}

void modo_prueba(int **matriz, int n, string vector[]) {
    int M[n][n] = {{ 0, 4, 11, -1, -1},
                 {-1, 0, -1,  6,  2},
                 {-1 ,3,  0,  6, -1},
                 {-1,-1, -1,  0, -1},
                 {-1,-1,  5,  3,  0}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = M[i][j];
        }
    }
}

void cambio_manual_matriz_enteros(int **matriz, int n, string vector[INT_MAX]) {
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            if (fila == col)
            {
                matriz[fila][col] = 0;
            }else{
            cout << "Ingrese el valor para la interacción de los nodos " << vector[fila] << " con el nodo " << vector[col] << ": ";
            cin >> matriz[fila][col];
            }
        }
    }
}

// imprime matriz.
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            cout << "|" << matriz[fila][col] << "|";
        }
        cout << endl;
    }
}

void inicializar_vector_D(int D[], int **M, int n) {
    for (int col = 0; col < n; col++) {
        D[col] = M[0][col];  // Acceso a los elementos de la matriz como puntero a puntero
    }
}

void agrega_vertice_a_S(string S[], char vertice, int n) {
  int i;
  // recorre buscando un espacio vacio, me daba error el S[0]. no sé pq funciona con [i][0].
    for (i=0; i<n; i++) {
        if (S[i][0]  == ' ') {
            S[i] = vertice;
            return;
        }
    }  
}

bool busca_caracter(char c, string vector[], int n) {
  int j;
  
  for (j=0; j<n; j++) {
    if (c == vector[j][0]) {
      return true;
    }
  }
  
  return false;
}

// actualiza VS[] cada ve< que se agrega un elemento a S[].
void actualizar_VS(string V[], string S[], string VS[], int n) {
    int j;
    int k = 0;

    inicializar_vector_caracter(VS, n);

    for (j=0; j<n; j++){
        char c = V[j][0];
        // por cada caracter de V[] evalua si está en S[],
        // Sino está, lo agrega a VS[].
        if (busca_caracter(c, S, n) != true) {
            VS[k] = V[j];
            k++;
        }
    }
}

int buscar_indice_caracter(string V[], char caracter, int n) {
    int i;

    for (i=0; i<n; i++) {
        if (V[i][0] == caracter)
            return i;
    }

    return i;
}


int elegir_vertice(string VS[], int D[], string V[], int n) {
    int i = 0;
    int menor = 0;
    int peso;
    char vertice;    
    while (VS[i][0] != ' ') {
        peso = D[buscar_indice_caracter(V, VS[i][0], n)];
        // descarta valores infinitos (-1) y 0.
        if ((peso != -1) && (peso != 0)) {
            if (i == 0) {
                menor = peso;
                vertice = VS[i][0];
            } else {
                if (peso < menor) {
                    menor = peso;
                    vertice = VS[i][0];
                }
            }
        } 
        i++;
    }

    printf("\nvertice: %c\n\n", vertice);
    return vertice;
}

// 
int calcular_minimo(int dw, int dv, int mvw) {
    int min = 0;
    
    if (dw == -1) {
        if (dv != -1 && mvw != -1) {
            min = dv + mvw;
        } else {
            min = dw;  // Mantiene el infinito
        }
    } else {
        if (dv != -1 && mvw != -1 && (dv + mvw < dw)) {
            min = dv + mvw;
        } else {
            min = dw;  // Mantiene la distancia original
        }
    }
    
    return min;
}

void actualizar_pesos(int D[], string VS[], int **M, string V[], char v, int n) {
    // busca el indice v
    int indice_v = buscar_indice_caracter(V, v, n);
    
    for (int i = 0; i < n; i++) {
        if (VS[i][0] != ' ' && VS[i][0] != v) {
            // busca el indice w, 
            int indice_w = buscar_indice_caracter(V, VS[i][0], n);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
    }
}





void aplicar_dijkstra(string V[], string S[], string VS[], int D[], int **M, int n) {
    // iterador
    int i;
    // vertice escogido
    char v;
    
    inicializar_vector_D(D, M, n);
    cout << "Estados iniciales" << endl;
    imprimir_matriz(M, n);
    cout << "V" << endl;
    imprimir_vector_caracter(V, n);
    cout << "S" << endl;
    imprimir_vector_caracter(S, n);
    cout << "VS" << endl;
    imprimir_vector_caracter(VS, n);
    cout << "D" << endl;
    imprimir_vector_entero(D, n);
    cout << "--------------------" << endl;

    // agrega primer véctice.
    cout << "> agrega primer valor V[0] a S[] y actualiza VS[]\n\n" << endl; 
    agrega_vertice_a_S(S, V[0][0], n);

    cout << "S" << endl;
    imprimir_vector_caracter(S, n);

    actualizar_VS(V, S, VS, n);
    cout << "VS" << endl;
    imprimir_vector_caracter(VS, n);
    cout << "D" << endl;
    imprimir_vector_entero(D, n);

    for (i = 1; i < n; i++)
    {
        // elige un vértice en v de VS[] tal que D[v] sea el mínimo 
        cout << "\n> elige vertice menor en VS[] según valores en D[]\n" << endl;
        cout << "> lo agrega a S[] y actualiza VS[]\n" << endl;
        v = elegir_vertice(VS, D, V, n);
        cout << "v es:" << v << endl;

        //
        agrega_vertice_a_S(S, v, n);
        cout << "S" << endl;
        
        //
        imprimir_vector_caracter(S, n);
        actualizar_VS(V, S, VS, n);
        
        //
        cout << "VS" << endl;
        imprimir_vector_caracter(VS, n);
        
        // aquí falta actualizar los pesos y calcular el mínimo
        actualizar_pesos(D, VS, M, V, v, n);
        cout << "D" << endl;
        imprimir_vector_entero(D, n);
    }
    
}

// hace el grafo y lo muestra
void imprimir_grafo(int ** matriz, string vector[], int n) {
    ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "graph [rankdir=LR];\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] > 0) {
                // vector letra[i] -> vector letra[j] [etiqueta = dirección]
                fp << vector[i] << " -> " << vector[j] << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

//
int main(int argc, char **argv) {
    // número de elementos.
    int n;
    // opción de como se colocan los nodos
    int opc;
    

    // valida cantidad de parámetros mínimos.
    if (argc < 2) {
        cout << "Uso: \n./matriz n" << endl;
        return -1;
    }
    
    // convierte string a entero.
    n = atoi(argv[1]);

    // vectores, V -> vector de nodos, letras, S vector que recorre (el camino que recorre)
    string V[n];
    string S[n];
    string VS[n];
    // VS nodos que faltan por ver

    // esta vinculado a la matriz, que es las distancia de los nodos
    int D[n];

    // inicializa e imprime vectores.
    inicializar_vector_caracter(V, n);
    inicializar_vector_caracter(S, n);
    inicializar_vector_caracter(VS, n);

    // basicamente crea letras con el código ascii respecto a las letras abecedario, hasta n
    leer_nodos(V, n);


    imprimir_vector_caracter(V, n);

    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++)
        matriz[i] = new int[n];

    inicializar_matriz_enteros(matriz, n);
    imprimir_matriz(matriz, n);

    cout << "¿Desea agregar manualmente las relaciones de los nodos?\n[1] si, otro número no" << endl;
    if (n==5)
    {
        cout << "[2] Si desea se puede usar los valores de prueba" << endl;

    }
    
    cin >> opc;
    if (opc == 1)
    {
        cambio_manual_matriz_enteros(matriz, n, V);
    }else if ( opc ==2 && n==5)
    {
        modo_prueba(matriz, n, V);
    }else
    {
        /* random*/
        cambio_random_matriz_enteros(matriz, n);
    }
    
    imprimir_matriz(matriz, n);
    
    aplicar_dijkstra(V, S, VS, D, matriz, n);

    imprimir_grafo(matriz, V, n);
    return 0;
}