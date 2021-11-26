#pragma once
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "usuario.h"
#include "motor.h"
#include "time.h"

typedef struct
{
    char palabra[20];
    int freq;

} palabraAux;

int confirmarID(nodoT *ocurrencias, int id);
void buscarPalabra(nodoA *motor, char palabra[20]);
int recorrerSublista(nodoT *ocurrencias, int id);
int buscarPalabraArchivos(nodoA *motor, char palabra[20], int idDOC);
void comprobarpalabraenDOCS(nodoA *motor, char palabra[20], int idDOC1, int idDOC2);
int buscarPalabraID(nodoA *motor, char palabra[20], int id);
void buscardosTerminos(nodoA *motor, char palabra1[20], char palabra2[20], int id);
int cargarArraydePOS(nodoA *motor, char palabra[20], int id, int *pos);
int terminoEncontrado(nodoA *motor, char palabra[20], int id, int pos);
int buscarPosicionesTermino(nodoT *ocurrencias, int pos, int id, char *palabra);
int scanearFrase(char frase[500], char array[][5000]);
int guardarPosiciones(nodoT *ocurrencias, int id, int *pos);
void buscarFrase(nodoA *motor, char frase[500]);
int buscarFrecuencias(nodoT *ocurrencias, int id);
void maximaFrecuencia(nodoA *motor, int id, palabraAux *array, int *validos);
void buscandoPalabraMaximaFreq(palabraAux array[], int validos1);
void distanciaLevenshtein(nodoA *motor, char palabra[20]);
int Levenshtein(char *s1, char *s2);

//aux
int mostrarPalabrasdeID(int id);
void integrantesTP();
int cantidadPalabrasTotal();
int cantidadDocumentos();
int buscarFrecuenciasTodos(nodoT *ocurrencias);
void maximaFrecuenciaTodos(nodoA *motor, palabraAux *array, int *validos);
void buscandoPalabraMaximaFreqTodos(palabraAux array[], int validos1);