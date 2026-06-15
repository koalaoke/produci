#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_lote(struct Produto *lote) {
    if (lote == NULL) {
        printf("\n");
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

struct Etapa* criar_etapa(char *nome_etapa, int capacidade){
    struct Etapa *nova_etapa = malloc(sizeof(struct Etapa));
    strcpy(nova_etapa->nome, nome_etapa);
    nova_etapa->atividade = NULL;
    nova_etapa->prox = NULL;
    nova_etapa->fila_espera = NULL;
    nova_etapa->capacidade = capacidade;
    nova_etapa->qtd_produtos = 0;

    return nova_etapa;
}

struct Atividade *criar_atividade(char* nome_atividade, int ciclos, int capacidade, int taxa_erro){
    struct Atividade *nova_atv = malloc(sizeof(struct Atividade));
    strcpy(nova_atv->nome, nome_atividade);
    nova_atv->ciclos = ciclos;
    nova_atv->capacidade = capacidade;
    nova_atv->taxa_erro = taxa_erro;
    nova_atv->prox = NULL;
    nova_atv->fila = NULL;

    return nova_atv;
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


void anexar_etapa(struct Linha *linha, struct Etapa *etapa) {
    struct Etapa **walk = &(linha)->etapa;
    struct Etapa *ante = NULL;
    while(*walk){
        ante = *walk;
        walk = &(ante)->prox;
    }

    etapa->ante = ante;
    *walk = etapa;
}

void anexar_atividade(struct Linha *linha, struct Atividade *atividade) {
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

    *walk = atividade;
}

void contar_ciclo(struct Produto **lote, int capacidade){
    struct Produto *aux = *lote;
    while (aux && capacidade-- > 0) {
        aux->ciclos++;
        aux = aux->prox;
    }
}

int contar_produtos(struct Produto *lote){
    int count = 0;
    while (lote) {
        lote = lote->prox;
        count++;
    }

    return count;
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
    while (*lote != NULL && (*lote)->ciclos > ciclos) {
        struct Produto *aux = remover_produto(lote);
        aux->ciclos = 0;
        inserir_produtos(&prontos, aux);
    }

    return prontos;
}

struct Produto* remover_erros(struct Produto **lote, int taxa_erros){
    struct Produto *erros = NULL;
    struct Produto **walk = lote;

    while (*walk) {
        struct Produto *aux = *walk;
        if(rand() % 100 < taxa_erros){
            *walk = aux->prox;
            aux->ciclos = 0;
            aux->prox = NULL;
            inserir_produtos(&erros, aux);
        } else {
            walk = &(*walk)->prox;
        }
    }
    return erros;
}
