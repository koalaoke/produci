#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_lote(struct Produto *lote) {
    if (lote == NULL) {
        printf("[!] O lote esta vazio (NULL).\n");
        return;
    }
    struct Produto *atual = lote;

    while (atual != NULL) {
        printf("%d ",atual->ciclos);
        atual = atual->prox;
    }
    printf("\n");
}

void imprime_processo(struct Linha *linha){
    struct Etapa *etapa = linha->etapa;

    while (etapa) {
        printf("%s\n",etapa->nome);
        struct Atividade *atividade = etapa->atividade;
        while (atividade) {
            printf("\t%s\n",atividade->nome);
            atividade = atividade->prox;
        }
        etapa = etapa->prox;
    }
}

void destruir_linha(struct Linha *linha){
    struct Etapa *etapa = linha->etapa;

    while (etapa) {
        struct Etapa *prox_etapa = etapa->prox;
        struct Atividade *atividade = etapa->atividade;

        while (atividade) {
            struct Atividade *prox_atv = atividade->prox;
            free(atividade);
            atividade = prox_atv;
        }

        free(etapa);
        etapa = prox_etapa;;
    }

    free(linha);
}


struct Linha* criar_linha(char* nome){
    struct Linha *linha = malloc(sizeof(struct Linha));
    linha->etapa = NULL;
    linha->qtd_produtos = 0;
    return linha;
}

void criar_etapa(struct Linha *linha, char* nome_etapa){
    struct Etapa *nova_etapa = malloc(sizeof(struct Etapa));
    strcpy(nova_etapa->nome, nome_etapa);
    nova_etapa->atividade = NULL;
    nova_etapa->prox = NULL;

    struct Etapa **walk = &(linha)->etapa;
    struct Etapa *ante = NULL;
    while(*walk){
        ante = *walk;
        walk = &(ante)->prox;
    }

    nova_etapa->ante = ante;
    *walk = nova_etapa;
}

void criar_atividade(struct Linha *linha, char* nome_atividade, int ciclos, int capacidade){
    struct Atividade *nova_atv = malloc(sizeof(struct Atividade));
    strcpy(nova_atv->nome, nome_atividade);
    nova_atv->ciclos = ciclos;
    nova_atv->capacidade = capacidade;
    nova_atv->prox = NULL;
    nova_atv->fila = NULL;

    struct Etapa *etapa = (linha)->etapa;
    if (!etapa) {
        return;
    }

    while(etapa->prox){
        etapa = etapa->prox;
    }

    struct Atividade **walk = &etapa->atividade;
    while(*walk){
        walk = &(*walk)->prox;
    }

    *walk = nova_atv;
}

struct Produto* criar_lote(struct Label *label, int qtd){
    struct Produto *lote = malloc(sizeof(struct Produto) * qtd);
    for (int i = 0; i < qtd; i++) {
        lote[i].label = label;
        lote[i].ciclos = 0;
        if (i == qtd - 1)
            lote[i].prox = NULL;
        else
            lote[i].prox = &lote[i+1];
    }
    return lote;
}

void contar_ciclo(struct Produto **lote, int capacidade){
    struct Produto *aux = *lote;
    while (aux && capacidade-- > 0) {
        aux->ciclos++;
        aux = aux->prox;
    }
}

void inserir_produtos(struct Produto **destination, struct Produto *source){
    struct Produto **aux = destination;
    while(*aux){
        aux = &(*aux)->prox;
    }
    *aux = source;
}

struct Produto *remover_produto(struct Produto **lote){
    if (!*lote) return NULL;
    struct Produto *aux = *lote;
    *lote = (*lote)->prox;
    aux->prox = NULL;
    return aux;
}

struct Produto *remover_prontos(struct Produto **lote, int ciclos){
    struct Produto *prontos = NULL;
    while (*lote != NULL && (*lote)->ciclos >= ciclos) {
        struct Produto *aux = remover_produto(lote);
        aux->ciclos = 0;
        inserir_produtos(&prontos, aux);
    }

    return prontos;
}
