#include "grupo.h"
#include "turma.h"
#include "aluno.h"
#include "relatorios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void incluir_aluno_no_grupo_de_uma_turma(Header* h, int turmaIndexExt, int codigoAlunoExt, int numeroGrupoExt){  // 07
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }
    
    int turmaIndex = turmaIndexExt - 1; // Ajusta o índice para 0 baseado (1,2,3) -> (0,1,2). Baseado no Listar_turmas
    int codigoAluno = codigoAlunoExt; 
    int numeroGrupo = numeroGrupoExt; 
    Turma *turmaAtual = NULL;
    Aluno *alunoSelecionado = NULL;

    if(turmaIndexExt == 0 || codigoAlunoExt == 0 || numeroGrupoExt  == 0)
    {
        do{
            listar_turmas(*h);
            printf("Digite o numero da turma que deseja acessar: ");
            scanf("%d", &turmaIndex);
            turmaIndex--;
        } while (turmaIndex < 0 || turmaIndex >= h->s_qClass);

        turmaAtual = &h->turma[turmaIndex];
        if (turmaAtual->alunos == NULL) {
            printf("Essa turma nao possui alunos.\n");
            return;
        }

        listar_alunos(*h, turmaIndex);
        do{
            printf("Digite o codigo do aluno que deseja adicionar a um grupo: ");
            scanf("%d", &codigoAluno);
        } while (codigoAluno <= 0);

        alunoSelecionado = turmaAtual->alunos;
        while (alunoSelecionado != NULL && alunoSelecionado->codigo != codigoAluno) {
            alunoSelecionado = alunoSelecionado->prox;
        }

        if (alunoSelecionado == NULL) {
            printf("Aluno com codigo %d nao encontrado.\n", codigoAluno);
            return;
        }

        printf("Digite o numero do grupo: ");
        scanf("%d", &numeroGrupo);

    }
    else
    {
        turmaAtual = &h->turma[turmaIndexExt - 1]; // Ajusta o índice para 0 baseado (1,2,3) -> (0,1,2). Baseado no Listar_turmas
        alunoSelecionado = turmaAtual->alunos;
        while (alunoSelecionado != NULL && alunoSelecionado->codigo != codigoAluno) {
            alunoSelecionado = alunoSelecionado->prox;
            if (alunoSelecionado == NULL) {
                printf("Aluno com codigo %d nao encontrado.\n", codigoAluno);
            }
        }
    }

    // Verifica se o aluno já está em algum grupo
    Grupo *g = turmaAtual->grupos;
    while (g != NULL) {
        Aluno *a = g->alunos_grupo;
        while (a != NULL) {
            if (a->codigo == codigoAluno) {
                printf("Aluno ja esta em um grupo da turma.\n");
                return;
            }
            a = a->prox;
        }
        g = g->prox;
    }

    // Verifica se o grupo já existe
    Grupo *grupoAtual = turmaAtual->grupos;
    Grupo *grupoAnterior = NULL;
    while (grupoAtual != NULL && grupoAtual->numero != numeroGrupo) {
        grupoAnterior = grupoAtual;
        grupoAtual = grupoAtual->prox;
    }

    if (grupoAtual == NULL) {
        // Grupo não existe, criar novo
        Grupo *novoGrupo = (Grupo*) malloc(sizeof(Grupo));
        novoGrupo->numero = numeroGrupo;
        novoGrupo->alunos_grupo = NULL;
        novoGrupo->prox = NULL;

        if (grupoAnterior == NULL)
            turmaAtual->grupos = novoGrupo;
        else
            grupoAnterior->prox = novoGrupo;

        grupoAtual = novoGrupo;
    }

    // Adiciona o aluno ao grupo
    Aluno *novoAlunoGrupo = (Aluno*) malloc(sizeof(Aluno));
    novoAlunoGrupo->codigo = alunoSelecionado->codigo;
    strcpy(novoAlunoGrupo->nome, alunoSelecionado->nome);
    novoAlunoGrupo->prox = NULL;

    if (grupoAtual->alunos_grupo == NULL) {
        grupoAtual->alunos_grupo = novoAlunoGrupo;
    } else {
        Aluno *aux = grupoAtual->alunos_grupo;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novoAlunoGrupo;
    }

    printf("Aluno '%s' adicionado ao grupo %d da turma '%s'.\n",
    alunoSelecionado->nome, grupoAtual->numero, turmaAtual->codigo);
}

void remover_aluno_do_grupo(Header *h) { // 08
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    int turmaIndex;
    int codigoAluno;
    int numeroGrupo;
    int encontradoNoGrupo = 0;
    Turma *turmaAtual = NULL;
    Grupo *grupoAtual = NULL;
    Grupo *grupoAnterior = NULL; // Para remover o grupo se ficar vazio
    Aluno *alunoRemover = NULL;
    Aluno *alunoAnterior = NULL; // Para remover o aluno do grupo


     do {
        listar_turmas(*h);
        printf("Digite o numero da turma: ");
        scanf("%d", &turmaIndex);
        fflush(stdin); // Limpa o buffer do teclado
        turmaIndex--; // Ajusta o índice para 0 baseado (1,2,3) -> (0,1,2). Baseado no Listar_turmas
    } while (turmaIndex < 0 || turmaIndex >= h->s_qClass);

    turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->grupos == NULL) {
        printf("A turma '%s' nao possui grupos.\n", turmaAtual->codigo);
        return;
    }

    // consultar_alunos_dos_grupos_de_uma_turma(h); // Mostra os grupos e alunos
    consultar_alunos_dos_grupos_de_uma_turma(h, turmaIndex);

    
    printf("Digite o numero do grupo do qual deseja remover o aluno: ");
    scanf("%d", &numeroGrupo);
    fflush(stdin); // Limpa o buffer do teclado

    grupoAtual = turmaAtual->grupos;

    // Encontra o grupo específico
    while (grupoAtual != NULL && grupoAtual->numero != numeroGrupo) {
        grupoAnterior = grupoAtual;
        grupoAtual = grupoAtual->prox;
    }

    if (grupoAtual == NULL) {
        printf("Grupo %d nao encontrado na turma '%s'.\n", numeroGrupo, turmaAtual->codigo);
        return;
    }

    if (grupoAtual->alunos_grupo == NULL) {
        printf("O grupo %d ja esta vazio.\n", numeroGrupo);
        return;
    }

    printf("Digite o codigo do aluno a ser removido do grupo %d: ", numeroGrupo);
    scanf("%d", &codigoAluno);
    fflush(stdin); // Limpa o buffer do teclado

    alunoRemover = grupoAtual->alunos_grupo;

    // Procura o aluno na lista de alunos DO GRUPO
    while (alunoRemover != NULL) {
         if (alunoRemover->codigo == codigoAluno) {
             encontradoNoGrupo = 1;

            if (alunoAnterior == NULL) 
                grupoAtual->alunos_grupo = alunoRemover->prox;
            else 
                alunoAnterior->prox = alunoRemover->prox;

            printf("Aluno '%s' (codigo %d) removido SOMENTE do grupo %d da turma '%s'.\n",
                   alunoRemover->nome, alunoRemover->codigo, numeroGrupo, turmaAtual->codigo);

            free(alunoRemover); 
            break; 
         }
         alunoAnterior = alunoRemover;
         alunoRemover = alunoRemover->prox;
    }


    if (!encontradoNoGrupo) {
        printf("Aluno com codigo %d nao encontrado no grupo %d.\n", codigoAluno, numeroGrupo);
        return; 
    }

    if (grupoAtual->alunos_grupo == NULL) {
        printf("O grupo %d ficou vazio e sera removido da turma.\n", numeroGrupo);
        if (grupoAnterior == NULL) 
            turmaAtual->grupos = grupoAtual->prox;
        else 
            grupoAnterior->prox = grupoAtual->prox;

        free(grupoAtual); 
    }
}
