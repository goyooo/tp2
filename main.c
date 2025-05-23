#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {

    // strLen
    int len1 = strLen("");
    printf("strLen(\"nada\") -> \"%i\"\n", len1);
    printf("\n");

    int len2 = strLen("v");
    printf("strLen(\"v\") -> \"%i\"\n", len2);
    printf("\n");

    int len3 = strLen("ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyz0123456789áéíóú");
    printf("strLen(\"ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyz0123456789áéíóú\") -> \"%i\"\n", len3);
    printf("\n");

    // strDup
    char* dup1 = strDup("");
    printf("strDup(\"nada\") -> \"%s\"\n", dup1);
    free(dup1);
    printf("\n");

    char* dup2 = strDup("v");
    printf("strDup(\"v\") -> \"%s\"\n", dup2);
    free(dup2);
    printf("\n");

    char* dup3 = strDup("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789áéíóú");
    printf("strDup(\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789áéíóú\") -> \"%s\"\n", dup3);
    free(dup3);
    printf("\n");

    // strCmp
    char* a1 = "";
    char* b1 = "";
    int cmp1 = strCmp(a1,b1);
    printf("strComp(\"nada, nada\") -> \"%i\"\n", cmp1);
    printf("\n");

    char* a2 = "m";
    char* b2 = "m";
    int cmp2 = strCmp(a2,b2);
    printf("strComp(\"m, m\") -> \"%i\"\n", cmp2);
    printf("\n");

    char* a3 = "manuel";
    char* b3 = "mamuel";
    int cmp31 = strCmp(a3,b3);
    int cmp32 = strCmp(b3,a3);
    printf("strComp(\"manuel, mamuel\") -> \"%i\"\n", cmp31);
    printf("strComp(\"mamuel, manuel\") -> \"%i\"\n", cmp32);
    printf("\n");

    char* a4 = "manuel";
    char* b4 = "juanmanuel";
    int cmp41 = strCmp(a4,b4);
    int cmp42 = strCmp(b4,a4);
    printf("strComp(\"manuel, juanmanuel\") -> \"%i\"\n", cmp41);
    printf("strComp(\"juanmanuel, manuel\") -> \"%i\"\n", cmp42);
    printf("\n");
    
    // pathAddFirst
    struct path* addf = pathNew();
    //añadir un nodo a un path vacío
    pathAddFirst(addf, "Paris", 48.857, 2.352);
    //añadir un nodo a un path con una única parada
    pathAddFirst(addf, "Oberá", 27.486, 55.12);
    //añadir un nodo a un path con más de una parada
    pathAddFirst(addf, "Rauch", -36.774, -59.089);
    printf("pathAddFirst");
    pathPrint(addf);
    printf("\n");

    // pathAddLast
    struct path* addl = pathNew();
    //añadir un nodo a una path vacío
    pathAddLast(addl, "Rauch", -36.774, -59.089);
    //añadir un nodo a un path con una única parada
    pathAddLast(addl, "Moose", 46.655, -11.0717);
    //añadir un nodo a un path con más de una parada
    pathAddLast(addl, "Ombada", 15.680, 32.316);
    printf("pathAddLast");
    pathPrint(addl);
    printf("\n");
    
    // pathDuplicate
    printf("pathDuplicate");
    struct path* dupp = pathNew();
    //duplicar un path vacío
    struct path* np = pathDuplicate(dupp);
    pathPrint(np);
    printf("\n");
    //duplicar un path con una unica parada
    pathAddFirst(dupp, "Rauch", -36.774, -59.089);
    struct path* np1 = pathDuplicate(dupp);
    pathPrint(np1);
    printf("\n");
    //duplicar un path con más de una parada
    pathAddLast(dupp, "Togusken", 48.371, 69.994);
    struct path* np2 = pathDuplicate(dupp);
    pathPrint(np2);
    printf("\n");

    // pathSwapStops
    printf("pathSwapStops");
    struct path* swapswap = pathNew();
    pathAddFirst(swapswap, "Venado Tuerto", -33.746, -61.960);
    pathAddFirst(swapswap, "Monte Buey", -32.918, -62.461);
    printf("original \n");
    pathPrint(swapswap);
    printf("\n");

    //Swap de ciudades con mismo nombre
    pathSwapStops(swapswap, "Venado Tuerto", "Venado Tuerto");
    printf("no deberia hacer nada\n");
    pathPrint(swapswap);
    printf("\n");

    //Swap de dos ciudades en un path con solo dos ciudades
    pathSwapStops(swapswap, "Venado Tuerto", "Monte Buey");
    printf("al vesre\n");
    pathPrint(swapswap);
    printf("\n");

    //Swap de dos ciudades tal que sean la primera y la ultima del camino
    pathAddLast(swapswap, "Oberá", 27.486, 55.12);
    pathAddLast(swapswap, "Rauch", -36.774, -59.089);

    printf("primera y ult\n");
    pathSwapStops(swapswap, "Venado Tuerto", "Rauch");
    pathPrint(swapswap);
    printf("\n");

    //pathRemoveCity
    struct path* rem = pathNew();
    pathAddFirst(rem,"Lieja", 50.639, 5.595);
    pathAddLast(rem, "Bergamo", 45.695, 9.671);
    pathAddLast(rem, "Kracovia", 50.061, 19.947);
    pathAddLast(rem, "Emmeloord", 52.708, 5.751);
    printf("original pathRemoveCity \n");
    pathPrint(rem);
    printf("\n");


    //Borrar primer ciudad de un camino de cuatro ciudades
    pathRemoveCity(rem, "Lieja");
    printf("borrar lieja, primera ciudad \n");
    pathPrint(rem);
    printf("\n");

    pathAddFirst(rem,"Palmas", -10.259, -48.328);
    //Borrar la última ciuada de un camino de cuatro ciudades
    printf("borra Emmeloord, la ultima ciudad \n");
    pathRemoveCity(rem, "Emmeloord");
    pathPrint(rem);
    printf("\n");

    //Borrar una ciudad intermedia de un camino de cuatro ciudades
    pathAddFirst(rem, "Bielefeld", 52.020, 8.535);
    printf("borra kracovia del medio \n");
    pathRemoveCity(rem, "Kracovia");
    pathPrint(rem);
    printf("\n");

    //preparo el path rem para que tenga una sola ciudad:
    pathRemoveCity(rem, "Bergamo");
    pathRemoveCity(rem, "Palmas");
    //queda solo Bielefeld
    printf("borra Bielefeld que deberia ser la unica \n");
    pathRemoveCity(rem, "Bielefeld");
    pathPrint(rem);
    printf("\n");

    // pathDelete
    //Borrar un path sin ciudades
    struct path* borrar = pathNew();
    pathDelete(borrar);
    //Borrar un path con una sola ciudad
    struct path* borrar1 = pathNew();
    pathAddFirst(borrar1, "Indio Rico", -38.328, -60.887);
    pathDelete(borrar1);
    //Borrar un path con mas de una ciuad
    pathDelete(addf);
    pathDelete(addl);
    pathDelete(dupp);
    pathDelete(np);
    pathDelete(np1);
    pathDelete(np2);
    pathDelete(swapswap);
    pathDelete(rem);

    return 0;
}
