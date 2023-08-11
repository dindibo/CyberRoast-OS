#include "./vgaapi.h"

VGA_Pixel VGA_nullPixel = {0, 0};

void clearScreen(){
	VGA_Pixel *ptr = (VGA_Pixel *)MMIO_TEXT_PRINT;

    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            ptr = VGA_8025_getPixel(x, y);
            *ptr = VGA_nullPixel;
        }
    }
    
    // Move cursor to start
    g_videoCursor = MMIO_TEXT_PRINT;
}

VGA_Pixel *VGA_8025_getPixel(unsigned char x, unsigned char y){
    return (VGA_Pixel*)( (0xB8000) + (2 * x) + ( 2 * (y * 80) )  );
}
