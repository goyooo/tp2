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
    // Verificar bien para len distintos.

    int size1 = strLen(a);
    int size2 = strLen(b);
    int min = size1;
   
    if(size2 < min) min = size2;
//min se define como el tamanio del str mas corto 
   	   
    int i=0;
    while(i < min){
    	if(a[i] == b[i]){
    		i++;
    	//mira si las letras en ambos str son iguales, si lo son suma 1 a i y vuelve a comparar hasta que no lo sean; si esto no pasa los str son iguales y retorna 0.
    		}		
    	else{
    	// solo entra si los str NO son iguales. Si el caracter en a es menor(en valor ascii que es equivalente a su orden lexicografico) retorna 1, si es ayo retorna -1. 
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

        float extraDistance = distance(p->first->stop, newCity);

        newNode->next = p->first;
        p->first = newNode;
        p->count ++;
        p->length = p->length + extraDistance;
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

        float extraDistance = distance(p->last->stop, newCity);

        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->stop = newCity;
        newNode->next = 0;

        p->last->next = newNode;
        p->last = newNode;
        p->length = p->length + extraDistance;
        p->count = p->count + 1;
    }
}

struct path* pathDuplicate(struct path* p){
    //esta no tengo la mas reputa idea que hacer, ma;ana veo.
    //no estoy seguro si estoy cumpliendo la parte del enunciado que dice:
    // "El resultado no puede compartir ning´un puntero con la estructura original." Como me aseguro?
    struct path* newPath = pathNew();
    newPath->count = p->count;
    newPath->length = p->length;

    struct node* aux = p->first->next;
    struct node* prev = p->first;
    
    newPath->first = prev;
    for(int i=0; i < p->count; i++){
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        struct city* newCity = (struct city*) malloc(sizeof(struct city));
        newCity->name = strDup(prev->stop->name);
        newCity = prev->stop;

        newNode->stop = newCity;
        newNode->next = aux;
        
        prev = aux;
        aux = aux->next;
    }
    //creo que me falta un nodo?? no estoy seguro. Lo tengo que hacer a mano?
    //podre cambiar la guarda para que itere hasta el final con el count o algo de eso?
    aux->next = 0;
    p->last = aux;
    return p;
}

void pathSwapStops(struct path* p, char* name1, char* name2) {
    //asumo que siempre las ciudades a swapear son dadas en orden, o sea que si se quiere swapear la primer
    //parada, esta tiene que estar en name1. Analogamente, la ultima parada siempre esta en name2.
    if(name1 == name2){return;}
    struct node* aux1 = findNodeCity(p->first, name1);
    struct node* aux2 = findNodeCity(p->first, name2);

    //tengo que agarrar dos y swappearlos, como en el parcial la concha de su madre !!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //fijarme como se modifica el length del path (ma;ana) (hecho)
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //como dijo jack, vamos por partes: hay que cambiar el primero con algun x  (hecho)
    //                                                  el primero con el ulimo (hecho)
    //                                                  el ultimo con algun x   (hecho)
    //                                                  algun x con algun x     (hecho)
    if(aux1 == p->first && aux2 == p->last){
        aux2->next = aux1->next;
        p->first = aux2;
        p->last = aux1;
        aux1->next = 0;
    }
    if(aux1 == p->first && aux2 != p->last){
        struct node* temp = aux1;
        aux1->next = aux2->next;
        aux2->next = temp->next;
        p->first = aux2;    
    }
    if(aux1 != p->first && aux2 == p->last){
        struct node* anterior = p->first;
        while(anterior->next != aux1){
            anterior = anterior->next;
        }
        anterior->next = aux2;
        aux2->next = aux1->next;
        aux1->next = 0;
        p->last = aux1;
    }
    if(aux1 != p->first && aux2 != p->last){
        struct node* anterior1 = p->first;
        while(anterior1->next != aux1){
            anterior1 = anterior1->next;
        }
        struct node* anterior2 = p->first;
        while(anterior2->next != aux2){
            anterior2 = anterior2->next;
        }

        struct node* temp = aux1->next;
        anterior1->next = aux2;
        aux2->next = aux1->next;
        anterior2->next = aux1;
        aux2->next = temp;
    }
    p->length = calculateLength(p->first);
}

void pathRemoveCity(struct path* p, char* name) {

    struct node* aux = findNodeCity(p->first, name);
    //tres casos: si es la primera, al diome o la cola del burro.
    //caso borde: si es la unica parada
    if(p->first->next == 0){
        free(aux->stop->name);
        free(aux->stop);        
    }
    //si es la primera:
    if(aux == p->first){
        p->first = p->first->next;
        free(aux->stop->name);
        free(aux->stop);
    }
    //si es la ultima:
    if(aux == p->last){
        struct node* anteUltimo = p->first;
        while(anteUltimo->next->next != 0){
            anteUltimo = anteUltimo->next;
        }
        p->last = anteUltimo;
        free(aux->stop->name);
        free(aux->stop);
    }
    //si esta al diome:
    else{
        struct node* anterior = p->first;
        while(anterior->next->stop->name != name){
            anterior = anterior->next;
        }
        anterior->next = aux->next;
        free(aux->stop->name);
        free(aux->stop);
    }
    //modifico el count y el length
    p->count = p->count - 1;
    p->length = calculateLength(p->first);
}

void pathDelete(struct path* p) { //Me trabe en la iteracion, no se como solucionarlo. Ma;ana el chat me iluminara
    //caso borde p==NULL
    //caso borde p->first == NULL
    //caso borde p->first->next == NULL

    if(p == 0){
        free(p); //no se si esta bien, o si solo deberia hacer un return;
    }
    if(p->first == 0){
        free(p->first);
        free(p->last);
        free(p);
    }                               //chequear todos los casos bases jatejode toy muerto
    if(p->first->next == 0){
        free(p->first->stop->name);
        free(p->first);
        free(p->last);
        free(p);
    }
    else{
        //hay que borrar todos lo nombres, despues los nodos y ultimo el path
        struct node* cur = p->first->next;
        struct node* prev = p->first;
        while(cur != p->last){ //borrar *last a mano al final    
            pathRemoveCity(p, prev->stop->name);
            free(prev); //esta linea y la anterior es borrar dos veces lo mismo?? no se
            prev = cur;
            cur= cur->next;
        }
        //libero el ultimo
        free(cur->stop->name);
        free(cur->stop);
        //libero los punteros y el path
        free(p->first);
        free(p->last);
        free(p);
    }
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

    float distancia;
    if(n == 0 || n->next == 0){
        return 0.0;
    }
    else{
        struct node* current = n->next;
        struct node* prev = n;
        while(current->next != 0){
            distancia = distancia + distance(current->stop, prev->stop);
            prev = current;
            current = current->next;
        }
    }
    return distancia;
}

struct node* findNodeCity(struct node* n, char* name) {

    struct node* current = n;
    while(current->stop->name != name){
        current = current->next;
    }

    return current;
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
