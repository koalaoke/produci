#ifndef STRUCTS_H
#define STRUCTS_H
#define STR_LEN 256

struct Linha{
    char nome[STR_LEN];             // Nome da linha
    struct Etapa *etapa;            // A primeira etapa;
};

struct Produto{
    char nome[STR_LEN];             // Nome do produto
	struct Produto *prox;           // (util para grupo de produtos)
};


struct Atividade{
    char nome[STR_LEN];             // Nome da atividade
	struct Atividade *prox;         // Próxima atividade
};

struct Etapa{
    char nome[STR_LEN];             // Nome da etapa
    struct Atividade *atividade;
    struct Etapa *ante;
    struct Etapa *prox;
};

struct Linha* criar_linha(char nome[STR_LEN]);
void imprime_processo(struct Linha *linha);
void criar_etapa(struct Linha *linha, char nome_etapa[STR_LEN]);
void criar_atividade(struct Linha *linha, char nome_atividade[STR_LEN]);
void destruir_linha(struct Linha *linha);

#endif
