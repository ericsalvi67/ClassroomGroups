# Trabalho de Implementação de Algoritmos e Estruturas de Dados: Listas

## Apresentação:  
O trabalho será apresentado para a professora, em aula. Para a apresentação, se 
o trabalho for feito em dupla ambos os participantes devem estar presentes e participar da 
explicação sobre a implementação realizada.
 Até o dia da apresentação, fazer upload do trabalho na tarefa correspondente no 
AVA do trabalho: 
- código-fonte da implementação, 
- explicação textual e uma figura com a estrutura de dados utilizada (como é cada 
lista, simples ou dupla; como as listas se relacionam, se foram incluídas 
informações ou estruturas adicionais dizer quais são.

 ### Descrição do problema:  
 
 Uma instituição de ensino superior tem várias turmas de alunos, para as diferentes 
disciplinas. Para realização de tarefas, os alunos são organizados em grupos, sendo que 
cada turma tem todos os seus alunos inseridos em grupos. Cada aluno, em uma turma, 
só pode estar um um grupo. É possível um mesmo aluno estar em mais de uma turma, e 
por consequência em mais de um grupo (desde que grupos vinculados a turmas 
diferentes).  
 O trabalho é definição da estrutura de dados para suportar turmas e grupos, e a 
implementação de um sistema de grupos, que vai dar suporte à organização dos 
alunos de cada turma em grupos. Para tanto, vai ser necessário implementar :
 - uma lista de turmas (para cada turma: código da turma, inicio da lista de alunos, 
início da lista de grupos, ...)  
 - uma lista de alunos por turma (lista de nomes de alunos, pode ter código de cada 
aluno, etc)  
 - uma lista de grupos por turma (cada grupo contém código da turma, número do 
grupo, alunos daquela turma, ...)  
 Só podem estar nos grupos de uma turma os alunos daquela turma.  
 
 ### Representação dos dados:  
 
Usar listas encadeadas (simples ou duplas) para listas de alunos e de grupos. Para a lista 
de turmas, pode ser utilizado vetor ou listaa encadeada.
 Pode ser definido para cada turma o máximo de alunos por grupo, ou essa pode ser uma 
definição padrão do programa.  

 ### Implementação:  
 
 Pode ser implementado em C, C++, C#, Java ou Python, desde que as referências 
entre os nodos sejam manipuladas explicitamente pelo programa (não pode usar classe, 
método ou função pronta da linguagem para listas encadeadas).
 Considere utilizar headers e outras estruturas auxiliares.
 A interface pode ser bem simples (textual), o importante é que as operações 
funcionem.
 Algumas operações básicas a serem oferecidas pelo programa (fazer um menu de 
opções, uma opção para cada operação):
 1) Incluir nova turma  
 2) Remover turma (remover todos os alunos da turma, e todos os grupos da turma)  
 3) Consultar turmas: escrever na tela as turmas existentes   
4) Incluir aluno na lista de alunos de uma turma  
 5) Remover aluno da lista de alunos de uma turma (se ele estiver em algum grupo 
daquela turma, remover do grupo)  
 6) Consultar alunos: escrever na tela a lista de alunos de uma turma  
 7) Incluir aluno no grupo de uma turma (controlar para que cada aluno só esteja 
em um grupo daquela turma)  
 8) Remover aluno do grupo de uma turma (remover só du grupo, não da turma)  
 9) Consultar alunos dos grupos de uma turma (mostrar cada grupo e alunos que 
fazem parte dele)  
 10) Alunos sem grupo: para uma turma informada, apresentar os nomes dos alunos 
sem grupo   
 11) Alunos em mais de uma turma: apresentar os nomes dos alunos  que estão em 
mais de uma turma   
 12) Alunos em apenas uma turma: apresentar os nomes dos alunos  que estão em 
apenas uma turma
 13) Outras operações (a seu critério), como: quantidade de grupos por turma, total 
geral de alunos (descartar as repetições), turma com mais grupos, etc
 Pode ter uma operação automática de divisão dos alunos de uma turma em 
grupos: informa-se o tamanho do grupo, e faz-se a divisão por algum critério. Talvez um 
grupo da turma fique com menos alunos do que o tamanho informado
