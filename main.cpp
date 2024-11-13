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
	char linha[tamArq];
	
	if(fgets(linha,tamArq,arq)){
		int i=0, contStr=0;
		char string[MAXSTRING];
		while(linha[i]!='\0'){
			if (linha[i] == ' ') {
			    string[contStr] = '\0';
			    strcat(stringCompilada,procurarStringTabela(string,t));
			    strcat(stringCompilada,procurarStringTabela(" ",t));
			    contStr = 0;
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
	FILE *F = fopen("tabela.tabela","w");
	
	while(T!=NULL){
		//printaTab no Arquivo
		fseek(F,0,SEEK_END);
		fwrite(&T, sizeof(Tabela),1,F);
		T=T->prox;
	}
	
	fclose(F);
}

int main(void){
	
	ListaGen *LG;
	Tabela *tabela;
	

	
	tabela = gerarTabela("message.txt");
	LG = gerarLG(tabela);
	
	GerarArvore(&LG);
	GeraCodigos(LG->no, &tabela , "");
	//printar(tabela);
	GerarStringCompilada("message.txt",tabela);
	GravarTabela(tabela);
	
	return 0;
}
