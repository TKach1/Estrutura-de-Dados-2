#include "abbLista.h"


Arvore* cria_arvore_vazia (void) {
    return NULL;
}

void arvore_libera (Arvore* a) {
if (a != NULL) {
    arvore_libera (a->esq);
    arvore_libera (a->dir);
    free(a);
}
}

//========= Q1 - inserir
Arvore* inserir (Arvore *a, int v) { // from slides
   if (a == NULL) {
       a = (Arvore *) malloc(sizeof(Arvore));
       a->info = v;
       a->esq = a->dir = NULL;
   }
   else if (v < a->info) 
       a->esq = inserir(a->esq, v);

   else
        a->dir = inserir(a->dir, v);

   return a;
}

//========= Q1 - remover
Arvore* remover (Arvore *a, int v) { // from slides
    if (a == NULL)
        return a;

    else if (a->info > v)
        a->esq = remover(a->esq, v);

    else if (a->info < v)
        a->dir = remover(a->dir, v);

    else if (a->esq == NULL && a->dir == NULL) {
        free(a);
        a = NULL;
    }
    else if (a->esq == NULL) {
        Arvore *tmp = a;
        a = a->dir;
        free(tmp);
    }   
    else if (a->dir == NULL) {
        Arvore *tmp = a;
        a = a->esq;
        free(tmp);
    }
    else {
        Arvore *tmp = a->esq;
        while (tmp->dir != NULL)
            tmp = tmp->dir;
        a->info = tmp->info;
        tmp->info = v;
        a->esq = remover(a->esq, v);
    }

   return a;
}


//========= Q1 - busca
int buscar (Arvore *a, int v) { 
    if (a == NULL)
        return 0;

    else if (v < a->info)
        return buscar(a->esq, v);

    else if (v > a->info)
        return buscar(a->dir, v);
  
    return 1;
}

//========= Q2 - min =====

int min (Arvore *a){
    if(a->esq == NULL) return a->info;
    min(a->esq);
}


//========= Q2 - max =====

int max (Arvore *a){
    if(a->dir == NULL) return a->info;
    min(a->dir);
}

//========= Q3 - imprime_decrescente =====

void imprime_decrescente (Arvore *a){
    if(a != NULL){
        imprime_decrescente(a->dir);
        printf("%d ", a->info);
        imprime_decrescente(a->esq);
    }
}

//========= Q4 - maior ramo =====
int maior_ramo (Arvore *a){
    if (a != NULL) {
        return maior_ramo (a->esq) >= maior_ramo (a->dir) ? maior_ramo (a->esq) + a->info : maior_ramo(a->dir) + a->info;
    }
    return 0;
}

//========= Q5 - random =====

Arvore* order(Arvore* a) {
    a = inserir(a, 50000);
    for(int i = 0; i<100000;i++){
        a = inserir(a, i);
    }
    return a;
}

Arvore* random(Arvore* a) {
    for(int i = 0; i<100000;i++){
        a = inserir(a, rand()%100000);
    }
}

void pre_order (Arvore* a) {
    if (a != NULL) {
        printf("%d ", a->info);
        pre_order (a->esq);
        pre_order (a->dir);
    } 
}

int main () {

    srand((unsigned)time(NULL));
    printf("intervalo da rand: [0,%d]\n", RAND_MAX);

    int i;

    Arvore *a = cria_arvore_vazia ();

    a = inserir (a, 50);
    a = inserir (a, 30);
    a = inserir (a, 90);
    a = inserir (a, 20);
    a = inserir (a, 40);
    a = inserir (a, 95);
    a = inserir (a, 10);
    a = inserir (a, 35);
    a = inserir (a, 45);

    printf("\n");
    pre_order (a);	
    printf("\n");
    printf("%d \n", min(a));
    printf("%d \n", max(a));
    imprime_decrescente(a);
    printf("\n");
    printf("%d \n", maior_ramo(a));

    Arvore *r = cria_arvore_vazia ();
    Arvore *o = cria_arvore_vazia ();

    r = random(r);
    printf("RANDOM READY \n"); //mais rapido
    o = order(o);
    printf("ORDER READY \n"); //demora mais
    
    printf("%d \n", buscar(r, 100000));
    printf("%d \n", buscar(o, 100000));

return 0;
}

