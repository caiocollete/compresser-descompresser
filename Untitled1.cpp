#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "arvhuff.h"

int main(void){
	
	ListaGen *LG;
	Tabela *tabela;
	tabela = gerarTabela("message.txt");
	//LG = gerarLG(tabela);
	
	return 0;
}
