#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include "cpu.h"
#include "helper.h"

int main(){
	srand(time(NULL));

	Registers *registers = malloc(sizeof(Registers));
	Registers *registers_prev = malloc(sizeof(Registers));
	unsigned char memory[MEM_SIZE];
	unsigned char* memory_prev = (unsigned char*) malloc(sizeof(unsigned char) * MEM_SIZE);

	read_script("script.txt");

	// set memory to random variables
	for(int i = 0; i < MEM_SIZE; i++)
		memory[i] = rand() % 0xff;
	//memset(memory,0,MEM_SIZE);
	memset(registers,0,sizeof(Registers));
	memcpy(memory_prev,memory,MEM_SIZE);
	memcpy(registers_prev,registers,sizeof(Registers));

	int offset = 0x10;
	int reserved_start = 0x0;
	int reserved_end = reserved_start + offset - 1;
	int magic_addr = 0x11;
	int magic_val = 0x69;
	int IP_val_addr = 0x14;

	memcpy(memory,"\x41\x01\x31\x41\x00\x03\x69",offset);

	memsee(memory,MEM_SIZE,reserved_start,reserved_end,memory_prev);
	registersee(registers,registers_prev);

	printf("\n=>");
	char inp[MEM_SIZE];
	scanf("%s",inp);

	memory[offset] = inp[0];
	//for(int i = 0; i < MEM_SIZE; i++)
		//printf("=> %x\n", inp[i]);
	printf("[*] Writing %d bytes.\n",memory[offset]);
	memcpy(memory + offset + 1,inp + 1,memory[offset]);

	memsee(memory,MEM_SIZE,reserved_start,reserved_end,memory_prev);
	//registersee(registers,registers_prev);

	if(memory[magic_addr] + memory[magic_addr + 1] + memory[magic_addr + 2] == magic_val){
	//if(memchk(memory,"\x69\x69",magic_addr,0,2)){
		printf("[*] Registers unlocked.\n");

		if(memory[IP_val_addr] < 0x10 || memory[IP_val_addr] > 0x16){
			rand_roast();
  			printf(ANSI_COLOR_BLUE);
			printf("Hint : ");
  			printf(ANSI_COLOR_RESET);
			printf("You can't \"directly\" access 0x%.2x, you jump beyond 0x15 or below 0x10\n",memory[IP_val_addr]);
			free(registers_prev);
			free(memory_prev);
			exit(0);
		}

		printf("[*] Randomising Register values.\n");

		registers->IP = memory[IP_val_addr] + (rand() % 0x30);
		registers->V[0] = (rand() % 0x50);
		registers->V[1] = (rand() % 0x50);

		registersee(registers,registers_prev);

		//printf("Reading instructions\n");
		readinstr(registers,memory);
	}
	else{
		rand_roast();
		printf("[*] Current sum: 0x%.2x\n",memory[IP_val_addr] + memory[IP_val_addr + 1] + memory[IP_val_addr +2]);
		printf("[*] Exptected sum: 0x%.2x\n",magic_val);
  		printf(ANSI_COLOR_BLUE);
		printf("Hint : ");
  		printf(ANSI_COLOR_RESET);
		printf("Register changing values not set\n");
		free(registers_prev);
		free(memory_prev);
		exit(0);
	}

}
