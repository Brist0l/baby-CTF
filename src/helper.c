#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#include "cpu.h"
#include "helper.h"

void destroy(System *s){
	free(s->registers);
	free(s->registers_prev);
	free(s->memory);
	free(s->memory_prev);
	free(s);
}

void initsys(System *s){
	srand(time(NULL));

	s->registers = malloc(sizeof(Registers));
	s->registers_prev = malloc(sizeof(Registers));
	s->memory = (unsigned char*) malloc(sizeof(unsigned char) *  MEM_SIZE);
	s->memory_prev = (unsigned char*) malloc(sizeof(unsigned char) * MEM_SIZE);

	// set memory to random variables
	for(int i = 0; i < MEM_SIZE; i++)
		s->memory[i] = rand() % 0xff;
	//memset(memory,0,MEM_SIZE);
	memset(s->registers,0,sizeof(Registers));
	memcpy(s->memory_prev,s->memory,MEM_SIZE);
	memcpy(s->registers_prev,s->registers,sizeof(Registers));
}

bool memchk(unsigned char* mem1,char* mem2,int buf1,int buf2,int n){
	for(int i = 0;i < n;i++){
		//printf("memory : 0x%x at 0x%x\n",*(mem1 + buf1 + i),buf1 + i);
		//printf("string : 0x%x at 0x%x\n",*(mem2 + buf2 + i),buf2 + i);
		if(*(mem1 + buf1 + i) != *(mem2 + buf2 + i))
			return false;
	}
	return true;
}

void memsee(System* s,int n,int reserved_start,int reserved_end){
	int a = 0;
	int j = 2;
	printf("\nMemory (in big endian):\n");

	for(int i = 0;i < n;i++){
		// memory locations
		if(a == 0){
  			printf(ANSI_COLOR_BLUE);
			printf("0x%.2x =>\t",i);
  			printf(ANSI_COLOR_RESET);
		}

		// converting byte repr to 2 bytes repr
		if(j == 2){
			if(i <= reserved_end && i >= reserved_start)
  				printf(ANSI_COLOR_RED);
			else
  				printf(ANSI_COLOR_GREEN);
			printf(" 0x");
  			printf(ANSI_COLOR_RESET);
			j = 0;
		}

		if(i <= reserved_end && i >= reserved_start){
  			printf(ANSI_COLOR_RED);
			printf("**");
  			printf(ANSI_COLOR_RESET);
		}
		else{
  			printf(ANSI_COLOR_GREEN);
			if(*(s->memory + i) ^ (*(s->memory_prev + i)))
  				printf(ANSI_COLOR_YELLOW);
			printf("%.2x",*(s->memory + i));
  			printf(ANSI_COLOR_RESET);
		}

		j++;
		a++;

		if(a == 16){
			printf("\n");
			a = 0;
		}
	}

	memcpy(s->memory_prev,s->memory,MEM_SIZE);
	printf("\n");
}

void read_script(char* name){
	FILE* file;
	char c;

	file = fopen(name,"r");

	while((c = fgetc(file)) != EOF)
		printf("%c",c);

	fclose(file);
}

void rand_roast(){
	srand(time(NULL));

	FILE* file;
	char c[10][200];
	int line = 0;
	int i = 0;

	file = fopen("src/story/roast.txt","r");

	while((c[line][i] = fgetc(file)) != EOF){
		//printf("Line count : %d\n",line);
		//printf("Char count : %d\n",i);
		if(c[line][i] == '\n'){
			line++;
			i = 0;
		}
		else
			i++;
	}

	int rand_line = rand() % line;

  	printf(ANSI_COLOR_RED);
	printf("%s",c[rand_line]);
  	printf(ANSI_COLOR_RESET);

	fclose(file);
}

void registersee(System* s){
	printf("\n");

	for(int i = 0;i < 2;i++){
  		printf(ANSI_COLOR_BLUE);
		printf("Register %d : ",i);
  		printf(ANSI_COLOR_GREEN);
		if(s->registers->V[i] ^ s->registers_prev->V[i])
  			printf(ANSI_COLOR_YELLOW);
		printf("0x%.2x\n",s->registers->V[i]);
  		printf(ANSI_COLOR_RESET);
	}

  	printf(ANSI_COLOR_BLUE);
	printf("Register IP : ");
  	printf(ANSI_COLOR_GREEN);
	if(s->registers->IP ^ s->registers_prev->IP)
  		printf(ANSI_COLOR_YELLOW);
	printf("0x%.2x\n",s->registers->IP);
  	printf(ANSI_COLOR_RESET);

	memcpy(s->registers_prev,s->registers,sizeof(Registers));
	printf("\n");
}
