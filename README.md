# Cubo-Rubick-OpenGL

**AKube.h** es una biblioteca que realiza una petición GET a un servidor creado específicamente para este proyecto

## Examples
`AKube.h` te proporciona una gran variedad de funciones, entre ellas hacer un petición GET a una página:
```c++
const int bufLen = 1024;
const char* szUrl = "https://akube.herokuapp.com/";
long fileSize;
char* memBuffer, * headerBuffer;
FILE* fp;
memBuffer = headerBuffer = NULL;
if (WSAStartup(0x101, &wsaData) != 0)
  return -1;
memBuffer = readUrl2(szUrl, fileSize, &headerBuffer);
```
Pero lo único que te debe interesar es como crear cubo aleatorio y como obtener su solución:
```javascript
std::string data=GetData(); //Obtenemos los datos en bruto
std::string cubo = get_cubo(data); //Obtenemos el Cubo
std::vector<std::string> solution = get_solution(data); //Obtenemos su solución
```
Devuelve un cubo que representa la cadena de caretas que lo componen. Una cara se compone de 9 caretas.
La cadena consta de 54 caracteres, 9 caretas por cara:

```javascript
"UUUUUUUUUR...F...D...L...B..."
```
`U` significa una careta del color de la cara hacia arriba,` R` significa una careta del color de la cara derecha, etc.
El siguiente diagrama muestra el orden de las caretas:

```
             +------------+
             | U1  U2  U3 |
             |            |
             | U4  U5  U6 |
             |            |
             | U7  U8  U9 |
+------------+------------+------------+------------+
| L1  L2  L3 | F1  F2  F3 | R1  R2  R3 | B1  B2  B3 |
|            |            |            |            |
| L4  L5  L6 | F4  F5  F6 | R4  R5  R6 | B4  B5  B6 |
|            |            |            |            |
| L7  L8  L9 | F7  F8  F9 | R7  R8  R9 | B7  B8  B9 |
+------------+------------+------------+------------+
             | D1  D2  D3 |
             |            |
             | D4  D5  D6 |
             |            |
             | D7  D8  D9 |
             +------------+
```
