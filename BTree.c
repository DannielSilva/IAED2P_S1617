#include "BTree.h"

//INIT
void STinit(link* head) {
	*head = NULL;
};

//INSERT
void STinsert(link* head, Item item) {
	*head = insertR(*head, item);
};

link insertR(link h, Item item) {
	if (h == NULL) {
		return NEW(item, NULL, NULL);
	};
	if (less(key(item), key(h->item))) {
		h->l = insertR(h->l, item);
	} else {
		h->r = insertR(h->r, item);
	};
	h = AVLbalance(h);
	return h;
};

link NEW(Item item, link l, link r) {
	link x = (link) malloc(sizeof(struct node));
	x->item = item;
	x->l = l;
	x->r = r;
	x->height = 1;
	return x;
};

//DELETE
void STdelete(link* head, Key k){
	*head = deleteR(*head, k);
}

link deleteR(link h, Key k) {
	if (h == NULL){
		return h;
	} else if (less(k, key(h->item))) {
		h->l = deleteR(h->l,k);
	} else if (less(key(h->item), k)) {
		h->r = deleteR(h->r,k);
	} else {
		if (h->l != NULL && h->r != NULL) {
			link aux = max(h->l);
			{
				Item x;
				x = h->item;
				h->item = aux->item;
				aux->item = x;
			};
			h->l = deleteR(h->l, key(aux->item));
		} else {
			link aux = h;
			if (h->l == NULL && h->r == NULL){
				h=NULL;
			} else if (h->l == NULL) {
				h = h->r;
			} else {
				h = h->l;
			};
			deleteItem(aux->item);
			free(aux);
		};
	};
	h = AVLbalance(h);
	return h;
};

//SEARCH
Item STsearch(link h, Key v) {
	return searchR(h, v);
};

Item searchR(link h, Key v) {
	if (h == NULL) {
		return NULL;
	} else if (equal(v, key(h->item))) {
		return h->item;
	} else if (less(v, key(h->item))) {
		return searchR(h->l, v);
	} else {
		return searchR(h->r, v);
	};
};

//SORT
void STsort(link head, void (*visit)(Item)) {
	sortR(head, visit);
};

void sortR(link h, void (*visit)(Item)) {
	if (h == NULL){
		return;
	};
	sortR(h->l, visit);
	visit(h->item);
	sortR(h->r, visit);
};

//FREE
void STfree(link* head) {
	*head = freeR(*head);
};

link freeR(link h) {
if (h == NULL){
	return h;
};
	h->l = freeR(h->l);
	h->r = freeR(h->r);
	return deleteR(h,key(h->item));
};

//OTHERS
int STcount(link head) {
	return count(head);
};

int count(link h) {
	if (h == NULL) {
		return 0;
	} else {
		return count(h->r) + count(h->l) + 1;
	};
};

link max(link h) {
	while (h != NULL && h->r != NULL) {
		h = h->r;
	};
	return h;
};

link min(link h) {
	while (h != NULL && h->l != NULL) {
		h = h->l;
	};
	return h;
};

//AUX
int height(link h) {
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

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
};

link rotR(link h) {
	int height_left, height_right;
	link x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
};

link rotLR(link h) { /*rotação dupla esquerda direita*/
	if (h == NULL) {
		return h;
	};
	h->l = rotL(h->l);
	return rotR(h);
};

link rotRL(link h) { /*rotação dupla direita esquerda*/
	if (h == NULL) {
		return h;
	};
	h->r = rotR(h->r);
	return rotL(h);
};

int Balance(link h) { /*Balance factor*/
	if (h == NULL) {
		return 0;
	};
	return height(h->l) - height(h->r);
};

link AVLbalance(link h) {
	int balanceFactor;
	if (h == NULL){
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
