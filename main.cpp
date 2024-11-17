#include <stdio.h>
#include <stdlib.h>
#include "arvhuff.h"

/*	
	int simbol;
	char string[MAXSTRING];
	int freq;
	char cod_huff[CODHUFF];
	struct infos *prox;
*/

void GeraCodigos(Tree*root, Tabela**T ,char codhuff[CODHUFF]){ // algoritimo fiz em pre_ordem para salvar os codigos de huff na tabela
	if(root!=NULL){
		if(strcmp(root->string,"%null")!=0){
			Tabela *aux=*T;
			while(aux!=NULL && strcmp(aux->string,root->string)!=0){
				aux=aux->prox;
			}
			if(aux!=NULL && strcmp(aux->string,root->string)==0){
				printf("\nINFO SENDO CODIFICADA: %s",aux->string);
				strcpy(aux->cod_huff,codhuff);
			}
		}
		else{
			char codhuffesq[CODHUFF], codhuffdir[CODHUFF];
			strcpy(codhuffesq,codhuff);
			strcpy(codhuffdir,codhuff);
			
			strcat(codhuffesq,"0");
			GeraCodigos(root->esq, T , codhuffesq);
			strcat(codhuffdir,"1");
			GeraCodigos(root->dir, T , codhuffdir);
		}
	}
}

void printar(Tabela *t){
	while(t!=NULL){
		printf("----\n");
		printf("SIMBOL: %d\tSTR: %s\tfreq: %d\tcodHuff: %s\n",t->simbol,t->string,t->freq,t->cod_huff);
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


char *procurarStringTabela(char string[], Tabela*t){
	while(t!=NULL && strcmp(t->string,string)!=0){
		t=t->prox;
	}
	if(t!=NULL && strcmp(t->string,string)==0)
		return t->cod_huff;
	return "";
}


void GerarStringCompilada(char filename[MAXSTRING], Tabela *t){
	
	FILE *arq = fopen(filename,"r");
	FILE *out = fopen("strCompilada.txt","w");
	int tamArq = getFileSize(arq);
	char stringCompilada[tamArq];
	stringCompilada[0] = '\0';
	char linha[tamArq];
	
	if(fgets(linha,tamArq,arq)){
		int i=0, contStr=0;
		char string[MAXSTRING];
		printf("\n%s",linha);
		while(linha[i]!='\0'){
			if (linha[i] == ' ') {
			    string[contStr] = '\0';
			    strcat(stringCompilada,procurarStringTabela(string,t));
			    strcat(stringCompilada,procurarStringTabela(" ",t));
			    contStr = 0;
			    //printf("\n%s",string);  //fiz esses prints pra testar
			    //printf("\n%s",stringCompilada);
			}
			else{
				string[contStr] = linha[i];
				contStr++;
			}
			i++;
		}
		fprintf(out,"%s" ,stringCompilada);
	}
	else
		printf("Nao foi possivel compressar a string: \n[READ ERROR: GerarStringCompiladaTabela()]");
	fclose(out);
}
	
void GravarTabela(Tabela *T){
	FILE *F = fopen("tabela.tabela","wb");
	
	while(T!=NULL){
		//printaTab no Arquivo
		printf("SIMBOL: %d\tSTR: %s\tfreq: %d\tcodHuff: %s\n",T->simbol,T->string,T->freq,T->cod_huff);
		fwrite(T, sizeof(Tabela),1,F);
		T=T->prox;
	}
	
	fclose(F);
}

void printarArvore(Tree *raiz){  //funcao pra printar a arvore, mas nao em formato de arvore
	if(raiz!=NULL){
		if(raiz->esq == NULL && raiz->dir == NULL){
			printf("\nINFO: %s -- FREQ: %d",raiz->string,raiz->freqArv);
		}
	
		printarArvore(raiz->esq);
		printarArvore(raiz->dir);
	}
}

void printarArvoreFormatada(Tree *raiz, int nivel) { //funcao pra printar a arvore em formato de arvore
    if (raiz == NULL) {
        return;
    }

    // Primeiro, imprime o nó da direita (subárvore direita)
    printarArvoreFormatada(raiz->dir, nivel + 1);

    // Imprime o nó atual com o deslocamento correspondente ao nível
    for (int i = 0; i < nivel; i++) {
        printf("\t"); // Tabulação para deslocar o nó
    }
    printf("(%s, %d)\n", raiz->string, raiz->freqArv);

    // Depois, imprime o nó da esquerda (subárvore esquerda)
    printarArvoreFormatada(raiz->esq, nivel + 1);
}


int main(void){
	
	ListaGen *LG;
	Tabela *tabela;
	

	
	tabela = gerarTabela("message.txt");
	LG = gerarLG(tabela);
	
	GerarArvore(&LG);
	GeraCodigos(LG->no, &tabela , "");
	printar(tabela);
	printarArvoreFormatada(LG->no,0);
	GravarTabela(tabela);
	GerarStringCompilada("message.txt",tabela);
	
	
	return 0;
}
