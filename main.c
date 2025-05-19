#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {

    // COMPLETAR

    // A Continuacion dejamos algunos ejemplos de como
    // llamar a las funciones pedidas. Este codigo debe
    // ser borrado / modificado.

    // strLen
    int len = strLen("hola");
    printf("strLen(\"hola\") -> \"%i\"\n", len);
    printf("\n");

    // strDup
    char* dup = strDup("hola");
    printf("strDup(\"hola\") -> \"%s\"\n", dup);
    free(dup);
    printf("\n");

    // strCmp
    char* a = "manuel";
    char* b = "manu";
    int cmp = strCmp(a,b);
    printf("strComp(\"manuel, manu\") -> \"%i\"\n", cmp);
    printf("\n");

    // pathNew
    struct path* p = pathNew();

    // pathAddFirst
    pathAddFirst(p, "Paris", 48.857, 2.352);
    pathAddFirst(p, "Buenos Aires", -34.600, -58.382);

    // pathAddLast
    pathAddLast(p, "Madrid", 40.417, -3.703);
    pathAddLast(p, "Tokio", 35.689, 139.692);

    // pathPrint
    //pathPrint(p);

    // pathDuplicate
    struct path* np = pathDuplicate(p);
    pathPrint(np);

    // pathSwapStops
    pathSwapStops(np, "Buenos Aires", "Tokio");
    pathPrint(np);

    // pathRemoveCity
    //pathRemoveCity(p, "Paris");
    //pathPrint(p);

    // pathDelete
    pathDelete(p);
    pathDelete(np);

    return 0;
}
