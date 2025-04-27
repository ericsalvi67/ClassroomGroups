#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "estruturas.h"

void consultar_alunos_dos_grupos_de_uma_turma(Header* h, int turmaIndex);
void listar_alunos_sem_grupo(Header* h);
void alunos_em_mais_de_uma_turma(Header h);
void alunos_em_apenas_uma_turma(Header h);

#endif
