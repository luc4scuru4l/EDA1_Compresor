#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "io.h"
#include "btree.h"
#include "funciones.h"

int main(int argI, char *argC[3]){

  if (argC[1][0] == 'C' || argC[1][0] == 'c') {

    char *fileName = argC[2];
    int bufLen;
    char *buf = readfile(fileName, &bufLen);

    /* Crea un arreglo con las hojas del arbol. */
    BTree* duplas = crear_duplas();
    contar_caracteres(duplas, buf, bufLen);
    ordena_duplas(duplas, 0);

    /* Crea el arbol */
    BTree arbol = btree_armar(duplas);
    free(duplas);
    
    /* Arma la codificación del arbol y la guarda en el archivo .tree */
    char *codeArbol = malloc(sizeof(char) * CANT_CHARS * 3);
    char *codeChars[CANT_CHARS];
    char *aux = malloc(CANT_CHARS * sizeof(char));
    char *pathTree = malloc(sizeof(char) * strlen(fileName) + 6);
    int lenCode = 0, lenChars = 0;
    strcpy(pathTree, fileName);
    strcat(pathTree, ".tree");

    btree_codificacion(arbol, codeArbol, &lenCode, &lenChars);
    writefile(pathTree, codeArbol, (CANT_CHARS*3) - 1);
    free(pathTree);
    
    /* Guarda la codificación en el arbol de cada caracter. */
    char_codificacion(arbol, aux, codeChars, 0);
    btree_destruir(arbol);
    free(codeArbol);
    free(aux);

    /* Con el arreglo de codificaciones anterior y el buf, codifica el texto. */
    int nLen;
    char* pathHf = malloc(sizeof(char) * strlen(fileName) + 4);
    strcpy(pathHf, fileName);
    strcat(pathHf, ".hf");
    char *bufCodificado = codificar_texto(buf, bufLen, codeChars, &nLen);
    free(buf);
    destruir_arreglo(codeChars);  

    /* Con implode lo deja listo para guardar en el archivo .hf. */
    char *bufImplotado = implode(bufCodificado, strlen(bufCodificado), &nLen);
    free(bufCodificado);

    writefile(pathHf, bufImplotado, nLen);
    free(bufImplotado);
    free(pathHf);

    return 0;
  }
  else if (argC[1][0] == 'D' || argC[1][0] == 'd') {
    
    /** 
     * Lee el archivo, guarda su contenido en un buffer y lo pasa a su 
     * codificación de 1's y 0's.
     */
    char *fileName = argC[2];
    int bufLen, bufELen;
    char *buf = readfile(fileName, &bufLen);
    char *bufExploded = explode(buf, bufLen, &bufELen);
    free(buf);

    /* Arma el arbol a partir de su codificación obtenida en el archivo .tree */
    char *pathTree = cambio_archivo(fileName, "tree");
    int codeArbolLen, contA = 0, contB = 0;
    char *codeArbol = readfile(pathTree, &codeArbolLen);;
    BTree arbol = arbol_desde_texto(codeArbol, &contA, &contB);
    free(pathTree);
    free(codeArbol);

    /** 
     * Recorre el buffer para pasar de la codificación en 0's y 1's a su 
     * representación en caracteres (textoDecodificado).
     */
    int lenDecoded = 0;
    char *textoDecodificado;
    textoDecodificado = decodificar_texto(arbol, bufExploded, bufELen, &lenDecoded);
    free(bufExploded);
    btree_destruir(arbol);
    
    /* Escribe el texto decodificado en el archivo .dec */
    char *pathDec = cambio_archivo(fileName, "dec");
    writefile(pathDec, textoDecodificado, lenDecoded);
    free(pathDec);
    free(textoDecodificado);
    return 1;
  }
  
  perror("Caracter no aceptado, elija 'C' o 'D'");
  return 2;
}