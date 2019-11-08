#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct abb abb_t;
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);
typedef struct abb_iter abb_iter_t;


//PRE: se pasan dos funciones existentes:
// una de comparacion de dos char* (modo de comparacion: <0 si la primera es menor, >0 si la segunda es menor, 0 si son iguales)
// y otra de destruccion de datos
//POST: se crea un arbol vacio. devuelve NULL si hubo un error
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

//PRE: el arbol fue creado.
//POST: guarda el dato con su correspondiente clave en el arbol. devuelve true si se pudo guardar, false si falla.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

//PRE: el arbol fue creado.
//POST: borra el valor asociado a esa clave en el arbol.se devuelve el valor si la clave existe, NULL en cualquier otro caso.
void *abb_borrar(abb_t *arbol, const char *clave);

//PRE: el arbol fue creado.
//POST: devuelve el valor asociado a la clave en el arbol, NULL en cualquier otro caso
void *abb_obtener(const abb_t *arbol, const char *clave);

//PRE: el arbol fue creado.
//POST: devuelve true si existe la clave en el arbol, false en caso contrario
bool abb_pertenece(const abb_t *arbol, const char *clave);

//PRE: el arbol fue creado.
//POST: devuelve la cantidad de elementos en el arbol
size_t abb_cantidad(abb_t *arbol);

//PRE: el arbol fue creado.
//POST: destruye el arbol, si se paso una funcion de destruccion de datos tambien libera los datos que contenia
void abb_destruir(abb_t *arbol);



//PRE: el arbol fue creado, la funcion visitar recibe una clave y dos datos y devuelve true si puede seguir iterando
// o false en caso contrario.
//POST: se recorre el arbol(de acuerdo con el recorrido in-order) hasta que recibe un false
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);



//PRE: el arbol fue creado
//POST: crea un iterador externo. devuelve NULL si no pudo ser creado
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//PRE: el arbol fue creado al igual que el iterador.
//POST: avanza una posicion en el arbol(de acuerdo con el recorrido in-order), devuelve false si no puede lograrlo.
bool abb_iter_in_avanzar(abb_iter_t *iter);

//PRE: el arbol fue creado al igual que el iterador.
//POST: devuelve la clave sobre la que esta posicionado. NULL si esta al final
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

//PRE: el arbol fue creado al igual que el iterador.
//POST: devuelve true si se encuentra al final, false en caso contrario.
bool abb_iter_in_al_final(const abb_iter_t *iter);

//PRE: el arbol fue creado al igual que el iterador.
//POST: libera la memoria asociada al iterador.
void abb_iter_in_destruir(abb_iter_t* iter);


void pruebas_abb_alumno();
