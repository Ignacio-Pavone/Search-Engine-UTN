
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diccionario.h"

typedef struct nodoT
{
    int idDOC;
    int pos;
    struct nodoT *sig;
} nodoT;

typedef struct nodoA
{
    char palabra[20];
    int frecuencia;     // representa la cantidad de nodos de la lista
    nodoT *ocurrencias; // ordenada por idDOC, luego por pos
    struct nodoA *der;
    struct nodoA *izq;
} nodoA;

void fechaYhora();
nodoT *crearnodoLista(int ID, int pos);
nodoA *crearnodoArbol(termino dato);
void insertarOrdenado(nodoT **lista, int idDOC, int pos);
void insertarenArbol(nodoA **arbol, termino info);
void cargarMotor(nodoA **motor);
void mostrarSublista(nodoT *ocurrencias);
void mostrarNodoocurrencias(nodoT *occurencia);
void mostrarMotor(nodoA *arbol);
void mostrarPalabra(nodoA *motor);
