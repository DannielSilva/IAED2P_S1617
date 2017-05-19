#ifndef _BTREE_
#define _BTREE_
#include <stdlib.h>
#include <stdio.h>
#include "Item.h"

typedef struct node {
	Item item;
	struct node *l;
	struct node *r;
	int height;
} *link;

void STinit(link*);

void STinsert(link*, Item);
link insertR(link, Item);
link NEW(Item, link, link);

void STdelete(link*, Key);
link deleteR(link, Key);

Item STsearch(link, Key);
Item searchR(link, Key);

void STsort(link, void (*visit)(Item));
void sortR(link, void (*visit)(Item));

void STfree(link*);
link freeR(link);

int STcount(link);
int count(link);
link max(link);
link min(link);
Item percorreAte(link, int (*cond)(Item));

int height(link);
link rotL(link);
link rotR(link);
link rotLR(link);
link rotRL(link);
int Balance(link);
link AVLbalance(link);

#endif
