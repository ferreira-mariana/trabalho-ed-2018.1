#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bMais.h"

void leLinhas(TAB *arv){
  FILE *arq;
  arq = fopen("bd", "r");
  int t = 2;
  char linha[256], *token;
  while (fgets(linha, sizeof(linha), arq)){
        Info *infos = (Info *) malloc(sizeof(Info));
        token = strtok(linha, "/");

        //while(token){
        //  printf("%s\n", token);
        //  token = strtok(NULL, "/");
        //}

        strcpy(infos->cantor, token);
        token = strtok(NULL, "/");
        char chave[200];
        strcpy(chave, infos->cantor);
        strcat(chave, token);

        //printf("%s\n", chave);

        infos->ano = atoi(token);
        token = strtok(NULL, "/");
        infos->nMusicas = atoi(token);
        token = strtok(NULL, "/");
        infos->minutos = atoi(token);
        token = strtok(NULL, "/");
        strcpy(infos->nmAlbum, token);

        Insere(arv, chave, infos, t);
      }
  }


int main(){
  char k[100] = "bd.txt";
  leLinhas(k);
}
