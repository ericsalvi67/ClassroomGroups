#ifndef GRUPO_H
#define GRUPO_H

#include "estruturas.h"

void incluir_aluno_no_grupo_de_uma_turma(Header* h, int turmaIndexExt, int codigoAlunoExt, int numeroGrupoExt);
void consultar_alunos_dos_grupos_de_uma_turma(Header* h, int turmaIndex);
void remover_aluno_do_grupo(Header *h);

#endif