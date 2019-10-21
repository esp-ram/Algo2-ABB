
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
