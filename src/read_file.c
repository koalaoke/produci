#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 256


/*
struct Linha{
    char nome[STR_LEN];             // Nome da linha
    struct Etapa *etapa;            // A primeira etapa;
};

struct Produto{
    char nome[STR_LEN];             // Nome do produto
	struct Produto *prox;           // (util para grupo de produtos)
};

*/
typedef struct Atividade{
    char nome[STR_LEN];             // Nome da atividade
	struct Atividade *prox;         // Próxima atividade
}Atividade;

typedef struct Etapa{
    char nome[STR_LEN];             // Nome da etapa
    struct Atividade *atividade;
    struct Etapa *ante;
    struct Etapa *prox;
}Etapa;


    
 
int ler_etapa(Etapa *etapa_adicionada, FILE *file);
void adicionar_etapa(Etapa **linha_producao, FILE *file);
void mostrar_etapas(Etapa *linha_producao);


int main(){
    FILE *file; 
    file = fopen("assets.txt", "r");
    if (file == NULL) {
        perror("fopen for read");
        return EXIT_FAILURE;
    }

    int flag = 0;
    Etapa *linha_producao = NULL;
    char nome_arquivo[128] = "assets.txt";

    printf("Lendo UMA Etapa:\n\n");
    adicionar_etapa(&linha_producao, file);
    mostrar_etapas(linha_producao);

    printf("\nLendo o arquivo novamente para adicionar mais etapas:\n\n");

    adicionar_etapa(&linha_producao, file);
    mostrar_etapas(linha_producao);

    printf("\nLendo MAIS UMA etapa:\n\n");
    adicionar_etapa(&linha_producao, file);
    mostrar_etapas(linha_producao);

    fclose(file);
    return 0;
}


void mostrar_etapas(Etapa *linha_producao){
    Etapa *aux = linha_producao;
    while (aux != NULL) {
        printf("Etapa: %s\n", aux->nome);
        aux = aux->prox;
    }
}


void adicionar_etapa(Etapa **linha_producao, FILE *file){
    Etapa *nova_etapa = (Etapa *)malloc(sizeof(Etapa)); nova_etapa->prox = NULL; 
    Etapa *aux = *linha_producao;
    
    if (nova_etapa == NULL) {
        perror("malloc for new etapa");
        exit(EXIT_FAILURE);
    }

    int flag = ler_etapa(nova_etapa, file);
    if (flag == -1){
        fprintf(stderr, "Sem mais etapas pra ler\n");
        free(nova_etapa);
        return;
    }

    if (*linha_producao == NULL) {
        *linha_producao = nova_etapa;
    } else {
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = nova_etapa;
    }
    

    nova_etapa->atividade = NULL;
    nova_etapa->ante = aux;

    

}


int ler_etapa(Etapa *etapa_adicionada, FILE *file){
    
    char buffer[STR_LEN];
    char nome_etapa[STR_LEN] = ""; // Nome da etapa

    while (strncmp(buffer, "ETAPA", 5 != 0)) { //compara se a linha começa com ETAPA
        if(fgets(buffer, sizeof(buffer), file) == NULL){ 
            return -1; //fim do arquivo, ou seja, nao tem etapas
        }        
    }
    
    sscanf(buffer + 6, "%s", nome_etapa); //pego somente o nome da Etapa no sccanf
    strcpy(etapa_adicionada->nome, nome_etapa); //copio o nome pra nova struct Etapa que fiz
    return 0;
    
    
}

