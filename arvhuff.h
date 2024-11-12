#include <string.h>
#include <windows.h>
#define MAXSTRING 64

//	ListaGen
//	|-----------|	  
//	|			| --> aponta para outra ListaGen
//	|-----------|
//		|
//	  |--------|	
//	  |Tree *no|
//	  |--------|

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

void corrigeTab(Tabela **t){
	if((*t)->simbol!=0)
		*t=(*t)->prox;
}

Tabela *gerarTabela(char filename[MAXSTRING]){
	
	FILE *arq = fopen(filename,"r");
	int tamArq = getFileSize(arq);
	char linha[tamArq];
	Tabela *tabela=(Tabela*)malloc(sizeof(Tabela));
	tabela->prox = NULL;
	
	
	
	if(fgets(linha,tamArq,arq)){
		int i=0, contStr=0;
		char string[MAXSTRING];
		while(linha[i]!='\0'){
			if (linha[i] == ' ') {
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
		corrigeTab(&tabela);
	}
	else
		printf("Nao foi possivel compressar a string: \n[READ ERROR:gerarTabela()]");
	
	return tabela;
}

ListaGen* CriaCaixaLG(Tabela *t){
	ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
	Tree *no = (Tree*)malloc(sizeof(Tree));
	
	no->freqArv = t->freq;
	strcpy(no->string,t->string);
	no->esq=NULL;
	no->dir=NULL;
	
	L->prox=NULL;
	L->no=no;
	
	return L;
}

Tabela* inserirOrdenado(Tabela* ordenada, Tabela* novo) {
    if (ordenada == NULL || novo->freq < ordenada->freq) {
        novo->prox = ordenada;
        return novo;
    }
    
    Tabela* atual = ordenada;
    while (atual->prox != NULL && atual->prox->freq <= novo->freq) {
        atual = atual->prox;
    }
    
    novo->prox = atual->prox;
    atual->prox = novo;
    return ordenada;
}

Tabela* gerarTabelaOrdenada(Tabela* tabela) {
    Tabela* ordenada = NULL;
    Tabela* atual = tabela;
    
    while (atual != NULL) {
        Tabela* novo = (Tabela*)malloc(sizeof(Tabela));
        if (novo == NULL) {
            printf("Erro de memória.\n");
            return NULL;
        }
        
        *novo = *atual;  // Copia os dados de 'atual' para 'novo'
        novo->prox = NULL;
        
        // Insere o novo elemento na tabela ordenada
        ordenada = inserirOrdenado(ordenada, novo);
        
        // Avança para o próximo elemento na tabela original
        atual = atual->prox;
    }
    
    return ordenada;
}

ListaGen* gerarLG(Tabela *T){
	/* 
	1 - Construir a listaGen, lembre-se que ela tem que estar ordenada do menor ao maior
		1.1 - Precisamos pegar da tabela, os simbolos com menor frequencia e inserir primeiro na ListaGen, ou seja, podemos realizar uma ordenacao na tabela primeiro, e assim ir inserindo na ListaGen.
			1.1.1 - Para nao desestruturar a t, e manter os simbols em sequencia comecando do 0, podemos criar uma tabela auxilixar e assim ordena-la; 
	*/
	Tabela *tOrd = gerarTabelaOrdenada(T);
	Tabela *aux = tOrd;
	
	ListaGen *L, *auxL;

	if(aux!=NULL){
		L = CriaCaixaLG(aux);
		auxL=L;
		aux=aux->prox;
		while(aux!=NULL){
			auxL->prox = CriaCaixaLG(aux);
			auxL=auxL->prox;
			aux=aux->prox;
		}	
	}
	auxL=L;	
	return L;
}

void inserirOrdenadoListaGen(ListaGen **L, ListaGen *info) {
    if (*L == NULL || (*L)->no->freqArv > info->no->freqArv) {
        info->prox = *L;
        *L = info;
        return;
    }
    
    ListaGen *aux = *L;
    while (aux->prox != NULL && aux->prox->no->freqArv <= info->no->freqArv) {
        aux = aux->prox;
    }

    info->prox = aux->prox;
    aux->prox = info;
}



void GerarArvore(ListaGen **L) {
    while (*L != NULL && (*L)->prox != NULL) {
        ListaGen *aux = (*L)->prox->prox; // salvando o proximo->proximo
        ListaGen *novo = (ListaGen *)malloc(sizeof(ListaGen)); // nova caixinha
        Tree *novoNo = (Tree *)malloc(sizeof(Tree)); // no que vai ser apontado pela nova caixinha

        if (novo != NULL || novoNo != NULL) {
	        novoNo->freqArv = (*L)->no->freqArv + (*L)->prox->no->freqArv;
	        strcpy(novoNo->string, "%null");
	        novoNo->dir = (*L)->prox->no;
	        novoNo->esq = (*L)->no;
	    
	        novo->no = novoNo;
	        novo->prox = NULL;
	        
	        inserirOrdenadoListaGen(&aux, novo);
	
	        free((*L)->prox);
	        free(*L);
	
	        *L = aux;
        }
		else
        	printf("novo==null\n");
    }
}










