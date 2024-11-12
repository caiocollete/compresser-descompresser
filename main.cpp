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

void pre_ordem(Tree*root){
	if(root!=NULL){
		printf("%s, ",root->string);
		pre_ordem(root->esq);
		pre_ordem(root->dir);
	}
}

void printar(Tabela *t){
	while(t!=NULL){
		printf("----\n");
		printf("SIMBOL: %d\tSTR: %s\tfreq: %d\n",t->simbol,t->string,t->freq);
		t=t->prox;
	}
} // apenas para teste

void printarL(ListaGen *L){
	while(L!=NULL){
		printf("----\n");
		printf("STR: %s\tfreq: %d\n",L->no->string,L->no->freqArv);
		L=L->prox;
	}
} // apenas para teste



int main(void){
	
	ListaGen *LG;
	Tabela *tabela;
	tabela = gerarTabela("message.txt");
	LG = gerarLG(tabela);
	// printarL(LG);
	// A arvore vai ficar na LG, o ultimo no, ou no caso, a raiz da arvore sera apontada pela listaGen
	GerarArvore(&LG);
	pre_ordem(LG->no);
	
	return 0;
}
