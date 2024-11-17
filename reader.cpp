#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 64
#define MAXSTR 1000
#define CODHUFF 24

struct infos{
	int simbolo;
	char string[MAX];
	int freq;
	char codHuff[CODHUFF];
	struct infos *prox;
}; typedef struct infos Tabela;

long getFileSize(FILE *file) {
  long size;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

void exibirTabela(char nomeArq[]){
	
	FILE *tab = fopen(nomeArq,"rb");
	Tabela tabela;
	
	while(fread(&tabela,sizeof(Tabela),1,tab)==1){
		
		printf("SIMBOL: %d\tSTR: %s\tfreq: %d\tcodHuff: %s\n",tabela.simbolo,tabela.string,tabela.freq,tabela.codHuff);

	}
}

char* procurarNaTabela(char str[], FILE *tab){
	rewind(tab);
	Tabela tabela;
	
	while(fread(&tabela,sizeof(Tabela),1,tab)==1){
		
		if(strcmp(str,tabela.codHuff)==0){
			return tabela.string;
		}

	}
	
	return "";
}

void initStrings(char aux[], char palavraDecod[], char nomeArqTabela[]){
	
	strcpy(aux,"");
	strcpy(palavraDecod,"");
	strcpy(nomeArqTabela,"");
}

void decodificar(char nomeArqCodigo[], char nomeArqTabela[]){
	
	FILE *tab = fopen(nomeArqTabela,"rb");
	FILE *cod = fopen(nomeArqCodigo,"r");
	
	if (tab == NULL || cod == NULL) {
    printf("Erro ao abrir arquivos!\n");
    return;
	}

	int tamArq = getFileSize(cod);
	char linha[tamArq],strDecod[MAXSTR];
	int i=0;
	Tabela tabela;
	
	if(fgets(linha,tamArq,cod)){
		char aux[MAXSTR],palavraDecod[MAXSTR],fraseDecod[MAXSTR];
		initStrings(aux,palavraDecod,fraseDecod);
		int cont = 0;
		int achou = 0;
		while(linha[i]!='\0'){
					
			aux[cont] = linha[i];
			aux[cont+1] = '\0';
			strcpy(palavraDecod,procurarNaTabela(aux,tab));
			
			
			if(strcmp(palavraDecod,"")!=0){
				strcat(fraseDecod,palavraDecod);
				cont = -1;
			}
			cont++;
			i++;
		}
		
		printf("\n%s",fraseDecod);
	}
	
	fclose(tab);
	fclose(cod);
}

int main(){
	//FILE *cod = fopen("strCompilada.txt","r");
	//printf("\nSize: %d",getFileSize(cod));
	//fclose(cod);
	
	exibirTabela("tabela.tabela");
	decodificar("strCompilada.txt","tabela.tabela");
}
