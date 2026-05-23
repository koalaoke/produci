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


    
 
void ler_arquivo(Etapa **linha_producao, char nome_arquivo[128]);

int main(){
    Etapa *linha_producao = NULL;
    char nome_arquivo[128] = "assets.txt";
    ler_arquivo(&linha_producao, nome_arquivo);
}
void ler_arquivo(Etapa **linha_producao, char nome_arquivo[128]){
    FILE *file;
    char buffer[STR_LEN];

    /*-----O QUE VAI SER LIDO-----*/
    char nome_etapa[STR_LEN] = ""; // Nome da etapa
    char nome_atividade[STR_LEN] = ""; //nome da(s) atividade(s)
    /*----------------------------*/
    
    sscanf(nome_arquivo, "%128s", nome_arquivo);
    file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        perror("fopen for read");
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) { //buffer já armazena a linha lida do arquivo
        if(strncmp(buffer, "ETAPA", 5) == 0){
            sscanf(buffer + 6, "%s", nome_etapa);
        }
        else if(strncmp(buffer, "ATIVIDADE", 9) == 0){
            sscanf(buffer + 10, "%s", nome_atividade);
        }

        
    }

    //ao final, vamos ter as informações das variáveis definidas no início da função

    fclose(file);

    
}
