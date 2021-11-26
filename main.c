#include "main.h"

int main()
{
    printf("VERSION 1.0");
    fechaYhora();

    //variables utilizadas
    int id1 = 0;
    int id2 = 0;
    int id3 = 0;
    int opcion = 0;
    int acumulador = 0;
    char palabra[20];
    char palabra1[20];
    char palabra2[20];
    char palabra3[500];
    int idMaxfreq = 0;
    int idDOC = 0;
    int validos = openDIR();                                         // open dir devuelve la cantidad de palabras
    termino *arreglo = (termino *)malloc(sizeof(termino) * validos); // multiplico x la cant de palabras para darle el tamaño justo
    palabraAux array[1000];
    nodoA *motor = NULL;
    //***************************************************************************

    //Funciones principales para cargar el motor de busqueda
    abrirDirectorio(arreglo);            // leyendo archivos y pasandolos al arreglo
    cargarDiccionario(arreglo, validos); // Pasando palabras a archivo diccionario.dat
    cargarMotor(&motor);                 // Cargando arbol de listas desde diccionario.dat

    do
    {
        opcion = MenuOpciones();
        switch (opcion)
        {
        case 1:
            system("cls");
            // Buscar todas las apariciones de un término en algún documento (operacion or)
            printf("->Que palabra desea buscar ?\n");
            fflush(stdin);
            printf("\n*Ingrese palabra -> ");
            scanf("%s", &palabra);
            buscarPalabra(motor, palabra);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            // Buscar todas las apariciones de un término en un documento y otro (operacion and)
            printf("->Que palabra desea buscar en varios documentos ?\n");
            fflush(stdin);
            printf("\n*Ingrese palabra -> ");
            scanf("%s", &palabra);
            printf("\n->Ingrese ID doc a buscar: ");
            scanf("%i", &id1);
            printf("\n->Ingrese ID doc a buscar: ");
            scanf("%i", &id2);
            comprobarpalabraenDOCS(motor, palabra, id1, id2);
            system("pause");
            system("cls");
            break;
        case 3:
            // Buscar la aparición de más de un término en el mismo documento
            system("cls");
            printf("->Palabras a buscar en un mismo documento\n\n");
            fflush(stdin);
            printf("->Ingrese primera palabra a buscar -> ");
            scanf("%s", &palabra1);
            fflush(stdin);
            printf("\n->Ingrese segunda palabra a buscar -> ");
            scanf("%s", &palabra2);
            printf("\n->Ingrese ID archivo en el que buscar -> ");
            scanf("%i", &idDOC);
            buscardosTerminos(motor, palabra1, palabra2, idDOC);
            system("pause");
            system("cls");
            break;
        case 4:
            // Buscar una frase completa (las palabras deben estar contiguas en alguno de los documentos)
            system("cls");
            printf("->Escriba la frase que desea buscar en el diccionario ?\n");
            fflush(stdin);
            printf("\n->Ingrese la Frase:  ");
            gets(palabra3);
            buscarFrase(motor, palabra3);
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
            // Buscar la palabra de más frecuencia que aparece en alguno de los docs
            int validos1 = 0;
            printf("\n->Ingrese ID archivo en el que buscar -> ");
            scanf("%i", &idMaxfreq);
            maximaFrecuencia(motor, idMaxfreq, array, &validos1);
            buscandoPalabraMaximaFreq(array, validos1);
            system("pause");
            system("cls");
            break;
        case 6:
            system("cls");
            // Utilizar la distancia de levenshtein en el ingreso de una palabra y sugerir similares a partir de una distancia <= 3
            printf("->Que palabra desea buscar ?\n");
            fflush(stdin);
            printf("\n*Ingrese palabra -> ");
            scanf("%s", &palabra);
            distanciaLevenshtein(motor, palabra);
            system("pause");
            system("cls");
            break;
        case 7:
            system("cls");
            // Funcion para crear archivo con texto y agregarlo al motor
            cargarNuevoArchivo();
            main();
            system("pause");
            system("cls");
            break;
        case 8:
            system("cls");
            // Mostrar Arbol
            mostrarMotor(motor);
            system("pause");
            system("cls");
            break;
        case 9:
            system("cls");
            // Mostrar diccionario.dat
            mostrararchivoDiccionario();
            system("pause");
            system("cls");
            break;
        case 10:
            system("cls");
            // Mostrar las palabras de un archivo en particular
            printf("\n->Ingrese ID archivo en el que buscar ->\n ");
            scanf("%i", &id3);
            int cant = mostrarPalabrasdeID(id3);
            printf("->Cantidad de palabras que contiene el documento: <%i>\n\n", cant);
            system("pause");
            system("cls");
            break;
        case 11:
            system("cls");
            // Mostrar arreglo de terminos
            mostrarArreglo(arreglo, validos);
            system("pause");
            system("cls");
            break;
        case 12:
            system("cls");
            // Palabra mas repetida en todo el motor
            int validos2 = 0;
            maximaFrecuenciaTodos(motor, array, &validos2);
            buscandoPalabraMaximaFreqTodos(array, validos2);
            system("pause");
            system("cls");
            break;
        case 13:
            system("cls");
            integrantesTP();
            system("pause");
            system("cls");
            break;
        default:
            printf("ERROR: No existe la opcion indicada \n");
            system("pause");
            system("cls");
            main();
            break;
        }
    } while (opcion != 0);

    return 0;
}
int MenuOpciones()
{
    int opcion = 0;
    printf("\n\n                                      TP FINAL                               \n");
    printf("                              [OPERACIONES DEL USUARIO]                            \n\n");
    printf("1-> Buscar todas las apariciones de un termino en algun documento (operacion or). \n");
    printf("2-> Buscar todas las apariciones de un termino en un documento y otro (operacion and).\n");
    printf("3-> Buscar la aparicion de mas de un termino en el mismo documento\n");
    printf("4-> Buscar una frase completa (las palabras deben estar contiguas en alguno de los documentos)\n");
    printf("5-> Buscar la palabra de mas frecuencia que aparece en alguno de los docs\n");
    printf("6-> Utilizar la distancia de levenshtein en el ingreso de una palabra y sugerir \nsimilares a partir de una distancia <= 3\n");
    printf("7-> Crear un archivo con palabras para agregar al motor\n");
    printf("\n\n                               [FUNCIONES AUXILIARES]                            \n\n");
    printf("8->  Mostrar Arbol de Palabras(Motor)\n");
    printf("9->  Mostrar Diccionario.dat\n");
    printf("10-> Mostrar Palabras de un documento en particular\n");
    printf("11-> Mostrar Arreglo de Terminos\n");
    printf("12-> Palabra que mas se repite en nuestro motor\n");
    printf("13-> Integrantes del Grupo\n");
    printf("14-> Ingrese 0 para salir\n\n");
    printf("\n                                [INFORMACION MOTOR]                            \n\n");
    printf("->Cantidad de palabras en el motor   < %i >\n", cantidadPalabrasTotal());
    printf("->Cantidad de documentos en el motor < %i >\n\n", cantidadDocumentos() - 1);
    printf("*Ingrese una opcion numerica -> ");
    scanf("%d", &opcion);
    return opcion;
}
