/* Joao Daniel Silva 86445 */
/* Francisco do Canto Sousa 86416*/

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h> 
//incluir bibliotecas de arvores



/* DEFINICAO DE CONSTANTES */
#define MAXCHARS 8 //para a chave do produto


/* DEFINICAO DE ESTRUTURAS*/
typedef struct produto{
 char *chave;
 int quantidade;
} *Item;
 

int main() {
	int done;
	char command;
	done = 0;
	while(!done) {
		lelinha();
		switch (command) {
			case 'a':
				add
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
			case 'X':
				/**/
				done = 1; //altera o valor da variavel de controlo para interromper o ciclo
				break;
			default: printf("ERRO: Comando desconhecido\n");
		}
	}
	return	0;
}

*char lelinha() {
	char c;
	*char command;
	scanf("%c",c);
	*command = (char *)malloc(sizeof(char)*2);
	*command = c;

}