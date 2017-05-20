#include "BTree.h"

/****************************************************************************/
/*********************************** INIT ***********************************/
/****************************************************************************/
void STinit(link* head) {
	//inicializa a posicao da raiz da arvore
	*head = NULL;
};

/****************************************************************************/
/********************************** INSERT **********************************/
/****************************************************************************/
void STinsert(link* head, Item item) {
	//insere um item na arvore
	*head = insertR(*head, item);
};

link insertR(link h, Item item) {
	if (h == NULL) { //se a posicao estiver vazia adiciona o item aqui
		return NEW(item, NULL, NULL);
	};
	if (less(key(item), key(h->item))) { //se a chave do item for menor que a
		//chave do item na posicao da arvore insere o a esquerda dele
		h->l = insertR(h->l, item);
	} else { //senao insere o item a direita do item da posicao da arvore
		h->r = insertR(h->r, item);
	};
	h = AVLbalance(h); //equilibra a arvore
	return h;
};

link NEW(Item item, link l, link r) {
	//aloca memoria para criar um item na arvore
	link x = (link) malloc(sizeof(struct node));
	x->item = item;
	x->l = l;
	x->r = r;
	x->height = 1;
	return x;
};

/****************************************************************************/
/********************************** DELETE **********************************/
/****************************************************************************/
void STdelete(link* head, Key k) {
	//dada uma chave, apaga o item q lhe corresponde da arvore
	*head = deleteR(*head, k);
};

link deleteR(link h, Key k) {
	if (h == NULL){
		return h;
	} else if (less(k, key(h->item))) { //se a chave do item for menor
		//procura o elemento a esquerda da posicao
		h->l = deleteR(h->l, k);
	} else if (less(key(h->item), k)) {//se a chave for maior procura a direita
		h->r = deleteR(h->r, k);
	} else { //senao e pq ja esta na posicao correta
		if (h->l != NULL && h->r != NULL) { //remocao de um no' interno
			link aux = max(h->l);  //guarda em aux o maior elemento
								   //a esquerda do elemento a remover
			{
				//troca os elementos
				Item x;
				x = h->item;
				h->item = aux->item;
				aux->item = x;
			};
			h->l = deleteR(h->l, key(aux->item)); //apaga o aux
		} else {
			link aux = h;
			if (h->l == NULL && h->r == NULL) { //se o no' nao tiver filhos
				h = NULL;
			} else if (h->l == NULL) { //se so houver um filho a direita,
				h = h->r; 		//o elemento e substituido por esse filho
			} else { //se so houver o filho da esquerda,
				h = h->l; //o elemento e substituido pro esse filho
			};
			deleteItem(aux->item); //apaga o item do no' em aux
			free(aux); //apaga o no'
		};
	};
	h = AVLbalance(h); //equilibra a arvore
	return h;
};

/****************************************************************************/
/********************************** SEARCH **********************************/
/****************************************************************************/
Item STsearch(link h, Key v) {
	//dada uma key procura na arvore o elemento que lhe corresponde
	return searchR(h, v);
};

Item searchR(link h, Key v) {
	if (h == NULL) { //se a arvore estiver vazia retorna NULL
		return NULL;
	} else if (equal(v, key(h->item))) { //se encontrou a chave retorna o item
		return h->item;
	} else if (less(v, key(h->item))) { //procura a esquerda se a key a procurar for menor que o item a comparar
		return searchR(h->l, v);
	} else {
		return searchR(h->r, v); //procura a direita se a key for maior
	};
};

/* SORT */
void STsort(link head, void (*visit)(Item)) {
	//ordena os elementos da arvore
	sortR(head, visit);
};


void sortR(link h, void (*visit)(Item)) {
	if (h == NULL) {
		return;
	};
	sortR(h->l, visit); //travessia in order
	visit(h->item);
	sortR(h->r, visit);
};

/****************************************************************************/
/*********************************** FREE ***********************************/
/****************************************************************************/
void STfree(link* head) {
	//apaga a arvore toda
	*head = freeR(*head);
};

link freeR(link h) {
	//apaga um elemento chamando a deleteR
	if (h == NULL){
		return h;
	};
	h->l = freeR(h->l);
	h->r = freeR(h->r);
	return deleteR(h, key(h->item));
};

/****************************************************************************/
/********************************** OTHERS **********************************/
/****************************************************************************/
link max(link h) {
	//procura o maximo a partir de uma posicao da arvore
	while (h != NULL && h->r != NULL) {
		h = h->r;
	};
	return h;
};

link min(link h) {
	//procura o minimo a partir de uma posicao da arvore
	while (h != NULL && h->l != NULL) {
		h = h->l;
	};
	return h;
};

Item percorreAte(link h, int (*cond)(Item)) {
	//percorre a arvore ate encontrar um item que satisfaca a condicao (recursiva)
	if (h == NULL) {
		return NULL;
	};
	Item maxItem = percorreAte(h->l, cond); //verifica se o filho filho a esquerda verifica a condicao
	if (maxItem == NULL){ //senao
		return cond(h->item) ? h->item : percorreAte(h->r, cond); //verifica se o elemento satisfaz a condicao
		//se nao verfica no filho a direita
	} else {
		return maxItem;
	};
};

void auxMax(link h, int* pmax, Item* p_maxItem) {
	//percorre a arvore toda para encontrar o maximo
	if (h == NULL) {
		return;
	};
	auxMax(h->l, pmax, p_maxItem);
	eMax(h->item, pmax, p_maxItem);
	auxMax(h->r, pmax, p_maxItem);
};

/****************************************************************************/
/*********************************** AUXs ***********************************/
/****************************************************************************/
int height(link h) {
	//devolve a altura de um no'
	if (h == NULL) {
		return 0;
	};
	return h->height;
};


link rotL(link h) {
	int height_left, height_right;
	link x = h->r;
	h->r = x->l;
	x->l = h;

	//atualiza a altura dos nos
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
};

link rotR(link h) {
	int height_left, height_right;
	link x = h->l;
	h->l = x->r;
	x->r = h;

	//atualiza a altura dos nos
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
};

link rotLR(link h) {
	//rotação dupla esquerda direita
	if (h == NULL) {
		return h;
	};
	h->l = rotL(h->l);
	return rotR(h);
};

link rotRL(link h) {
	//rotação dupla direita esquerda
	if (h == NULL) {
		return h;
	};
	h->r = rotR(h->r);
	return rotL(h);
};

int Balance(link h) {
	//balance factor
	if (h == NULL) {
		return 0;
	};
	return height(h->l) - height(h->r);
};

link AVLbalance(link h) {
	int balanceFactor;
	if (h == NULL) {
		return h;
	};
	balanceFactor = Balance(h);
	if (balanceFactor > 1) {
		if (Balance(h->l) >= 0) {
			h = rotR(h);
		} else {
			h = rotLR(h);
		};
	} else if (balanceFactor<-1) {
		if (Balance(h->r) <= 0) {
			h = rotL(h);
		} else {
			h = rotRL(h);
		};
	} else {
		int height_left = height(h->l);
		int height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	};
	return h;
};
