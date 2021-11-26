#include "diccionario.h"

int openDIR()
{
    DIR *dir;
    struct dirent *ent;
    int palabras = 0;
    int i = 0;
    dir = opendir("./DIR");
    if (dir == NULL)
        printf("error\n");

    //readdir lee un directorio especifico
    while ((ent = readdir(dir)) != NULL)
    {
        // Nos devuelve el directorio actual (.) y el anterior (..)
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            i++;
            palabras += contarPalabras(ent->d_name, i); // contando palabras de todos los archivos
        }
    }
    closedir(dir);
    return palabras;
}

int contarPalabras(char *nombre, int iD) // funcion para contar la cantidad de palabras que hay, y darle al arreglo el tamaño justo
{
    char directorio[20];
    strcpy(directorio, "DIR/");
    strcat(directorio, nombre);
    termino info;
    FILE *buff = fopen(directorio, "rb");

    char *auxpalabra = (char *)calloc(sizeof(char), 20);
    char *palabra = (char *)calloc(sizeof(char), 20);
    int contador = 0;
    char character;
    int posicion = 0;
    int i = 0;
    if (buff != NULL)
    {
        while (fread(&character, sizeof(char), 1, buff) > 0)
        {
            if (!filtrarCarater(character))
            {
                if (i == 0)
                {
                    continue;
                }
                strncpy(palabra, auxpalabra, i + 1);
                palabra[i] = '\0';
                posicion -= strlen(palabra);
                contador++;
                i = 0;
            }
            else
            {
                auxpalabra[i] = character;
                i++;
            }
            posicion++;
        }
        fclose(buff);
        free(palabra);
        free(auxpalabra);
    }
    return contador;
}

termino cargarTermino(char *palabra, int posicion, int archivoID) // guarda la informacion de la palabra en termino
{
    termino aux;
    strcpy(aux.palabra, palabra);
    aux.pos = posicion;
    aux.idDOC = archivoID;
    return aux;
}

int filtrarCarater(char caracter)
{
    //si un carácter es alfabético  //si un carácter es alfabético o numérico
    return IsCharAlpha(caracter) || IsCharAlphaNumeric(caracter);
}

FILE *abrirArchi()
{
    FILE *buffer = fopen(DICCIONARIO, "ab");

    if (buffer)
    {
        return buffer;
    }
    printf(" Error al abrir el archivo\n");
}

void cerrarArchi(FILE *buffer)
{
    fclose(buffer);
}

void mostrararchivoDiccionario() // auxiliar para mostrar diccionario.dat
{
    FILE *buffer = fopen(DICCIONARIO, "rb");
    termino motor;
    if (buffer)
    {

        while (fread(&motor, sizeof(termino), 1, buffer) > 0)
        {
            mostrarTermnino(motor);
        }
        fclose(buffer);
    }
    printf("\t**********************\n");
}

void mostrarTermnino(termino aux)
{
    printf("\t**********************\n");
    printf("\n\tPALABRA   :  %s\n", aux.palabra);
    printf("\tPOSICION  :  %i\n", aux.pos);
    printf("\tID DOC    :  %i\n\n", aux.idDOC);
}

void abrirDirectorio(termino *array)
{
    DIR *dir;
    struct dirent *ent;
    int palabras = 0;
    int j = 0;
    int i = 0;
    dir = opendir("./DIR");
    if (dir == NULL)
        printf("error\n");

    while ((ent = readdir(dir)) != NULL)
    {
        if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
        {
            i++;
            cargarVector(ent->d_name, i, array, &j); // cargando primero el arreglo de terminos con toda la informacion
        }
    }
    closedir(dir);
}

void cargarVector(char *nombre, int iD, termino *array, int *j)
{
    char directorio[20];
    strcpy(directorio, "DIR/");
    strcat(directorio, nombre);
    termino info;
    FILE *buff = fopen(directorio, "rb");
    int k = *j; // igualado a cantidad de palabras
    char *auxpalabra = (char *)calloc(sizeof(char), 20);
    char *palabra = (char *)calloc(sizeof(char), 20);

    char character;
    int posicion = 0;
    int i = 0;
    if (buff != NULL)
    {
        while (fread(&character, sizeof(char), 1, buff) > 0)
        {
            if (!filtrarCarater(character)) // si es 0
            {
                if (i == 0)
                {
                    continue; 
                }
                strcpy(palabra, auxpalabra);
                palabra[i] = '\0';
                array[k] = cargarTermino(palabra, posicion, iD); // cargo 1 termino en cada posicion del arreglo
                (*j)++;                                          // sumo palabras
                k++;
                posicion++;
                i = 0;
            }
            else
            {
                auxpalabra[i] = character;
                i++;
            }
        }
        fclose(buff);
        free(palabra);
        free(auxpalabra);
    }
}

void mostrarArreglo(termino *arreglo, int validos)
{
    for (int i = 0; i < validos; i++)
    {
        printf("\t**********************\n");
        printf("\n\tPALABRA   :  %s\n", arreglo[i].palabra);
        printf("\tPOSICION  :  %i\n", arreglo[i].pos);
        printf("\tID DOC    :  %i\n\n", arreglo[i].idDOC);
    }
}

void cargarDiccionario(termino *arreglo, int validos)
{
    FILE *buffer = fopen(DICCIONARIO, "wb");
    if (buffer)
    {
        for (int i = 0; i < validos; i++)
        {
            fwrite(&arreglo[i], sizeof(termino), 1, buffer);
        }
        fclose(buffer);
    }
}

//auxiliar

void cargarNuevoArchivo()
{
    char nombre[20];
    char texto[5000];
    char directorio[20];

    printf("-> Que nombre le desea dar a su archivo\n");
    printf("->");
    fflush(stdin);
    gets(nombre);

    strcpy(directorio, "DIR/");
    strcat(directorio, nombre);
    strcat(directorio, ".txt");

    FILE *buffer = fopen(directorio, "wt");

    printf("\n-> Ingrese texto para agregar al motor de busqueda\n");
    printf("->");
    fflush(stdin);
    gets(texto);

    if (buffer)
    {
        fwrite(&texto, strlen(texto), 1, buffer);

        fclose(buffer);
    }
}