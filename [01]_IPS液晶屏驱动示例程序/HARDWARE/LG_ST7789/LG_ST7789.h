#ifndef __LG_ST7789_H
#define __LG_ST7789_H

#include "stm32f10x.h" 
#include "sys.h"

#define ST7789_TFTWIDTH_240 	240
#define ST7789_TFTHEIGHT_240 	240

#define ST7789_240x240_XSTART 0
#define ST7789_240x240_YSTART 0

#define ST_CMD_DELAY   0x80    // special signifier for command lists

#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36

#define ST7789_MADCTL_MY  0x80
#define ST7789_MADCTL_MX  0x40
#define ST7789_MADCTL_MV  0x20
#define ST7789_MADCTL_ML  0x10
#define ST7789_MADCTL_RGB 0x00

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0xA514

////////////////////////////////////

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))


#define swap(a, b) { int16_t t = a; a = b; b = t; }

////////////////////////////////////
#define PIN_DC PBout(0) //DC,WR
#define PIN_RST PBout(1)   //RST
extern u16 POINT_COLOR;		/* »­±ÊÑÕÉ« */
extern u16 BACK_COLOR;  	/* ±³¾°É« */ 


/////////////////////////////////////
typedef struct
{
	u16 _colstart;
	u16 _rowstart;
	u16 _xstart;
	u16 _ystart;
	u16 _width;
	u16 _height;
	u8 _rotation;
}IPS_TypeDef;


//»æÍ¼»ù±¾·þÎñº¯Êý
void ips_display_Init(IPS_TypeDef *ips, u16 w, u16 h, u8 r);
void ST7789_init(void);
void lcd_write_reg(u8 reg);
void lcd_write_data(u8 data);
void lcd_set_address(u16 x1, u16 y1, u16 x2, u16 y2);
void lcd_display_on(void);
void lcd_display_off(void);
void lcd_write_ram(void);
void lcd_clear(IPS_TypeDef *ips, u16 color);



//µã£¬Ïß
void setAddrWindow(IPS_TypeDef *ips, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void drawPixel(IPS_TypeDef *ips, int16_t x, int16_t y, uint16_t color);
void drawLine(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void drawFastVLine(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t h, uint16_t color);
void drawFastHLine(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t w, uint16_t color);
//¾ØÐÎ£¬Ìî³ä¾ØÐÎ
void drawRect(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fillRect(IPS_TypeDef *ips, u16 x, u16 y, u16 w, u16 h, u16 color);
//Ô²£¬Ìî³äÔ²
void drawCircle(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r, uint16_t color);
void drawCircleHelper(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
void fillCircle(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r, uint16_t color);
void fillCircleHelper(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
//Èý½ÇÐÎ£¬Ìî³äÈý½ÇÐÎ
void drawTriangle(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void fillTriangle(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
//Ô²½Ç£¬Ìî³äÔ²½Ç
void drawRoundRect(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
void fillRoundRect(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
//Bitmap
void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
void drawChar(IPS_TypeDef *ips, int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

//È«ÆÁ²Ù×÷
void setCursor(int16_t x, int16_t y);
void fillScreen(IPS_TypeDef *ips, u16 color);
void setRotation(IPS_TypeDef *ips, uint8_t r);
void invertDisplay(u8 i);
#endif




