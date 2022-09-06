#include "btree.h"

#ifndef __FUNCIONES_H_
#define __FUNCIONES_H_

/**
 * Crea e inicializa 256 hojas (árboles con peso 0 y sin hijos), asignandole
 * un caracter de la tabla ASCII a cada uno.
 */
BTree* crear_duplas();

/**
 * Recorriendo el buf, va guardando en duplas cuantas veces aparece cada uno 
 * de sus caracteres.
 */
void contar_caracteres(BTree* duplas, char* buf, int len);


/**
 * Función de ordenamiento. Utiliza el algoritmo de ordenamiento por selección.
 */
void ordena_duplas(BTree* duplas, int inicio);

/**
 * Recorre el arbol para ir guardando la codificación de cada caracter en su 
 * posición de la tabla ASCII.
 * 
 * Ej: 
 *    -Codificacion de 'A' en el arbol: 00011.
 *    -'A' en tabla ASCII: 65.
 *    -arreglo[65] = "00011".
 */
void char_codificacion (BTree arbol, char* strAux, char* arreglo[CANT_CHARS], int contador);

/**
 * Recorre el buf y a cada caracter lo reemplaza por su codificación en el
 * arbol (almacenada en codes). Retorna el buf codificado.
 */
char* codificar_texto(char* buf, int len, char* codes[CANT_CHARS], int* nLen);

/**
 * Toma la codificación de un arbol, lo crea e inicializa con sus caracteres
 * correspondientes en cada hoja y lo retorna.     
 */
BTree arbol_desde_texto (char *code, int *pos, int *charsAgregados);

/**
 * Recorre un arbol siguiendo las instrucciones de buf hasta encontrar una hoja.
 * Retorna el caracter que haya en la misma.
 * Instrucciones a seguir:
 *  - Si el arbol es una hoja retorna el caracter que contenga.
 *  - Si no es una hoja mira el buf:
 *      i) Si hay un 0, llama a su hijo izquierdo.
 *      ii) Si hay un 1, llama a su hijo derecho.
 */
char buscar_caracter(BTree arbol, char* buf, int *pos);

/**
 * Decodifica el buf de 0's y 1's.
 */
char *decodificar_texto(BTree arbol, char *buf, int len, int *lenDecoded);

/**
 * Toma el nombre de un archivo y la modificación deseada. Retorna la nueva
 * ruta. Ej:
 *  fileName = "probando.txt.hf", dato = "pdf"
 *  retorno: "probando.txt.pdf"
 */
char *cambio_archivo (char *fileName, char *dato);

/**
 * Recorre el arreglo de strings para liberar la memoria de cada uno. 
 */
void destruir_arreglo(char *chars[CANT_CHARS]);

#endif /*  __FUNCIONES_H_ */