#ifndef STRUCTS_H
#define STRUCTS_H
#define STR_LEN 256

struct Label{
    char nome[STR_LEN];             // Nome do produto
};

struct Linha{
    char nome[STR_LEN];             // Nome da linha
    int qtd_produtos;               // Quantidade de produtos na linha;
    struct Etapa *etapa;            // A primeira etapa;
};

struct Produto{
    struct Label *label;            // Nome do produto
    int ciclos;                     // Quantos ciclos o produto passou;
    struct Produto *prox;           // Utilitário para lista de produtos
};

struct Atividade{
    char nome[STR_LEN];             // Nome da atividade
    int ciclos;                     // Ciclos necessários para passar da atividade
    int capacidade;                 // Quantos produtos podem ser tratados
    int taxa_erro;                  // Taxa de erros leves (%)
    struct Produto *fila;           // Os produtos dentro da atividade
    struct Atividade *prox;         // Próxima atividade
};

struct Etapa{
    char nome[STR_LEN];             // Nome da etapa
    int capacidade;                 // Quantos produtos podem ser tratados
    int qtd_produtos;               // Quantos produtos estão
    struct Produto *fila_espera;    // Fila de espera de produtos
    struct Atividade *atividade;    // Lista de atividades
    struct Etapa *ante;             // Etapa anterior
    struct Etapa *prox;             // Próxima etapa
};

struct Linha* criar_linha(char *nome);
void imprime_processo(struct Linha *linha);
void imprimir_lote(struct Produto *lote);

void criar_etapa(struct Linha *linha, char *nome_etapa, int capacidade);
void criar_atividade(struct Linha *linha, char *nome_atividade, int ciclos, int capacidade, int taxa_erro);
struct Produto* criar_lote(struct Label *label, int qtd);

void inserir_produtos(struct Produto **destination, struct Produto *source);
void contar_ciclo(struct Produto **lote, int capacidade);
int contar_produtos(struct Produto *lote);

struct Produto* remover_produto(struct Produto **lote);
struct Produto* remover_prontos(struct Produto **lote, int ciclos);
struct Produto* remover_erros(struct Produto **lote, int taxa_erros);
void destruir_linha(struct Linha *linha);

#endif
