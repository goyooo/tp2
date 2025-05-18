#include "utils.h"

int strLen(char* src) {

    int contador = 0;
    while (src[contador] != '/0'){
        contador ++;
    }

    return contador;
}

char* strDup(char* src) {

    char* dup = (char*) malloc( sizeof(char) * (strLen(src) + 1));
    int i = 0;
    while(src[i] != '/0'){
        dup[i] = src[i];
        i++;
    }
    dup[i] = '/0';

    return dup;
}

int strCmp(char* a, char* b) {

    // COMPLETAR

    return 0;
}


struct path* pathNew() {

    struct path* newPath = (struct path*) malloc(sizeof(struct path));
    newPath->first = 0;
    newPath->last = 0;
    newPath->length = 0;
    newPath->count = 0;
    return newPath;
}

void pathAddFirst(struct path* p, char* name, float latitude, float longitude) {

    struct city* newCity = (struct city*) malloc(sizeof(struct city));
    newCity->name = strDup(name);
    newCity->latitude = latitude;
    newCity->longitude = longitude;

    if(p->first->stop == 0){
        p->first->stop = newCity;
        p->first->next = 0;
    } else{ //seguir!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
        
    }
}

void pathAddLast(struct path* p, char* name, float latitude, float longitude) {

    struct city* newCity = (struct city*) malloc(sizeof(struct city));
    newCity->name = strDup(name);
    newCity->latitude = latitude;
    newCity->longitude = longitude;

    struct node* current = p->first;
    while(current->next != 0){
        current = current->next;
    }

    current->next->stop = newCity;
    current->next = &(newCity);
    current->next->next = 0;
}

struct path* pathDuplicate(struct path* p) {

    //COMPLETAR

    return 0;
}

void pathSwapStops(struct path* p, char* name1, char* name2) {

    // COMPLETAR
}

void pathRemoveCity(struct path* p, char* name) {

    // COMPLETAR
}

void pathDelete(struct path* p) {

    // COMPLETAR
}

void pathPrint(struct path* p) {
    if(p->first==0) {
        printf("[null] -> [null], ");
    } else {
        printf("[%s] -> [%s], ", p->first->stop->name, p->last->stop->name);
    }
    printf("Count=%i, Length=%f\n", p->count, p->length);
    struct node* curr = p->first;
    while (curr) {
        printf("%s (%f,%f) \n", curr->stop->name, curr->stop->latitude, curr->stop->longitude);
        curr = curr->next;
    }
}

// --- Auxiliar functions -----------------------------------------------------

float calculateLength(struct node* n) {

    // COMPLETAR
}

struct node* findNodeCity(struct node* n, char* name) {

    // COMPLETAR

    return 0;
}

float distance(struct city* c1, struct city* c2) {
    // Formula de Haversine
    // Calcula la distancia entre dos puntos en la superficie de una esfera
    // R es el radio de la Tierra

    double degrees2radians = PI / 180.0;

    double lat1 = c1->latitude * degrees2radians;
    double lon1 = c1->longitude * degrees2radians;
    double lat2 = c2->latitude * degrees2radians;
    double lon2 = c2->longitude * degrees2radians;

    double dlat = lat2-lat1;
    double dlon = lon2-lon1;

    double a = sin(dlat/2.0) * sin(dlat/2.0) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);

    double R = EARTH_RADIUS_KM;

    double c = 2 * atan2(sqrt(a), sqrt(1.0-a));

    double d = R * c;

    return (float)d;
}

// --- Heuristic ---------------------------------------------------------

struct path* applyHeuristic(struct path* p) {

    // COMPLETAR

    return 0;
    
}
