#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#include "cpu.h"
#include "helper.h"

int main(){
	System* s = malloc(sizeof(System));
	initsys(s);

	read_script("src/story/script.txt");

	int offset = 0x10;
	int reserved_start = 0x0;
	int reserved_end = reserved_start + offset - 1;
	int magic_sum_addr = 0x11;
	int magic_val = 0x69;
	int IP_val_addr = 0x14;

	char* instrs = "\x41\x01\x31\x41\x00\x03\x69";

	memcpy(s->memory + reserved_start,instrs,sizeof(*instrs)*8);

	//memcpy(s->memory + reserved_start,"\x41\x01\x31\x41\x00\x03\x69",8);

	memsee(s,MEM_SIZE,reserved_start,reserved_end);
	registersee(s);

	printf("\n=>");
	char inp[MEM_SIZE];
	scanf("%s",inp);

	s->memory[offset] = inp[0];
	//for(int i = 0; i < MEM_SIZE; i++)
		//printf("=> %x\n", inp[i]);
	printf("[*] Writing %d bytes.\n",s->memory[offset]);
	memcpy(s->memory + offset + 1,inp + 1,s->memory[offset]);

	memsee(s,MEM_SIZE,reserved_start,reserved_end);
	//registersee(registers,registers_prev);

	if(s->memory[magic_sum_addr] + s->memory[magic_sum_addr + 1] + s->memory[magic_sum_addr + 2] == magic_val){
	//if(memchk(memory,"\x69\x69",magic_sum_addr,0,2)){
		printf("[*] Registers unlocked.\n");

		if(s->memory[IP_val_addr] < 0x10 || s->memory[IP_val_addr] > 0x16){
			rand_roast();
  			printf(ANSI_COLOR_BLUE);
			printf("Hint : ");
  			printf(ANSI_COLOR_RESET);
			printf("You can't \"directly\" access 0x%.2x, you must jump beyond 0x15 or below 0x10\n",s->memory[IP_val_addr]);
			free(s->registers_prev);
			free(s->memory_prev);
			exit(0);
		}

		printf("[*] Randomising Register values.\n");

		s->registers->IP = s->memory[IP_val_addr] + (rand() % 0x30);
		s->registers->V[0] = (rand() % 0x50);
		s->registers->V[1] = (rand() % 0x50);

		registersee(s);

		//printf("Reading instructions\n");
		readinstr(s);
	}
	else{
		rand_roast();
		printf("[*] Current sum: 0x%.2x\n",s->memory[magic_sum_addr] + s->memory[magic_sum_addr + 1] + s->memory[magic_sum_addr +2]);
		printf("[*] Exptected sum: 0x%.2x\n",magic_val);
  		printf(ANSI_COLOR_BLUE);
		printf("Hint : ");
  		printf(ANSI_COLOR_RESET);
		printf("Register changing values not set\n");
		free(s->registers_prev);
		free(s->memory_prev);
		exit(0);
	}

}
