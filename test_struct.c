#include "structs.h"
#include "read_file.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    srand(time(NULL));

    char nome_arquivo[128] = "assets.txt";
    FILE *file = fopen(nome_arquivo, "r"); //ponteiro pro arquivo
    if (file == NULL) { //erro de abertura do arquivo
        perror("fopen for read");
        return EXIT_FAILURE;
    }

    struct Linha *processo1 = criar_linha("Linha de processo");
    int flag = ler_processo(processo1, file);

    imprime_processo(processo1);

    struct Label label;
    strcpy(label.nome, "Chinela Havianas");

    struct Produto* lote1 = criar_lote(&label, 10);
    processo1->qtd_produtos = 10;

    struct Produto* produtos_novos = lote1;

    while (processo1->qtd_produtos) {
        struct Etapa *etapa = processo1->etapa;

        if (produtos_novos) {
            inserir_produtos(&processo1->etapa->fila_espera, produtos_novos);
            produtos_novos = NULL;
        }

        struct Produto* produtos_em_transito = NULL;

        while (etapa) {
            // Para toda etapa
            inserir_produtos(&etapa->fila_espera, produtos_em_transito);
            produtos_em_transito = NULL;

            while (etapa->qtd_produtos < etapa->capacidade && etapa->fila_espera) {
                struct Produto *aux = remover_produto(&etapa->fila_espera);
                inserir_produtos(&etapa->atividade->fila, aux);
                etapa->qtd_produtos++;
            }

            printf("%s: [%d/%d] -> ",etapa->nome, etapa->qtd_produtos, etapa->capacidade);
            imprimir_lote(etapa->fila_espera);
            struct Atividade *atividade = etapa->atividade;

            while (atividade) {
                // Para toda atividade
                printf("%s: ",atividade->nome);
                imprimir_lote(atividade->fila);

                contar_ciclo(&atividade->fila, atividade->capacidade);

                struct Produto *produtos_prontos = remover_prontos(&atividade->fila, atividade->ciclos);

                if (produtos_prontos) {
                    struct Produto *produtos_falhos = remover_erros(&produtos_prontos, atividade->taxa_erro);
                    printf("Defeituosos: ");
                    imprimir_lote(produtos_falhos);
                    etapa->qtd_produtos = etapa->qtd_produtos - contar_produtos(produtos_falhos);
                    inserir_produtos(&etapa->fila_espera, produtos_falhos);
                }

                inserir_produtos(&atividade->fila, produtos_em_transito);
                produtos_em_transito = produtos_prontos;
                atividade = atividade->prox;
            }

            etapa->qtd_produtos = etapa->qtd_produtos - contar_produtos(produtos_em_transito);
            etapa = etapa->prox;
        }

        printf("---\n");
        sleep(1);

        if(produtos_em_transito){
            struct Produto* produtos_finalizados = remover_prontos(&produtos_em_transito, 0);
            printf("Feitos: \n");
            imprimir_lote(produtos_finalizados);
            while (produtos_finalizados) {
                remover_produto(&produtos_finalizados);
                processo1->qtd_produtos--;
            }
        }
    } 

    free(lote1);
    destruir_linha(processo1);

    return 0;
}
