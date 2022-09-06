#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "btree.h"

BTree* crear_duplas(){
  BTree* nodos = malloc(sizeof(BTree) * CANT_CHARS);
  for (int i = 0; i < CANT_CHARS; i++) {
    BTree nuevo = malloc(sizeof(Nodo));
    nuevo->caracter = i;
    nuevo->peso = 0;
    nuevo->left = nuevo->right = btree_crear();
    nodos[i] = nuevo;
  }
  return nodos;
}

void contar_caracteres(BTree* duplas, char* buf, int len){
  int pos, cont = 0;
  for (int i = 0; i < len; i++) {
    pos = (unsigned char)buf[i];
    duplas[pos]->peso++;
  }
}

void mostrar_duplas(BTree* duplas){
  for (int i = 0; i < CANT_CHARS; i++) {
    if (duplas[i]->peso)
      printf("char: '%c', peso: %d\n", duplas[i]->caracter, duplas[i]->peso);
  }
}

void ordena_duplas(BTree* duplas, int inicio){ /* Selección */
  int min, minPos;
  BTree aux;
  for (int i = inicio; i < CANT_CHARS; i++) {
    minPos = i;
    for (int j = i+1; j < CANT_CHARS; j++) {
      if (duplas[j]->peso < duplas[minPos]->peso)
        minPos = j;
    }
    aux = duplas[i];
    duplas[i] = duplas[minPos];
    duplas[minPos] = aux;
  }
}

char *str_copia(char *palabra, int len) {
  char *palabraCopia = malloc((sizeof(char) * len) + 1);
  for (int i = 0; i < len; i ++) {
    palabraCopia[i] = palabra[i];
  }
  palabraCopia[len] = '\0';
  return palabraCopia;
}




void char_codificacion (BTree arbol, char* strAux, char* arreglo[CANT_CHARS], int contador){
  if (btree_empty(arbol)){
    contador--; 
    return;
  }
  if (es_hoja(arbol)) {
    unsigned char pos = (unsigned char)arbol->caracter;
    arreglo[pos] = str_copia(strAux, contador);
  } else {
    strAux[contador] = '0';
    contador++;
  }
  
  char_codificacion(arbol->left, strAux, arreglo, contador);
  strAux[contador-1] = '1';
  char_codificacion(arbol->right, strAux, arreglo, contador);
}

char* codificar_texto(char* buf, int len, char* codes[CANT_CHARS], int* nLen){
  int textLen = 0;
  int capBuf = len * 8;
  char* textoCodificado = malloc(capBuf+1);
  textoCodificado[0] = '\0';
  unsigned char pos;
  for (int i = 0; i < len; i++) {
    pos = (unsigned char)buf[i];
    if (textLen >= capBuf) {
      textoCodificado = realloc(textoCodificado, capBuf*2 + 1);
      capBuf *= 2;
    }
    for (int j = 0; j < strlen(codes[pos]); j++)
      textoCodificado[textLen + j] = codes[pos][j];
    textLen += strlen(codes[pos]);
    textoCodificado[textLen] = '\0';
  }
  *nLen = textLen;
  return textoCodificado;
}


char buscar_caracter(BTree arbol, char *buf, int *pos) {
  if (es_hoja(arbol)){
    return arbol->caracter;
  }
  *pos += 1;

  if (buf[*pos - 1] == '0') 
    return buscar_caracter(arbol->left, buf, pos);
  else 
    return buscar_caracter(arbol->right, buf, pos);
  

}

char *decodificar_texto(BTree arbol, char *buf, int len, int *i) {
  int largo = len, pos = 0;
  char *texto = malloc(largo);
  texto[0] = '\0';
  while ( pos < len) {
    if (*i > largo) {
      texto = realloc(texto, largo + len + 1);
    }
    texto[*i] = buscar_caracter(arbol, buf, &pos);
    *i += 1;
  }
  return texto;
}

BTree arbol_desde_texto (char *code, int *pos, int *charsAgregados) {
  BTree arbol = malloc(sizeof(Nodo));
  *pos += 1;
  if (code[*pos - 1] == '1' && *pos < 512) {
    arbol->caracter = code[*charsAgregados + 511];
    arbol->left = arbol->right = NULL;
    *charsAgregados += 1;
  } else if (code[*pos - 1] == '0' && *pos < 512){
    arbol->left = arbol_desde_texto(code, pos, charsAgregados);
    arbol->right = arbol_desde_texto(code, pos, charsAgregados);
  }
  return arbol;
}



char *cambio_archivo (char *fileName, char *dato) {
  int len = strlen(fileName) + strlen(dato);
  char *newFileName = malloc(sizeof(char) * len);
  for (int i = 0; i < len; i++) {
    if (i < strlen(fileName) - 2)
      newFileName[i] = fileName[i];
    else
      newFileName[i] = dato[i - strlen(fileName) + 2];
  }
  return newFileName;
}


void destruir_arreglo(char *chars[CANT_CHARS]){
  for (int i = 0; i < CANT_CHARS; i++)
      free(chars[i]);
}