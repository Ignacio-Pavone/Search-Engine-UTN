#include "usuario.h"
#include "motor.h"

void fechaYhora()
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output, 128, "\t\t\t[%d/%m/%y %H:%M:%S]", tlocal);
    printf("%s\n", output);
}

//ejercicio 1
//para buscar la palabra recorro el motor (arbol) comparando la palabra ingresada por el usuario por parametro
//sino recorro el arbol por derecha y por izquierda descartando la mitad, hasta encontrarla sino le notifico al usuario
//que la palabra no existe
void buscarPalabra(nodoA *motor, char palabra[20])
{
    if (motor)
    {
        if (strcmpi(palabra, motor->palabra) == 0)
        {
            mostrarPalabra(motor);
            mostrarSublista(motor->ocurrencias);
        }
        else
        {
            if (strcmpi(motor->palabra, palabra) > 0)
            {
                buscarPalabra(motor->izq, palabra);
            }
            else
            {
                buscarPalabra(motor->der, palabra);
            }
        }
    }
    else
    {
        printf("\n->Palabra <%s> no encontrada en nuestro motor de busqueda\n\n", palabra);
    }
}

//ejercicio 2, una palabra, 2 archivos q el usuario diga
//recorro sublista verificando si ID existe, si existe lo retorno
int recorrerSublista(nodoT *ocurrencias, int id)
{
    nodoT *aux;
    aux = ocurrencias;
    while (aux != NULL && aux->idDOC != id)
    {
        aux = aux->sig;
    }
    if (aux)
    {
        return aux->idDOC;
    }
}

//comparo las palabras, si la enviada por parametro existe, invoco a la funcion de arriba
//verificando que el idDOC exista, si las 2 cosas son verdaderas retorno 1
int buscarPalabraArchivos(nodoA *motor, char palabra[20], int idDOC)
{
    int flag = 0;
    if (motor)
    {
        if (strcmpi(palabra, motor->palabra) == 0)
        {
            if (recorrerSublista(motor->ocurrencias, idDOC) == idDOC)
            {
                return 1;
            }
        }
        flag = buscarPalabraArchivos(motor->der, palabra, idDOC);
        if (flag != 1)
        {
            flag = buscarPalabraArchivos(motor->izq, palabra, idDOC);
        }
    }
}

//con las funciones de arriba, comparo en el if con 2 IDDOCS ingresados por el usuario, para saber si dicha palabra
//se encuentra en los dos IDs, si este es el caso imprimo y muestro, sino notifico al usuario de que en uno de los docs
//no existe.
void comprobarpalabraenDOCS(nodoA *motor, char palabra[20], int idDOC1, int idDOC2)
{
    if (motor)
    {
        if (buscarPalabraArchivos(motor, palabra, idDOC1) == 1 && buscarPalabraArchivos(motor, palabra, idDOC2) == 1)
        {
            printf("\n>La palabra <%s> existe en los documentos con [ID %i-ID %i]\n\n", palabra, idDOC1, idDOC2);
            buscarPalabra(motor, palabra);
        }
        else
        {
            printf("\n->La palabra <%s> no existe en uno de los documentos\n", palabra);
            buscarPalabra(motor, palabra);
        }
    }
}
//ejercicio 3
// busco palabra pero con una segunda condicion de que el id pasado por parametro sea igual

int confirmarID(nodoT *ocurrencias, int id)
{
    nodoT *aux;
    aux = ocurrencias;
    while (aux)
    {
        if (aux->idDOC == id)
        {
            return 1;
        }
        aux = aux->sig;
    }
}
int buscarPalabraID(nodoA *motor, char palabra[20], int id)
{
    if (motor)
    {

        if (strcmpi(palabra, motor->palabra) == 0 && confirmarID(motor->ocurrencias, id) == 1)
        {
            return 1;
        }
        else
        {
            if (strcmpi(motor->palabra, palabra) > 0)
            {
                buscarPalabraID(motor->izq, palabra, id);
            }
            else
            {
                buscarPalabraID(motor->der, palabra, id);
            }
        }
    }
}

void buscardosTerminos(nodoA *motor, char palabra1[20], char palabra2[20], int id)
{
    if (motor)
    {
        if (buscarPalabraID(motor, palabra1, id) == 1 && buscarPalabraID(motor, palabra2, id) == 1)
        {
            printf("\n->Las palabras <%s> y <%s> existen en el documento con ID <%i>\n", palabra1, palabra2, id);
        }
        else
        {
            printf("\n->Las palabras <%s> y <%s> no existen en el mismo documento con ID <%i>\n\n", palabra1, palabra2, id);
        }
    }
    else
    {
        printf("Error\n");
    }
}
//ejercicio 4
int cargarArraydePOS(nodoA *motor, char palabra[20], int id, int *pos) // cargar un array con todas las posiciones de la palabra que llega
{
    int posiciones = 0;
    if (motor)
    {

        if (strcmpi(palabra, motor->palabra) == 0)
        {
            posiciones = guardarPosiciones(motor->ocurrencias, id, pos);
        }
        else
        {
            if (strcmpi(motor->palabra, palabra) > 0)
            {
                return cargarArraydePOS(motor->izq, palabra, id, pos);
            }
            else
            {
                return cargarArraydePOS(motor->der, palabra, id, pos);
            }
        }
    }
    else
    {
        posiciones = 0;
    }
    return posiciones;
}

int terminoEncontrado(nodoA *motor, char palabra[20], int id, int pos)
{
    int flag = 0;
    if (motor)
    {
        if (strcmpi(palabra, motor->palabra) == 0 && (motor->ocurrencias->idDOC == id))
        {

            flag = buscarPosicionesTermino(motor->ocurrencias, motor->ocurrencias->pos, id, motor->palabra);
            // si la pos, y el id son iguales esta funcion retorna 1
        }
        else
        {
            if (strcmpi(motor->palabra, palabra) > 0)
            {
                return terminoEncontrado(motor->izq, palabra, id, pos);
            }
            else
            {
                return terminoEncontrado(motor->der, palabra, id, pos);
            }
        }
    }
    else
    {
        flag = 0;
    }
    return flag;
}

int buscarPosicionesTermino(nodoT *ocurrencias, int pos, int id, char *palabra) // si encuentra la posicion de un termino determinado devuelve 1
{
    nodoT *aux;
    aux = ocurrencias;
    while (aux != NULL)
    {
        if (aux->idDOC == id)
        {
            if (pos == aux->pos)
            {
                return 1;
            }
        }
        aux = aux->sig;
    }
    return 0;
}

int guardarPosiciones(nodoT *ocurrencias, int id, int *pos) // cargando array con todas las posiciones de las palabras
{
    nodoT *aux;
    aux = ocurrencias;
    int validos = 0;

    while (aux != NULL)
    {
        if (aux->idDOC == id)
        {
            pos[validos] = ocurrencias->pos; // guardo las posiciones de una palabra en un arreglo
            validos++;
        }
        aux = aux->sig;
    }
    return validos;
}

int scanearFrase(char frase[500], char array[][5000])
{
    char *ptr = strtok(frase, " ,.");
    int i = 0;
    while (ptr != 0)
    {
        strcpy(array[i], ptr);
        i++;
        ptr = strtok(NULL, " ,.");
    }
    return i;
}

void buscarFrase(nodoA *motor, char frase[500])
{
    char array[100][5000];
    int pos[1000];
    int arrayValidospos = 0;
    int validosFrase = 0;

    validosFrase = scanearFrase(frase, array); // cantidad de palabras de la frase

    if (validosFrase <= 1) // por si el usuario ingresa una sola palabra y no una frase
    {
        printf("\n-> Ingrese mas de una palabra para poder buscar una frase\n\n");
    }
    else
    {       
        for (int k = 0; k < cantidadDocumentos(); k++) //Recorriendo todos los documentos
        {         
            arrayValidospos = cargarArraydePOS(motor, array[0], k, pos); // paso la primera palabra de la frase [0], cargo las pos y retrono cantidad de posiciones
            for (int i = 0; i < arrayValidospos; i++) // recorro cada una de las pos para ver si las posiciones son contiguas
            {
                int encontrado = 1;
                int j = 1;                                                                                            //2         3
                int aux = pos[i] + 1; // guarda la posicion de la primera palabra +1, para comparar con la siguiente HOLA (2), COMO (2+1)
                while (j < validosFrase && encontrado == 1)
                {
                    encontrado = terminoEncontrado(motor, array[j], k, aux); // se fija si la siguiente palabra tenga la pos i+1 (continua a la anterior)
                    j++;                                                     //cantidad de palabras array[j]
                    aux++;                                                   // aumento aux para la siguiente palabra
                }
                if (encontrado == 1)
                {
                    printf("\n-> Frase encontrada en el DOCUMENTO <%i>\n\n", k);
                    break;
                }
            }
        }
    }
}

//ejercicio 5
int buscarFrecuencias(nodoT *ocurrencias, int id)
{
    nodoT *aux;
    aux = ocurrencias;
    int cont = 0;
    while (aux)
    {
        if (aux->idDOC == id)
        {
            cont++;
        }
        aux = aux->sig;
    }
    return cont;
}

void maximaFrecuencia(nodoA *motor, int id, palabraAux *array, int *validos) // guardando frecuencias, y pasando datos a nueva estructura
{
    if (motor)
    {
        int frecuencia = buscarFrecuencias(motor->ocurrencias, id);

        maximaFrecuencia(motor->izq, id, array, validos);
        maximaFrecuencia(motor->der, id, array, validos);
        // tengo todas las frecuencias
        (*validos)++;
        strcpy(array[*validos].palabra, motor->palabra);
        array[*validos].freq = frecuencia;
    }
}

void buscandoPalabraMaximaFreq(palabraAux array[], int validos1)
{
    palabraAux maximo;
    maximo = array[1];

    for (int i = 0; i < validos1; i++)
    {
        if (maximo.freq < array[i].freq)
        {
            maximo = array[i];
        }
    }
    printf("\n->La Palabra con mas frecuencia es <%s>, se repite <%i> veces\n", maximo.palabra, maximo.freq);
}

//ejercicio 6
//con una palabra ingresada utilizo el algoritmo de Levenshtein para comparar palabra por palabra con mi motor
//para guardar en una variable la palabra que tiene una distancia menor a 3 (parecidas), sabiendo esto las imprimo por pantalla
//para sugerirselas al usuario.
void distanciaLevenshtein(nodoA *motor, char palabra[20])
{
    int distancia = 0;
    char *guardando = (char *)calloc(sizeof(char), 20);

    if (motor)
    {
        distancia = Levenshtein(palabra, motor->palabra);
        if (distancia <= 3)
        {
            strcpy(guardando, motor->palabra);
            printf("\n->USTED QUISO DECIR? <%s>\n", guardando);
        }
        else
        {
            distanciaLevenshtein(motor->izq, palabra);
            distanciaLevenshtein(motor->der, palabra);
        }
    }
}

int Levenshtein(char *s1, char *s2)
{
    int t1, t2, i, j, *m, costo, res, ancho;
    t1 = strlen(s1);
    t2 = strlen(s2);

    if (t1 == 0)
        return (t2);
    if (t2 == 0)
        return (t1);
    ancho = t1 + 1;

    m = (int *)malloc(sizeof(int) * (t1 + 1) * (t2 + 1));
    if (m == NULL)
        return (-1);

    for (i = 0; i <= t1; i++)
        m[i] = i;
    for (j = 0; j <= t2; j++)
        m[j * ancho] = j;

    for (i = 1; i <= t1; i++)
        for (j = 1; j <= t2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                costo = 0;
            else
                costo = 1;
            m[j * ancho + i] = min(min(m[j * ancho + i - 1] + 1, m[(j - 1) * ancho + i] + 1), m[(j - 1) * ancho + i - 1] + costo);
        }

    res = m[t2 * ancho + t1];
    free(m);
    return (res);
}

//auxiliar

int mostrarPalabrasdeID(int id)
{
    FILE *buffer = fopen(DICCIONARIO, "rb");
    termino aux;
    int i = 0;

    while (fread(&aux, sizeof(termino), 1, buffer) > 0)
    {
        if (aux.idDOC == id)
        {
            mostrarTermnino(aux);
            i++;
        }
    }
    return i;
}

void integrantesTP()
{
    printf("->Mostrando Integrantes del Grupo\n\n");
    printf("->Pavone Ignacio\n");
    printf("->Bruno Starita\n");
    printf("->Franco Ferro\n\n");
}

int cantidadPalabrasTotal()
{
    FILE *buffer = fopen(DICCIONARIO, "rb");
    termino aux;
    int i = 0;

    while (fread(&aux, sizeof(termino), 1, buffer) > 0)
    {
        i++;
    }
    return i;
}

int cantidadDocumentos() // cant de documentos validos
{
    FILE *buffer = fopen(DICCIONARIO, "rb");
    termino aux;
    int maximo = 0;
    int i = 1;

    while (fread(&aux, sizeof(termino), 1, buffer) > 0)
    {
        if (maximo < aux.idDOC)
        {
            maximo = aux.idDOC;
        }
    }
    return maximo+i;
}

int buscarFrecuenciasTodos(nodoT *ocurrencias)
{
    nodoT *aux;
    aux = ocurrencias;
    int cont = 0;
    while (aux)
    {
        cont++;
        aux = aux->sig;
    }
    return cont;
}
void maximaFrecuenciaTodos(nodoA *motor, palabraAux *array, int *validos)
{
    if (motor)
    {

        int frecuencia = buscarFrecuenciasTodos(motor->ocurrencias);
        maximaFrecuenciaTodos(motor->izq, array, validos);
        maximaFrecuenciaTodos(motor->der, array, validos);
        // tengo todas las frecuencias
        (*validos)++;
        strcpy(array[*validos].palabra, motor->palabra);
        array[*validos].freq = frecuencia;
    }
}

void buscandoPalabraMaximaFreqTodos(palabraAux array[], int validos1)
{
    palabraAux maximo;
    maximo = array[1];
    for (int i = 2; i < validos1; i++)
    {
        if (maximo.freq < array[i].freq)
        {
            maximo = array[i];
        }
    }
    printf("\n->La Palabra con mas frecuencia es <%s> y se repite <%d>\n", maximo.palabra, maximo.freq);
}