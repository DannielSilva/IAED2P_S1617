/* Joao Daniel Silva 86445 ~ Francisco do Canto Sousa 86416 */

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "Item.h"

static link head;

/* DEFINICAO DE CONSTANTES */
#define MAXCHARS 8 //para a chave do produto

void addProduto();
void readChave(char* chave);

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
				/**/
				break;
			case 'r':
				/**/
				break;
			case 'x':
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
	if (existIt == NULL) {
		existIt = newItem(chave, unis);
		STinsert(&head, existIt);
	} else {
		existIt->quantidade += unis;
		if (existIt->quantidade<0) {
			existIt->quantidade = 0;
		};
	};
};
