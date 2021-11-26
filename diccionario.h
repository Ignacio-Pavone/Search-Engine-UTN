#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#define DICCIONARIO "diccionario.dat"

typedef struct
{
    char palabra[20]; // fwrite en un archivo .bin
    int idDOC;
    int pos; // incrementa palabra por palabra, y no letra por letra
} termino;

int filtrarCarater(char caracter);
termino cargarTermino(char *palabra, int posicion, int archivoID);
int contarPalabras(char *nombre, int iD);
int openDIR();
FILE *abrirArchi();
void cerrarArchi(FILE *buffer);
void mostrararchivoDiccionario();
void cargarVector(char *nombre, int iD, termino *array, int *j);
void abrirDirectorio(termino *array);
void mostrarArreglo(termino *arreglo, int validos);
void cargarDiccionario(termino *arreglo, int validos);
void mostrarTermnino(termino aux);
void cargarNuevoArchivo();