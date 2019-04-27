#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 50

void sayHiMrMeeseek(){
	printf("Hi, I'm Mr Meeseeks! Look at Meeeee! (pid: %d, ppid: %d)\n", getpid(), getppid());
}

void giveResultMrMeeseek(){
	printf("Hi, I'm Mr Meeseeks! I finished the JOB! See ya! I'm the Meeseeks (pid: %d, ppid: %d)\n", getpid(), getppid());
}

void sayErrorMrMeeseek(){
	printf("Sorry, there was with the task!!!, See ya! I'm the Meeseeks (pid: %d, ppid: %d)\n", getpid(), getppid());
}

int executeAnotherProgram(char pprogramName[]){
	return system(pprogramName);
}

void makeOperation(int poperating1, char poperator, int poperating2){
	if ('+'==poperator){
		printf ("El resultado de la operación es: %d\n", (poperating1 + poperating2));
	}else if ('-'==poperator){
		printf ("El resultado de la operación es: %d\n", poperating1 - poperating2);
	}else if ('*'==poperator){
		printf ("El resultado de la operación es: %d\n", poperating1 * poperating2);
	}else if (('/'==poperator) && (poperating2 != 0)){
		printf ("El resultado de la operación es: %f\n", (poperating1+0.0) / poperating2);
	}else
		printf("Error el divisor es igual a cero, por lo que no se puede llevar acabo la operacion");
}

int getHardness(int plength){
	int hardness = 100-(5*plength/3);
	return rand() % 1 + hardness;
}

int generatePos(){
	int total = 0;
	for (int c = 1; c <= 10; c++){
		total += rand() % 101;
	}
	return total/10;
}

int solveTask(int phardness){
	float probability;
	int achieve;
	
	if (phardness > 85)
		probability = 100;
	else if (phardness >45)
		probability = ((float)phardness/40)*100;
	else
		probability = ((float)phardness/45)*100;
	
	return probability-generatePos();
}

int getAmountMeeseeksCase1(){
	return rand() % 1 + 3;
}

int getAmountMeeseeksCase2(int phardness){
	return rand() % 3 + (100 - phardness);
}

int goDownHardness(int pamountMeeseeks, int phardness){
	int new = rand() % (pamountMeeseeks / phardness) + pamountMeeseeks;
	return phardness + new;
}

void zeroHardness(){
	printf("Oh no!, I can't do it, this task is imposible");
	printf("NOOOOOOOOOOOO!!! I don't want to stay here, please kill meeeeeee");
	alarm(300);
}

void makeTask(int phardnessTask, char ptask[]){
	if (phardnessTask == 0)
		zeroHardness();
	else if ((phardnessTask > 0) && (phardnessTask <= 45)){
		pid_t pid;
		pid = fork();
		// cambiar esto
	}else if ((phardnessTask > 45)  && (phardnessTask <= 85)){
		pid_t pid;
		pid = fork();
		// cambiar esto
	}else if ((phardnessTask > 85) && (phardnessTask <= 100)){
		pid_t pid;
		pid = fork();
		// cambiar esto
	}else
		printf("La dificultad ingresada no es válida por lo cual no es posible realizar la tarea\n");
}

//para usar semaforos su usa sem_t sem

void menu(){
	char option;
	int pipe[2]; //tubería
	
	printf("Mrs. Meeseeks Box cargando...\n");
	printf("Mrs. Meeseeks Box cargada\n");
    while(1) {
		printf("Bienvenido usuario, por favor elegí una opción de las mostradas a continuación:\n");
		printf("1-Realizar una petición\n");
		printf("2-Realizar operación aritmetica\n");
		printf("3-Ejecutar programa externo\n");
		printf("4-Salir\n");
		printf("Por favor introduzca el numero de la opción elegida: \n");
		scanf("%c", &option);
		if (option == '1'){
			char task[SIZE];
			char answer;
			int hardness;
			printf("Por favor introduzca la tarea que desea ejecutar\n");
			scanf("%50s",task);
			getchar();
			printf("¿Desea introducir la dificultad de la tarea? S/N \n");
			scanf("%c",&answer);
			getchar();
			if (answer == 'S'){
				printf("Por favor introduzca el valor de dificultad de la tarea\n");
				scanf("%d",&hardness);
				getchar();
			}else{
				int length = strlen(task);
				hardness = getHardness(length);
			}
			makeTask(hardness, task);
		}else if (option == '2'){
			pid_t pid;
			int operating1, operating2;
			char operator;
			printf("Por favor introduzca la operacion aritmetica que desea realizar: \n");
			scanf("%d %c %d",&operating1,&operator,&operating2);
			getchar();
			pid = fork();
			if (pid < 0)
				printf("Error al crear un Mr Meeseeks\n");
			else if (pid==0){
				sayHiMrMeeseek();
				makeOperation(operating1,operator,operating2);
				giveResultMrMeeseek();
				exit(0);
			}else
				wait(NULL);
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
