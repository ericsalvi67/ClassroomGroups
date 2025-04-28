#include "turma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listar_turmas(Header h) { // 03
    if (h.s_qClass == 0) {
        printf("nenhuma turma cadastrada.\n");
        return;
    }

    printf("\n--- lista de turmas ---\n");
    for (int i = 0; i < h.s_qClass; i++) {
        printf("%d. %s\n", i + 1, h.turma[i].codigo);
    }
    printf("-------------------\n");
}

void incluir_nova_turma(Header* h, char novoCodigoExt[20]) { // 01 - recebe um codigo externo para a turma para pre carrregar dados
    char novoCodigo[20];
    if (strcmp(novoCodigoExt, "") == 0) {
        do{
        printf("\ninforme o codigo da nova turma: ");
        gets(novoCodigo);
        }while(strcmp(novoCodigo, "") == 0);
    }
    else
        strcpy(novoCodigo, novoCodigoExt);
        
    // verificando se já não existe outra turma com o mesmo codigo, se tiver ele não add
    for (int i = 0; i < h->s_qClass; i++) {
        if (strcmp(h->turma[i].codigo, novoCodigo) == 0) {
            printf("codigo de turma '%s' ja utilizado.\n", novoCodigo);
            return;
        }
    }

    // ajusto o tamanho das turmas
    Turma *temp = realloc(h->turma, (h->s_qClass + 1) * sizeof(Turma));
    if (!temp) {
        printf("erro ao alocar.\n");
        return;
    }

    h->turma = temp;

    // nova turma é iniciada
    strcpy(h->turma[h->s_qClass].codigo, novoCodigo);
    h->turma[h->s_qClass].alunos = NULL;
    h->turma[h->s_qClass].grupos = NULL;

    // +1 turma add
    h->s_qClass +=1;

    printf("Turma '%10s' incluida com sucesso!\n", novoCodigo);
}

void remover_turma(Header *h) { //02
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    int turmaIndex;
    Grupo *tempGrupo = NULL;
    Aluno *temp = NULL;
    Aluno *alunoGrupo = NULL;
    Grupo *grupo = NULL;
    Aluno *aluno = NULL;
    Turma *turma = NULL;

    do {
        listar_turmas(*h);
        printf("Digite o numero da turma que deseja remover: ");
        scanf("%d", &turmaIndex);
        turmaIndex--;
    } while ((turmaIndex < 0 || turmaIndex >= h->s_qClass));

    turma = &h->turma[turmaIndex];

    printf("Removendo a turma: %s\n", turma->codigo);

    // Liberar memória dos alunos
    aluno = turma->alunos;
    while (aluno != NULL) {
        temp = aluno;
        aluno = aluno->prox;
        free(temp);
    }

    // Liberar memória dos grupos e dos alunos nos grupos
    grupo = turma->grupos;
    while (grupo != NULL) {
        alunoGrupo = grupo->alunos_grupo;
        while (alunoGrupo != NULL) {
            temp = alunoGrupo;
            alunoGrupo = alunoGrupo->prox;
            free(temp);
        }

        tempGrupo = grupo;
        grupo = grupo->prox;
        free(tempGrupo);
    }

    // Deslocar as turmas para seguir sequencia
    for (int i = turmaIndex; i < h->s_qClass - 1; i++) {
        h->turma[i] = h->turma[i + 1];
    }

    h->s_qClass--;

    printf("Turma removida com sucesso.\n");
}
