#ifndef _ITEM_
#define _ITEM_

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARS 8 //para a chave do produto
#define key(A) (A != NULL ? A->chave : "")
#define less(A, B) strcmp(A, B) < 0
#define equal(A, B) strcmp(A, B) == 0
#define quant(A) A->quantidade

/* DEFINICAO DE ESTRUTURAS*/
typedef char* Key;
typedef struct produto {
	//char chave[MAXCHARS+1];
	char* chave;
	int quantidade;
} *Item;

void deleteItem(Item);
Item newItem(char*, int);
void visitItem(Item);

#endif
