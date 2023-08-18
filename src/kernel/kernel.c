#include "TermIo/vgaapi.h"

// Siman 7
#include "screen.h"
#include "./ProtectedMode/descriptors.h"

extern void goto_vm8086();
extern void putc ();
extern void convert_to_graphic_mode ();
extern unsigned int read_cr0();
extern unsigned int foo();
extern void do_int();

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

void writePixels(unsigned char x, unsigned char y, VGA_Pixel *pixels, unsigned short pixelsLen){
	VGA_Pixel *pPtr = VGA_8025_getPixel(x, y);

	for (int i = 0; i < pixelsLen; i++)
	{
		*pPtr = pixels[i];
	}
}

void writePixelsText(unsigned char x, unsigned char y, VGA_Pixel *pixelTemplate, const char *text, unsigned short pixelsLen){
	VGA_Pixel *pPtr = VGA_8025_getPixel(x, y);
	VGA_Pixel tmp = *pixelTemplate;

	for (int i = 0; i < pixelsLen; i++)
	{
		tmp.charecter = text[i];
		*pPtr = tmp;
	}
}

void write_string_with_color( int colour, const char *string )
{
    while( *string != 0 )
    {
        *g_videoCursor++ = *string++;
        *g_videoCursor++ = colour;
    }
}

void setCursor(unsigned char x, unsigned char y){
	g_videoCursor = 2 * (x + 80 * y) + MMIO_TEXT_PRINT;
}

void makeNewline(){
	unsigned char line = (((unsigned int)g_videoCursor - MMIO_TEXT_PRINT) / 2) / 80;
	setCursor(0, ++line);
}

void write_string( const char *string, char newline)
{
	const static int MIMO_MAX = 0xb8fa0;

    write_string_with_color(VGA_COLOR_FG_WHITE, string);

	if(newline){
		makeNewline();
	}

	if(g_videoCursor > (MIMO_MAX)){
		clearScreen();
	}
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
	write_string(buf, 0);
}

void convert_to_graphic_mode_TEST(){
	outw(0x3d4,0x000C);
	outw(0x3d4,0x000D);
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
	write_string_with_color(VGA_COLOR_FG_CYAN, arrTest);
	sleep(1000);
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

	screen_clear();
	if (magic!=0x2BADB002){
		screen_print("Invalid multiboot header.");
		return -1;
	}
	screen_print("Hello World!\n");
	screen_print("Setting up the GDT.\n");
	gdt_setup();
	screen_print("GDT set.\n");
	screen_print("Setting up the IDT.\n");
	idt_setup();
	screen_print("IDT set.\n");
	screen_print("Sending interrupt.\n");
	__asm__("int $0x00");
	__asm__("int $0x80");

	return 0;
}

