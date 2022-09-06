#include "btree.h"
#include "funciones.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }


BTree btree_unir(BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->peso = left->peso + right->peso; 
  return nuevoNodo;
}


int es_hoja(BTree arbol) {
  return btree_empty(arbol->left);
}

void btree_codificacion (BTree arbol, char* codificacion, int* bitsAgregados, int* charsAgregados) {
  if (btree_empty(arbol)) {/* Si es NULL no se debe contar */
    return;
  }
  
  if (es_hoja(arbol)) {  /* Si es una hoja */
    codificacion[*bitsAgregados] = '1';
    int charPos = *charsAgregados + (CANT_CHARS * 2) - 1;
    codificacion[charPos] = arbol->caracter;
    *charsAgregados += 1;
  } else {
    codificacion[*bitsAgregados] = '0';
  }
  
  *bitsAgregados += 1;

  btree_codificacion(arbol->left, codificacion, bitsAgregados, charsAgregados);
  btree_codificacion(arbol->right, codificacion, bitsAgregados, charsAgregados); 
}


BTree btree_armar(BTree* duplas){ 
  int i = 0;
  for (; i < CANT_CHARS-1; i++){
    if (duplas[i]->peso > duplas[i+1]->peso)
      ordena_duplas(duplas, i);
    duplas[i+1] = btree_unir(duplas[i], duplas[i+1]);
  }
  return duplas[i];
}

