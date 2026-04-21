#include<string.h>
#include<stdlib.h>

#include "cpu.h"
#include "helper.h"

int main(){
	System* s = malloc(sizeof(System));
	initsys(s);

	//read_script("src/story/script.txt");

	int offset = 0x10;
	int reserved_start = 0x0;
	int reserved_end = reserved_start + offset - 1;

	// In reserved area:
	// CMP R1,0x31
	// CMP R0,0x03
	// GETFLG

	char* flag_instrs = "\x1a\x69";
	//printf("string len:%ld\n",strlen(flag_instrs));

	memcpy(s->memory + reserved_start,flag_instrs,sizeof(*flag_instrs)*5);

	//memcpy(s->memory + reserved_start,"\x41\x01\x31\x41\x00\x03\x69",8);

	//CALL 0x40
	//EXT
	char* start_instrs = "\xca\x40\xe4";

	//GETINP 0x44
	//RET
	char* func_instrs = "\x3e\x44\x4e";
	s->registers->IP = 0x10 ;
	memcpy(s->memory + reserved_end + 1,start_instrs,sizeof(*flag_instrs)*strlen(start_instrs));
	memcpy(s->memory + 0x40,func_instrs,sizeof(*flag_instrs)*strlen(func_instrs));
	memsee(s,MEM_SIZE,reserved_start,0x0);
	readinstr(s);

	memsee(s,MEM_SIZE,reserved_start,reserved_end);
	registersee(s);

}
