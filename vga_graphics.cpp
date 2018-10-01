#include "vga_graphics.h"

inline vga_entry_color get_vga_color(uint8_t back_color, uint8_t fore_color)
{
	vga_entry_color color = (back_color << 4) | fore_color;
	return color;
}

void print_char(const char c, int x, int y, vga_entry_color color)
{
	int offset = 0;
	
	offset = (y * VGA3_WIDTH) + x;
	
	if(color != 0)
	{
		uint16_t entry = color << 8;
		entry |= c;
		video_base[offset] = entry;
	}
	else
	{
		video_base[offset] &= 0xff00;
		video_base[offset] |= c;
	}
}

void print_string(string str, int x, int y, vga_entry_color color)
{
	for(int i = 0; i < str_len(str); i++)
	{
		print_char(str[i], x + i, y, color);
	}
}

void clear_screen(vga_entry_color color)
{
	for(int i = 0; i < VGA3_HEIGHT; i++)
	{
		for(int j = 0; j < VGA3_WIDTH; j++)
		{
			print_char(' ', j, i, color);
		}
	}
}

void get_cursor(int &x, int &y)
{
	uint16_t offset = 0;
	
	//la porta data conterrà gli 8 bit bassi dell'offset
	port_byte_out(PORT_CURSOR_CTRL, 0xf);
	offset = port_byte_in(PORT_CURSOR_DATA);
	offset << 8;
	//la porta data conterrà gli 8 bit alti dell'offset
	port_byte_out(PORT_CURSOR_CTRL, 0xe);
	offset += port_byte_in(PORT_CURSOR_DATA);
	
	x = offset % VGA3_WIDTH;
	y = (offset - x) / VGA3_WIDTH;
}

void set_cursor(int x, int y)
{
	uint16_t offset = x + y * VGA3_WIDTH;
	
	//la porta data conterrà gli 8 bit bassi dell'offset
	port_byte_out(PORT_CURSOR_CTRL, 0xf);
	port_byte_out(PORT_CURSOR_DATA, (uint8_t) (offset & 0x00ff));
	//la porta data conterrà gli 8 bit alti dell'offset
	port_byte_out(PORT_CURSOR_CTRL, 0xe);
	port_byte_out(PORT_CURSOR_DATA, (uint8_t) ((offset >> 8) & 0x00ff));
}
