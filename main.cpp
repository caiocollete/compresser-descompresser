#include <stdio.h>
#include <stdlib.h>
#include "arvhuff.h"

/*	
	int simbol;
	char string[MAXSTRING];
	int freq;
	char cod_huff[8];
	struct infos *prox;
*/
void printar(Tabela *t){
	while(t!=NULL){
		printf("----\n");
		printf("SIMBOL: %d\tSTR: %s\tfreq: %d\n",t->simbol,t->string,t->freq);
		t=t->prox;
	}
} // apenas para teste


int main(void){
	
	ListaGen *LG;
	Tabela *tabela;
	tabela = gerarTabela("message.txt");
	LG = gerarLG(tabela);
	// A arvore vai ficar na LG, o ultimo no, ou no caso, a raiz da arvore sera apontada pela listaGen
	GerarArvore(LG);
	
	return 0;
}
