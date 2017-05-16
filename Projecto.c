/* Joao Daniel Silva 86445 ~ Francisco do Canto Sousa 86416 */

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
//incluir bibliotecas de arvores



/* DEFINICAO DE CONSTANTES */
#define MAXCHARS 8 //para a chave do produto


/* DEFINICAO DE ESTRUTURAS*/
typedef struct produto{
 char *chave;//Meter no Item.h
 int quantidade;
} *Item;


int main() {
	int done;
	char command;
	done = 0;
	while (!done) {
		leChave();
		switch (command) {
			case 'a':
				/**/
				break;
			case 'l':
				/**/
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
		}
	}
	return 0;
}

*char leChave() {
	char buffer[MAXCHARS+1]; char* chave;
	scanf("%s", buffer);
	chave = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(strings[i],buffer);
	return chave;
};
