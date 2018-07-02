#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmais.h"

TAB* leLinhas(TAB *arv, char *nome){
  FILE *arq;
  arq = fopen(nome, "r");
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
        //printf("%s\n", chave);
        strcat(chave, token);
        //printf("%s\n", chave);
        //printf("%s\n", chave);
        infos->ano = atoi(token);
        //printf("%d\n", ano);
        token = strtok(NULL, "/");
        infos->nMusicas = atoi(token);
        //printf("%d\n", infos->nMusicas);
        token = strtok(NULL, "/");
        infos->minutos = atoi(token);
        token = strtok(NULL, "/");
        strcpy(infos->nmAlbum, token);
        arv = Insere(arv, chave, infos, t);
      }
      return arv;
  }
