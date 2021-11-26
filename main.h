#pragma once
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "diccionario.h"
#include "motor.h"
#include "usuario.h"
#include "time.h"

void funcionesMotor();
void funcionesDiccionario();
void mostrarArchivo();
void cerrarArchi(FILE *buffer);
FILE *abrirArchi();
void mostrarAb(nodoA *arbol);
int openDIR();
void busquedeApariceronesxTermino(char palabra[20], int idDoc);
int MenuOpciones();