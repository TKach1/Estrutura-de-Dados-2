#include "avl.h"

int main () {

   Arvore *AVL = NULL;

   AVL = Inserir (AVL, 14);
   AVL = Inserir (AVL, 5);
   AVL = Inserir (AVL, 28);
   AVL = Inserir (AVL, 2);
   AVL = Inserir (AVL, 8);
   AVL = Inserir (AVL, 18);
   AVL = Inserir (AVL, 33);
   AVL = Inserir (AVL, 1);
   AVL = Inserir (AVL, 3);
   AVL = Inserir (AVL, 6);
   AVL = Inserir (AVL, 11);
   AVL = Inserir (AVL, 15);
   AVL = Inserir (AVL, 20);
   AVL = Inserir (AVL, 30);
   AVL = Inserir (AVL, 38);
   AVL = Inserir (AVL, 4);
   AVL = Inserir (AVL, 7);
   AVL = Inserir (AVL, 10);
   AVL = Inserir (AVL, 12);
   AVL = Inserir (AVL, 16);
   AVL = Inserir (AVL, 19);
   AVL = Inserir (AVL, 21);
   AVL = Inserir (AVL, 29);
   AVL = Inserir (AVL, 31);
   AVL = Inserir (AVL, 35);
   AVL = Inserir (AVL, 39);
   AVL = Inserir (AVL, 13);
   AVL = Inserir (AVL, 22);
   AVL = Inserir (AVL, 32);
   AVL = Inserir (AVL, 34);
   AVL = Inserir (AVL, 36);
   AVL = Inserir (AVL, 40);
   AVL = Inserir (AVL, 37);

   AVL = remover (AVL, 1);

   //AVL = remover (AVL, 'A');
   //AVL = remover (AVL, 'H');
   //AVL = remover (AVL, 'E');
   //AVL = remover (AVL, 'W');
   //AVL = remover (AVL, 'G');
   //AVL = remover (AVL, 'N');
   //AVL = remover (AVL, 'P');
   //AVL = remover (AVL, 'O');

   imprimir_in_order (AVL, 0);

   return 0;
}

/*Função que devolve o maior entre dois números inteiros!*/
int maior (int esq, int dir) {
   return (esq > dir ? esq : dir);
}

/*----------------------*/
int Altura (Arvore* a) {
   return (a == NULL ? -1 : a->altura);	
}

int Atualizar (Arvore *a) {
   return (maior(Altura(a->esq), Altura(a->dir)) + 1);	
}

/*----------------------*/
int Balanceamento (Arvore *a) {
   return (Altura(a->dir) - Altura(a->esq));
}

/*----------------------*/
Arvore* Rotacao_simples_esq (Arvore* a) {
   No *t = a->dir;
   a->dir = t->esq;
   t->esq = a;
   a->altura = Atualizar(a);
   t->altura = Atualizar(t);
   return t;
}

/*----------------------*/
Arvore* Rotacao_simples_dir (Arvore* a) {
   No *t = a->esq;
   a->esq = t->dir;
   t->dir = a;
   a->altura = Atualizar(a);
   t->altura = Atualizar(t);
   return t;

}

/*----------------------*/
Arvore* Rotacao_dupla_esq (Arvore* a) {
   a->dir = Rotacao_simples_dir (a->dir);
   return Rotacao_simples_esq (a);
}

/*----------------------*/
Arvore* Rotacao_dupla_dir (Arvore* a) {
   a->esq = Rotacao_simples_esq (a->esq);
   return Rotacao_simples_dir (a);
}

/*----------------------*/
Arvore* Atualizar_fb_dir (Arvore *a) {
   a->altura = Atualizar(a);
   if (Balanceamento(a) == +2) {
      if (Balanceamento(a->dir) >= 0) {
         a = Rotacao_simples_esq (a);
      }
      else {
         a = Rotacao_dupla_esq (a);
      }
   }
   return a;
}

/*----------------------*/
Arvore* Atualizar_fb_esq (Arvore *a) {
   a->altura = Atualizar(a);
   if (Balanceamento(a) == -2) {
      if (Balanceamento(a->esq) <= 0) {
         a = Rotacao_simples_dir (a);
      }
      else {
         a = Rotacao_dupla_dir (a);
      }
   }
   return a;

}

/*----------------------*/
Arvore* Inserir (Arvore *a, int chave) {
   if (a == NULL){
      a = (No*)malloc(sizeof(No));
      a->chave = chave;
      a->altura = 0;
      a->esq = a->dir = NULL;
   }
   else if (chave < a->chave){
      a->esq = Inserir (a->esq, chave);
      a = Atualizar_fb_esq (a);
   }else{
      a->dir = Inserir (a->dir, chave);
      a = Atualizar_fb_dir (a);
   }
   return a;
}

/*Função para remover um nó de uma árvore binária de busca balanceada!*/
Arvore* remover (Arvore *a, int chave) {
   if (a == NULL) {
      return NULL;
   }
   else {
      if (chave < a->chave) {
         a->esq = remover (a->esq, chave);
         a = Atualizar_fb_dir (a);
      }
      else if (chave > a->chave) {
         a->dir = remover (a->dir, chave);
         a = Atualizar_fb_esq (a);
      }
      else {
         if ((a->esq == NULL) && (a->dir == NULL)) {
            free (a);
            a = NULL;
         }
         else if (a->esq == NULL) {
            No *tmp = a;
            a = a->dir;
            free (tmp);
         }
         else if (a->dir == NULL) {
            No *tmp = a;
            a = a->esq;
            free (tmp);
         }
         else {
            No *tmp = a->esq;
            while (tmp->dir != NULL) {
               tmp = tmp->dir;
            }
            a->chave = tmp->chave; 
            tmp->chave = chave;
            a->esq = remover (a->esq, chave); 
            a = Atualizar_fb_dir (a);
         }
      }
      return a; 
   }   
}

/*Função para imprimir os nós de uma árvore binária de acordo com um percurso in-ordem!*/
void imprimir_in_order (Arvore* a, int nivel) {
   if (a != NULL) {
      int i;
      for (i = 0; i < nivel; i++) {
         printf("      ");
      }
      printf("Chave: %d (altura: %d, fb: %+d) no nivel: %d\n", a->chave, a->altura, Balanceamento(a), nivel);
      imprimir_in_order (a->esq, nivel + 1);
      imprimir_in_order (a->dir, nivel + 1);
   }
}
