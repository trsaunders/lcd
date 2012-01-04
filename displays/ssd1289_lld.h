#ifndef __SSD1289_LLD_H__
#define __SSD1289_LLD_H__

#ifdef LCD_USE_SSD1289

#define LCD_SCREEN_WIDTH 320
#define LCD_SCREEN_HEIGHT 240

#ifdef __cplusplus
extern "C" {
#endif

void lcd_init_lld(void);
void lcd_set_area_lld(uint16_t, uint16_t, uint16_t, uint16_t);
void lcd_fill_area_lld(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
void lcd_set_point_lld(uint16_t, uint16_t, uint16_t);

#ifdef __cplusplus
}
#endif


#define SSD_OSC_START         0x00
#define SSD_OSCEN             0x01

#define SSD_DRV_OUT_CNTRL     0x01
#define SSD_LCD_DRV_AC_CNTRL  0x02
#define SSD_PWR_CNTRL_1       0x03
#define SSD_CMP_REG_1         0x05
#define SSD_CMP_REG_2         0x06
#define SSD_DISP_CNTRL        0x07
#define SSD_FRAME_CYC_CNTRL   0x0B
#define SSD_PWR_CNTRL_2       0x0C
#define SSD_PWR_CNTRL_3       0x0D
#define SSD_PWR_CNTRL_4       0x0E
#define SSD_GATE_SCAN_START   0x0F
#define SSD_SLEEP_MODE        0x10
#define SSD_ENTRY_MODE        0x11
#define SSD_GENERIC_INT_CNTRL 0x15
#define SSD_HORZ_PORCH        0x16
#define SSD_VERT_PORCH        0x17
#define SSD_PWR_CNTRL_5       0x1E
#define SSD_RAM_DATA_WRITE    0x22
#define SSD_RAM_WRITE_MASK_1  0x23
#define SSD_RAM_WRITE_MASK_2  0x24
#define SSD_FRAME_FREQ        0x25
#define SSD_VCOM_OTP_1        0x28
#define SSD_VCOM_OTP_2        0x29

/* y control 1:10 => 0x30 -> 0x37, 0x3A, 0x3B */

#define SSD_VERT_SCROLL_1     0x41
#define SSD_VERT_SCROLL_2     0x42
#define SSD_HORZ_RAM_ADDR     0x44
#define SSD_VERT_RAM_START    0x45
#define SSD_VERT_RAM_END      0x46
#define SSD_FIRST_WIN_START   0x48
#define SSD_FIRST_WIN_END     0x49
#define SSD_SECOND_WIN_START  0x4A
#define SSD_SECOND_WIN_END    0x4B
#define SSD_GDDRAM_X          0x4E
#define SSD_GDDRAM_Y          0x4F


/* LCD Registers */
#define R0             0x00
#define R1             0x01
#define R2             0x02
#define R3             0x03
#define R4             0x04
#define R5             0x05
#define R6             0x06
#define R7             0x07
#define R8             0x08
#define R9             0x09
#define R10            0x0A
#define R12            0x0C
#define R13            0x0D
#define R14            0x0E
#define R15            0x0F
#define R16            0x10
#define R17            0x11
#define R18            0x12
#define R19            0x13
#define R20            0x14
#define R21            0x15
#define R22            0x16
#define R23            0x17
#define R24            0x18
#define R25            0x19
#define R26            0x1A
#define R27            0x1B
#define R28            0x1C
#define R29            0x1D
#define R30            0x1E
#define R31            0x1F
#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R36            0x24
#define R37            0x25
#define R40            0x28
#define R41            0x29
#define R43            0x2B
#define R45            0x2D
#define R48            0x30
#define R49            0x31
#define R50            0x32
#define R51            0x33
#define R52            0x34
#define R53            0x35
#define R54            0x36
#define R55            0x37
#define R56            0x38
#define R57            0x39
#define R59            0x3B
#define R60            0x3C
#define R61            0x3D
#define R62            0x3E
#define R63            0x3F
#define R64            0x40
#define R65            0x41
#define R66            0x42
#define R67            0x43
#define R68            0x44
#define R69            0x45
#define R70            0x46
#define R71            0x47
#define R72            0x48
#define R73            0x49
#define R74            0x4A
#define R75            0x4B
#define R76            0x4C
#define R77            0x4D
#define R78            0x4E
#define R79            0x4F
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53
#define R96            0x60
#define R97            0x61
#define R106           0x6A
#define R118           0x76
#define R128           0x80
#define R129           0x81
#define R130           0x82
#define R131           0x83
#define R132           0x84
#define R133           0x85
#define R134           0x86
#define R135           0x87
#define R136           0x88
#define R137           0x89
#define R139           0x8B
#define R140           0x8C
#define R141           0x8D
#define R143           0x8F
#define R144           0x90
#define R145           0x91
#define R146           0x92
#define R147           0x93
#define R148           0x94
#define R149           0x95
#define R150           0x96
#define R151           0x97
#define R152           0x98
#define R153           0x99
#define R154           0x9A
#define R157           0x9D
#define R192           0xC0
#define R193           0xC1
#define R229           0xE5

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#endif

#endif
