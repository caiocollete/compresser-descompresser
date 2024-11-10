#include <string.h>
#define MAXSTRING 64

//	ListaGen
//	|-----------|	  
//	|			| --> aponta para outra ListaGen
//	|-----------|
//		|
//	  |--------|	
//	  |Tree *no|
//	  |--------|

int tamArq;

struct infos{
	int simbol;
	char string[MAXSTRING];
	int freq;
	char cod_huff[8];
	struct infos *prox;
}; typedef struct infos Tabela;

struct arvHuff{
	struct arvHuff *esq, *dir;
	int freqArv;
	char string[MAXSTRING];
}; typedef struct arvHuff Tree;

struct lgen{
	struct lgen *prox;
	Tree *no;
}; typedef struct lgen ListaGen;

long getFileSize(FILE *file) {
  long size;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

void adicionarFreqTabela(Tabela **tabela,char string[]){
	//search string in tabela;
	Tabela *aux = *tabela;
	int simbol = -1;
	while(aux->prox!=NULL && strcmp(aux->prox->string,string)!=0){
		aux=aux->prox;
		simbol=aux->simbol;
	}
	if(aux->prox!=NULL){
		aux->prox->freq++;
	}
	else{
		Tabela *novo = (Tabela*)malloc(sizeof(Tabela));
		
		novo->simbol=simbol+1;
		strcpy(novo->string,string);
		novo->freq=1;
		novo->prox=NULL;
		
		aux->prox = novo;
	}	
}

Tabela *gerarTabela(char filename[MAXSTRING]){
	
	FILE *arq = fopen(filename,"r");
	char linha[tamArq];
	Tabela *tabela=(Tabela*)malloc(sizeof(Tabela));
	
	tamArq = getFileSize(arq);
	
	if(fgets(linha,tamArq,arq)){
		int i=0, contStr=0;
		char string[MAXSTRING];
		while(linha[i]!='\0'){
			if (linha[i] == ' ') { // erro nessa linha, algum ponteiro esta NULL, nao consegui encontrar
			    string[contStr] = '\0';
			    adicionarFreqTabela(&tabela, string);
			    contStr = 0;
			}
			else{
				string[contStr] = linha[i];
				contStr++;
			}
			i++;
		}
	}
	else
		printf("Nao foi possivel compressar a string: \n[READ ERROR:gerarTabela()]");
	
	return tabela;
}

ListaGen* LG(Tabela tabela){
	ListaGen *L;
	
	L=(ListaGen*)malloc(sizeof(ListaGen));
	L->prox=NULL;
	L->no=NULL;
	
	return L;
	
	//construir a listaGen, lembre-se que ela tem que estar ordenada do menor ao maior
	
}










