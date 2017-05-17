#include "Item.h"

void deleteItem(Item item) {
	free(item->chave);
	free(item);
};

Item newItem(char* chave, int quant) {
	Item novo;
 	novo = (Item) malloc(sizeof(struct produto));
	strcpy(novo->chave, chave);
	novo->quantidade = quant;
	return novo;
};

void visitItem(Item a) {
	printf("%s, n=%d\n", a->chave, a->quantidade);

};
