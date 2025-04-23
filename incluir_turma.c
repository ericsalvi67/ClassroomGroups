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

void listar_alunos(Header h) // 06
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
            printf("   Nenhum aluno cadastrado.\n");
        } 
        else 
        {
            int j = 1;
            while (aux != NULL) 
            {
                printf("   %d. %s.\n", aux->codigo, aux->nome);
                aux = aux->prox;
                j += 1;
            }
        }
    }
    printf("-------------------\n");
}

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

void listar_alunos_de_uma_turma(Header h, int turmaIndex) { // precisa kkkk
    if (turmaIndex < 0 || turmaIndex >= h.s_qClass) {
        printf("Turma inválida.\n");
        return;
    }

    Turma t = h.turma[turmaIndex];

    printf("\n--- Alunos da Turma %s ---\n", t.codigo);
    Aluno *aux = t.alunos;

    if (aux == NULL) {
        printf("   Nenhum aluno cadastrado.\n");
    } else {
        while (aux != NULL) {
            printf("   %d. %s\n", aux->codigo, aux->nome);
            aux = aux->prox;
        }
    }
    printf("--------------------------\n");
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

void incluir_novo_aluno(Header* h, int codigoAluno, char nomeAlunoExt[50], int turmaIndexExt) // 04
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

void incluir_aluno_no_grupo_de_uma_turma(Header* h){  // 07
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    listar_turmas(*h);

    int turmaIndex;
    printf("Digite o numero da turma que deseja acessar: ");
    scanf("%d", &turmaIndex);
    turmaIndex--;

    if (turmaIndex < 0 || turmaIndex >= h->s_qClass) {
        printf("Turma inválida.\n");
        return;
    }

    Turma *turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->alunos == NULL) {
        printf("Essa turma nao possui alunos.\n");
        return;
    }

    listar_alunos_de_uma_turma(*h, turmaIndex);

    int codigoAluno;
    printf("Digite o codigo do aluno que deseja adicionar a um grupo: ");
    scanf("%d", &codigoAluno);

    Aluno *alunoSelecionado = turmaAtual->alunos;
    while (alunoSelecionado != NULL && alunoSelecionado->codigo != codigoAluno) {
        alunoSelecionado = alunoSelecionado->prox;
    }

    if (alunoSelecionado == NULL) {
        printf("Aluno com codigo %d não encontrado.\n", codigoAluno);
        return;
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

    int numeroGrupo;
    printf("Digite o numero do grupo: ");
    scanf("%d", &numeroGrupo);

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

void consultar_alunos_dos_grupos_de_uma_turma(Header* h) { // 09
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    listar_turmas(*h);

    int turmaIndex;
    printf("Digite o numero da turma que deseja consultar os grupos: ");
    scanf("%d", &turmaIndex);
    turmaIndex--;

    if (turmaIndex < 0 || turmaIndex >= h->s_qClass) {
        printf("Turma inválida.\n");
        return;
    }

    Turma *turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->grupos == NULL) {
        printf("A turma '%s' nao possui nenhum grupo cadastrado.\n", turmaAtual->codigo);
        return;
    }

    Grupo *grupo = turmaAtual->grupos;
    printf("\n--- Grupos da Turma '%s' ---\n", turmaAtual->codigo);

    while (grupo != NULL) {
        printf("Grupo %d:\n", grupo->numero);

        if (grupo->alunos_grupo == NULL) {
            printf("   Nenhum aluno neste grupo.\n");
        } else {
            Aluno *a = grupo->alunos_grupo;
            while (a != NULL) {
                printf("   %d. %s\n", a->codigo, a->nome);
                a = a->prox;
            }
        }

        grupo = grupo->prox;
    }

    printf("------------------------------\n");
}

void remover_aluno(Header *h) {  // 05
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    listar_turmas(*h);

    int turmaIndex;
    printf("Digite o numero da turma que deseja acessar: ");
    scanf("%d", &turmaIndex);
    turmaIndex--;

    if (turmaIndex < 0 || turmaIndex >= h->s_qClass) {
        printf("Turma invalida.\n");
        return;
    }

    Turma *turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->alunos == NULL) {
        printf("Essa turma nao possui alunos.\n");
        return;
    }

    listar_alunos_de_uma_turma(*h, turmaIndex);

    int codigoAluno;
    printf("Digite o codigo do aluno que deseja remover: ");
    scanf("%d", &codigoAluno);

    Aluno *atual = turmaAtual->alunos;
    Aluno *anterior = NULL;

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
    Grupo *g = turmaAtual->grupos;
    while (g != NULL) {
        Aluno *ag = g->alunos_grupo;
        Aluno *ag_ant = NULL;

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

void alunos_em_mais_de_uma_turma(Header h) {
    if (h.s_qClass < 2) {
        printf("E necessário ao menos duas turmas para essa verificacao.\n");
        return;
    }

    printf("\n--- Alunos em mais de uma turma ---\n");

    // O que ja foi guardado fica listado
    Aluno *jaListados = NULL;

    for (int i = 0; i < h.s_qClass; i++) {
        Aluno *a1 = h.turma[i].alunos;
        while (a1 != NULL) {

            int contador = 0;

            for (int j = 0; j < h.s_qClass; j++) {
                if (i == j) continue;

                Aluno *a2 = h.turma[j].alunos;
                while (a2 != NULL) {
                    if (strcmp(a1->nome, a2->nome) == 0) {
                        contador++;
                        break;
                    }
                    a2 = a2->prox;
                }
            }

            // Se tem +1 turma e nao foi listado
            if (contador > 0) {
                int jaExiste = 0;
                Aluno *aux = jaListados;
                while (aux != NULL) {
                    if (strcmp(aux->nome, a1->nome) == 0) {
                        jaExiste = 1;
                        break;
                    }
                    aux = aux->prox;
                }

                if (!jaExiste) {
                    printf("%s\n", a1->nome);

                    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
                    strcpy(novo->nome, a1->nome);
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
        Aluno *temp = jaListados;
        jaListados = jaListados->prox;
        free(temp);
    }

    printf("-------------------------------\n");
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
    printf("5. Remover aluno\n");
    printf("6. Incluir aluno no grupo\n");
    printf("7. Consultar alunos dos grupos de uma turma\n");

    printf("\n0. Sair\n");

    do{
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado
    }while(opcao < 0 || opcao > 7);

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
        case 5:
            remover_aluno(sistema);
            break;
        case 6:
            incluir_aluno_no_grupo_de_uma_turma(sistema);
            break;
        case 7:
            consultar_alunos_dos_grupos_de_uma_turma(sistema);
            break;
        case 0:
            free(sistema->turma); // Libera a memória alocada para as turmas
            exit(0);
    }

}

// ---------- //

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
