#include "Item.h"

void deleteItem(Item item) {
	free(item->chave);
	free(item);
};

Item newItem(char* chave, int quant) {
	Item novo = (Item) malloc(sizeof(struct produto));
	novo->chave = strdup(chave);
	novo->quantidade = quant;
	//strcpy(novo->chave, chave);
	return novo;
};

void visitItem(Item a) {
	printf("%s %d\n", a->chave, a->quantidade);
};
