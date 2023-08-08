extern void goto_vm8086();
extern void putc ();
extern void convert_to_graphic_mode ();

#define VGA_COLOR_BLACK       	(0)
#define VGA_COLOR_BLUE        	(1)
#define VGA_COLOR_GREEN       	(2)
#define VGA_COLOR_CYAN        	(3)
#define VGA_COLOR_RED         	(4)
#define VGA_COLOR_PURPLE      	(5)
#define VGA_COLOR_BROWN       	(6)
#define VGA_COLOR_GRAY        	(7)
#define VGA_COLOR_DARK_GRAY   	(8)
#define VGA_COLOR_LIGHT_BLUE  	(9)
#define VGA_COLOR_LIGHT_GREEN 	(10)
#define VGA_COLOR_LIGHT_CYAN  	(11)
#define VGA_COLOR_LIGHT_RED   	(12)
#define VGA_COLOR_LIGHT_PURPLE	(13)
#define VGA_COLOR_YELLOW      	(14)
#define VGA_COLOR_WHITE       	(15)

#define MMIO_TEXT_PRINT (0xB8000)

const char hexCharset[] = "0123456789ABCDEF";
const char arrTest[] = "[ Welcome to CyberRoast-1 OS ]";
const char clearText[] = "                                                                                ";

volatile char *g_videoCursor = (volatile char*)MMIO_TEXT_PRINT;

void outw(unsigned short port, unsigned short value)
{
	asm volatile ("outw %%ax,%%dx": :"dN"(port), "a"(value));
}

void testText () {
	*((int*)0xb8000)=0x07690748;
	*((int*)0xb8004)=0x07690748;
}

void write_string_with_color( int colour, const char *string )
{
    while( *string != 0 )
    {
        *g_videoCursor++ = *string++;
        *g_videoCursor++ = colour;
    }
}

void write_string( const char *string )
{
    write_string_with_color(VGA_COLOR_WHITE, string);
}

void write_char_with_color( int colour, char c )
{
	char buf[2] = {0};
	buf[0] = c;
	write_string_with_color(colour, buf);
}

void write_char( char c )
{
	char buf[2] = {0};
	buf[0] = c;
	write_string(buf);
}

void convert_to_graphic_mode_TEST(){
	outw(0x3d4,0x000C);
	outw(0x3d4,0x000D);
}

void clearScreen(){
	g_videoCursor = MMIO_TEXT_PRINT;
	write_string_with_color(0, clearText);
	g_videoCursor = MMIO_TEXT_PRINT;
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

void doIntroScreen(){
	clearScreen();
	write_string_with_color(VGA_COLOR_CYAN, arrTest);
	sleep(2000);
	clearScreen();
}

void hex_print(unsigned char ch){
	unsigned char rem, dev;

	dev = ch / 16;
	rem = ch % 16;

	write_char((hexCharset[dev]));
	write_char((hexCharset[rem]));
	write_char(' ');

}

void print_hexdump(void *addr, unsigned int size){
	for (int i = 0; i < size; i++)
	{
		hex_print(((unsigned char *)addr)[i]);
	}
}

int kmain(void *mbd,unsigned int magic){
	if (magic!=0x2BADB002){
		return -1;
	}

	doIntroScreen();

	char hhh[] = "ABCDEFGH";
	print_hexdump(hhh, sizeof(hhh) - 1);

	convert_to_graphic_mode_TEST();

	return 0;
}

