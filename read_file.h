#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include "structs.h"
#define STR_LEN 256

int ler_etapa(struct Etapa *etapa_adicionada, FILE *file);
int adicionar_etapa(struct Etapa **linha_producao, FILE *file);
void mostrar_etapas(struct Etapa *linha_producao);
void adicionar_atividades(struct Etapa *etapa, FILE *file);
void mostrar_atividades(struct Etapa *etapa);
int ler_atividade(struct Atividade *atividade_adicionada, FILE *file);

#endif