#include <stdio.h>
#include <stdlib.h>
#include "bMais.h"

TAB *Cria(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(char**)malloc(sizeof(char**)*((t*2)-1)); //É assim? Não sei se ta certo (Thiago aqui)
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*t*2);
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  novo->prox = NULL;
  Info *infos = (Info *) malloc(sizeof(Info));
  novo->adic = infos;
  return novo;
}


TAB *Libera(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->adic);
    free(a->filho);
    free(a);
    return NULL;
  }
}


void Imprime(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d\n", a->chave[i]);
    }
    Imprime(a->filho[i],andar+1);
  }
}


TAB *Busca(TAB* x, int ch){
  if(!x) return x;
  int i = 0;
  while(i < x->nchaves && x->chave[i] < ch) i++;
  if((i < x->nchaves) && (ch == x->chave[i])){
    if(x->folha) return x;
    return Busca(x->filho[i+1], ch);
  }
  return Busca(x->filho[i], ch);
}


TAB *Inicializa(){
  return NULL;
}


TAB *Divisao(TAB *x, int i, TAB* y, int t){
  TAB *z=Cria(t);
  if(y->folha){
    TAB *proxOrig = y->prox; //auxiliar que guarda valor do proximo do no dividido
    z->nchaves= t;
    z->folha = 1;
    int j;
    for(j=0;j<t;j++) z->chave[j] = y->chave[j+t-1];
    y->nchaves = t - 1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j]; //só entra nesse for quando tem pai
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1]; //só entra nesse for quando tem pai
    x->chave[i-1] = y->chave[t-1];
    x->nchaves++;
    // printf("####################\n");
    // Imprime(x, 0);
    // printf("####################\n");
    if((y->folha)&&(z->folha)) y->prox = z;
    if(proxOrig) z->prox = proxOrig;
    return x;
  }
  z->nchaves= t-1;
  z->folha = 0;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t - 1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  // printf("####################\n");
  // Imprime(x, 0);
  // printf("####################\n");
  return x;
}

void testeFolhas(TAB *t){
  TAB *p = t;
  while(!p->folha) p = p->filho[0];
  while(p!=NULL){
    if(p->folha) printf("eh folha\n");
    int i;
    for(i=0;i<p->nchaves;i++) printf("%d\n", p->chave[i]);
    p = p->prox;
  }
}

TAB *Insere_Nao_Completo(TAB *arv, char **chave, Info *adic, int t){
  int i = arv->nchaves-1;
  if(arv->folha){

    /*
    0: conteúdo das strings são iguais

    < 0: conteúdo da string1 é menor do que string2

    > 0: conteúdo da string1 é maior do que string2
    */
    while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)){ //se chave for menor que o conteudo de no atual
      arv->chave[i+1] = arv->chave[i];
      i--;
    }
    arv->chave[i+1] = chave;
    arv->nchaves++;
    return arv;
  }//VAI SER O CASO MAIS IMPORTANTE - SÓ INSERE EM FOLHA (B+)
  while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) i--; //se chave for menor que o conteudo de no atual
  i++;
  if(arv->filho[i]->nchaves == ((2*t)-1)){
    arv = Divisao(arv, (i+1), arv->filho[i], t); //o que é i+1??? na outra era 1 só
    if(strcmp(chave, arv->chave[i]) > 0) i++; //se chave for maior que o conteudo de no atual
  }
  arv->filho[i] = Insere_Nao_Completo(arv->filho[i], chave, adic, t);
  return arv;
}


TAB *Insere(TAB *T, char **chave, Info *adic, int t){
  if(Busca(T,chave)) return T; //modificar a funcao busca p/ char
  if(!T){
    T=Cria(t);
    T->chave[0] = chave;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t); //acho que o 1 devia ser a metade de (2*t)-1 ???
    S = Insere_Nao_Completo(S,chave, adic, t);
    return S;
  }
  T = Insere_Nao_Completo(T,chave, adic, t);
  return T;
}


TAB* remover(TAB* arv, int ch, int t){
  if(!arv){
    printf("nao tem nada\n");
    return arv;
  }
  Imprime(arv, 0);
  int i, trocou = 0;
  printf("Removendo %d...\n", ch);
  for(i = 0; i<arv->nchaves && arv->chave[i] < ch; i++);
  if(arv->chave[i]==ch && !arv->folha){
    i++;
    trocou = 1;
  }
  if(i < arv->nchaves && ch == arv->chave[i]){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;
    }
    //if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
    //  printf("\nCASO 2A\n");
    //  TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
    //  while(!y->folha) y = y->filho[y->nchaves];
    //  int temp = y->chave[y->nchaves-1];
    //  arv->filho[i] = remover(arv->filho[i], temp, t);
    //  //Eliminar recursivamente K e substitua K por K' em x
  //  //  arv->chave[i] = temp;
    //  return arv;
    //}
    //if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
    //  printf("\nCASO 2B\n");
    //  TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
  //    while(!y->folha) y = y->filho[0];
    //  int temp = y->chave[0];
    //  y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
    //  arv->chave[i] = temp;
    //  return arv;
    //}//
    //if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
    //  printf("\nCASO 2C\n");
    //  TAB *y = arv->filho[i];
    //  TAB *z = arv->filho[i+1];
    //  y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
    //  int j;
  //  //  for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
    //    y->chave[t+j] = z->chave[j];
    //  for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
    //    y->filho[t+j] = z->filho[j];
    //  y->nchaves = 2*t-1;
    //  for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
    //    arv->chave[j] = arv->chave[j+1];
  //    for(j=i+1; j <= arv->nchaves; j++)  //remover ponteiro para filho[i+1]
    //    arv->filho[j] = arv->filho[j+1];
    //  arv->filho[j] = NULL; //Campello
    //  arv->nchaves--;
    //  arv->filho[i] = remover(arv->filho[i], ch, t);
    //  return arv;
    //}Não haverá remoção em nós intermediários
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if(y->folha){
      if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
        printf("\nCASO 3A: i menor que nchaves\n");
        z = arv->filho[i+1];
        //y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
        int j;
        //for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
          //z->chave[j] = z->chave[j+1];
        //z->chave[j] = 0; Rosseti
        y->chave[y->nchaves] = z->chave[0];
        y->nchaves++;
        for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
          z->chave[j] = z->chave[j+1];
        z->nchaves--;
        arv->chave[i] = z->chave[0];//dar a arv uma chave de z
        arv->filho[i] = remover(arv->filho[i], ch, t);
        return arv;
      }
      if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
        printf("\nCASO 3A: i igual a nchaves\n");
        z = arv->filho[i-1];
        int j;
        for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
          y->chave[j] = y->chave[j-1];
        //for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
          //y->filho[j] = y->filho[j-1];
        //y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
        y->nchaves++;
        arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
        y->chave[0] = z->chave[z->nchaves-1];         //enviar ponteiro de z para o novo elemento em y
        z->nchaves--;
        arv->filho[i] = remover(y, ch, t);
        return arv;
      }
    }

    if(!z){ //CASO 3B - QUEBRADO-TEM QUE CONSERTAR(Funcionando só para o caso i=0)
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        int j;
        if(!y->folha){
          y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
          y->nchaves++;
          for(j=0; j < t-1; j++){
            y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
            y->nchaves++;
          }

          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }

        }else{
          for(j=0; j < t-1; j++){
            y->chave[t-1+j] = z->chave[j];     //passar filho[i+1] para filho[i]
            y->nchaves++;
          }
          arv->filho[i+1] = y; //aposto que é isso quebrando, mas estou sem forças KKKKKKKK
          //vou dormir
          //bj
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, int k, int t){
  if(!arv || !Busca(arv, k)) return arv;
  return remover(arv, k, t);
}
