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

void listar_alunos(Header h, int turma) // 06
{
    if (h.s_qClass == 0) 
    {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    if (turma < 0 || turma >= h.s_qClass) 
    {
        printf("Turma inválida.\n");
        return;
    }

    if (turma == 0){
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
        Aluno *aux = h.turma[turma].alunos;
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

void incluir_aluno_no_grupo_de_uma_turma(Header* h, int turmaIndexExt, int codigoAlunoExt, int numeroGrupoExt) {  // 07
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

void consultar_alunos_dos_grupos_de_uma_turma(Header* h, int turmaIndex) { // 09
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }
    
    Aluno *aluno = NULL;
    Grupo *grupo = NULL;
    Turma *turmaAtual = NULL;

    if (turmaIndex == 0) {
        do{
            listar_turmas(*h);
            printf("Digite o numero da turma que deseja acessar: ");
            scanf("%d", &turmaIndex);
            turmaIndex--;
        } while (turmaIndex < 0 || turmaIndex >= h->s_qClass);
    }

    turmaAtual = &h->turma[turmaIndex];

    if (turmaAtual->grupos == NULL) {
        printf("A turma '%s' nao possui nenhum grupo cadastrado.\n", turmaAtual->codigo);
        return;
    }

    grupo = turmaAtual->grupos;
    printf("\n--- Grupos da Turma '%s' ---\n", turmaAtual->codigo);

    while (grupo != NULL) {
        printf("Grupo %d:\n", grupo->numero);

        if (grupo->alunos_grupo == NULL) {
            printf("   Nenhum aluno neste grupo.\n");
        } else {
            aluno = grupo->alunos_grupo;
            while (aluno != NULL) {
                printf("   %d. %s\n", aluno->codigo, aluno->nome);
                aluno = aluno->prox;
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

void alunos_em_mais_de_uma_turma(Header h) { // 11
    if (h.s_qClass < 2) {
        printf("E necessário ao menos duas turmas para essa verificacao.\n");
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

            int contador = 0;

            for (int j = 0; j < h.s_qClass; j++) {
                if (i == j) continue;

                a2 = h.turma[j].alunos;
                while (a2 != NULL) {
                    if (a1->codigo == a2->codigo) {
                        contador++;
                        break;
                    }
                    a2 = a2->prox;
                }
            }

            // Se tem +1 turma e nao foi listado
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

void remover_aluno_do_grupo(Header *h) { //08
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

    consultar_alunos_dos_grupos_de_uma_turma(h,turmaIndex); // Mostra os grupos e alunos

    
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

void remover_turma(Header *h) { // 02
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

    int i;
    // Deslocar as turmas para seguir sequencia
    for (i = turmaIndex; i < h->s_qClass - 1; i++) {
        h->turma[i] = h->turma[i + 1];
    }
    
    h->turma = realloc(h->turma, (h->s_qClass - 1) * sizeof(Turma));
    h->s_qClass--;

    printf("Turma removida com sucesso.\n");
}

void listar_alunos_sem_grupo(Header* h) { // 10
    if (h->s_qClass == 0) {
        printf("Nenhuma turma cadastrada.\n");
        return;
    }

    int turmaIndex;
    int estaEmGrupo;
    int encontrou = 0;
    Turma *turmaAtual = NULL;
    Aluno *aluno = NULL;
    Grupo *grupo = NULL;
    Aluno *alunoGrupo = NULL;
    
    do {
        listar_turmas(*h);
        printf("Digite o numero da turma para verificar: ");
        scanf("%d", &turmaIndex);
        turmaIndex--;
    } while (turmaIndex < 0 || turmaIndex >= h->s_qClass);

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

void alunos_em_apenas_uma_turma(Header h) { // 12
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

// ---------- //

void inicioProg(Header* sistema) {
    printf("-------------------\n");
    printf("Compilando informacoes...\n");
    //pre-carrega as turmas
    incluir_nova_turma(sistema, "Turma 1");
    incluir_nova_turma(sistema, "Turma 2");
    incluir_nova_turma(sistema, "Turma 3");
    incluir_nova_turma(sistema, "Turma da monica");
    incluir_nova_turma(sistema, "Turma do bairro");
    printf("--- Turmas incluidas ---\n");
    //pre-carrega os alunos
    incluir_novo_aluno(sistema, 123, "Eric Salvi", 1);
    incluir_novo_aluno(sistema, 123, "Eric Salvi", 4);
    incluir_novo_aluno(sistema, 123, "Eric Salvi", 3);
    incluir_novo_aluno(sistema, 124, "Gustavo Quadri", 1);
    incluir_novo_aluno(sistema, 124, "Gustavo Quadri", 2);
    incluir_novo_aluno(sistema, 124, "Gustavo Quadri", 3);
    incluir_novo_aluno(sistema, 125, "Lucas Almeida", 2);
    incluir_novo_aluno(sistema, 126, "Emerson Oliveira", 3);
    incluir_novo_aluno(sistema, 126, "Emerson Oliveira", 1);
    incluir_novo_aluno(sistema, 127, "Andressa Campos", 3);
    incluir_novo_aluno(sistema, 127, "Andressa Campos", 2);
    incluir_novo_aluno(sistema, 128, "Ana Beatriz", 2);
    incluir_novo_aluno(sistema, 129, "Gabriel Silva", 1);
    incluir_novo_aluno(sistema, 129, "Gabriel Silva", 4);
    incluir_novo_aluno(sistema, 130, "Lucas Santos", 2);
    incluir_novo_aluno(sistema, 131, "Guilherme Almeida", 3);
    incluir_novo_aluno(sistema, 132, "Ana Clara", 1);
    incluir_novo_aluno(sistema, 133, "Mariana Oliveira", 2);
    incluir_novo_aluno(sistema, 133, "Mariana Oliveira", 3);
    incluir_novo_aluno(sistema, 134, "Pedro Henrique", 3);
    incluir_novo_aluno(sistema, 135, "Joao Pedro", 1);
    incluir_novo_aluno(sistema, 136, "Ana Laura", 3);
    incluir_novo_aluno(sistema, 137, "Gabriel Ferreira", 2);
    incluir_novo_aluno(sistema, 138, "Isabella Costa", 1);
    incluir_novo_aluno(sistema, 139, "Rafael Lima", 2);
    incluir_novo_aluno(sistema, 139, "Rafael Lima", 4);
    incluir_novo_aluno(sistema, 140, "Luana Martins", 3);
    incluir_novo_aluno(sistema, 141, "Felipe Souza", 1);
    incluir_novo_aluno(sistema, 142, "Bianca Rocha", 2);
    incluir_novo_aluno(sistema, 143, "Matheus Oliveira", 3);
    incluir_novo_aluno(sistema, 144, "Juliana Santos", 1);
    incluir_novo_aluno(sistema, 144, "Juliana Santos", 4);
    incluir_novo_aluno(sistema, 145, "Fernanda Almeida", 2);
    incluir_novo_aluno(sistema, 146, "Thiago Pereira", 3);
    incluir_novo_aluno(sistema, 147, "Larissa Costa", 1);
    incluir_novo_aluno(sistema, 148, "Vinicius Lima", 2);
    incluir_novo_aluno(sistema, 148, "Vinicius Lima", 4);
    incluir_novo_aluno(sistema, 149, "Amanda Martins", 3);
    incluir_novo_aluno(sistema, 150, "Lucas Ferreira", 1);
    printf("--- Alunos incluidos ---\n");
    //pre-carrega os alunos e grupos
    incluir_aluno_no_grupo_de_uma_turma(sistema, 1, 123, 1); 
    incluir_aluno_no_grupo_de_uma_turma(sistema, 1, 124, 1);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 2, 125, 2); 
    incluir_aluno_no_grupo_de_uma_turma(sistema, 3, 126, 2); 
    incluir_aluno_no_grupo_de_uma_turma(sistema, 3, 127, 3); 
    incluir_aluno_no_grupo_de_uma_turma(sistema, 2, 128, 3);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 1, 129, 2);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 2, 130, 1);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 3, 131, 2);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 1, 132, 3);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 2, 133, 1);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 3, 134, 2);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 1, 135, 3);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 3, 136, 1);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 2, 137, 2);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 1, 138, 3);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 2, 139, 1);
    incluir_aluno_no_grupo_de_uma_turma(sistema, 3, 140, 2);
    printf("--- Grupos incluidos ---\n");
    printf("Informacoes incluidas com sucesso.\n");
    printf("-------------------\n");
}

void menu(Header* sistema) { //menu de opções para o usuario
    int opcao;
    printf("\n--- Menu ---\n");
    printf("1.  Incluir turma\n");
    printf("2.  Remover turma\n"); 
    printf("3.  Listar turmas\n");

    printf("4.  Incluir aluno\n");
    printf("5.  Remover aluno\n"); 
    printf("6.  Listar alunos\n");

    printf("7.  Incluir aluno no grupo\n");
    printf("8.  Remover aluno de um grupo\n"); 
    printf("9.  Consultar alunos dos grupos de uma turma\n");

    printf("10. Alunos sem grupo\n"); 
    printf("11. Alunos em mais de uma turma\n"); 
    printf("12. Alunos em apenas uma turma\n"); 

    printf("\n0. Sair\n");

    do{
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado
    }while(opcao < 0 || opcao > 12);

    switch (opcao) {
        case 1:
            incluir_nova_turma(sistema, "");
            break;
        case 2:
            remover_turma(sistema);
            break;
        case 3:
            listar_turmas(*sistema);
            break;
        case 4:
            incluir_novo_aluno(sistema, 0, "", 0);
            break;
        case 5:
            remover_aluno(sistema);
            break;
        case 6:
            listar_alunos(*sistema, 0);
            break;
        case 7:
            incluir_aluno_no_grupo_de_uma_turma(sistema,0,0,0);
            break;
        case 8:
            remover_aluno_do_grupo(sistema);
            break;
        case 9:
            consultar_alunos_dos_grupos_de_uma_turma(sistema,0);
            break;
        case 10:
            listar_alunos_sem_grupo(sistema);
            break;
        case 11:
            alunos_em_mais_de_uma_turma(*sistema);
            break;
        case 12:
            alunos_em_apenas_uma_turma(*sistema);
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
