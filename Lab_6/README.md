# Sexto laboratorio Dijkstra

En este laboratorio se trabaja el código dijkstra
para compilarlo es:
g++ Lab_6.cpp -o matriz_lab6
Para ejecutarlo es:
./matriz [numero]
El número es por el usuario debe ser mayor a 2.
Se necesita tener graphviz y eog.
Está basado en el código en c que fué dado por el profesor.
No entiendo porque no funciona todo el tiempo adecuadamente. Adjuntado cuando funciona mal y cuando funciona bien visto en terminal respectivamente:
Por cierto si se usan los valores de prueba 1 funciona bien, por eso está el modo prueba para ver que funciona con determinados números

./matriz_lab6 5

|vector[0]: a||vector[1]: b||vector[2]: c||vector[3]: d||vector[4]: e|

|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
¿Desea agregar manualmente las relaciones de los nodos?
[1] si, otro número no
'

|0||-1||16||73||85|
|10||0||73||28||22|
|92||26||0||77||-1|
|63||24||-1||0||71|
|-1||-1||-1||31||0|
Estados iniciales

|0||-1||16||73||85|
|10||0||73||28||22|
|92||26||0||77||-1|
|63||24||-1||0||71|
|-1||-1||-1||31||0|
V

|vector[0]: a||vector[1]: b||vector[2]: c||vector[3]: d||vector[4]: e|
S

|vector[0]:  ||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
VS

|vector[0]:  ||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
D
D[0]: 0 D[1]: -1 D[2]: 16 D[3]: 73 D[4]: 85 
--------------------
> agrega primer valor V[0] a S[] y actualiza VS[]


S

|vector[0]: a||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
VS

|vector[0]: b||vector[1]: c||vector[2]: d||vector[3]: e||vector[4]:  |
D
D[0]: 0 D[1]: -1 D[2]: 16 D[3]: 73 D[4]: 85 

> elige vertice menor en VS[] según valores en D[]

> lo agrega a S[] y actualiza VS[]


vertice: �

v es:�
S

|vector[0]: a||vector[1]: �||vector[2]:  ||vector[3]:  ||vector[4]:  |
VS

|vector[0]: b||vector[1]: c||vector[2]: d||vector[3]: e||vector[4]:  |
Violación de segmento (`core' generado)


------- Aquí cuando funciona bien:------------------------

|vector[0]: a||vector[1]: b||vector[2]: c||vector[3]: d||vector[4]: e|

|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
|-1||-1||-1||-1||-1|
¿Desea agregar manualmente las relaciones de los nodos?
[1] si, otro número no
0

|0||88||-1||79||57|
|30||0||7||-1||-1|
|-1||-1||0||-1||-1|
|-1||76||-1||0||-1|
|49||62||52||21||0|
Estados iniciales

|0||88||-1||79||57|
|30||0||7||-1||-1|
|-1||-1||0||-1||-1|
|-1||76||-1||0||-1|
|49||62||52||21||0|
V

|vector[0]: a||vector[1]: b||vector[2]: c||vector[3]: d||vector[4]: e|
S

|vector[0]:  ||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
VS

|vector[0]:  ||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
D
D[0]: 0 D[1]: 88 D[2]: -1 D[3]: 79 D[4]: 57 
--------------------
> agrega primer valor V[0] a S[] y actualiza VS[]


S

|vector[0]: a||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
VS

|vector[0]: b||vector[1]: c||vector[2]: d||vector[3]: e||vector[4]:  |
D
D[0]: 0 D[1]: 88 D[2]: -1 D[3]: 79 D[4]: 57 

> elige vertice menor en VS[] según valores en D[]

> lo agrega a S[] y actualiza VS[]


vertice: e

v es:e
S

|vector[0]: a||vector[1]: e||vector[2]:  ||vector[3]:  ||vector[4]:  |
VS

|vector[0]: b||vector[1]: c||vector[2]: d||vector[3]:  ||vector[4]:  |
D
D[0]: 0 D[1]: 88 D[2]: 109 D[3]: 78 D[4]: 57 

> elige vertice menor en VS[] según valores en D[]

> lo agrega a S[] y actualiza VS[]


vertice: d

v es:d
S

|vector[0]: a||vector[1]: e||vector[2]: d||vector[3]:  ||vector[4]:  |
VS

|vector[0]: b||vector[1]: c||vector[2]:  ||vector[3]:  ||vector[4]:  |
D
D[0]: 0 D[1]: 88 D[2]: 109 D[3]: 78 D[4]: 57 

> elige vertice menor en VS[] según valores en D[]

> lo agrega a S[] y actualiza VS[]


vertice: b

v es:b
S

|vector[0]: a||vector[1]: e||vector[2]: d||vector[3]: b||vector[4]:  |
VS

|vector[0]: c||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
D
D[0]: 0 D[1]: 88 D[2]: 95 D[3]: 78 D[4]: 57 

> elige vertice menor en VS[] según valores en D[]

> lo agrega a S[] y actualiza VS[]


vertice: c

v es:c
S

|vector[0]: a||vector[1]: e||vector[2]: d||vector[3]: b||vector[4]: c|
VS

|vector[0]:  ||vector[1]:  ||vector[2]:  ||vector[3]:  ||vector[4]:  |
D
D[0]: 0 D[1]: 88 D[2]: 95 D[3]: 78 D[4]: 57 

Cuando funciona mal el vector escogido es uno fuera de rango, una letra ascii que no corresponde a las que debería
