/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~ Joao Daniel Silva 86445 ~ Francisco do Canto Sousa 86416 ~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/****************************************************************************/
/******************************** BIBLIOTECAS *******************************/
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "Item.h"

/****************************************************************************/
/******************************** CONSTANTES ********************************/
/****************************************************************************/
#define MAXCHARS 8 //para a chave do produto
#define maior(A,B) A > B ? A : B

/****************************************************************************/
/***************************** VARIAVEIS GLOBAIS ****************************/
/****************************************************************************/
static link head; //arvore
int nProds = 0, //numero de produtos
maxQuant = 0, maxNum = 0; //quantidade max e numero de produtos com essa quanti
Item maxPoint = NULL; //produto com a quantidade maxima e menor chave


/****************************************************************************/
/******************************** PROTOTIPOS ********************************/
/****************************************************************************/
void addProduto();
void readChave(Key);
void removeProduto();
void maxProduto();

Item searchMax();
Item search4QuantidadeMax();

/****************************************************************************/
/*********************************** MAIN ***********************************/
/****************************************************************************/
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
				if (nProds) {
					maxProduto();
				};
				break;
			case 'r':
				removeProduto();
				break;
			case 'x':
				STfree(&head);
				printf("%d\n", nProds);
				done = 1; //interrompe o ciclo
				break;
			default: printf("ERRO: Comando desconhecido\n");
		};
	};
	return 0;
};

/****************************************************************************/
/***************************** FUNCOES DE LEITURA ***************************/
/****************************************************************************/
void readChave(Key chave) {
	scanf("%s", chave);
};

void readUnidades(int* uni) {
	scanf("%d", uni);
};

/****************************************************************************/
/****************************** FUNCOES DA MAIN *****************************/
/****************************************************************************/
void addProduto() {
	Item existIt; char chave[MAXCHARS+1]; int unis;
	readChave(chave);
	readUnidades(&unis);
	existIt = STsearch(head, chave);

	if (!existIt) { //Se a chave nao for encontrada
		existIt = newItem(chave, unis);
		STinsert(&head, existIt);
		nProds++;
	} else { //Se o produto ja existir
		if (maxQuant == existIt->quantidade && unis < 0 && maxQuant) {
			//Se subtrair numeros ao produto maximo, e o maximo nao for ja 0
			if (existIt == maxPoint) { //Se for o maximo guardado
				maxPoint = NULL;
			};
			maxNum--;
		};
		//Fazer calculos
		existIt->quantidade += unis;
		existIt->quantidade = maior(existIt->quantidade, 0);
	};

	//Definir o novo maximo
	if (maxQuant < existIt->quantidade) { //Se for um maximo novo
		maxQuant = existIt->quantidade;
		maxPoint = existIt;
		maxNum = 1;
	} else if (maxQuant == existIt->quantidade) { //Se for um maximo existente
		if (!maxPoint || strcmp(existIt->chave, maxPoint->chave) < 0) {
			maxPoint = existIt;
		};
		maxNum++;
	};
};

void removeProduto() {
	Item existIt; char chave[MAXCHARS+1];
	readChave(chave);
	existIt = STsearch(head, chave);
	if (existIt) {
		if (maxQuant == existIt->quantidade) { //Se for um dos maximos
			if (existIt == maxPoint) { //Se for o maximo guardado
				maxPoint = NULL;
			};
			maxNum--;
		};
		STdelete(&head, chave);
		nProds--;
	};
};

void maxProduto() {
	if (maxNum) { //Se houver quantidade maxima guardada
		if (!maxPoint) { //Se tivermos de procurar ponteiro para o maximo
			maxPoint = search4QuantidadeMax();
		};
	} else { //Se nao houver quantidade guardada
		maxPoint = searchMax();
	};
	visitItem(maxPoint);
};

/****************************************************************************/
/****************************** FUNCOES DO MAXIMO ***************************/
/****************************************************************************/
Item search4QuantidadeMax() {
	return percorreAte(head, equalMax);
};

Item searchMax() {
	int max = -1; Item maxItem;
	auxMax(head, &max, &maxItem);
	maxQuant = max;
	return maxItem;
};
