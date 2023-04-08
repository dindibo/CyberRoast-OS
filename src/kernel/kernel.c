extern void putc ();

#define MMIO_TEXT_PRINT (0xB8000)

const char arrTest[] = "[ Welcome to Nivux-1 ]";
const char clearText[] = "                                                                                ";

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

void clearScreen(){
	write_string(0, clearText);
}

int kmain(void *mbd,unsigned int magic){
	if (magic!=0x2BADB002){
		return -1;
	}

	clearScreen();
	write_string(3, arrTest);

	return 0;
}

