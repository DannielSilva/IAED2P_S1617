#include "Item.h"

/****************************************************************************/
/*************************** FUNCOES SOBRE ITEMs ****************************/
/****************************************************************************/
Item newItem(Key chave, int quant) {
	Item novo = (Item) malloc(sizeof(struct produto)); //aloca memoria
	novo->chave = strdup(chave);
	novo->quantidade = quant;
	return novo;
};

void deleteItem(Item item) {
	free(item->chave);
	free(item);
};

void visitItem(Item a) {
	printf("%s %d\n", a->chave, a->quantidade);
};

/****************************************************************************/
/************************** FUNCOES SOBRE MAXIMO ****************************/
/****************************************************************************/
int equalMax(Item item) {
	return !(item->quantidade - maxQuant);
};

void eMax(Item item, int* pmax, Item* p_maxItem) {
	if (item->quantidade > *pmax) {
		*pmax = item->quantidade;
		*p_maxItem = item;
		maxNum = 1;
	} else if (item->quantidade == *pmax) {
		maxNum++;
	};
};
