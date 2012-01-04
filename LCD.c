/* Chibios LCD Driver */

#include "ch.h"
#include "hal.h"

#include "LCD.h"
#include "font.h"

#if LCD_USE_FONT_SMALL == 1 && LCD_USE_FONTS == 1
extern const unsigned char FONT6x8[97][8];
#endif

#if LCD_USE_FONT_MEDIUM == 1 && LCD_USE_FONTS == 1
extern const unsigned char FONT8x8[97][8];
#endif

#if LCD_USE_FONT_LARGE == 1 && LCD_USE_FONTS == 1
extern const unsigned char FONT8x16[97][8];
#endif

/* build font table */

#if LCD_USE_FONTS == 1
unsigned char *FontTable[] = {
#if LCD_USE_FONT_SMALL == 1
		(unsigned char *)FONT6x8,
#else
		NULL,
#endif

#if LCD_USE_FONT_MEDIUM == 1
		(unsigned char *)FONT8x8,
#else
		NULL,
#endif

#if LCD_USE_FONT_LARGE == 1
		(unsigned char *)FONT8x16
#else
		NULL
#endif
};
#endif

void lcdInit(void) {
	lcd_init_lld();
}

void lcdSetArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	lcd_set_area_lld(x0, y0, x1, y1);
}

void lcdFillArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t colour) {
	lcd_fill_area_lld(x0, y0, x1, y1, colour);
}

void lcdClearScreen(uint16_t colour) {
	lcdFillArea(0, 0, LCD_SCREEN_WIDTH, LCD_SCREEN_HEIGHT, colour);
}

void lcdSetPixel(int x, int y, uint16_t colour) {
	lcd_set_pixel_lld(x, y, colour);
}

void lcdDemo(void) {

}

void lcdDrawString(uint16_t x, uint16_t y, const char *str, uint16_t colour, uint8_t size) {
	unsigned char *pFont = (unsigned char *)FontTable[size];
	// get the nColumns, nRows and nBytes
	uint8_t nCols = *pFont;
	uint8_t nRows = *(pFont + 1);
	uint8_t nBytes = *(pFont + 2);
	while(*str) {
		//cPrintf("%c",*str++);
		lcdDrawChar(x,y,*str++,colour,size);
		if (x < (LCD_SCREEN_WIDTH - nCols)) {
			x += nCols;
		} else if (y < (LCD_SCREEN_HEIGHT - nRows)) {
			x=0;
			y+=nRows;
		} else {
			x=0;
			y=0;
		}
	}
}

void lcdDrawChar(uint16_t x, uint16_t y, const char c, uint16_t colour, uint8_t size) {
	unsigned char PixelRow;
	unsigned char Mask;
	int i,j;
	// get pointer to the beginning of the selected font table
	unsigned char *pFont = (unsigned char *)FontTable[size];
	// get the nColumns, nRows and nBytes
	uint8_t nCols = *pFont;
	uint8_t nRows = *(pFont + 1);
	uint8_t nBytes = *(pFont + 2);

	// get pointer to the last byte of the desired character
	unsigned char *pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;

	// loop on each row, working backwards from the bottom to the top
	for (i = nRows - 1; i >= 0; i--) {

		// copy pixel row from font table and then decrement row
		PixelRow = *pChar--;

		// loop on each pixel in the row (left to right)
		// Note: we do two pixels each loop
		Mask = 0x80;
		for (j = 0; j < nCols; j += 2) {
			if ( (PixelRow >> 7-j) & 0x01 == 0x01) {
				lcdSetPixel(x+j,y+i, colour);
			} else {
				/* handle background colour somehow - maybe passed to this function? or store when set */
				//lcdSetPixel(Xpos+j,Ypos+i,colour);
			}

		}
	}
}

void lcdDrawLine(int x0, int y0, int x1, int y1,uint16_t colour)
{
	int x,y,dx,dy,Dx,Dy,e,i;
	Dx=x1-x0;
	Dy=y1-y0;

	dx=fabs(x1-x0);
	dy=fabs(y1-y0);
	x=x0;
	y=y0;
	if(dy>dx) {
		e=-dy;
		for(i=0;i<dy;i++)
		{
			lcdSetPixel(x,y,colour);
			if(Dy>=0) y++;
			else y--;
			e+=2*dx;
			if(e>=0)
			{
				if(Dx>=0) x++;
				else x--;
				e-=2*dy;
			}
		}
	}
	else
	{
		e=-dx;
		for(i=0;i<dx;i++)
		{
			lcdSetPixel(x,y,colour);
			if(Dx>=0) x++;
			else x--;
			e+=2*dy;
			if(e>=0)
			{
				if(Dy>=0) y++;
				else y--;
				e-=2*dx;
			}
		}
	}
}
void lcddrawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const unsigned char *bmp) {

}
float lcdFPS(void) {
	return 30.0f;
}
