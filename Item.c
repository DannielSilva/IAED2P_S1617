#include "Item.h"

typedef struct node {
	Item item;
	struct node *l;
	struct node *r;
} *link;

static link head;
void init() {
	head = NULL;
};

link NEW(Item item, link l, link r) {
	link x = (link) malloc(sizeof(struct node));
	x->item = item;
	x->l = l;
	x->r = r;
	return x;
};

link search(link h, int v) {
	if (h == NULL){
		return NULL;
	} else if (eq(v, h->item))) {
		return h;
	} else if (less(v, h->item))) {
		return search(h->l, v);
	} else {
		return search(h->r, v);
	};
};

link insert(link h, Item item) {
	Item v = item;
	if (h == NULL){
		return NEW(item, NULL, NULL);
	} else {
		if (less(v, h->item)){
			h->l = insert(h->l, item);
		} else {
			h->r = insert(h->r, item);
		};
		return h;
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

link delete(link h, Item item) {
	link aux;
	if (h == NULL){
		return h;
	} else if (less(item, h->item)) {
		h->l=delete(h->l, item);
	} else if (less(h->item, item)) {
		h->r=delete(h->r, item) ;
	} else {
		if (h->l !=NULL && h->r !=NULL) { /*caso 3*/
			aux = max(h->l);
			h->item = aux->item;
			h->l = delete(h->l, aux->item);
		} else { /*casos 1 e 2*/
			aux = h;
			if (h->l == NULL && h->r == NULL ) {
				h = NULL;
			} else if (h->l == NULL) {
				h = h->r;
			} else {
				h = h->l;
			};
			deleteItem(aux->item);
			free(aux);
		};
	};
	return h;
};

int count(link h) {
	if (h == NULL) {
		return 0;
	} else {
		return count(h->r) + count(h->l) + 1;
	};
};

int height(link h) {
	int u, v;
	if (h == NULL) {
		return 0;
	};
	u = height(h->l);
	v = height(h->r);
	if (u > v) {
		return u+1;
	} else {
		return v+1;
	};
};

void visit(Item i) {
	//
};
