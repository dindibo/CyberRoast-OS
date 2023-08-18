#include "isr.h"

extern void write_string( const char *string, char newline);
extern void makeNewline();
extern void print_hexdump(void *addr, unsigned int size);

void isr_handler(registers_t regs)
{
	//write_string("Recieved interrupt: 0x", 0);

	//int dbg = (char *)(&regs.int_no) - (char *)(&regs);

	//print_hexdump(dbg, 4);
	//makeNewline();

	unsigned int aaa = regs.int_no;

	if(regs.int_no >= 0x0)
	{
		write_string("[TEST]", 1);
		//print_hexdump(((char *)(&regs)) + 10, 25);
		print_hexdump(regs.int_no, 4);
		makeNewline();

		for (int i = 0; i < 5000000; i++)
		{
			;
		}
		
	}
	
}
