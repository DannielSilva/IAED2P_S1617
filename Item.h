#ifndef _ITEM_
#define _ITEM_

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(A) (A != NULL ? A->chave : "")
#define less(A, B) strcmp(A, B) < 0
#define equal(A, B) strcmp(A, B) == 0
//#define itemlink(A) A->item
#define MAXCHARS 8 //para a chave do produto

/* DEFINICAO DE ESTRUTURAS*/
typedef char* Key;
typedef struct produto {
	char chave[MAXCHARS+1];
	int quantidade;
} *Item;

void deleteItem(Item);
Item newItem(char*, int);
void visitItem(Item);

#endif
