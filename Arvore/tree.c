#include "tree.h"


Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* constroi_arv (char c, Arvore *e, Arvore *d) {
   Arvore *no = (Arvore*)malloc(sizeof(Arvore));
   no->info = c;
   no->esq = e;
   no->dir = d;
   return no;
}

int verifica_arv_vazia (Arvore *a) {
   return (a == NULL);
}

void arv_libera (Arvore* a) {
   if (!verifica_arv_vazia(a)) {
      arv_libera (a->esq);
      arv_libera (a->dir);
      free(a);
   }
}

//========= Exercício 2 - pré-ordem ====

void read_arv(Arvore* a){
    if (!verifica_arv_vazia(a)) {
        printf("%c ", a->info);
        read_arv(a->esq);
        read_arv(a->dir);
   }
}

//========= Exercício 2 - in-ordem ====

void read_arv_in(Arvore* a){
    if (!verifica_arv_vazia(a)) {
        read_arv_in(a->esq);
        printf("%c ", a->info);
        read_arv_in(a->dir);
   }
}

//========= Exercício 2 - pós-ordem ====

void read_arv_pos(Arvore* a){
    if (!verifica_arv_vazia(a)) {
        read_arv_pos(a->esq);
        read_arv_pos(a->dir);
        printf("%c ", a->info);
   }
}

//========= Exercício 3 - pertence ====

int pertence_arv (Arvore *a, char c){
    if (!verifica_arv_vazia(a)) {
        if( a->info == c ||
            pertence_arv(a->esq, c) == 1 ||
            pertence_arv(a->dir, c) == 1
        )return 1;
   }
   return 0;
}

//========= Exercício 4 - conta nós ====

int conta_nos (Arvore *a){
    if (!verifica_arv_vazia(a)) {
        return 1 + conta_nos(a->esq) + conta_nos(a->dir);
    }
    return 0;
}


//========= Exercício 5 - calcula altura ====

int calcula_altura_arvore (Arvore *a){
    if (!verifica_arv_vazia(a)) {
        return calcula_altura_arvore (a->esq) >= calcula_altura_arvore (a->dir) ? calcula_altura_arvore (a->esq) + 1 : calcula_altura_arvore(a->dir) + 1;
    }
    return 0;
}

//========= Exercício 6 - conta folhas ====

int conta_nos_folha (Arvore *a){
    if (!verifica_arv_vazia(a)) {
        if(!verifica_arv_vazia(a->dir)) {
            return 1 + conta_nos_folha(a->dir);
        }
        if(!verifica_arv_vazia(a->esq)) {
            return 1 + conta_nos_folha(a->esq);
        }
    }
    return 0;
}


int main () {

    Arvore *a = constroi_arv ('a',
        constroi_arv('b',
        cria_arv_vazia(),
        constroi_arv('d', cria_arv_vazia(),cria_arv_vazia())
        ),
        constroi_arv('c',
        constroi_arv('e',cria_arv_vazia(),cria_arv_vazia()),
        constroi_arv('f',cria_arv_vazia(),cria_arv_vazia())
        )
    );	
    
    //printf("\n");

    //printf("%d", pertence_arv(a, 'c'));

    //printf("%d", calcula_altura_arvore(a));

    printf("%d", conta_nos_folha(a));

    arv_libera(a);

    return 0;
}