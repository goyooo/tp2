#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {

    // COMPLETAR

    // A Continuacion dejamos algunos ejemplos de como
    // llamar a las funciones pedidas. Este codigo debe
    // ser borrado / modificado.

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
    char* b4 = "manu";
    int cmp4 = strCmp(a4,b4);
    int cmp4 = strCmp(b4,a4);
    printf("strComp(\"manuel, juanmanuel\") -> \"%i\"\n", cmp4);
    printf("\n");

    // pathNew
    struct path* addf = pathNew();
    struct path* addl = pathNew();
    struct path* dupp = pathNew();

    // pathAddFirst
    pathAddFirst(addf, "Paris", 48.857, 2.352);
    pathAddFirst(addf, "Obera", 27.486, 55.12);
    pathAddFirst(addf, "Rauch", -36.774, -59.089);

    // pathAddLast
    pathAddLast(addl, "Rauch", -36.774, -59.089);
    pathAddLast(addl, "Moose", 46.655, -11.0717);
    pathAddLast(addl, "Ombada", 15.680, 32.316);
    
    // pathDuplicate
    struct path* np = pathDuplicate(dupp);
    pathPrint(np);
    printf("\n");
    pathAddFirst(dupp, "Rauch", -36.774, -59.089);
    struct path* np1 = pathDuplicae(dupp);
    pathPrint(np);
    printf("\n");
    pathAddLast(dupp, "Togusken", 48.371, 69.994);
    struct path* np2 = pathDuplicate(dupp);
    pathPrint(np);
    printf("\n");

    //pathPrint(np);

    // pathSwapStops
    pathSwapStops(np, "Buenos Aires", "Rauch");
    pathPrint(np);

    // pathRemoveCity
    //pathRemoveCity(p, "Paris");
    //pathPrint(p);

    // pathDelete
    pathDelete(addf);
    pathDelete(addl);
    pathDelete(dupp);
    pathDelete(np);
    pathDelete(np1);
    pathDelete(np2);

    return 0;
}
