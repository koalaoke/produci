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
    int id;
    int n_atividades;
    char nome[STR_LEN];             // Nome da etapa
    struct Atividade *atividade;
    struct Etapa *ante;
    struct Etapa *prox;
}Etapa;


    
 
int ler_etapa(Etapa *etapa_adicionada, FILE *file);

int adicionar_etapa(Etapa **linha_producao, FILE *file);

void mostrar_etapas(Etapa *linha_producao);

void adicionar_atividades(Etapa *etapa, FILE *file);

void mostrar_atividades(Etapa *etapa);

int ler_atividade(Atividade *atividade_adicionada, FILE *file);




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
    while (flag == 0) {
        flag = adicionar_etapa(&linha_producao, file);
    }
    mostrar_etapas(linha_producao);
    fclose(file);
    return 0;
}


void adicionar_atividades(Etapa *etapa, FILE *file){
    int flag = 0;
    
    while (flag == 0){ //lê enquanto não chegar no fim do arquivo ou não tiver mais atividades pra ler
        Atividade *nova_atividade = (Atividade *)malloc(sizeof(Atividade)); nova_atividade->prox = NULL;
        if (nova_atividade == NULL) {
            perror("malloc for new atividade");
            exit(EXIT_FAILURE);
            return;
        }


        flag = ler_atividade(nova_atividade, file);
        if(flag == -1){
            free(nova_atividade);
            break;
        }

        if(etapa->atividade == NULL){
            etapa->atividade = nova_atividade;
        }else{
            Atividade *aux = etapa->atividade;
            while(aux->prox != NULL)
                aux = aux->prox;
            aux->prox = nova_atividade;
        }
    }   
}



int ler_atividade(Atividade *atividade_adicionada, FILE *file){
    char buffer[STR_LEN];
    char nome_atividade[STR_LEN] = ""; // Nome da atividade

    if( fgets(buffer, sizeof(buffer), file) != NULL){
        if(strncmp(buffer, "ATIVIDADE", 9) == 0){ //compara se a linha começa com ATIVIDADE
            sscanf(buffer + 10, "%s", nome_atividade); //pego somente o nome da Atividade no sccanf
            strcpy(atividade_adicionada->nome, nome_atividade); //copio o nome
            return 0;
        }
    }
    return -1; //fim do arquivo ou nao tem mais atividades pra ler
}



void mostrar_atividades(Etapa *etapa){
    if(etapa->atividade == NULL){
        printf("Nenhuma Atividade Registrada.\n");
        return;
    }
    Atividade *aux_atividade = etapa->atividade;
    while (aux_atividade != NULL) {
        printf("     Atividade da Etapa %s: %s\n", etapa->nome, aux_atividade->nome);
        aux_atividade = aux_atividade->prox;
    }
    
}



void mostrar_etapas(Etapa *linha_producao){
    if(linha_producao == NULL){
        printf("Nenhuma etapa na linha de produção.\n");
        return;
    }
    Etapa *aux = linha_producao;
    while (aux != NULL) {
        printf("Etapa %s (ID: %d ; Nº de Atividades: %d)\n", aux->nome, aux->id, aux->n_atividades);
        mostrar_atividades(aux);
        printf("\n");
        aux = aux->prox;
    }
}



int adicionar_etapa(Etapa **linha_producao, FILE *file){
    Etapa *nova_etapa = (Etapa *)malloc(sizeof(Etapa)); nova_etapa->prox = NULL; nova_etapa->ante = NULL; nova_etapa->atividade = NULL;
    Etapa *aux = *linha_producao;
    
    if (nova_etapa == NULL) {
        perror("malloc for new etapa");
        exit(EXIT_FAILURE);
    }

    int flag = ler_etapa(nova_etapa, file);
    if (flag == -1){
        printf("Sem mais etapas pra ler\n");
        free(nova_etapa);
        return -1;
    }

    if (*linha_producao == NULL) {
        *linha_producao = nova_etapa;
    } else {
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = nova_etapa;
        nova_etapa->ante = aux;
    }
    
    adicionar_atividades(nova_etapa, file);
    printf("Etapa %s adicionada com sucesso!\n", nova_etapa->nome);
    return 0;
}



int ler_etapa(Etapa *etapa_adicionada, FILE *file){
    
    int id, n_atividades;
    char buffer[STR_LEN];
    char nome_etapa[STR_LEN] = ""; // Nome da etapa


    while ((strncmp(buffer, "ETAPA", 5) != 0)) { //compara se a linha começa com ETAPA
        if(fgets(buffer, sizeof(buffer), file) == NULL){ 
            return -1; //fim do arquivo, ou seja, nao tem etapas
        }        
    }
    
    sscanf(buffer + 6, "%d %d %s", &id, &n_atividades, nome_etapa); //pego somente o nome da Etapa no sccanf
    strcpy(etapa_adicionada->nome, nome_etapa); //copio o nome pra nova struct Etapa que fiz
    etapa_adicionada->id = id;
    etapa_adicionada->n_atividades = n_atividades;
    return 0;
    
    
}

