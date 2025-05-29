#include "utils.h"


int strLen(char* src) {

    int contador = 0;
    while (src[contador] != '\0'){
        contador ++;
    }

    return contador;
}

char* strDup(char* src) {

    char* dup = (char*) malloc( sizeof(char) * (strLen(src) + 1));
    int i = 0;
    while(src[i] != '\0'){
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';

    return dup;
}

int strCmp(char* a, char* b) {

    int size1 = strLen(a)+1;
    int size2 = strLen(b)+1;
    int min = size1;
   
    if(size2 < min) min = size2;
    //min se define como el size del str mas corto incluyendo el \0
   	   
    int i=0;
    while(i < min){
    	if(a[i] == b[i]){
    		i++;
    	//mira si las letras en ambos str son iguales, si lo son suma 1 a i y vuelve a comparar hasta que no lo sean; si esto no pasa los str son iguales y retorna 0.
    		}		
    	else{
    	// solo entra si los str NO son iguales. Si el caracter en a es menor(en valor ascii que es equivalente a su orden lexicografico) retorna 1, sino retorna -1. 
    		if(a[i] < b[i]){
    			return 1;
    		}else{
                return -1;
            }
    	}
    }	
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

    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->stop = newCity;

    if(p->first == 0){
        newNode->next = 0;
        p->first = newNode;
        p->last = newNode;
        p->length = 0;
        p->count = 1;

    } else{ 

        newNode->next = p->first;
        p->first = newNode;
        p->count ++;
        p->length = calculateLength(p->first);
    }
}

void pathAddLast(struct path* p, char* name, float latitude, float longitude) {

    if(p->first == 0){
        pathAddFirst(p, name, latitude, longitude);
    }else{

        struct city* newCity = (struct city*) malloc(sizeof(struct city));
        newCity->name = strDup(name);
        newCity->latitude = latitude;
        newCity->longitude = longitude;

        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->stop = newCity;
        newNode->next = 0;

        p->last->next = newNode;
        p->last = newNode;
        p->length = calculateLength(p->first);
        p->count = p->count + 1;
    }
}

struct path* pathDuplicate(struct path* p){
    struct path* newPath = pathNew();

    if(p->first == 0){
        return newPath;
    }

    struct node* ogNode = p->first;
    struct node* prev = 0;
    
    while(ogNode != 0){
        struct city* newCity = (struct city*) malloc(sizeof(struct city));
        newCity->name = strDup(ogNode->stop->name);
        newCity->latitude = ogNode->stop->latitude;
        newCity->longitude = ogNode->stop->longitude;
        
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->stop = newCity;
        newNode->next = 0;
        
        if(newPath->first == 0){
            newPath->first = newNode;
        }else{
            prev->next = newNode;
        }
        prev = newNode;

        if(ogNode->next == 0){
            newPath->last = newNode;
        }
        ogNode = ogNode->next;
    }
    newPath->count = p->count;
    newPath->length = p->length;
    return newPath;
}

void pathSwapStops(struct path* p, char* name1, char* name2) {
    if(strCmp(name1, name2) == 0){return;}
    struct node* node1 = findNodeCity(p->first, name1);
    struct node* node2 = findNodeCity(p->first, name2);
    
    if(!node1 || !node2){return;}
    
    struct node* prev1 = 0;
    struct node* prev2 = 0;

    struct node* temp = p->first;
    
    temp = p->first;
    while (temp != NULL && temp->next != NULL && temp->next != node1) {
        temp = temp->next;
    }
    if (temp && temp->next == node1) {
        prev1 = temp;
    }

    temp = p->first;
    while (temp != NULL && temp->next != NULL && temp->next != node2) {
        temp = temp->next;
    }
    if (temp && temp->next == node2) {
        prev2 = temp;
    }

    //si son adyacentes (1,2)
    if(node1->next == node2){
        node1->next = node2->next;
        if (prev1 != NULL) {
            prev1->next = node2;
        } else {
            p->first = node2;
        }
    node2->next = node1;
    }
    //si son adyacentes (2,1)
    else if(node2->next == node1){
        node2->next = node1->next;
        if (prev2 != NULL) {
            prev2->next = node1;
        } else {
            p->first = node1;
        }
    node1->next = node2;
    }
    else{
        if(prev1){ prev1->next = node2;}
        else{p->first = node2;}

        if(prev2){prev2->next = node1;}
        else{p->first = node1;}

        struct node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }
    if(node1->next == 0){p->last = node1;}
    if(node2->next == 0){p->last = node2;}

    p->length = calculateLength(p->first);
}

void pathRemoveCity(struct path* p, char* name) {

    struct node* aux = findNodeCity(p->first, name);
    if(!aux){return;}
    //tres casos: si es la primera, al diome o la cola del burro.

    //caso borde: si es la unica parada
    if(p->first == p->last){
        free(aux->stop->name);
        free(aux->stop);
        free(aux);
        p->first = 0;
        p->last = 0;        
    }
    //si es la primera:
    else if(aux == p->first){
        p->first = p->first->next;
        free(aux->stop->name);
        free(aux->stop);
        free(aux);
    }
    //si es la ultima:
    else if(aux == p->last){
        struct node* anteUltimo = p->first;
        while(anteUltimo->next->next != 0){
            anteUltimo = anteUltimo->next;
        }
        anteUltimo->next = 0;
        p->last = anteUltimo;
        free(aux->stop->name);
        free(aux->stop);
        free(aux);
    }
    //si esta al diome:
    else{
        struct node* anterior = p->first;
        while(strCmp(anterior->next->stop->name, name) != 0){
            anterior = anterior->next;
        }
        anterior->next = aux->next;
        free(aux->stop->name);
        free(aux->stop);
        free(aux);
    }
    //modifico el count y el length
    p->count = p->count - 1;
    p->length = calculateLength(p->first);
}

void pathDelete(struct path* p) {
    if (p == NULL) return;

    struct node* current = p->first;
    while (current != NULL) {
        struct node* next = current->next;

        free(current->stop->name);
        free(current->stop);
        free(current);

        current = next;
    }

    free(p);
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

    float distancia = 0.0;
    //si no hay paradas o hay una sola la distancia es 0
    if(n == 0 || n->next == 0){
        return 0.0;
    }
    else{
        //recorro la lista calculando la distancia entre cada parada y la siguiente
        struct node* current = n->next;
        struct node* prev = n;
        while(current != 0){
            distancia += distance(current->stop, prev->stop);
            prev = current;
            current = current->next;
        }
    }
    return distancia;
}

struct node* findNodeCity(struct node* n, char* name) {

    struct node* current = n;
    while(current != 0){
        if(strCmp(current->stop->name, name) == 0){
            return current;
        }
        current = current->next;
    }

    return NULL;
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

    if (p->count <= 1) return pathDuplicate(p);

    struct path* ej4 = pathDuplicate(p);
    int cambios = 1;
    while(cambios){
        cambios = 0;
        struct node* cur = ej4->first->next;

        while(cur != 0 && cur->next != 0){
            struct city* c1 = cur->stop;
            struct city* c2 = cur->next->stop;

            struct node* siguiente = cur->next;

            float oldLength = ej4->length;
            pathSwapStops(ej4, c1->name, c2->name);

            if(ej4->length < oldLength){
                cambios = 1;
                cur = siguiente;

            }else{
                pathSwapStops(ej4, c1->name, c2->name);
                cur = cur->next;
            }
        }

    }
    
    return ej4;
}

