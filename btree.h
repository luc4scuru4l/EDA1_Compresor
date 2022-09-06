#ifndef __BTREE_H__
#define __BTREE_H__

#ifndef CANT_CHARS
#define CANT_CHARS 256
#endif

typedef struct _BTNodo {
  int peso;
  char caracter;
  struct _BTNodo *left;
  struct _BTNodo *right;
} Nodo;

typedef Nodo* BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);


/**
 * Retorna un arbol cuyos hijos son left y right y el peso la suma de ambos.
 */
BTree btree_unir(BTree left, BTree right);

/**
 * Indica si el arbol es una hoja.
 */
int es_hoja(BTree arbol);


/**
 * Recorre el arbol y guarda en un arreglo su codificación y los caracteres en
 * el orden en que aparecen.
 * codificacion[0 - 510] --> codificacion del arbol.
 * codificacion[511 - 767] --> caracteres.
 */
void btree_codificacion(BTree arbol, char* code, int* contTotal, int* contUnos);

/**
 * Arma un arbol cuyas hojas son los arboles del arreglo duplas. 
 */
BTree btree_armar(BTree* duplas);

#endif /* __BTREE_H__ */
