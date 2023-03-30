#ifndef _AVL_H
#define _AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
   char chave[20];
   int altura;
   struct node* esq;
   struct node* dir;
} No, Arvore;

int maior (int esq, int dir);

int Altura (Arvore* a);

int Atualizar_altura (Arvore *a);

int Balanceamento (Arvore *a);

Arvore* Rotacao_simples_esq (Arvore* a);

Arvore* Rotacao_simples_dir (Arvore* a);

Arvore* Rotacao_dupla_esq (Arvore* a);

Arvore* Rotacao_dupla_dir (Arvore* a);

Arvore* Atualizar_fb_dir (Arvore *a);

Arvore* Atualizar_fb_esq (Arvore *a);

Arvore* Inserir (Arvore *a, char* chave);

Arvore* remover (Arvore *a, char* chave);

void imprimir_in_order (Arvore* a, int nivel);

#endif
