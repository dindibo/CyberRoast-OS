#ifndef GDT_HEADER
#define GDT_HEADER


struct gdt_entry_struct
{
 unsigned short limit_low;
 unsigned short base_low;
 unsigned char base_middle;
 unsigned char access;
 unsigned char granularity;
 unsigned char base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;


struct gdt_ptr_struct
{
 unsigned short limit;
 unsigned int base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

gdt_ptr_t *gdt_setup();


#endif