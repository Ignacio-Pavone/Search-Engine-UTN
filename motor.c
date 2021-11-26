#include "motor.h"

nodoA *crearnodoArbol(termino dato)
{
    nodoA *nuevo = (nodoA *)malloc(sizeof(nodoA));
    strcpy(nuevo->palabra, dato.palabra);
    nuevo->frecuencia = 0;
    nuevo->ocurrencias = NULL;
    nuevo->der = NULL;
    nuevo->izq = NULL;

    return nuevo;
}

nodoT *crearnodoLista(int ID, int pos)
{
    nodoT *nuevo = (nodoT *)malloc(sizeof(nodoT));
    nuevo->idDOC = ID;
    nuevo->pos = pos;
    nuevo->sig = NULL;
    return nuevo;
}

void insertarOrdenado(nodoT **lista, int idDOC, int pos)
{
    nodoT *act;
    nodoT *ant;
    nodoT *nuevoNodo;
    nuevoNodo = crearnodoLista(idDOC, pos);

    if (*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        if ((*lista)->idDOC > nuevoNodo->idDOC)
        {
            nuevoNodo->sig = *lista;
            *lista = nuevoNodo;
        }
        else
        {
            act = (*lista)->sig;
            ant = *lista;
            while (act != NULL && act->idDOC < nuevoNodo->idDOC)
            {
                ant = act;
                act = act->sig;
            }
            ant->sig = nuevoNodo;
            nuevoNodo->sig = act;
        }
    }
}

void insertarenArbol(nodoA **arbol, termino info)
{

    if (*arbol == NULL)
    {
        *arbol = crearnodoArbol(info);
        insertarOrdenado(&(*arbol)->ocurrencias, info.idDOC, info.pos);
        (*arbol)->frecuencia += 1;
    }
    else
    {
        if (strcmpi(info.palabra, (*arbol)->palabra) < 0)
        {
            insertarenArbol(&(*arbol)->izq, info);
        }
        else if (strcmpi(info.palabra, (*arbol)->palabra) > 0)
        {
            insertarenArbol(&(*arbol)->der, info);
        }
        else
        {
            insertarOrdenado(&(*arbol)->ocurrencias, info.idDOC, info.pos);
            (*arbol)->frecuencia += 1;
        }
    }
}

void mostrarMotor(nodoA *arbol)
{
    if (arbol)
    {
        mostrarMotor(arbol->izq);
        mostrarPalabra(arbol);
        mostrarSublista(arbol->ocurrencias);
        mostrarMotor(arbol->der);
    }
}

void cargarMotor(nodoA **motor)
{
    FILE *buffer = fopen(DICCIONARIO, "rb");
    termino aux;

    if (buffer)
    {
        while (fread(&aux, sizeof(termino), 1, buffer) > 0)
        {
            insertarenArbol(motor, aux);
        }
    }
}

void mostrarSublista(nodoT *ocurrencias)
{
    printf("|\t[LISTA REPETICIONES]\n|\n");
    while (ocurrencias)
    {
        mostrarNodoocurrencias(ocurrencias);
        ocurrencias = ocurrencias->sig;
    }
    printf("'------------------------------------\n\n");
}

void mostrarNodoocurrencias(nodoT *occurencia)
{
    printf("|\tPOSICION     : %i\n", occurencia->pos);
    printf("|\tID DOCUMENTO : %i\n|\n", occurencia->idDOC);
}

void mostrarPalabra(nodoA *motor)
{
    printf(".------------------------------------\n");
    printf("|\t\t[PALABRA]\n|\n");
    printf("|\tPALABRA   : < %s >\n", motor->palabra);
    printf("|\tFRECUENCIA:  %i\n|\n", motor->frecuencia);
    printf(".------------------------------------\n");
}