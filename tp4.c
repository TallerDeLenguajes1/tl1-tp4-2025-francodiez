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
Nodo* QuitarNodo(Nodo* L, int id);
Nodo* borrarPrimerElemento(Nodo* L); //esta la usare para al final borrar la memoria de todas las listas
//////////////////////////////////////////
int main(){
    Nodo* TareasPendientes;
    Nodo* TareasRealizadas;
    Nodo* nuevo;
    Tarea tar;
    tar.Descripcion=(char *)malloc(100 * sizeof(char));
    int opciones, idauto=999, finaliza=0;
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
    
    /*printf("ID: %d",TareasPendientes->T.TareaID);
    printf("\nDescripcion: %s",TareasPendientes->T.Descripcion);
    printf("\nDuracion: %d",TareasPendientes->T.Duracion); */

    while(TareasPendientes!=NULL){
        TareasPendientes=borrarPrimerElemento(TareasPendientes); //para liberar toda la memoria
    }
    /* while(TareasRealizadas!=NULL){
        TareasRealizadas=borrarPrimerElemento(TareasRealizadas);
    } */
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
    nuevo->T=tar;
    nuevo->Siguiente=NULL;
    return nuevo;
}

void InsertarNodo(Nodo **L,Nodo *nuevo){
    nuevo->Siguiente = *L;
    *L=nuevo;
}

Nodo* QuitarNodo(Nodo* L, int id){
    Nodo **aux=&L;
    while(*aux!=NULL && (*aux)->T.TareaID !=id){
        aux= &(*aux)->Siguiente;
    }

    if(*aux){
        Nodo* temp=*aux;
        *aux=(*aux)->Siguiente;
        temp->Siguiente=NULL;
        return temp;
    }
    return NULL;
}

Nodo* borrarPrimerElemento(Nodo* L){
    Nodo* aux= L;
    L= L->Siguiente;
    free (aux);
    return L;
}