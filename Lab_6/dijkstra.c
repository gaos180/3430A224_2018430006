#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 0
#define FALSE 1
#define N 5

void leer_nodos (char vector[N]);
void inicializar_vector_D (int D[N], int M[N][N]);
void inicializar_vector_caracter (char vector[N]);
void aplicar_dijkstra (char V[N], char S[N], char VS[N], int D[N], int M[N][N]);
void actualizar_VS(char V[N], char S[N], char VS[N]);
int buscar_indice_caracter(char V[N], char caracter);
void agrega_vertice_a_S(char S[N], char vertice);
int elegir_vertice(char VS[N], int D[N], char V[N]);
void actualizar_pesos (int D[N], char VS[N], int M[N][N], char V[N], char v);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char vector[N], char *);
void imprimir_vector_entero(int vector[N]);
void imprimir_matriz(int matriz[N][N]);
void imprimir_grafo(int matriz[N][N], char vector[N]);

int main(int argc, char **argv) {
  char V[N], S[N], VS[N];
  int D[N];
  /*
  matriz de aproximación con los valores. Esta matriz muestra la
  relación con los vecinos más cercanos y las relaciones, -1 es infinto, 
  0 es el escogido. 0 representaría la creación de las relaciones con ese
  M es la matriz
  
  */
  // valores de prueba1.
  int M[N][N] = {{ 0, 4, 11, -1, -1},
                 {-1, 0, -1,  6,  2},
                 {-1 ,3,  0,  6, -1},
                 {-1,-1, -1,  0, -1},
                 {-1,-1,  5,  3,  0}};
  
  // valores de prueba2.
  /*int M[N][N] = {{ 0, 2,  1, -1,  3},
                 {-1, 0, -1,  4, -1},
                 {-1, 1,  0, -1,  1},
                 { 1,-1,  3,  0,  5},
                 {-1,-1, -1, -1,  0}};*/

  //
  inicializar_vector_caracter(V);
  inicializar_vector_caracter(S);
  inicializar_vector_caracter(VS);
  
  //
  leer_nodos(V);
  
  //
  aplicar_dijkstra (V, S, VS, D, M);

  //  
  imprimir_grafo(M, V);

  return 0;
}

// copia contenido inicial a D[] desde la matriz M[][].
void inicializar_vector_D (int D[N], int M[N][N]) {
  int col;
  
  for (col=0; col<N; col++) {
    D[col] = M[0][col];
  }
}

// inicializa con espacios el arreglo de caracteres.
void inicializar_vector_caracter (char vector[N]) {
  int col;
  
  for (col=0; col<N; col++) {
    vector[col] = ' ';
  }
}

// aplica el algoritmo.
void aplicar_dijkstra (char V[N], char S[N], char VS[N], int D[N], int M[N][N]) {
  int i;
  int v;
  
  // inicializar vector D[] segun datos de la matriz M[][] 
  // estado inicial.
  inicializar_vector_D(D, M);

  //
  printf("---------Estados iniciales ---------------------------------------\n");
  imprimir_matriz(M);
  printf("\n");
  imprimir_vector_caracter(S, "S");
  imprimir_vector_caracter(VS, "VS");
  imprimir_vector_entero(D);
  printf("------------------------------------------------------------------\n\n");

  // agrega primer véctice.
  printf("> agrega primer valor V[0] a S[] y actualiza VS[]\n\n");
  agrega_vertice_a_S (S, V[0]);
  imprimir_vector_caracter(S, "S");
  //
  actualizar_VS (V, S, VS);
  imprimir_vector_caracter(VS, "VS");
  imprimir_vector_entero(D);

  //
  for (i=1; i<N; i++) {
    // elige un vértice en v de VS[] tal que D[v] sea el mínimo 
    printf("\n> elige vertice menor en VS[] según valores en D[]\n");
    printf("> lo agrega a S[] y actualiza VS[]\n");
    v = elegir_vertice (VS, D, V);

    //
    agrega_vertice_a_S (S, v);
    imprimir_vector_caracter(S, "S");

    //
    actualizar_VS (V, S, VS);
    imprimir_vector_caracter(VS, "VS");

    //
    actualizar_pesos(D, VS, M, V, v);
    imprimir_vector_entero(D);
  }
}

//
void actualizar_pesos (int D[N], char VS[N], int M[N][N], char V[N], char v) {
  int i = 0;
  int indice_w, indice_v;

  printf("\n> actualiza pesos en D[]\n");
  
  indice_v = buscar_indice_caracter(V, v);
  while (VS[i] != ' ') {
    if (VS[i] != v) {
      indice_w = buscar_indice_caracter(V, VS[i]);
      D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
    }
    i++;
  }
}

//
int calcular_minimo(int dw, int dv, int mvw) {
  int min = 0;

  //
  if (dw == -1) {
    if (dv != -1 && mvw != -1)
      min = dv + mvw;
    else
      min = -1;

  } else {
    if (dv != -1 && mvw != -1) {
      if (dw <= (dv + mvw))
        min = dw;
      else
        min = (dv + mvw);
    }
    else
      min = dw;
  }
  
  printf("dw: %d dv: %d mvw: %d min: %d\n", dw, dv, mvw, min);

  return min;
}

// agrega vértice a S[].
void agrega_vertice_a_S(char S[N], char vertice) {
  int i;
  
  // recorre buscando un espacio vacio.
  for (i=0; i<N; i++) {
    if (S[i] == ' ') {
      S[i] = vertice;
      return;
    }
  }  
}

// elige vértice con menor peso en VS[].
// busca su peso en D[].
int elegir_vertice(char VS[N], int D[N], char V[N]) {
  int i = 0;
  int menor = 0;
  int peso;
  int vertice;

  while (VS[i] != ' ') {
    peso = D[buscar_indice_caracter(V, VS[i])];
    // descarta valores infinitos (-1) y 0.
    if ((peso != -1) && (peso != 0)) {
      if (i == 0) {
        menor = peso;
        vertice = VS[i];
      } else {
        if (peso < menor) {
          menor = peso;
          vertice = VS[i];
        }
      }
    }

    i++;
  }
  
  printf("\nvertice: %c\n\n", vertice);
  return vertice;
}

// retorna el índice del caracter consultado.
int buscar_indice_caracter(char V[N], char caracter) {
  int i;
  
  for (i=0; i<N; i++) {
    if (V[i] == caracter)
      return i;
  }
  
  return i;
}

// busca la aparición de un caracter en un vector de caracteres.
int busca_caracter(char c, char vector[N]) {
  int j;
  
  for (j=0; j<N; j++) {
    if (c == vector[j]) {
      return TRUE;
    }
  }
  
  return FALSE;
}

// actualiza VS[] cada ves que se agrega un elemnto a S[].
void actualizar_VS(char V[N], char S[N], char VS[N]) {
  int j;
  int k = 0;
  
  inicializar_vector_caracter(VS);
  
  for (j=0; j<N; j++){
    // por cada caracter de V[] evalua si está en S[],
    // Sino está, lo agrega a VS[].
    if (busca_caracter(V[j], S) != TRUE) {
      VS[k] = V[j];
      k++;
    }
  }
}

// lee datos de los nodos.
// inicializa utilizando código ASCII.
void leer_nodos (char vector[N]) {
  int i;
  int inicio = 97;
  
  for (i=0; i<N; i++) {
    vector[i] = inicio+i;
  }
}

// imprime el contenido de un vector de caracteres.
void imprimir_vector_caracter(char vector[N], char *nomVector) {
  int i;
  
  for (i=0; i<N; i++) {
    printf ("%s[%d]: %c ", nomVector, i, vector[i]);
  }
  printf ("\n");
}

//
void imprimir_vector_entero(int vector[N]) {
  int i;
  
  for (i=0; i<N; i++) {
    printf ("D[%d]: %d ", i, vector[i]);
  }
  printf ("\n");
}

// imprime el contenido de una matriz bidimensional de enteros.
void imprimir_matriz(int matriz[N][N]) {
  int i, j;
  
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      printf ("matriz[%d,%d]: %d ", i, j, matriz[i][j]);
    }
    printf ("\n");
  }
}

// genera y muestra apartir de una matriz bidimensional de enteros
// el grafo correspondiente.
void imprimir_grafo(int matriz[N][N], char vector[N]) {
  int i, j;
  FILE *fp;
  
  fp = fopen("grafo.txt", "w");
  fprintf(fp, "%s\n", "digraph G {");
  fprintf(fp, "%s\n", "graph [rankdir=LR]");
  fprintf(fp, "%s\n", "node [style=filled fillcolor=yellow];");
  
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      // evalua la diagonal principal.
      if (i != j) {
        if (matriz[i][j] > 0) {
          fprintf(fp, "%c%s%c [label=%d];\n", vector[i],"->", vector[j], matriz[i][j]);
        }
      }
    }
  }
  
  fprintf(fp, "%s\n", "}");
  fclose(fp);

  system("dot -Tpng -ografo.png grafo.txt");
  system("eog grafo.png &");
}
