#include "relatorios.h"
#include "turma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alunos_em_mais_de_uma_turma(Header h) { // 11
    if (h.s_qClass < 2) {
        printf("E necessario ao menos duas turmas para essa verificacao.\n");
        return;
    }

    int jaExiste = 0;
    Aluno *temp = NULL;
    Aluno *a1 = NULL;
    Aluno *a2 = NULL;
    Aluno *jaListados = NULL; // O que ja foi guardado fica listado
    Aluno *aux = NULL;
    Aluno *novo = NULL;

    printf("\n--- Alunos em mais de uma turma ---\n");

    for (int i = 0; i < h.s_qClass; i++) {
        a1 = h.turma[i].alunos;
        while (a1 != NULL) {

            // conta em quantas turmas o aluno aparece
            int contador = 0;

            for (int j = 0; j < h.s_qClass; j++) {
                if (i == j) continue;

                a2 = h.turma[j].alunos;
                while (a2 != NULL) {

                    // se for o mesmo aluno
                    if (a1->codigo == a2->codigo) {
                        // soma mais um no contador
                        contador++;
                        break;
                    }
                    a2 = a2->prox;
                }
            }

            // Se ele aparece em mais de uma turma
            if (contador > 0) {
                jaExiste = 0;
                aux = jaListados;
                while (aux != NULL) {
                    if (aux->codigo == a1->codigo) {
                        jaExiste = 1;
                        break;
                    }
                    aux = aux->prox;
                }
                
                // se ele nao tiver listado ja, o lista em jaListados
                if (!jaExiste) {
                    printf("%d. %s\n",a1->codigo, a1->nome);

                    novo = (Aluno*) malloc(sizeof(Aluno));
                    strcpy(novo->nome, a1->nome);
                    novo->codigo = a1->codigo;
                    novo->prox = jaListados;
                    jaListados = novo;
                }
            }

            a1 = a1->prox;
        }
    }

    if (jaListados == NULL)
        printf("Nenhum aluno esta em mais de uma turma.\n");

    while (jaListados != NULL) {
        temp = jaListados;
        jaListados = jaListados->prox;
        free(temp);
    }

    printf("-------------------------------\n");
}

void listar_alunos_sem_grupo(Header* h, int turmaIndex) { //10
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    int estaEmGrupo;
    int encontrou = 0;
    Turma *turmaAtual = NULL;
    Aluno *aluno = NULL;
    Grupo *grupo = NULL;
    Aluno *alunoGrupo = NULL;
    
    if (turmaIndex == -1)
    {
        do {
            listar_turmas(*h);
            printf("Digite o numero da turma para verificar: ");
            scanf("%d", &turmaIndex);
            turmaIndex--;
        } while (turmaIndex < 0 || turmaIndex >= h->s_qClass);
    }
    turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->alunos == NULL) {
        printf("Essa turma nao possui alunos.\n");
        return;
    }

    printf("\n--- Alunos da turma '%s' que NAO estao em nenhum grupo ---\n", turmaAtual->codigo);

    aluno = turmaAtual->alunos;
    // verifica se o aluno está em algum grupo
    while (aluno != NULL) {
        estaEmGrupo = 0;
        grupo = turmaAtual->grupos;

        while (grupo != NULL && !estaEmGrupo) {
            alunoGrupo = grupo->alunos_grupo;
            while (alunoGrupo != NULL) {
                if (alunoGrupo->codigo == aluno->codigo) {
                    estaEmGrupo = 1;
                    break;
                }
                alunoGrupo = alunoGrupo->prox;
            }
            grupo = grupo->prox;
        }

        if (!estaEmGrupo) {
            printf("   %d. %s\n", aluno->codigo, aluno->nome);
            encontrou = 1;
        }

        aluno = aluno->prox;
    }

    if (!encontrou) {
        printf("Todos os alunos dessa turma estao em grupos.\n");
    }

    printf("-----------------------------------------------\n");
}

void alunos_em_apenas_uma_turma(Header h) { //12
    if (h.s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    int encontrou = 0;
    int codigo;
    int contagem;
    Aluno *aluno = NULL;
    Aluno *alunoBusca = NULL;

    printf("\n--- Alunos que estao em apenas uma turma ---\n");

    // Percorre todas as turmas
    for (int i = 0; i < h.s_qClass; i++) {
        aluno = h.turma[i].alunos;
        while (aluno != NULL) {
            codigo = aluno->codigo;
            contagem = 0;

            // Verifica em quantas turmas o aluno aparece
            for (int j = 0; j < h.s_qClass; j++) {
                alunoBusca = h.turma[j].alunos;
                while (alunoBusca != NULL) {
                    if (alunoBusca->codigo == codigo) {
                        contagem++;
                        break; // Evita contar mais de uma vez na mesma turma
                    }
                    alunoBusca = alunoBusca->prox;
                }
            }

            // Se está em apenas uma turma, imprime
            if (contagem == 1) {
                printf("   %d. %s\n", aluno->codigo, aluno->nome);
                encontrou = 1;
            }

            aluno = aluno->prox;
        }
    }

    if (!encontrou) {
        printf("Nao ha alunos em apenas uma turma.\n");
    }

    printf("---------------------------------------------\n");
}
