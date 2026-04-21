#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

#include "cpu.h"
#include "helper.h"

/* ISA:
 * 0x90 => NOP
 * 0x01 => MOV
 * 0xff => JMP
 * 0x41 => CMP
 * 0x69 => GETFLG
 * 0xca => CALL
 * 0x4e => RET
 * 0x3e => GETINP
 * 0xe4 => EXT
 * 0x1a => IGNR
 */


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

	s->registers->SP = STK_STRT;
	s->registers->flag[0] = false;
	s->registers->flag[1] = false;
}

void readinstr(System* s){
	//for(int i = 0; i < 10;i++)
		//printf("%d => 0x%.2x\n",i,*(memory + registers->IP + i));

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
						read_script("src/story/ending_baby2.txt");
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

			// call
			case 0xca:
				unsigned char func_addr = s->memory[++(s->registers->IP)];

				if(func_addr < 0 || func_addr > MEM_SIZE){
					rand_roast();
					printf(ANSI_COLOR_BLUE);
					printf("Hint : ");
					printf(ANSI_COLOR_RESET);
					printf("[0xca CALL]Address out of bounds!\n");
					exit(0);
				}

				int x = (s->registers->SP)++;
				printf("x => 0x%.2x\n",x);
				s->memory[x] = ++(s->registers->IP);
				printf("Written 0x%.2x at 0x%.2x\n",--s->registers->IP,--x);
				s->registers->IP = func_addr;

				break;

			// ret
			case 0x4e:
				s->registers->IP = s->memory[--(s->registers->SP)];
				printf("Returning to 0x%.2x\n",s->registers->IP);
				break;

			// get input
			case 0x3e:
				unsigned char write_addr = s->memory[++(s->registers->IP)];
				bool new_line = false;
				printf("\n=>");

				//while(new_line == false){
					//for(int i = 0; i < 5;i++){
						//s->registers->cache[i] = getchar();
						//if(s->registers->cache[i] == '\n'){
							//new_line =true;
							//break;
						//}
					//for(int i = 0; i < 5; i++)
						//s->memory[write_addr++] = s->registers->cache[i];
				//}

				while(new_line == false){
					char i = getchar();

					if(i == '\n'){
						new_line = true;
						break;
					}

					s->memory[write_addr++] = i;
				}

				s->registers->IP++;

				break;

			// exit
			case 0xe4:
				printf("Yea , goodbye my man.\n");
				exit(0);
				break;

			//ignore flags
			case 0x1a:
				s->registers->flag[0] = true;
				s->registers->flag[1] = true;
				printf("Register flags Set !\n");
				s->registers->IP++;
				break;

			default:
				memsee(s,MEM_SIZE,0x0,0x0);
				printf("instr : 0x%.2x\n",s->memory[s->registers->IP]);
				rand_roast();
				printf(ANSI_COLOR_BLUE);
				printf("Hint : ");
				printf(ANSI_COLOR_RESET);
				printf("INSTRUCTION NOT DEFINED\n");
				exit(0);
		}
	}
}
