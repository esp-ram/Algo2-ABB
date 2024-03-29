#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>  // For ssize_t in Linux.


bool suma_total(const char* clave, void*dato,void* total){
    *(int*)total += *(int*)dato;
    return true;
}

bool duplicar_4_primeros(const char* clave, void* dato, void* extra){
  if(*(int*)dato > 4){
    return false;
  }
  *(int*)dato =*(int*)dato*2;
  return true;
}


static void prueba_crear_abb_vacio()
{
    printf("\nprueba abb vacio\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}


static void prueba_iterar_abb_vacio(){
    printf("\nprueba iterar abb vacio\n");
    abb_t* abb = abb_crear(strcmp,NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


static void prueba_abb_insertar()
{
    printf("\nprueba abb insertar\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
    char *clave4 = "testa", *valor4 = "test4";
    char *clave5 = "testb", *valor5 = "test5";
    char *clave6 = "testc", *valor6 = "test6";
    char *clave7 = "testd", *valor7 = "test7";


    print_test("Prueba insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba la cantidad de elementos es 0", abb_cantidad(abb) == 0);


    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave4 es valor4", abb_obtener(abb, clave4) == valor4);
    print_test("Prueba abb pertenece clave4, es true", abb_pertenece(abb, clave4));

    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
    print_test("Prueba abb obtener clave5 es valor5", abb_obtener(abb, clave5) == valor5);
    print_test("Prueba abb pertenece clave5, es true", abb_pertenece(abb, clave5));

    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Prueba abb obtener clave6 es valor6", abb_obtener(abb, clave6) == valor6);
    print_test("Prueba abb pertenece clave6, es true", abb_pertenece(abb, clave6));

    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb la cantidad de elementos es 6", abb_cantidad(abb) == 6);
    print_test("Prueba abb obtener clave7 es valor7", abb_obtener(abb, clave7) == valor7);
    print_test("Prueba abb pertenece clave7, es true", abb_pertenece(abb, clave7));


    abb_destruir(abb);
}


static void prueba_abb_reemplazar()
{
    printf("\nprueba abb reemplazar\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";


    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


static void prueba_abb_reemplazar_con_destruir()
{
    printf("\nprueba abb reemplazar con destruir\n");
    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;


    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    print_test("Prueba insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}


static void prueba_abb_clave_vacia(){
    printf("\nprueba abb clave vacia\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


static void prueba_abb_valor_null(){
    printf("\nprueba abb valor null\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = NULL;

    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    abb_destruir(abb);
}


static void prueba_abb_volumen(size_t largo, bool debug)
{
    printf("\nprueba abb volumen\n");
    abb_t* abb = abb_crear(strcmp,NULL);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%X", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);
    // REVIEW: FALLA.
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);


    abb_destruir(abb);
    abb = abb_crear(strcmp,free);

    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }
    free(claves);
    abb_destruir(abb);
}


static void prueba_abb_borrar(){
    printf("\nprueba abb borrar\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


static ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}


static void prueba_abb_iterar(){
    printf("\nprueba abb iterar\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};


    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));


    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));


    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));


    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));


    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


static void prueba_abb_iterar_volumen(size_t largo)
{
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];


    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%X", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);
    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void prueba_iterador_interno_total(){
    printf("\nprueba abb iterador interno total\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    char* claves [10] = {"h","c","f","b","d","g","i","a","e","k"};
    int arr[10] ={6,8,20,3,71,93,1,0,100,212};
    for(int i = 0; i < 10; i++){
        abb_guardar(abb, claves[i], &arr[i]);
    }
    int suma = 0;
    abb_in_order(abb, suma_total, &suma);
    print_test("suma es 514", suma == 514);
    abb_destruir(abb);
}


void prueba_iterador_interno_parcial(){
    printf("\nprueba abb iterador interno parcial\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    char* claves [10] = {"f","c","h","b","d","g","i","a","e","j"};
    int arr[10] ={6,3,8,2,4,7,9,1,5,10};
    for(int i = 0; i < 10; i++){
        abb_guardar(abb, claves[i], &arr[i]);
    }
    abb_in_order(abb, duplicar_4_primeros, NULL);
    bool resultado_correcto = true;
    abb_iter_t* iter = abb_iter_in_crear(abb);
    if(!iter){
        abb_destruir(abb);
        return;
    }
    int i = 0;
    while(!abb_iter_in_al_final(iter)){
        if(*(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != ((i+1)*2) && i < 4){
            resultado_correcto = false;
        }
        if(i >= 4 && *(int*)abb_obtener(abb,abb_iter_in_ver_actual(iter)) != (i+1)){
            resultado_correcto = false;
        }
        abb_iter_in_avanzar(iter);
        i++;
    }
    print_test("ultimos 6 elementos sin modificar", resultado_correcto);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void prueba_borrar_borde(){
    printf("\nprueba abb borrar borde\n");
    abb_t* abb = abb_crear(strcmp, NULL);
	char *clave1 = "j", *valor1 = "valor 11";
	char *clave2 = "c", *valor2 = "valor 22";
	char *clave3 = "w", *valor3 = "valor 33";
	char *clave4 = "f", *valor4 = "valor 44";
	char *clave5 = "u", *valor5 = "valor 55";
    char *clave6 = "z", *valor6 = "valor 66";
    char *clave7 = "a", *valor7 = "valor 77";
    char *clave8 = "r", *valor8 = "valor 88";


	abb_guardar(abb, clave1, valor1);
	abb_guardar(abb, clave2, valor2);
  	abb_guardar(abb, clave3, valor3);
    abb_guardar(abb, clave4, valor4);
    abb_guardar(abb, clave5, valor5);
	abb_guardar(abb, clave6, valor6);
	abb_guardar(abb, clave7, valor7);
	abb_guardar(abb, clave8, valor8);


	print_test("Borrar U con 1 hijo", abb_borrar(abb, clave5) == valor5);
	print_test("cantidad es 7",abb_cantidad(abb) == 7);
	print_test("Prueba pertenece Z, es true", abb_pertenece(abb , clave6));
	print_test("Prueba pertenece F, es true", abb_pertenece(abb , clave4));
	print_test("Prueba pertenece R, es true", abb_pertenece(abb , clave8));
	print_test("Borrar Z hoja", abb_borrar(abb, clave6) == valor6);
    print_test("cantidad es 6",abb_cantidad(abb) == 6);
	print_test("Prueba pertenece W, es true", abb_pertenece(abb , clave3));
	print_test("Prueba pertenece R, es true", abb_pertenece(abb , clave8));
	print_test("Prueba pertenece A, es true", abb_pertenece(abb , clave7));
    print_test("Borrar J con 2 hijos y es raiz", abb_borrar(abb, clave1) == valor1);
    print_test("cantidad es 5",abb_cantidad(abb) == 5);
    print_test("Prueba pertenece W, es true", abb_pertenece(abb , clave3));
    print_test("Prueba pertenece C, es true", abb_pertenece(abb , clave2));
    print_test("Prueba pertenece F, es true", abb_pertenece(abb , clave4));

    abb_destruir(abb);

}


void pruebas_abb_alumno(){
    prueba_crear_abb_vacio(); //OK
    prueba_iterar_abb_vacio(); //OK
    prueba_abb_insertar(); //OK
    prueba_abb_reemplazar(); //OK
    prueba_abb_reemplazar_con_destruir(); //OK
    prueba_abb_clave_vacia(); //OK
    prueba_abb_borrar(); //OK
    prueba_abb_valor_null(); //OK
    prueba_abb_iterar(); //OK
    prueba_abb_volumen(5000,true); //OK
    prueba_abb_iterar_volumen(2500); //OK
    prueba_iterador_interno_total();
    prueba_iterador_interno_parcial();
    prueba_borrar_borde();
}
