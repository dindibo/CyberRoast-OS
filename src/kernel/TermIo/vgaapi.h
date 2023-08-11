#define MMIO_TEXT_PRINT (0xB8000)

#define VGA_COLOR_FG_BLACK       	(0)
#define VGA_COLOR_FG_BLUE        	(1)
#define VGA_COLOR_FG_GREEN       	(2)
#define VGA_COLOR_FG_CYAN        	(3)
#define VGA_COLOR_FG_RED         	(4)
#define VGA_COLOR_FG_PURPLE      	(5)
#define VGA_COLOR_FG_BROWN       	(6)
#define VGA_COLOR_FG_GRAY        	(7)
#define VGA_COLOR_FG_DARK_GRAY   	(8)
#define VGA_COLOR_FG_LIGHT_BLUE  	(9)
#define VGA_COLOR_FG_LIGHT_GREEN 	(10)
#define VGA_COLOR_FG_LIGHT_CYAN  	(11)
#define VGA_COLOR_FG_LIGHT_RED   	(12)
#define VGA_COLOR_FG_LIGHT_PURPLE	(13)
#define VGA_COLOR_FG_YELLOW      	(14)
#define VGA_COLOR_FG_WHITE       	(15)

#define VGA_COLOR_BG_BLACK       	(0)
#define VGA_COLOR_BG_BLUE        	(1)
#define VGA_COLOR_BG_GREEN       	(2)
#define VGA_COLOR_BG_CYAN        	(3)
#define VGA_COLOR_BG_RED         	(4)
#define VGA_COLOR_BG_PURPLE      	(5)
#define VGA_COLOR_BG_BROWN       	(6)
#define VGA_COLOR_BG_GRAY        	(7)

extern volatile char *g_videoCursor;

struct VGA_Pixel
{
    char charecter : 8;

    unsigned char foregoundColor : 4;
    unsigned char backgroundColor : 3;
    unsigned char isBlinking : 1;

} typedef VGA_Pixel, *lpVGA_Pixel;


// Struct initialization
#ifndef VGAAPI_INIT
#define VGAAPI_INIT

extern VGA_Pixel VGA_nullPixel;

#endif


VGA_Pixel *VGA_8025_getPixel(unsigned char x, unsigned char y);
void clearScreen();
