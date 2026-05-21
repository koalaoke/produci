#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


struct Linha* criar_linha(char nome[STR_LEN]){
    struct Linha *linha = malloc(sizeof(struct Linha));
    linha->etapa = NULL;
    return linha;
}

void criar_etapa(struct Linha *linha, char nome_etapa[STR_LEN]){
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

void criar_atividade(struct Linha *linha, char nome_atividade[STR_LEN]){
    struct Atividade *nova_atv = malloc(sizeof(struct Atividade));
    strcpy(nova_atv->nome, nome_atividade);
    nova_atv->prox = NULL;

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
