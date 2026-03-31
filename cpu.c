#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "cpu.h"
#include "helper.h"

void readinstr(Registers *r,unsigned char* memory){
	//for(int i = 0; i < 10;i++)
		//printf("%d => 0x%.2x\n",i,*(memory + r->IP + i));

	r->flag[0] = false;
	r->flag[1] = false;

	while(r->IP < MEM_SIZE){
	//	printf("IP = %x and mem = %x\n",r->IP,memory[r->IP]);
		switch(memory[r->IP]){

			// nop
			case 0x90:
				r->IP++;
				break;

			//mov
			case 0x01:
				unsigned char regis = memory[++r->IP];
				unsigned char val = memory[++r->IP];

				if(regis < 0 || regis > 2){
					rand_roast();
					printf(ANSI_COLOR_BLUE);
					printf("Hint : ");
					printf(ANSI_COLOR_RESET);
					printf("Illegal operation , there are only 2 registers!\n");
					exit(0);
				}

				r->V[regis] = val;
				//printf("Register %d : %x\n",regis,r->V[regis]);

				printf("[*] After MOV:\n");
				registersee(r,r);
				r->IP++;
				break;

			//jmp
			case 0xff:
				unsigned char addr = memory[++r->IP];

				if(addr < 0 || addr > MEM_SIZE){
					rand_roast();
					printf(ANSI_COLOR_BLUE);
					printf("Hint : ");
					printf(ANSI_COLOR_RESET);
					printf("Address out of bounds!\n");
					exit(0);
				}

				r->IP = addr;
				break;

			// cmp
			case 0x41:
				if(r->IP < 0x10 && r->IP >= 0x0){
					unsigned char regis1 = memory[++r->IP];
					unsigned char _val = memory[++r->IP];

					//printf("register:%d\nval at register:%x\nval:%x\n",regis1,r->V[regis1],_val);

					if(regis1 < 0 || regis1 > 2){
						rand_roast();
						printf(ANSI_COLOR_BLUE);
						printf("Hint : ");
						printf(ANSI_COLOR_RESET);
						printf("Illegal operation , there are only 2 registers!\n");
						exit(0);
					}

					if(r->V[regis1] == _val)
						r->flag[regis1] = true;
					else
						r->flag[regis1] = false;

					if(r->V[regis1] != _val)
						printf("[*] Register %d difference : 0x%.2hhx\n",regis1, r->V[regis1] - _val);

					//printf("Flag of %d is %d\n",regis1,r->flag[regis1]);
					r->IP++;
					break;
					}
					else{
						rand_roast();
						printf("Instr => 0x%.2x at 0x%.2x\n",memory[r->IP],r->IP);
						printf(ANSI_COLOR_BLUE);
						printf("Hint : ");
						printf(ANSI_COLOR_RESET);
						printf("You can't run these instructions in non reserved spaces\n");
						exit(0);
					}

			// getflag
			case 0x69:
				if(r->IP < 0x10 && r->IP >= 0x0){
					if(r->flag[0] && r->flag[1]){
						read_script("ending.txt");
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
					printf("Instr => 0x%.2x at 0x%.2x\n",memory[r->IP],r->IP);
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
