#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"
#include "abb.h"


typedef struct nodo nodo_t;

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


enum Tipo {Derecho,Izquierdo};


typedef struct abb_iter{
    const abb_t* arbol;
    pila_t* pila;
} abb_iter_t;

/////////////AUXILIARES

nodo_t* comparacion_rec(nodo_t* inicial, const char* nuevo, nodo_t* anterior, const abb_t* arbol){
    if(inicial == NULL){
        return anterior;
    }
    int resultado = arbol->comparar_clave(inicial->clave,nuevo);
    if (resultado == 0){
        return inicial;
    }else if(resultado > 0){
        return comparacion_rec(inicial->hijo_izq,nuevo,inicial,arbol);
    }else{
        return comparacion_rec(inicial->hijo_der,nuevo,inicial,arbol);
    }
}


nodo_t* nodo_crear(const char*clave, void* valor){
    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if (nodo_nuevo == NULL){
        return NULL;
    }

    char* copiar_clave = malloc(strlen(clave)+1 * sizeof(char));
    if(copiar_clave == NULL){
        free(nodo_nuevo);
        return NULL;
    }

    strcpy(copiar_clave,clave);
    nodo_nuevo->clave = copiar_clave;
    nodo_nuevo->valor = valor;
    nodo_nuevo->hijo_izq = NULL;
    nodo_nuevo->hijo_der = NULL;
    return nodo_nuevo;
}


nodo_t* devuelve_nodo(const abb_t *arbol, const char *clave){
    nodo_t* resultado = comparacion_rec(arbol->raiz,clave,NULL,arbol);
    if (resultado != NULL && arbol->comparar_clave(resultado->clave,clave) == 0){
        return resultado;
    }
    return NULL;
}


nodo_t* encontrar_padre(nodo_t* inicial, char* clave, nodo_t* padre, abb_t* arbol){
    int resultado = arbol->comparar_clave(inicial->clave,clave);
    if (resultado == 0){
        return padre;
    }else if(resultado > 0){
        return encontrar_padre(inicial->hijo_izq,clave,inicial,arbol);
    }else{
        return encontrar_padre(inicial->hijo_der,clave,inicial,arbol);
    }
}


nodo_t* buscar_reemplazo(nodo_t* nodo){
    if(!nodo){
        return NULL;
    }
    if(nodo->hijo_izq){
        return buscar_reemplazo(nodo->hijo_izq);
    }
    return nodo;
}


void destruccion_rec(nodo_t* nodo, void destr_dato(void*)){
    if(!nodo){
        return;
    }
    destruccion_rec(nodo->hijo_izq,destr_dato);
    destruccion_rec(nodo->hijo_der,destr_dato);
    free(nodo->clave);
    if(destr_dato){
        destr_dato(nodo->valor);
    }
    free(nodo);
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
    if((arbol->raiz) == NULL){
        nodo_t* nodo_nuevo = nodo_crear(clave,dato);
        if(nodo_nuevo == NULL){
            return false;
        }
        arbol->raiz = nodo_nuevo;
        arbol->cantidad += 1;
        return true;
    }
    nodo_t* padre = comparacion_rec(arbol->raiz,clave,NULL,arbol);
    int comparacion_padre = arbol->comparar_clave(padre->clave,clave);
    if (comparacion_padre == 0){
        void* auxiliar = padre->valor;
        padre->valor = dato;
        if(arbol->destruir_dato){
            arbol->destruir_dato(auxiliar);
        }
    }else{
        nodo_t* nodo_nuevo = nodo_crear(clave,dato);
        if(nodo_nuevo == NULL){
            return false;
        }
        if (comparacion_padre > 0) {
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


void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_t* obtenido = devuelve_nodo(arbol,clave);
    if(obtenido != NULL){
        return obtenido->valor;
    }
    return NULL;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){
    if(devuelve_nodo(arbol,clave) != NULL){
        return true;
    }
    return false;
}


void borrar_completo(nodo_t* borrado, abb_t* arbol){
    nodo_t* reemplazante = buscar_reemplazo(borrado->hijo_der);
    char* clave_reemplazo = malloc(strlen(reemplazante->clave)+1 * sizeof(char));
    if (clave_reemplazo == NULL){
        return;
    }
    strcpy(clave_reemplazo,reemplazante->clave);
    void* valor_reemplazo = abb_borrar(arbol,clave_reemplazo);
    free(borrado->clave);
    borrado->clave = clave_reemplazo;
    borrado->valor = valor_reemplazo;
}


bool borrar_con_hijo(abb_t* arbol, nodo_t* borrado){
    nodo_t* padre = encontrar_padre(arbol->raiz,borrado->clave,NULL,arbol);
    if(padre == NULL){// es raiz
        if(!borrado->hijo_izq){
            arbol->raiz = borrado->hijo_der;
        }else{
            arbol->raiz = borrado->hijo_izq;
        }
        free(borrado->clave);
        free(borrado);
        return true;
    }
    int es_hijo = arbol->comparar_clave(padre->clave,borrado->clave);
    if(!borrado->hijo_izq){
        if (es_hijo < 0) {
            padre->hijo_der = borrado->hijo_der;
        }else{
            padre->hijo_izq = borrado->hijo_der;
        }
    }else{
        if (es_hijo < 0){
            padre->hijo_der = borrado->hijo_izq;
        }else{
            padre->hijo_izq = borrado->hijo_izq;
        }
    }
    free(borrado->clave);
    free(borrado);
    return true;
}


bool borrar_sin_hijos(abb_t* arbol, nodo_t* borrado){
    nodo_t* padre = encontrar_padre(arbol->raiz,borrado->clave,NULL,arbol);
    if(padre == NULL){// es raiz
        arbol->raiz = NULL;
        free(borrado->clave);
        free(borrado);
        return true;
    }
    int es_hijo = arbol->comparar_clave(padre->clave,borrado->clave);
    if(es_hijo < 0){
        padre->hijo_der = NULL;
    }else{
        padre->hijo_izq = NULL;
    }
    free(borrado->clave);
    free(borrado);
    return true;
}


void *abb_borrar(abb_t *arbol, const char *clave){
    if(arbol->raiz == NULL){
        return NULL;
    }
    nodo_t* busqueda = devuelve_nodo(arbol,clave);
    if(busqueda == NULL){
        return NULL;
    }
    void* dato_devolver = busqueda->valor;
    if((busqueda->hijo_izq != NULL) && (busqueda->hijo_der != NULL)){
        borrar_completo(busqueda, arbol);
        // TODO: revisar return de borrar_completo
        return dato_devolver;
    }else if ((busqueda->hijo_izq != NULL)|| (busqueda->hijo_der != NULL)){
        borrar_con_hijo(arbol, busqueda);
    }else{
        borrar_sin_hijos(arbol, busqueda);
    }
    arbol->cantidad -= 1;
    return dato_devolver;
}


void abb_destruir(abb_t *arbol){
    destruccion_rec(arbol->raiz,arbol->destruir_dato);
    free(arbol);
}


abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* nuevo_iter = malloc(sizeof(abb_iter_t));
    if(nuevo_iter == NULL){
        return NULL;
    }
    pila_t* nueva_pila = pila_crear();
    if(nueva_pila == NULL){
        free(nuevo_iter);
        return NULL;
    }
    nuevo_iter->arbol = arbol;
    nuevo_iter->pila = nueva_pila;
    nodo_t* apilado = arbol->raiz;
    while(apilado){
        pila_apilar(nuevo_iter->pila,apilado);
        apilado = apilado->hijo_izq;
    }
    return nuevo_iter;
}


bool abb_iter_in_avanzar(abb_iter_t *iter){
    if (abb_iter_in_al_final(iter)){
        return false;
    }
    nodo_t* nodo1 = pila_desapilar(iter->pila);
    if (nodo1->hijo_der){
        nodo_t* apilado = nodo1->hijo_der;
        while(apilado){
            pila_apilar(iter->pila,apilado);
            apilado = apilado->hijo_izq;
        }
    }
    return true;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)){
        return NULL;
    }
    return (((nodo_t*)(pila_ver_tope(iter->pila)))->clave);
}


bool abb_iter_in_al_final(const abb_iter_t *iter){
    return (pila_esta_vacia(iter->pila)==true);
}


void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}


bool aux_iter_i(nodo_t* nodo, abb_t* arbol, bool visitar(const char *, void *, void *), void *extra){
    if(nodo == NULL){
        return true;
    }
    if (aux_iter_i(nodo->hijo_izq,arbol,visitar,extra) == false){
        return false;
    }
    if (visitar(nodo->clave,nodo->valor,extra) == false){
        return false;
    }
    if (aux_iter_i(nodo->hijo_der,arbol,visitar,extra)== false){
        return false;
    }
    return true;
}


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    aux_iter_i(arbol->raiz,arbol,visitar,extra);
}
