#include "read_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 256

typedef struct Atividade Atividade;
typedef struct Etapa Etapa;

/*int main(){
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
}*/


void adicionar_atividades(Etapa *etapa, FILE *file){ //trivial
    int flag = 0; //flag de controle do loop, fica 0 enquanto tiver atividades pra ler e -1 se chegar no final do arquivo ou nao tiver mais atividades pra ler
    
    while (flag == 0){ 
        Atividade *nova_atividade = (Atividade *)malloc(sizeof(Atividade)); nova_atividade->prox = NULL;
        if (nova_atividade == NULL) { //erro de malloc
            perror("malloc for new atividade");
            exit(EXIT_FAILURE);
            return;
        }


        flag = ler_atividade(nova_atividade, file); //retorna -1 se tiver no final do arquivo ou nao tiver mais atividades pra ler, retorna 0 se ler com sucesso
        if(flag == -1){ //entra se nao tiver atividades pra ler
            free(nova_atividade); //se tem malloc tem free
            break;
        }

        if(etapa->atividade == NULL){ //entra se nao tiver atividades
            etapa->atividade = nova_atividade; //nova atividade vira a primeira
        }else{ //entra se tiver atividades
            Atividade *aux = etapa->atividade; //ponteiro pra primeira atv.
            while(aux->prox != NULL) 
                aux = aux->prox; //aux vai ate o final
            aux->prox = nova_atividade; //coloca a nova atividade no final da lista de atividades
        }
    }   
}



int ler_atividade(struct Atividade *atividade_adicionada, FILE *file){ //retorna -1 se for EOF ou se a linha nao comecar com ATIVIDADE, retorna 0 se ler com sucesso
    char buffer[STR_LEN]; //buffer armazena linha do arquivo
    char nome_atividade[STR_LEN] = ""; // Nome da atividade

    if( fgets(buffer, sizeof(buffer), file) != NULL){ //entra se nao for EOF
        if(strncmp(buffer, "ATIVIDADE", 9) == 0){ //entra se a linha começar com ATIVIDADE
            sscanf(buffer + 10, "%s", nome_atividade); //parsing do nome da atividade
            strcpy(atividade_adicionada->nome, nome_atividade); //copio o nome
            return 0; 
        }
    }
    return -1; //fim do arquivo ou nao tem mais atividades pra ler
}



void mostrar_atividades(Etapa *etapa){ //trivial
    if(etapa->atividade == NULL){
        printf("Nenhuma Atividade Registrada.\n");
        return;
    }
    int counter = 0; //contador de atividades
    Atividade *aux_atividade = etapa->atividade; //recebe a primeira atividade da etapa
    while (aux_atividade != NULL) { //anda enquanto tiver atividades
        printf("     Atividade da Etapa %s: %s\n", etapa->nome, aux_atividade->nome); //print fofinho :3
        aux_atividade = aux_atividade->prox; //ponteiro anda
        counter++; //counter conta
    }
    printf("Total de Atividades da etapa %s: %d\n", etapa->nome, counter); //print nao tao fofinho :/
    
}



void mostrar_etapas(Etapa *linha_producao){ //trivial
    if(linha_producao == NULL){ 
        printf("Nenhuma etapa na linha de produção.\n");
        return;
    }
    Etapa *aux = linha_producao; //aux recebe a primeira etapa
    while (aux != NULL) {
        printf("Etapa %s (ID: %d)\n", aux->nome, aux->id); //print da etapa q aux aponta
        mostrar_atividades(aux); //mostra as atividades da etapa aux
        printf("\n"); 
        aux = aux->prox; //aux anda
    }
}



int adicionar_etapa(struct Etapa **linha_producao, FILE *file){ //retorna -1 se nao tiver etapas, retorna 0 se adicionar com sucesso
    Etapa *nova_etapa = (Etapa *)malloc(sizeof(Etapa)); nova_etapa->prox = NULL; nova_etapa->ante = NULL; nova_etapa->atividade = NULL;
    Etapa *aux = *linha_producao;
    
    if (nova_etapa == NULL) { //se der NULL eh erro de malloc
        perror("malloc for new etapa");
        exit(EXIT_FAILURE);
    }

    int flag = ler_etapa(nova_etapa, file); //ler_etapa retorna -1 se tiver nao tem etapa ou ta no final do arquivo
    if (flag == -1){
        printf("Sem mais etapas pra ler\n");
        free(nova_etapa);
        return -1;
    }

    if (*linha_producao == NULL) {
        *linha_producao = nova_etapa; //se linha for NULL ela basta receber essa primeira etapa
    } else { //senao vamos ter q acoplar essa nova etapa no final da lista
        while(aux->prox != NULL){
            aux = aux->prox; //aux aponta pra ultima etapa
        }
        aux->prox = nova_etapa; //auxn aponta pra nova etapa
        nova_etapa->ante = aux; //nova etapa tem q apontar pra trás
    }
    
    adicionar_atividades(nova_etapa, file); //adiciona atividades
    printf("Etapa %s adicionada com sucesso!\n", nova_etapa->nome);
    return 0;
}



int ler_etapa(struct Etapa *etapa_adicionada, FILE *file){ //retorna -1 se nao encontrar etapa retorna 0 se achar
    
    int id; //id da etapa
    char buffer[STR_LEN]; //buffer pega linha do arquivo
    char nome_etapa[STR_LEN] = ""; // Nome da etapa


    while ((strncmp(buffer, "ETAPA", 5) != 0)) { //fica no loop enquanto a linha não começar com ETAPA
        if(fgets(buffer, sizeof(buffer), file) == NULL){ //se chegar no final do arquivo retorna -1
            return -1; //EOF
        }        
    }
    
    sscanf(buffer + 6, "%d %s", &id, nome_etapa); //pego somente o nome no sccanf
    strcpy(etapa_adicionada->nome, nome_etapa); //copio o nome pra nova struct Etapa
    etapa_adicionada->id = id;
    return 0;
    
    
}

