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

void incluir_nova_turma(Header* h, char novoCodigoExt[20]) { //recebe um codigo externo para a turma para pre carrregar dados
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
    // ---------- //

void listar_turmas(Header h) {
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

// ---------- //

void incluir_novo_aluno(Header* h, int codigoAluno, char nomeAlunoExt[50], int turmaIndexExt) 
{   
    int turmaIndex;
    char nomeAluno[50];
    if ((codigoAluno == 0) && strcmp(nomeAlunoExt, "")== 0 && (turmaIndexExt == 0))
    {
        do
        {   
            printf("\nDigite o codigo do aluno: ");
            scanf("%d", &codigoAluno);
            getchar(); // Limpa o buffer do teclado
            printf("Digite o nome do aluno: ");
            gets(nomeAluno);
            printf("Digite o numero da turma: ");
            scanf("%d", &turmaIndex);
            turmaIndex -= 1; // Ajusta o índice para 0 baseado (1,2,3) -> (0,1,2). Baseado no Listar_turmas
        } while (codigoAluno == 0 || strcmp(nomeAluno, "")== 0 || turmaIndex == 0);    
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

    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    if (!novo) 
    {
        printf("Erro ao alocar memória para novo aluno.\n");
        return;
    }

    novo->prox = NULL;
    novo->codigo = codigoAluno;
    strcpy(novo->nome, nomeAluno);

    Turma *turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->alunos == NULL) 
    {
        turmaAtual->alunos = novo;
    } 
    else 
    {
        Aluno *aux = turmaAtual->alunos;
        while (aux->prox != NULL) 
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("Aluno '%20s' adicionado a turma '%10s' com sucesso!\n", nomeAluno, turmaAtual->codigo);
}


void listar_alunos(Header h)
{
    if (h.s_qClass == 0) 
    {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    printf("\n--- Lista de Alunos por Turma ---\n");
    for (int i = 0; i < h.s_qClass; i++) 
    {
        printf("%d. %s\n", i + 1, h.turma[i].codigo);
        Aluno *aux = h.turma[i].alunos;
        if (aux == NULL) 
        {
            printf("      Nenhum aluno cadastrado.\n");
        } 
        else 
        {
            int j = 1;
            while (aux != NULL) 
            {
                printf("   %d. %s\n", j++, aux->nome);
                aux = aux->prox;
            }
        }
    }
    printf("-------------------\n");
}

void inicioProg(Header* sistema)
{
    printf("-------------------\n");
    printf("Compilando informacoes...\n");

    //pre-carrega as turmas
    incluir_nova_turma(sistema, "Turma 1");
    incluir_nova_turma(sistema, "Turma 2");
    incluir_nova_turma(sistema, "Turma 3");
    incluir_nova_turma(sistema, "Turma da monica");
    printf("--- Turmas incluidas ---\n");
    //pre-carrega os alunos
    incluir_novo_aluno(sistema, 123, "Eric Salvi", 1);
    incluir_novo_aluno(sistema, 124, "Gustavo Quadri", 1);
    incluir_novo_aluno(sistema, 125, "Lucas Almeida", 2);
    incluir_novo_aluno(sistema, 126, "Emerson Oliveira", 3);
    incluir_novo_aluno(sistema, 127, "Andressa Campos", 3);
    incluir_novo_aluno(sistema, 128, "Ana Beatriz", 2);
    incluir_novo_aluno(sistema, 129, "Gabriel Silva", 1);
    incluir_novo_aluno(sistema, 130, "Lucas Santos", 2);
    incluir_novo_aluno(sistema, 131, "Guilherme Almeida", 3);
    incluir_novo_aluno(sistema, 132, "Ana Clara", 1);
    incluir_novo_aluno(sistema, 133, "Mariana Oliveira", 2);
    incluir_novo_aluno(sistema, 134, "Pedro Henrique", 3);
    incluir_novo_aluno(sistema, 135, "Joao Pedro", 1);
    printf("--- Alunos incluidos ---\n");
    //pre-carrega os grupos
    //pre-carrega os alunos dos grupos


    printf("Informacoes incluidas com sucesso.\n");
    printf("-------------------\n");
}

void menu(Header* sistema) //menu de opções para o usuario
{
    int opcao;
    printf("\n--- Menu ---\n");
    printf("1. Incluir nova turma\n");
    printf("2. Listar turmas\n");
    printf("3. Incluir novo aluno\n");
    printf("4. Listar alunos\n");

    printf("\n0. Sair\n");

    do{
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado
    }while(opcao < 0 || opcao > 4);

    switch (opcao) {
        case 1:
            incluir_nova_turma(sistema, "");
            break;
        case 2:
            listar_turmas(*sistema);
            break;
        case 3:
            incluir_novo_aluno(sistema, 0, "", 0);
            break;
        case 4:
            listar_alunos(*sistema);
            break;
        case 0:
            free(sistema->turma); // Libera a memória alocada para as turmas
            exit(0);
    }

}

int main() 
{
    Header sistema;
    sistema.s_qClass = 0;
    sistema.turma = NULL;

    inicioProg(&sistema);

    while(1)
        menu(&sistema);

    return 0;
}
