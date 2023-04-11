extern void goto_vm8086();
extern void putc ();
extern void convert_to_graphic_mode ();

#define MMIO_TEXT_PRINT (0xB8000)

const char arrTest[] = "[ Welcome to Nivux-1 ]";
const char clearText[] = "                                                                                ";

void outw(unsigned short port, unsigned short value)
{
	asm volatile ("outw %%ax,%%dx": :"dN"(port), "a"(value));
}

void testText () {
	*((int*)0xb8000)=0x07690748;
	*((int*)0xb8004)=0x07690748;
}

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

void convert_to_graphic_mode_TEST(){
	outw(0x3d4,0x000C);
	outw(0x3d4,0x000D);
}

void clearScreen(){
	write_string(0, clearText);
}

void nopFunc() {
	
}

void sleep_core(){
	for(int i = 0; i < 48154; i++){
		nopFunc();
	}
}

/* example for 320x200 VGA */
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

void sleep(int ms){
	for (int i = 0; i < ms; i++)
	{
		sleep_core();
	}
	
}

int kmain(void *mbd,unsigned int magic){
	if (magic!=0x2BADB002){
		return -1;
	}

	clearScreen();
	write_string(3, arrTest);

	sleep(2000);

	clearScreen();

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			putpixel(i, j, 0x99);
		}
	}

	convert_to_graphic_mode_TEST();

	return 0;
}

