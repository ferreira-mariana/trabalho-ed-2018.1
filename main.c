#include "b-mais.h"

int main(int argc, char *argv[]){
  int t = 2;
  TAB * arvore = Inicializa();
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar; 0 para imprimir; -9 para remover; -2 para testeFolhas e -1 para sair\n");
    scanf("%i", &num);
    if(num == -9){
      printf("Que número quer remover? ");
      scanf("%d", &from);
      arvore = retira(arvore, from, t);
      Imprime(arvore,0);
    }
    else if(num == -1){
      printf("\n");
      Imprime(arvore,0);
      Libera(arvore);
      return 0;
    }else if(num == -2){
      testeFolhas(arvore);
      printf("\n");
    }
    else if(!num){
      printf("\n");
      Imprime(arvore,0);
    }
    else arvore = Insere(arvore, num, t);
    printf("\n\n");
  }

}
