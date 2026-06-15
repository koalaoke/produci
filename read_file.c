#include "read_file.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 256

typedef struct Atividade Atividade;
typedef struct Etapa Etapa;

int ler_processo(struct Linha *linha_producao, FILE *arquivo) {
    char linha_texto[256];
    while (fgets(linha_texto, sizeof(linha_texto), arquivo) != NULL) {
        char comando[50];
        if (sscanf(linha_texto, "%49s", comando) == 1) {
            if (strcmp(comando, "ETAPA") == 0) {
                struct Etapa *etapa = ler_etapa(linha_texto);
                anexar_etapa(linha_producao,etapa);
            }
            else if (strcmp(comando, "ATIVIDADE") == 0) {
                struct Atividade *atividade = ler_atividade(linha_texto);
                anexar_atividade(linha_producao,atividade);
            }
            else {
                // None
            }
            // Você pode adicionar outros "else if (strcmp(comando, "OUTRO_COMANDO") == 0)" aqui
        }
    }
    return 0;
}

struct Etapa *ler_etapa(char *buffer){
    char nome[STR_LEN];
    int capacidade = 0;

    int argc = sscanf(buffer, "%*s %s %d", nome, &capacidade);

    struct Etapa *etapa = criar_etapa(nome,capacidade);

    return etapa;
}


struct Atividade *ler_atividade(char *buffer){
    char nome[STR_LEN];
    int capacidade = 0;
    int ciclos = 0;
    int taxa_erro = 0;

    int argc = sscanf(buffer, "%*s %s %d %d %d", nome, &ciclos, &capacidade, &taxa_erro);

    struct Atividade *atividade = criar_atividade(nome,ciclos,capacidade,taxa_erro);

    return atividade;
}