#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include "structs.h"
#define STR_LEN 256

int ler_processo(struct Linha *linha_producao, FILE *arquivo);
struct Etapa *ler_etapa(char *buffer);
struct Atividade *ler_atividade(char *buffer);

#endif