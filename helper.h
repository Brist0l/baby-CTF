#ifndef HELPER_H
#define HELPER_H

#include<stdbool.h>

#include"cpu.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool memchk(unsigned char* mem1,char* mem2,int buf1,int buf2,int n);
void memsee(unsigned char* mem,int n,int reserved_start,int reserved_end,unsigned char* prev_mem);
void read_script(char* name);
void registersee(Registers *r,Registers *prev_r);
void rand_roast();

#endif
