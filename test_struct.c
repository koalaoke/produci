#include "structs.h"

int main(){
    struct Linha *processo1 = criar_linha("Linha de processo");

    criar_etapa(processo1, "Etapa 1");
    criar_atividade(processo1, "Atividade 1");
    criar_atividade(processo1, "Atividade 2");
    criar_atividade(processo1, "Atividade 3");
    criar_etapa(processo1, "Etapa 2");
    criar_atividade(processo1, "Atividade 4");
    criar_atividade(processo1, "Atividade 5");
    criar_atividade(processo1, "Atividade 6");
    criar_etapa(processo1, "Etapa 3");
    criar_atividade(processo1, "Atividade 7");
    criar_atividade(processo1, "Atividade 8");
    criar_atividade(processo1, "Atividade 9");
    imprime_processo(processo1);

    destruir_linha(processo1);
}
