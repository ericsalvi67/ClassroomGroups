#include "aluno.h"
#include "turma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listar_alunos(Header h, int turma) //06
{
    if (h.s_qClass == 0) 
    {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    Aluno *aux = NULL;

    if (turma < -1 || turma >= h.s_qClass) 
    {
        printf("Turma inválida.\n");
        return;
    }

    if (turma == -1){
        printf("\n--- Lista de Alunos por Turma ---\n");
        for (int i = 0; i < h.s_qClass; i++) 
        {
            printf("%d. %s\n", i + 1, h.turma[i].codigo);
            aux = h.turma[i].alunos;
            if (aux == NULL) 
            {
                printf("   Nenhum aluno cadastrado.\n");
            } 
            else 
            {
                while (aux != NULL) 
                {
                    printf("   %d. %s\n", aux->codigo, aux->nome);
                    aux = aux->prox;
                }
            }
        }
    }
    else {
        printf("\n--- Alunos da Turma %s ---\n", h.turma[turma].codigo);
        aux = h.turma[turma].alunos;
        if (aux == NULL) 
        {
            printf("   Nenhum aluno cadastrado.\n");
        } 
        else 
        {
            while (aux != NULL) 
            {
                printf("   %d. %s\n", aux->codigo, aux->nome);
                aux = aux->prox;
            }
        }
    }
    printf("-------------------\n");
}

void incluir_novo_aluno(Header* h, int codigoAluno, char nomeAlunoExt[50], int turmaIndexExt) //04
{   
    int turmaIndex;
    char nomeAluno[50];
    Aluno *novo = NULL;
    Turma *turmaAtual = NULL;
    Aluno *aux = NULL;
    Aluno *VerificaAluno = NULL;


    if ((codigoAluno == 0) && strcmp(nomeAlunoExt, "")== 0 && (turmaIndexExt == 0))
    {
        do
        {   
            printf("\nDigite o codigo do aluno: ");
            scanf("%d", &codigoAluno);
            fflush(stdin); // Limpa o buffer do teclado
        } while (codigoAluno == 0);

        do
        {
            printf("Digite o nome do aluno: ");
            gets(nomeAluno);
        } while (strcmp(nomeAluno, "") == 0);
        do
        {
            listar_turmas(*h);
            printf("Digite o numero da turma: ");
            scanf("%d", &turmaIndex);
        } while (turmaIndex < 0 );
        turmaIndex -= 1; // Ajusta o índice para 0 baseado (1,2,3) -> (0,1,2). Baseado no Listar_turmas 

        VerificaAluno = h->turma[turmaIndex].alunos;
        while (VerificaAluno != NULL) //valida aluno por aluno
        {
            if (VerificaAluno->codigo == codigoAluno)
            {
                printf("O codigo %d ja esta vinculado a um aluno na turma.\n",VerificaAluno->codigo);
                return;
            }
            aux = aux->prox;
        }
    }
    else 
    {
        turmaIndex = turmaIndexExt - 1; // Ajusta o índice para 0 baseado (1,2,3) -> (0,1,2). Baseado no Listar_turmas
        strcpy(nomeAluno, nomeAlunoExt);
        if (turmaIndex < 0 || turmaIndex >= h->s_qClass) 
        {
            printf("Turma inválida.\n");
            return;
        }
    } 

    novo = (Aluno*) malloc(sizeof(Aluno));
    if (!novo) 
    {
        printf("Erro ao alocar memória para novo aluno.\n");
        return;
    }

    novo->prox = NULL;
    novo->codigo = codigoAluno;
    strcpy(novo->nome, nomeAluno);

    turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->alunos == NULL) 
    {
        turmaAtual->alunos = novo;
    } 
    else 
    {
        aux = turmaAtual->alunos;
        while (aux->prox != NULL) 
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("Aluno '%20s' adicionado a turma '%10s' com sucesso!\n", nomeAluno, turmaAtual->codigo);
}

void remover_aluno(Header *h) {  // 05
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    int turmaIndex;
    Turma *turmaAtual = NULL;
    Aluno *atual = NULL;
    Aluno *anterior = NULL;
    Grupo *g = NULL;
    Aluno *ag = NULL; // Aluno do grupo
    Aluno *ag_ant = NULL; // Aluno do grupo anterior

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

    int codigoAluno;
    do{
        listar_alunos(*h, turmaIndex);
        printf("Digite o codigo do aluno que deseja remover: ");
        scanf("%d", &codigoAluno);
        fflush(stdin); // Limpa o buffer do teclado
    } while (codigoAluno <= 0);


    atual = turmaAtual->alunos;

    while (atual != NULL && atual->codigo != codigoAluno) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Aluno com codigo %d não encontrado.\n", codigoAluno);
        return;
    }

    if (anterior == NULL)
        turmaAtual->alunos = atual->prox;
    else
        anterior->prox = atual->prox;

    printf("Aluno '%s' removido da turma '%s'.\n", atual->nome, turmaAtual->codigo);

    free(atual);

    // Remove grupo
    g = turmaAtual->grupos;
    while (g != NULL) {
        ag = g->alunos_grupo;
        while (ag != NULL) {
            if (ag->codigo == codigoAluno) {
                if (ag_ant == NULL)
                    g->alunos_grupo = ag->prox;
                else
                    ag_ant->prox = ag->prox;

                free(ag);
                break;
            }

            ag_ant = ag;
            ag = ag->prox;
        }

        g = g->prox;
    }

    printf("Aluno removido de todos os grupos da turma.\n");
}
