#include <stdio.h>
#include <stdlib.h>

//const int t = 2;
typedef struct info{
  char cantor[100];
  int ano;
  int nMusicas;
  int minutos;
  char nmAlbum[100];
}Info;

typedef struct ArvB{
  int nchaves, folha;
  char **chave;
  struct Info *adic;
  struct ArvB **filho, *prox;
}TAB;

/* como era com inteiro antes
typedef struct ArvB{ com inteiro
  int nchaves, folha;
  int *chave;
  struct ArvB **filho, *prox;
}TAB;
*/

TAB *Cria(int t);
TAB *Libera(TAB *a);
void Imprime(TAB *a, int andar);
TAB *Busca(TAB* x, int ch);
TAB *Inicializa();
TAB *Divisao(TAB *x, int i, TAB* y, int t);
TAB *Insere_Nao_Completo(TAB *arv, char **chave, Info *adic, int t);
TAB *Insere(TAB *T, char **chave, Info *adic, int t);
TAB* remover(TAB* arv, int ch, int t);
TAB* retira(TAB* arv, int k, int t);
void testeFolhas(TAB *t);
