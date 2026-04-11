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

void destroy(System* s);
void initsys(System* s);
bool memchk(unsigned char* mem1,char* mem2,int buf1,int buf2,int n);
void memsee(System* s,int n,int reserved_start,int reserved_end);
void read_script(char* name);
void registersee(System* s);
void rand_roast();

#endif
