#ifndef ALUNO_H
#define ALUNO_H

#include "estruturas.h"

void listar_alunos(Header h, int turma);
void incluir_novo_aluno(Header* h, int codigoAluno, char nomeAlunoExt[50], int turmaIndexExt);
void remover_aluno(Header *h);

#endif