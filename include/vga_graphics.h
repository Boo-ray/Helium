#ifndef VGA_GRAPHICS
#define VGA_GRAPHICS

#include "tipi.h"
#include "io_iasm.h"
#include "str_util.h"

#define VIDEO_ADDRESS 0xb8000

#define VGA3_WIDTH	80
#define	VGA3_HEIGHT	25

#define PORT_CURSOR_CTRL	0x3d4
#define PORT_CURSOR_DATA	0x3d5

typedef u8 vga_entry_color;

enum VGA_COLOR
{
	//colori scuri
	VGA_BLACK			= 0x0,
	VGA_BLUE			= 0x1,
	VGA_GREEN			= 0x2,
	VGA_CYAN			= 0x3,
	VGA_RED				= 0x4,
	VGA_MAGENTA			= 0x5,
	VGA_BROWN			= 0x6,
	VGA_LIGHT_GRAY		= 0x7,
	
	//colori chiari
	VGA_DARK_GRAY		= 0x8,
	VGA_LIGHT_BLUE		= 0x9,
	VGA_LIGHT_GREEN		= 0xa,
	VGA_LIGHT_CYAN		= 0xb,
	VGA_LIGHT_RED		= 0xc,
	VGA_LIGHT_MAGENTA	= 0xd,
	VGA_YELLOW			= 0xe,
	VGA_WHITE			= 0xf
};

//Metodi utili INLINE
inline vga_entry_color get_vga_color(u8 back_color, u8 fore_color)
{
	return (back_color << 4) | fore_color;
}

inline u16 get_vga_offset(int x, int y)
{
	return x + y*VGA3_WIDTH;
}

inline char get_halfbyte_char(u8 num)
{
	num = num & 0x0f;
	return num < 10 ? num+48 : num + 55;
}

//Formattazione
void new_line();

//Cursore
void get_cursor(int &x, int &y);
u16 get_cursor();

void set_cursor(int x, int y);
void set_cursor(u16 offset);
void disable_cursor();
void enable_cursor(u8 cursor_start, u8 cursor_end);

//Inserimento caratteri
void put_char(const char c, int x, int y, vga_entry_color color);
void put_char(const char c, u16 offset, vga_entry_color color);

//Stampa di stringhe
void print(string, u16 offset = get_cursor(), vga_entry_color color = 0);
void println(string str, u16 offset = get_cursor(), vga_entry_color color = 0);

//Stampa di valori numerici
void print_hex(u8 num, int x, int y);
void print_hex(u16 num, int x, int y);
void print_hex(u32 num, int x, int y);

void print_int(u32 num, u16 offset = get_cursor());

void print_bits(u16 val, u16 offset);

//Pulizia schermo
void clear_screen(vga_entry_color);

#endif
