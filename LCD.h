#ifndef __LCD_H__
#define __LCD_H__

/* include all displays here */
#include "displays/ssd1289_lld.h"

#ifdef __cplusplus
extern "C" {
#endif

void lcdInit(void);
void lcdSetArea(uint16_t, uint16_t, uint16_t, uint16_t);
void lcdFillArea(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
void lcdClearScreen(uint16_t);
void lcdSetPixel(int, int, uint16_t);
void lcdDemo(void);
void lcdDrawString(uint16_t, uint16_t, const char *, uint16_t, uint8_t);
void lcdDrawChar(uint16_t, uint16_t, const char, uint16_t, uint8_t);
void lcdDrawBitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const unsigned char *bmp);
void lcdDrawLine(int x0, int y0, int x1, int y1,uint16_t colour);
float lcdFPS(void);

#ifdef __cplusplus
}
#endif
#endif
