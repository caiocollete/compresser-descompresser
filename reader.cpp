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

struct bits{
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
};

union bytes{
	struct bits bi;
	unsigned char num;
};


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

void *BitToString(char *stringCompilada, char *string){
	union bytes bytes;
	int i=0, TL=0;
	while(TL<strlen(stringCompilada)){
		
		bytes.num=stringCompilada[TL];
		
		if(bytes.bi.b0==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;

		if(bytes.bi.b1==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;
		
		if(bytes.bi.b2==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;

		if(bytes.bi.b3==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;
		
		if(bytes.bi.b4==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;
		
		if(bytes.bi.b5==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;
		
		if(bytes.bi.b6==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;
		
		if(bytes.bi.b7==0){
			string[i]='0';
		}
		else string[i]='1';
		i++;
		TL++;
	}
	string[i]='\0';
	return string;
}


void decodificar(const char nomeArqCodigo[], const char nomeArqTabela[]) {
    FILE *tab = fopen(nomeArqTabela, "rb");
    FILE *cod = fopen(nomeArqCodigo, "r");

    int tamArq = getFileSize(cod) + 10;
    char linha[tamArq];
    char string[MAXSTR], aux[MAXSTR], palavraDecod[MAXSTR], fraseDecod[MAXSTR];

    initStrings(aux, palavraDecod, fraseDecod);

    if (fgets(linha, tamArq, cod)) {
        BitToString(linha, string);

        int i = 0, cont = 0;
        while (string[i] != '\0') {
            aux[cont] = string[i];
            aux[cont + 1] = '\0';

            strcpy(palavraDecod, procurarNaTabela(aux, tab));
            if (strcmp(palavraDecod, "") != 0) {
                strcat(fraseDecod, palavraDecod);
                cont = -1;  // Reinicia o contador para a próxima palavra.
            }
            cont++;
            i++;
        }

        printf("\nFrase decodificada: %s\n", fraseDecod);
    } else {
        printf("Arquivo de código está vazio ou inválido!\n");
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
