/*
TRABALHO 1: Implementação de um Shell
-------------------------------------
Aluno: André Luis Gonçalves Bien
    RA: 111829 Turma: Integral
Aluno: Andrew Medeiros de Campos
    RA: 111775 Turma: Noturno
Aluno: Washington Holanda de Oliveira
    RA: 112268 Turma: Noturno
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define TRUE 1
#define FALSE 0
#define TAM_LINHA 30 // tamanho máximo dos comandos

int main(){
    char **comando, in[100], *token;
    int **fd; // descritor de arquivos
    int cmd_div[30]; // vetor com a posição de cada pipe
    int tam = 0; // quantidade de linhas da matriz
    int i,j; // contador
    int flag_exit = FALSE; // flag de controle
    pid_t child; // processo filho

    scanf("%[^\n]s",in); // scanf() guarda a linha toda na string in
    token = strtok(in," "); // tokeniza a entrada usando espaço como separador
    comando = (char**) calloc(TAM_LINHA*sizeof(char*), 1);

    // insere cada palavra em uma linha da matriz de comandos
    i = 0;
    j = 1;
    cmd_div[0]=0;
    while(token != NULL){
        comando[i] = (char*) calloc(strlen(token)*sizeof(char*), 1);
        // parser para encontar os pipes
        if(strcmp(token,"|") == 0){
            cmd_div[j] = i+1;
            comando[i] = NULL; // o pipe precisa ser null para o execvp() saber onde parar de executar o comando
            j++;
        }else{
            strcpy(comando[i],token); // copia palavra do comando para a matriz
        }
        i++;
        tam++;
        token = strtok(NULL," ");
    }

    // alocação do descritor de arquivos
    fd = malloc(j*sizeof(int*));
    for(i=0;i<j;i++){
        fd[i] = malloc(2*sizeof(int));
        pipe(fd[i]); // cria um pipe para cada descritor de arquivos
    }

    for(i=0;i<j;i++){ // j guarda a quantiade de forks necessários
        child = fork();
        if(child == 0){
            int FILE_out, FILE_in; // arquivos para redirecionamento de entrada ou saida
            int indice = cmd_div[i];
            if(i != 0){
                close(fd[i-1][1]); // fecha o descritor de escrita
                dup2(fd[i-1][0], STDIN_FILENO); // muda o descritor de leitura para stdin
				close(fd[i-1][0]); // fecha o descritor de leitura
            }
            if(i != j){
                close(fd[i][0]); // fecha o descritor de leitura
				dup2(fd[i][1], STDOUT_FILENO); // muda o descritor de escrita para stdout
				close(fd[i][1]); // fecha o descritor de escrita
            }
            printf("Comando: %s\n",comando[indice]);
            execvp(comando[indice],&comando[indice]);

        }else{
            int status;
            waitpid(-1,&status,0); // pai espera ate o fim da execussão dos filhos
        }
    }
    return 0;
}