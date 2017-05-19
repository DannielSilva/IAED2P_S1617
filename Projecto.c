/* Joao Daniel Silva 86445 ~ Francisco do Canto Sousa 86416 */

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "Item.h"

/* DEFINICAO DE CONSTANTES */
#define MAXCHARS 8 //para a chave do produto
#define maior(A,B) A > B ? A : B
 ///METER TODOS OS CHAR* a KEY
 //APAGAR FUNCOES INUTEIS
static link head;
int nProds = 0; int maxQuant = 0; int maxNum = 0;

void addProduto();
void readChave(char*);
void removeProduto();
void maxProduto();
Item searchMax();
void auxMax(link, int*, Item*);

Item search4QuantidadeMax();
int sameQuant(Item);

int main() {
	int done = 0; char command;
	STinit(&head);
	while (!done) {
		scanf("\n%c", &command);
		switch (command) {
			case 'a':
				addProduto();
				break;
			case 'l':
				STsort(head, visitItem);
				break;
			case 'm':
				if (/*maxNum && */nProds) {
					maxProduto();
				};
				break;
			case 'r':
				removeProduto();
				break;
			case 'x':
				STfree(&head);
				printf("%d\n", nProds);
				done = 1; //altera o valor da variavel de controlo para interromper o ciclo
				break;
			default: printf("ERRO: Comando desconhecido\n");
		};
	};
	return 0;
};

void readChave(char* chave) {
	scanf("%s", chave);
};

void readUnidades(int* uni) {
	scanf("%d", uni);
};

void addProduto() {
	Item existIt; char chave[MAXCHARS+1]; int unis;
	readChave(chave);
	readUnidades(&unis);
	existIt = STsearch(head, chave);
	if (existIt == NULL) { //Se a chave nao for encontrada
		existIt = newItem(chave, unis);
		STinsert(&head, existIt);
		nProds++;
	} else { //Se o produto ja existir
		if (maxQuant == existIt->quantidade && unis < 0 && maxQuant) {
			//Se subtrair produtos ao item maximo, e o maximo nao for ja 0
			maxNum--;
			//if (!maxNum) maxQuant = -1;
		};
		//Fazer calculos
		existIt->quantidade += unis;
		existIt->quantidade = maior(existIt->quantidade, 0);
	};
	//Definir o novo maximo
	if (maxQuant < existIt->quantidade) {
		maxQuant = existIt->quantidade;
		maxNum = 1;
	} else if (maxQuant == existIt->quantidade) {
		maxNum++;
	};
};

void removeProduto() {
	Item existIt; char chave[MAXCHARS+1];
	readChave(chave);
	existIt = STsearch(head, chave);
	if (existIt != NULL) {
		if (maxQuant == existIt->quantidade) {
			//Se for um dos maximos
			maxNum--;
			//if (!maxNum) maxQuant = -1;
		};
		STdelete(&head, chave);
		nProds--;
	};
};

void maxProduto() {
	Item maxItem;
	if (maxNum) {
		maxItem = search4QuantidadeMax();
	} else {
		maxItem = searchMax();

	};
	visitItem(maxItem);
};

Item search4QuantidadeMax() {
	return percorreAte(head, sameQuant);
};

int sameQuant(Item item) {
	return item->quantidade - maxQuant;
};

Item searchMax() {
	int max = -1; Item maxItem;
	auxMax(head, &max, &maxItem);
	maxQuant = max;
	return (maxItem);
};

void auxMax(link h, int* pmax, Item* p_maxItem) {
	if (h == NULL) {
		return;
	};
	auxMax(h->l, pmax, p_maxItem);
	if (h->item->quantidade > *pmax) {
		*pmax = h->item->quantidade;
		*p_maxItem = h->item;
		//printf("bef maxNum = 1 maxnum %d act %d %s max %d\n", maxNum, h->item->quantidade, h->item->chave, *pmax);
		maxNum = 1;
	} else if (h->item->quantidade == *pmax) {
		//printf("bef maxNum++ maxnum %d act %s max %d\n", maxNum, h->item->chave, *pmax);
		maxNum++;
	};
	auxMax(h->r, pmax, p_maxItem);
};
