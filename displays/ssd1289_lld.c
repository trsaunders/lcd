#include "ch.h"
#include "hal.h"

#ifdef LCD_USE_SSD1289
/* SSD1289 Low Level Driver */
#include "ssd1289_lld.h"

static uint16_t DeviceCode;

#define SSD1289_Delay(n) chThdSleep(n)

#define LCD_REG              (*((volatile uint16_t *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile uint16_t *) 0x60020000)) /* RS = 1 */

static __inline void LCD_WriteReg(uint8_t LCD_Reg,uint16_t LCD_RegValue) {
	/* Write 16-bit Index, then Write Reg */
	LCD_REG = LCD_Reg;
	/* Write 16-bit Reg */
	LCD_RAM = LCD_RegValue;
}

static __inline uint16_t LCD_ReadReg(uint8_t LCD_Reg) {
	/* Write 16-bit Index (then Read Reg) */
	LCD_REG = LCD_Reg;
	/* Read 16-bit Reg */
	return (LCD_RAM);
}

static __inline void LCD_WriteRAM_Prepare(void) {
	LCD_REG = R34;
}

static __inline void LCD_WriteRAM(uint16_t RGB_Code) {
	/* Write 16-bit GRAM Reg */
	LCD_RAM = RGB_Code;
}

static __inline uint16_t LCD_ReadRAM(void) {
	volatile uint16_t dummy;
	/* Write 16-bit Index (then Read Reg) */
	LCD_REG = R34; /* Select GRAM Reg */
	/* Read 16-bit Reg */
	dummy = LCD_RAM;

	return LCD_RAM;
}

static void lcd_set_cursor_lld(uint16_t Xpos,uint16_t Ypos) {
	if(DeviceCode==0x8989) {
		LCD_WriteReg(0x004e,Xpos); /* Row */
		LCD_WriteReg(0x004f,Ypos); /* Line */
	} else if(DeviceCode==0x9919) {
		LCD_WriteReg(0x004e,Xpos); /* Row */
		LCD_WriteReg(0x004f,Ypos); /* Line */
	} else {
		LCD_WriteReg(0x0020,Xpos); /* Row */
		LCD_WriteReg(0x0021,Ypos); /* Line */
	}
}


void lcd_set_area_lld(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1) {
	lcd_set_cursor_lld(x0, y0);
	LCD_WriteReg(0x0050,x0);
	LCD_WriteReg(0x0051,x0+x1-1);
	LCD_WriteReg(0x0052,y0);
	LCD_WriteReg(0x0053,y0+y1-1);
}

void lcd_fill_area_lld(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t colour) {
	//lcd_set_area_lld(x0, y0, x1, y1);
	lcd_set_cursor_lld(x0, y0);
	uint32_t index = 0;
	LCD_WriteRAM_Prepare();
	for(index=0; index < (x1-x0)*(y1-y0); index++)
		LCD_RAM = colour;
}


void lcd_init_lld(void) {
	/* FSMC setup */
	rccEnableAHB(RCC_AHBENR_FSMCEN, 0);
	int FSMC_Bank = 0;
	/* timing structure */
	/* from datasheet:
        address setup: 0ns
        address hold: 0ns
        Data setup: 5ns
        Data hold: 5ns
        Data access: 250ns
        output hold: 100ns
	 */
	FSMC_Bank1->BTCR[FSMC_Bank+1] = FSMC_BTR1_ADDSET_1 | FSMC_BTR1_DATAST_1;

	/* Bank1 NOR/SRAM control register configuration */
	FSMC_Bank1->BTCR[FSMC_Bank] = FSMC_BCR1_MWID_0 | FSMC_BCR1_WREN | FSMC_BCR1_MBKEN;

	DeviceCode = LCD_ReadReg(0x0000);

	/* initialise LCD */
	if(DeviceCode == 0x8989) {
		LCD_WriteReg(SSD_OSC_START, SSD_OSCEN);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_PWR_CNTRL_1,0xA8A4);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_PWR_CNTRL_2,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_PWR_CNTRL_3,0x080C);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_PWR_CNTRL_4,0x2B00);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_PWR_CNTRL_5,0x00B0);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_DRV_OUT_CNTRL,0x2B3F);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_LCD_DRV_AC_CNTRL,0x0600);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_SLEEP_MODE,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_ENTRY_MODE,0x6070);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_CMP_REG_1,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_CMP_REG_2,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_HORZ_PORCH,0xEF1C);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_VERT_PORCH,0x0003);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_DISP_CNTRL,0x0133);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_FRAME_CYC_CNTRL,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_GATE_SCAN_START,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_VERT_SCROLL_1,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_VERT_SCROLL_2,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_FIRST_WIN_START,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_FIRST_WIN_END,0x013F);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_SECOND_WIN_START,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_SECOND_WIN_END,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_HORZ_RAM_ADDR,0xEF00);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_VERT_RAM_START,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_VERT_RAM_END,0x013F);    SSD1289_Delay(5);
		/* y control */
		LCD_WriteReg(0x0030,0x0707);    SSD1289_Delay(5);
		LCD_WriteReg(0x0031,0x0204);    SSD1289_Delay(5);
		LCD_WriteReg(0x0032,0x0204);    SSD1289_Delay(5);
		LCD_WriteReg(0x0033,0x0502);    SSD1289_Delay(5);
		LCD_WriteReg(0x0034,0x0507);    SSD1289_Delay(5);
		LCD_WriteReg(0x0035,0x0204);    SSD1289_Delay(5);
		LCD_WriteReg(0x0036,0x0204);    SSD1289_Delay(5);
		LCD_WriteReg(0x0037,0x0502);    SSD1289_Delay(5);
		LCD_WriteReg(0x003A,0x0302);    SSD1289_Delay(5);
		LCD_WriteReg(0x003B,0x0302);    SSD1289_Delay(5);

		LCD_WriteReg(SSD_RAM_WRITE_MASK_1,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_RAM_WRITE_MASK_2,0x0000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_FRAME_FREQ,0x8000);    SSD1289_Delay(5);
		LCD_WriteReg(SSD_GDDRAM_Y,0);
		LCD_WriteReg(SSD_GDDRAM_X,0);
	} else {
		chSysHalt();
	}
	/* TODO: add other devices from original code */
}

void lcd_set_point_lld(uint16_t x, uint16_t y, uint16_t colour) {
	lcd_set_cursor_lld(x, y);
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(colour);
}

#endif
