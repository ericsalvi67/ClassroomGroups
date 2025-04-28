#include <stdio.h>
#include <stdlib.h>

// puxando as funcoes
#include "estruturas.h"
#include "turma.h"
#include "aluno.h"
#include "grupo.h"
#include "relatorios.h"

// menu
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
            consultar_alunos_dos_grupos_de_uma_turma(sistema, 0);
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
// inicializa turmas
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

// main
int main() {
    Header sistema;
    sistema.s_qClass = 0;
    sistema.turma = NULL;

    inicioProg(&sistema);

    while(1)
        menu(&sistema);

    return 0;
}
