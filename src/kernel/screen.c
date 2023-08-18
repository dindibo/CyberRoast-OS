#include "screen.h"

unsigned char *vidmem=(unsigned char *)0xb8000;

unsigned char x=0,y=0;

void screen_clear(){
	int i;
	for(i=0;i<4000;i+=2){
		vidmem[i]=0x20;
		vidmem[i+1]=0x07;
	}
	x=0;
	y=0;
}

char * itoa( int value, char * str, int base )
{
	char * rc;
	char * ptr;
	char * low;
	// Check for supported base.
	if ( base < 2 || base > 36 )
	{
		*str = '\0';
		return str;
	}
	rc = ptr = str;
	// Set '-' for negative decimals.
	if ( value < 0 && base == 10 )
	{
		*ptr++ = '-';
	}
	// Remember where the numbers start.
	low = ptr;
	// The actual conversion.
	do
	{
	// Modulo is negative for negative value. This trick makes abs() unnecessary.
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
		value /= base;
	} while ( value );
	// Terminating the string.
		*ptr-- = '\0';
	// Invert the numbers.
	while ( low < ptr )
	{
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}

void screen_print_int(int i,int base){
	char buf[100];
	itoa(i,buf,base);
	screen_print(buf);
}

void screen_scroll(){
	int i;
	for(i=160;i<4000;i+=2){
		vidmem[i-160]=vidmem[i];
	}
}

void screen_print(char *string){
	int i=0;
	while(string[i]){
		if(y==25){
			screen_scroll();
			y=24;
		}
		if(string[i]>0x1f&&string[i]!=0x7f){
			vidmem[2*(x+y*80)]=string[i];
			x++;
			if(x==80){
				y++;
				x=0;
			}
		}
		else{
			switch(string[i]){
			case 0x08:
				if(x!=0){
					x--;
				}
				break;
			case 0x09:
				x+=4;
				if(x>=80){
					x=0;
					y++;
				}
				break;
			case 0x0a:
				x=0;
				y++;
				break;
			}
		}
		i++;
	}
}
