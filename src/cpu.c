#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "cpu.h"
#include "helper.h"

void readinstr(System* s){
	//for(int i = 0; i < 10;i++)
		//printf("%d => 0x%.2x\n",i,*(memory + registers->IP + i));

	s->registers->flag[0] = false;
	s->registers->flag[1] = false;

	while(s->registers->IP < MEM_SIZE){
	//	printf("IP = %x and mem = %x\n",registers->IP,memory[registers->IP]);
		switch(s->memory[s->registers->IP]){

			// nop
			case 0x90:
				(s->registers->IP)++;
				break;

			//mov
			case 0x01:
				unsigned char regis = s->memory[++(s->registers->IP)];
				unsigned char val = s->memory[++(s->registers->IP)];

				if(regis < 0 || regis > 2){
					rand_roast();
					printf(ANSI_COLOR_BLUE);
					printf("Hint : ");
					printf(ANSI_COLOR_RESET);
					printf("[at 0x01,MOV]Illegal operation , there are only 2 registers!\n");
					exit(0);
				}

				s->registers->V[regis] = val;
				//printf("Register %d : %x\n",regis,registers->V[regis]);

				printf("[*] After MOV:\n");
				registersee(s);
				s->registers->IP++;
				break;

			//jmp
			case 0xff:
				unsigned char addr = s->memory[++(s->registers->IP)];

				if(addr < 0 || addr > MEM_SIZE){
					rand_roast();
					printf(ANSI_COLOR_BLUE);
					printf("Hint : ");
					printf(ANSI_COLOR_RESET);
					printf("Address out of bounds!\n");
					exit(0);
				}

				s->registers->IP = addr;
				break;

			// cmp
			case 0x41:
				if(s->registers->IP < 0x10 && s->registers->IP >= 0x0){
					unsigned char regis1 = s->memory[++(s->registers->IP)];
					unsigned char _val = s->memory[++(s->registers->IP)];

					//printf("register:0x%.2x\nval at register:0x%.2x\nval:0x%.2x\n",regis1,s->registers->V[regis1],_val);
					//printf("IP: 0x%.2x",s->registers->IP);

					if(regis1 < 0 || regis1 > 2){
						rand_roast();
						printf(ANSI_COLOR_BLUE);
						printf("Hint : ");
						printf(ANSI_COLOR_RESET);
						printf("[At 0x41, CMP]Illegal operation , there are only 2 registers!\n");
						exit(0);
					}

					if(s->registers->V[regis1] == _val)
						s->registers->flag[regis1] = true;
					else
						s->registers->flag[regis1] = false;

					if(s->registers->V[regis1] != _val)
						printf("[*] Register %d difference : 0x%.2hhx\n",regis1, s->registers->V[regis1] - _val);

						//printf("Flag of %d is %d\n",regis1,registers->flag[regis1]);
					s->registers->IP++;
					break;

				}
				else{
						rand_roast();
						printf("Instr => 0x%.2x at 0x%.2x\n",s->memory[s->registers->IP],s->registers->IP);
						printf(ANSI_COLOR_BLUE);
						printf("Hint : ");
						printf(ANSI_COLOR_RESET);
						printf("You can't run these instructions in non reserved spaces\n");
						exit(0);
					}

			// getflag
			case 0x69:
				if(s->registers->IP < 0x10 && s->registers->IP >= 0x0){
					if(s->registers->flag[0] && s->registers->flag[1]){
						read_script("src/story/ending.txt");
						unsigned char enc_flag[] = {
						    0x37, 0x27, 0x34, 0x20, 0x3b, 0x2e,
						    0x22, 0x30, 0x0a, 0x34, 0x27, 0x30,
						    0x0a, 0x3f, 0x20, 0x26, 0x21, 0x0a,
						    0x33, 0x27, 0x3c, 0x30, 0x3b, 0x31,
						    0x26, 0x28, 0x00
						};
						for (int i = 0; enc_flag[i] != 0; i++)
						    enc_flag[i] ^= 0x55;
						printf(ANSI_COLOR_MAGENTA);
						printf("\nFLAG: %s\n", enc_flag);
						printf(ANSI_COLOR_RESET);
					}
					else
						printf("NO FLAG\n");
					exit(0);
				}
				else{
					rand_roast();
					printf("Instr => 0x%.2x at 0x%.2x\n",s->memory[s->registers->IP],s->registers->IP);
					printf(ANSI_COLOR_BLUE);
					printf("Hint : ");
					printf(ANSI_COLOR_RESET);

					printf("You can't run these instructions in non reserved spaces\n");
					exit(0);
					}

				break;

			default:
				rand_roast();
				printf(ANSI_COLOR_BLUE);
				printf("Hint : ");
				printf(ANSI_COLOR_RESET);
				printf("INSTRUCTION NOT DEFINED\n");
				exit(0);
		}
	}
}
