#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 50

int executeAnotherProgram(char pprogramName[]){
    int returnValue = system(pprogramName);
	return returnValue;
}

void sayHiMrMeeseek(){
	printf("Hi, I'm Mr Meeseeks! Look at Meeeee! (pid: %d, ppid: %d)\n", getpid(), getppid());
}

void giveResultMrMeeseek(){
	printf("Hi, I'm Mr Meeseeks! I finished the JOB! See ya! I'm the Meeseeks (pid: %d, ppid: %d)\n", getpid(), getppid());
}

void sayErrorMrMeeseek(){
	printf("Sorry, there was with the task!!!, See ya! I'm the Meeseeks (pid: %d, ppid: %d)\n", getpid(), getppid());
}

void menu(){
	char option;
	
	printf("Mrs. Meeseeks Box cargando...\n");
	printf("Mrs. Meeseeks Box cargada\n");
    while(1) {
		printf("Bienvenido usuario, por favor elegí una opción de las mostradas a continuación:\n");
		printf("1-Realizar una petición\n");
		printf("2-Realizar operación aritmetica o lógica\n");
		printf("3-Ejecutar programa externo\n");
		printf("4-Salir\n");
		printf("Por favor introduzca el numero de la opción elegida: \n");
		scanf("%c", &option);
		if (option == '1'){
			continue;
		}else if (option == '2'){
			continue;
		}else if (option == '3'){
			pid_t pid;
			char program[SIZE];
			printf("Por favor introduzca el programa que desea ejecutar o bien el comando\n");
			scanf("%50s",program);
			getchar();
			pid = fork();
			if (pid < 0)
				printf("Error al crear un Mr Meeseeks\n");
			else if (pid==0){
				int value;
				sayHiMrMeeseek();
				value = executeAnotherProgram(program);
				if (value == 0)
					giveResultMrMeeseek();
				else
					sayErrorMrMeeseek();
				exit(0);
			}else
				wait(NULL);
		}else{
			printf("Fin del programa...\n");
			break;
		}
	}
}


int main() {
    menu();
    return 0;
}
