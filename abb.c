#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct nodo{
    char* clave;
    void* valor;
    nodo_t* hijo_izq;
    nodo_t* hijo_der;
}nodo_t;


typedef struct abb{
    nodo_t* raiz;
    size_t cantidad;
    abb_comparar_clave_t comparar_clave;
    abb_destruir_dato_t destruir_dato;
}abb_t;



/////////////AUXILIARES

nodo_t* comparacion_rec(nodo_t* inicial, const char* nuevo, nodo_t* anterior){
    if(inicial == NULL){
        return anterior;
    }
    int resultado = arbol->comparar_clave(inicial->clave,nuevo);
    if (resultado == 0){
        //existe un nodo con la misma clave.
        return inicial;
    }else if(resultado < 0){
        //se mueve a la izquierda
        return comparacion_rec(inicial->hijo_izq,nuevo,inicial);
    }else{
        //se mueve a la derecha
        return comparacion_rec(inicial->hijo_der,nuevo,inicial);
    }
}


nodo_t* nodo_crear(char*clave, void* valor){
    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if (nodo_nuevo == NULL){
        return NULL;
    }

    char* copiar_clave = calloc(strlen(clave)+1,sizeof(char));
    if (copiar_clave == NULL){
        free(nodo_nuevo);
        return NULL;
    }

    strcpy(copiar_clave,clave);
    nodo_nuevo->valor = valor;
    nodo_nuevo->clave = copiar_clave;
    nodo_nuevo->hijo_izq = NULL;
    nodo_nuevo->hijo_der = NULL;
    return nodo_nuevo;
}


////////////////PRIMITIVAS

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb_nuevo = malloc(sizeof(abb_t));

    if (abb_nuevo == NULL){
        return NULL;
    }

    abb_nuevo->raiz = NULL;
    abb_nuevo->cantidad = 0;
    abb_nuevo->comparar_clave = cmp;
    abb_nuevo->destruir_dato = destruir_dato;

    return abb_nuevo;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_t* padre = comparacion_rec(arbol->raiz,clave,NULL);
    int comparacion_padre = arbol->comparar_clave(padre->clave,clave);
    if (padre != NULL && comparacion_padre == 0){
        void* auxiliar = padre->valor;
        padre->valor = dato;
        if(arbol->destruir_dato){
            arbol->destruir_dato(auxiliar);
        }
    }else{
        nodo_t* nodo_nuevo = nodo_crear(clave,valor);
        if(nodo_nuevo == NULL){
            return false;
        }

        if (padre == NULL) {
            arbol->raiz = nodo_nuevo;
        } else if (comparacion_padre < 1) {
            padre->hijo_izq = nodo_nuevo;
        } else {
            padre->hijo_der = nodo_nuevo;
        }
        arbol->cantidad += 1;
    }
    return true;
}


size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}
