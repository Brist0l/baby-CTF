#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#include "cpu.h"
#include "helper.h"

bool memchk(unsigned char* mem1,char* mem2,int buf1,int buf2,int n){
	for(int i = 0;i < n;i++){
		//printf("memory : 0x%x at 0x%x\n",*(mem1 + buf1 + i),buf1 + i);
		//printf("string : 0x%x at 0x%x\n",*(mem2 + buf2 + i),buf2 + i);
		if(*(mem1 + buf1 + i) != *(mem2 + buf2 + i))
			return false;
	}
	return true;
}

void memsee(unsigned char* mem,int n,int reserved_start,int reserved_end,unsigned char* prev_mem){
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
			if(*(mem + i) ^ (*(prev_mem + i)))
  				printf(ANSI_COLOR_YELLOW);
			printf("%.2x",*(mem + i));
  			printf(ANSI_COLOR_RESET);
		}

		j++;
		a++;

		if(a == 16){
			printf("\n");
			a = 0;
		}
	}

	memcpy(prev_mem,mem,MEM_SIZE);
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

	file = fopen("roast.txt","r");

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

void registersee(Registers *r,Registers* prev_r){
	printf("\n");

	for(int i = 0;i < 2;i++){
  		printf(ANSI_COLOR_BLUE);
		printf("Register %d : ",i);
  		printf(ANSI_COLOR_GREEN);
		if(r->V[i] ^ prev_r->V[i])
  			printf(ANSI_COLOR_YELLOW);
		printf("0x%.2x\n",r->V[i]);
  		printf(ANSI_COLOR_RESET);
	}

  	printf(ANSI_COLOR_BLUE);
	printf("Register IP : ");
  	printf(ANSI_COLOR_GREEN);
	if(r->IP ^ prev_r->IP)
  		printf(ANSI_COLOR_YELLOW);
	printf("0x%.2x\n",r->IP);
  	printf(ANSI_COLOR_RESET);

	memcpy(prev_r,r,sizeof(Registers));
	printf("\n");
}
