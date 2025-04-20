#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////
typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo* Siguiente;
} Nodo;
//////////////////////////////////////////
Nodo* crearLista();
Nodo* CrearNodo(Tarea tar);
void InsertarNodo(Nodo **L,Nodo *nuevo);
Nodo* QuitarNodo(Nodo** L, int id);
Nodo* borrarPrimerElemento(Nodo* L); //esta la usare para al final borrar la memoria de todas las listas
Nodo* buscarNodoPorID(Nodo* L, int IdBuscado);
void TrasladoTarea(Nodo** L1, Nodo** L2,int ID);
void mostrar(Nodo*L);
//////////////////////////////////////////
int main(){
    Nodo* TareasPendientes;
    Nodo* TareasRealizadas;
    Nodo* nuevo;
    Nodo* encontrado;
    Tarea tar;
    tar.Descripcion=(char *)malloc(100 * sizeof(char));
    int opciones, idauto=999, finaliza=0,opciones2;
    TareasPendientes=crearLista();
    TareasRealizadas=crearLista();

    printf("Carga de tareas:\n");
    do{
        idauto++;
        printf("Ingrese Descripcion de la tarea:\n");
        gets(tar.Descripcion);
        fflush(stdin);
        do {
            printf("Ingrese duracion de la tarea entre 10 y 100:\n");
            scanf("%d",&tar.Duracion);
            fflush(stdin);
        } while(tar.Duracion<10 || tar.Duracion>100);
        tar.TareaID=idauto;
        nuevo=CrearNodo(tar);
        InsertarNodo(&TareasPendientes,nuevo);
        printf("Ingrese 1 para finalizar la carga de tareas, cualquier otro numero si quiere continuar\n");
        scanf("%d",&finaliza);
        fflush(stdin);
    } while(finaliza!=1);
    finaliza=0;

    //para el checkeo de tareas, tengo que buscar el nodo, quitarlo y luego insertarlo en la otra lista
    printf("Checkeo de tareas:\n");
    do{
        printf("Ingrese el id de la tarea para marcarla como completada:\n");
        scanf("%d",&tar.TareaID);
        fflush(stdin);
        TrasladoTarea(&TareasPendientes, &TareasRealizadas,tar.TareaID);
        printf("Ingrese 1 si quiere parar de marcar tareas como completadas, cualquier otro numero para continuar\n");
        scanf("%d",&finaliza);
        fflush(stdin);
    } while(finaliza!=1);
    finaliza=0;

    while(finaliza!=1){
        printf("\n1-Mostrar ambas lista \n2-Mostrar lista de tareas pendientes \n3-Mostrar lista de tareas realizadas\n4-Finalizar\n");
        scanf("%d",&opciones2);
        switch (opciones2){
        case 1:
            printf("Lista de tareas pendientes:");
            mostrar(TareasPendientes);
            printf("\n\nLista de tareas realizadas:");
            mostrar(TareasRealizadas);
            break;
        case 2:
            printf("Lista de tareas pendientes:");
            mostrar(TareasPendientes);
            break;  
        case 3:
            printf("Lista de tareas realizadas:");
            mostrar(TareasRealizadas);
            break;      
        
        default:
            finaliza=1;
            break;
        }
    }

    while(TareasPendientes!=NULL){
        TareasPendientes=borrarPrimerElemento(TareasPendientes); //para liberar toda la memoria
    }
    while(TareasRealizadas!=NULL){
        TareasRealizadas=borrarPrimerElemento(TareasRealizadas);
    }
    free(tar.Descripcion);
    printf("\nprobando final");

    getchar();
    return 0;
}
//////////////////////////////////////////
Nodo* crearLista(){
    return NULL;
}

Nodo* CrearNodo(Tarea tar){
    Nodo *nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->T.TareaID=tar.TareaID;
    nuevo->T.Duracion=tar.Duracion;
    nuevo->T.Descripcion=(char*)malloc(strlen(tar.Descripcion)+1);
    strcpy(nuevo->T.Descripcion,tar.Descripcion);
    nuevo->Siguiente=NULL;
    return nuevo;
}

void InsertarNodo(Nodo **L,Nodo *nuevo){
    nuevo->Siguiente = *L;
    *L=nuevo;
}

Nodo* QuitarNodo(Nodo** L, int id){
    Nodo **aux = L;                 
    while (*aux != NULL && (*aux)->T.TareaID != id)
    {                             
        aux = &(*aux)->Siguiente; 
    }
    if (*aux) 
    {
        Nodo *temp = *aux;       
        *aux = (*aux)->Siguiente; 
        temp->Siguiente = NULL;   
        return temp;             //retorna el nodo que quiero transferir 
    }
    return NULL; //si no se encuentra
}

Nodo* borrarPrimerElemento(Nodo* L){
    Nodo* aux= L;
    L= L->Siguiente;
    free (aux);
    return L;
}

Nodo* buscarNodoPorID(Nodo* L, int IdBuscado){
    Nodo* Aux = L;
    while((Aux!=NULL) && Aux->T.TareaID != IdBuscado){
        Aux = Aux->Siguiente;
    }
    return Aux; //si no lo encuentra me da nulo
}

void TrasladoTarea(Nodo** L1, Nodo** L2,int ID){
    Nodo* nodoTraslado;
    nodoTraslado=QuitarNodo(L1,ID);
    if (nodoTraslado){
        InsertarNodo(L2,nodoTraslado);
        printf("Tarea id:%d movida\n",ID);
    } else{
        printf("Esa tarea no forma parte de la lista de tareas pendientes\n");
    }
}

void mostrar(Nodo*L){
    while(L!=NULL){
        printf("\nTarea ID: %d",L->T.TareaID);
        printf("\nDescripcion: %s",L->T.Descripcion);
        printf("\nDuracion: %d",L->T.Duracion);
        L=L->Siguiente;
    }
}