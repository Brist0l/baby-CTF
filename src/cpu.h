#ifndef CPU_H
#define CPU_H

#define MEM_SIZE 128

#include<stdbool.h>

typedef struct _registers{
	unsigned int V[0x2];
	unsigned int IP;
	bool flag[0x2];
}Registers;

void readinstr(Registers *r,unsigned char* memory);

#endif
