#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    struct Linha *processo1 = criar_linha("Linha de processo");

    criar_etapa(processo1, "Etapa 1");
    criar_atividade(processo1, "Atividade 1", 3);
    criar_atividade(processo1, "Atividade 2", 3);
    criar_atividade(processo1, "Atividade 3", 3);
    criar_etapa(processo1, "Etapa 2");
    criar_atividade(processo1, "Atividade 4", 3);
    criar_atividade(processo1, "Atividade 5", 3);
    criar_atividade(processo1, "Atividade 6", 3);
    criar_etapa(processo1, "Etapa 3");
    criar_atividade(processo1, "Atividade 7", 3);
    criar_atividade(processo1, "Atividade 8", 3);
    criar_atividade(processo1, "Atividade 9", 3);
    imprime_processo(processo1);

    struct Label label;
    strcpy(label.nome, "Chinela Havianas");

    struct Produto* lote1 = criar_lote(&label, 10);
    imprimir_lote(lote1);
    struct Produto* prods_transito = lote1;
    processo1->qtd_produtos = 10;

    while (processo1->qtd_produtos > 0) {
        struct Etapa *etapa = processo1->etapa;
        while (etapa) {
            struct Atividade *atividade = etapa->atividade;
            while (atividade) {
                printf("%s: ",atividade->nome);
                imprimir_lote(atividade->fila);

                contar_ciclo(&atividade->fila);
                inserir_produtos(&atividade->fila, prods_transito);
                prods_transito = remover_prontos(&atividade->fila, atividade->ciclos);
                atividade = atividade->prox;
            }
            etapa = etapa->prox;
        }
        printf("---\n");
        sleep(1);

        if(prods_transito){
            struct Produto* feitos = remover_prontos(&prods_transito, 0);
            printf("Feitos: \n");
            imprimir_lote(feitos);
            while (feitos) {
                remover_produto(&feitos);
                processo1->qtd_produtos--;
            }
        }
    }

    free(lote1);
    destruir_linha(processo1);

    return 0;
}
