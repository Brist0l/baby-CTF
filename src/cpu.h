#ifndef CPU_H
#define CPU_H

#define MEM_SIZE 128
//stack grows from lower mem address to higher mem address
#define STK_SIZE 25
#define STK_STRT (MEM_SIZE-STK_SIZE)
#define STK_END (MEM_SIZE)


#include<stdbool.h>

typedef struct _registers{
	unsigned int V[0x2];
	unsigned int IP;
	unsigned int SP;
	bool flag[0x2];
	unsigned char cache[0x5];
}Registers;

typedef struct{
	Registers *registers;
	Registers *registers_prev;
	unsigned char *memory;
	unsigned char *memory_prev;
}System;

void readinstr(System* s);

#endif
