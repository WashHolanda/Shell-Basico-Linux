/*
Aluno: André Luis Gonçalves Bien
    RA: 111829 Turma: Integral
Aluno: Andrew Medeiros de Campos
    RA: 111775 Turma: Noturno
Aluno: Washington Holanda de Oliveira
    RA: 112268 Turma: Noturno
TRABALHO 1: Implementação de um Shell
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
#define TAM_LINHA 30 // tamanho máximo da linha nos 

int main(){
    char **comando, in[100], *token;
    int cmd_div[30]; // vetor com a posição de cada pipe
    int tam = 0; // quantidade de linhas da matriz
    int i,j; // contador
    int flag_exit = FALSE; // flag de controle
    pid_t pid;

    while(flag_exit == FALSE){ // executa o shell enquanto não é inserido o comando exit

        scanf("%[^\n]s",in); // scanf() guarda a linha toda na string in
        token = strtok(in," "); // tokeniza a entrada usando espaço como separador
        comando = (char**) calloc(TAM_LINHA*sizeof(char*), 1);

        // insere cada palavra em uma linha da matriz de comandos
        i = 0;
        j = 0;
        while(token != NULL){
            comando[i] = (char*) calloc(strlen(token)*sizeof(char**), 1);
            if(strcmp(token,"|") == 0){
                cmd_div[j] = i;
                strcpy(comando[i],NULL);
                i++;
                j++;
            }else{
                strcpy(comando[i],token);
                i++;
            }
            tam++;
            token = strtok(NULL," ");
        }
        // parser para encontar os pipes
        j=0;
        for(i=0;i<tam;i++){
        }
        //TESTE ------------
        printf("IMPRIME\n");
        for(i=0;i<tam;i++){
            printf("%s\n",comando[i]);
        }

        // processa os comandos
        pid = fork(); // cria processo filho
        if(pid == 0){ // confere se o processo é filho
            
        }
        return 0;
    }
}