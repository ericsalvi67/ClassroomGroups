#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- //

typedef struct aluno {
    char nome[100];
    int codigo;
    struct aluno *prox;
} Aluno;

typedef struct grupo {
    int numero;
    Aluno *alunos_grupo;
    struct grupo *prox;
} Grupo;

typedef struct turma {
    char codigo[20];
    Aluno *alunos;
    Grupo *grupos;
} Turma;

typedef struct header {
    int s_qClass;
    Turma *turma;
} Header;

// ---------- //

void incluir_nova_turma(Header *h) {
    char novoCodigo[20];
    printf("informe o codigo da nova turma: ");
    scanf(" %19s", novoCodigo);

    // verificando se já não existe outra turma com o mesmo codigo, se tiver ele não add
    for (int i = 0; i < h->s_qClass; i++) {
        if (strcmp(h->turma[i].codigo, novoCodigo) == 0) {
            printf("codigo de turma '%s' ja utilizado.\n", novoCodigo);
            return;
        }
    }

    // ajusto o tamanho das turmas
    Turma *temp = realloc(h->turma, (h->s_qClass + 1) * sizeof(Turma));
    if (temp == NULL) {
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

    printf("turma '%s' incluida com sucesso!\n", novoCodigo);
    printf("\n");
}

void listar_turmas(Header h) {
    if (h.s_qClass == 0) {
        printf("nenhuma turma cadastrada.\n");
        return;
    }

    printf("\n--- lista de turmas ---\n");
    for (int i = 0; i < h.s_qClass; i++) {
        printf("%d. %s\n", i + 1, h.turma[i].codigo);
    }
}

// ---------- //

int main() {
    Header sistema;
    sistema.s_qClass = 0;
    sistema.turma = NULL;

    incluir_nova_turma(&sistema);
    incluir_nova_turma(&sistema);
    listar_turmas(sistema);

    free(sistema.turma);
    return 0;
}
