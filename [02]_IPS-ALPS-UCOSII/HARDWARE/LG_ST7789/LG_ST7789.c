#include "LG_ST7789.h"
#include "spi.h"
#include "delay.h"
#include "glcdfont.c"
#include "font.h"
//

void ips_display_Init(IPS_TypeDef *ips, u16 w, u16 h, u8 r)
{
	ips->_colstart = ST7789_240x240_XSTART;
	ips->_rowstart = ST7789_240x240_YSTART;
	ips->_xstart = 0;//default: 0
	ips->_ystart = 0;//default: 0
	ips->_width = w;
	ips->_height = h;
	ips->_rotation = r;
	///////////////////////////////////////////////////////////////
	
	//第一步：ST7789端口配置DC,RST：
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //PB0/1推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB

 	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);  //PB0/1上拉

	//第二步：SPI2配置,使能：
	SPI2_Init();		   			//初始化SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);		//设置为21M时钟,高速模式 :SPI_BaudRatePrescaler_4	
	
	ST7789_init();
}


///////////////////////////////////////////////////////////////////
///////// 服务函数
///////////////////////////////////
/**************************************************************
函数名称 : lcd_write_reg
函数功能 : 向lcd驱动芯片写一个命令
输入参数 : reg：要写入的命令
返回值  	 : 无
备注		 : LCD_WR为0时表示写命令
**************************************************************/
void lcd_write_reg(u8 reg)
{
	PIN_DC = 0;
	SPI2_ReadWriteByte(reg);	
}

/**************************************************************
函数名称 : lcd_write_data
函数功能 : 向lcd驱动芯片写一个数据
输入参数 : data：要写入的数据
返回值  	 : 无
备注		 : LCD_WR为1时表示写数据
**************************************************************/
void lcd_write_data(u8 data)
{
	PIN_DC = 1;
	SPI2_ReadWriteByte(data);
}


/**************************************************************
函数名称 : lcd_init
函数功能 : lcd初始化
输入参数 : 无
返回值  	 : 无
备注		 : 无
**************************************************************/
void ST7789_init(void)
{
	PIN_RST=0;
    delay_ms(120);
    PIN_RST=1;
	delay_ms(120);
 
	/* Sleep Out */
    lcd_write_reg(0x11);
    /* wait for power stability */
    delay_ms(120);
 
    /* Memory Data Access Control */
    lcd_write_reg(0x36);
    lcd_write_data(0x00);
 
    /* RGB 5-6-5-bit  */
    lcd_write_reg(0x3A);
    lcd_write_data(0x65);
 
    /* Porch Setting */
    lcd_write_reg(0xB2);
    lcd_write_data(0x0C);
    lcd_write_data(0x0C);
    lcd_write_data(0x00);
    lcd_write_data(0x33);
    lcd_write_data(0x33);
 
    /*  Gate Control */
    lcd_write_reg(0xB7);
    lcd_write_data(0x72);
 
    /* VCOM Setting */
    lcd_write_reg(0xBB);
    lcd_write_data(0x3D);   //Vcom=1.625V
 
    /* LCM Control */
    lcd_write_reg(0xC0);
    lcd_write_data(0x2C);
 
    /* VDV and VRH Command Enable */
    lcd_write_reg(0xC2);
    lcd_write_data(0x01);
 
    /* VRH Set */
    lcd_write_reg(0xC3);
    lcd_write_data(0x19);
 
    /* VDV Set */
    lcd_write_reg(0xC4);
    lcd_write_data(0x20);
 
    /* Frame Rate Control in Normal Mode */
    lcd_write_reg(0xC6);
    lcd_write_data(0x0F);	//60MHZ
 
    /* Power Control 1 */
    lcd_write_reg(0xD0);
    lcd_write_data(0xA4);
    lcd_write_data(0xA1);
 
    /* Positive Voltage Gamma Control */
    lcd_write_reg(0xE0);
    lcd_write_data(0xD0);
    lcd_write_data(0x04);
    lcd_write_data(0x0D);
    lcd_write_data(0x11);
    lcd_write_data(0x13);
    lcd_write_data(0x2B);
    lcd_write_data(0x3F);
    lcd_write_data(0x54);
    lcd_write_data(0x4C);
    lcd_write_data(0x18);
    lcd_write_data(0x0D);
    lcd_write_data(0x0B);
    lcd_write_data(0x1F);
    lcd_write_data(0x23);
 
    /* Negative Voltage Gamma Control */
    lcd_write_reg(0xE1);
    lcd_write_data(0xD0);
    lcd_write_data(0x04);
    lcd_write_data(0x0C);
    lcd_write_data(0x11);
    lcd_write_data(0x13);
    lcd_write_data(0x2C);
    lcd_write_data(0x3F);
    lcd_write_data(0x44);
    lcd_write_data(0x51);
    lcd_write_data(0x2F);
    lcd_write_data(0x1F);
    lcd_write_data(0x1F);
    lcd_write_data(0x20);
    lcd_write_data(0x23);
 
    /* Display Inversion On */
    lcd_write_reg(0x21);
    lcd_write_reg(0x29);
 
	//lcd_clear(BACK_COLOR);
	/*打开显示*/
	// LCD_PWR=1; 背光	
}


/**************************************************************
函数名称 : lcd_display_on
函数功能 : 打开显示
输入参数 : 无
返回值  	 : 无
备注		 : 无
**************************************************************/
void lcd_display_on(void)
{
    //LCD_PWR(1);
	lcd_write_reg(0x29);
}

/**************************************************************
函数名称 : lcd_display_off
函数功能 : 关闭显示
输入参数 : 无
返回值  	 : 无
备注		 : 无
**************************************************************/
void lcd_display_off(void)
{
   // LCD_PWR(0);
	lcd_write_reg(0x28);
}

/**************************************************************
函数名称 : lcd_clear
函数功能 : lcd清屏函数
输入参数 : color：要清屏的颜色
返回值  	 : 无
备注		 : 先关闭显示，等到所有颜色数据写入到RAM后再打开显示
**************************************************************/
void lcd_clear(IPS_TypeDef *ips, u16 color)
{	
    u16 i, j;

	lcd_display_off();		/* 关闭显示 */
	lcd_set_address(0, 0, ips->_width - 1, ips->_height - 1);
	lcd_write_ram();
	
	for(i = 0; i < ips->_height; i++)
	{
		for(j = 0; j < ips->_width; j++)
		{
			lcd_write_data(color >> 8);
			lcd_write_data(color & 0x00ff);
		}
	}
	lcd_display_on();		/* 打开显示 */
}

/**************************************************************
函数名称 : lcd_write_ram
函数功能 : 使能写入数据到RAM
输入参数 : 无
返回值  	 : 无
备注		 : 无
**************************************************************/
void lcd_write_ram(void)
{
	lcd_write_reg(0x2C);
}

/**************************************************************
函数名称 : lcd_set_address
函数功能 : 设置坐标
输入参数 : x1,y1：起始地址，x2,y2：终点地址
返回值  	 : 无
备注		 : 无
**************************************************************/
void lcd_set_address(u16 x1, u16 y1, u16 x2, u16 y2)
{
    lcd_write_reg(0x2a);
    lcd_write_data(x1 >> 8);
    lcd_write_data(x1);
    lcd_write_data(x2 >> 8);
    lcd_write_data(x2);

    lcd_write_reg(0x2b);
    lcd_write_data(y1 >> 8);
    lcd_write_data(y1);
    lcd_write_data(y2 >> 8);
    lcd_write_data(y2);
}

void setAddrWindow(IPS_TypeDef *ips,uint8_t x0, uint8_t y0, uint8_t x1,
 uint8_t y1) {


	uint16_t x_start = x0 + ips->_xstart, x_end = x1 + ips->_xstart;
	uint16_t y_start = y0 + ips->_ystart, y_end = y1 + ips->_ystart;


	lcd_write_reg(ST7789_CASET); // Column addr set
	lcd_write_data(x_start >> 8);
	lcd_write_data(x_start & 0xFF);     // XSTART 
	lcd_write_data(x_end >> 8);
	lcd_write_data(x_end & 0xFF);     // XEND

	lcd_write_reg(ST7789_RASET); // Row addr set
	lcd_write_data(y_start >> 8);
	lcd_write_data(y_start & 0xFF);     // YSTART
	lcd_write_data(y_end >> 8);
	lcd_write_data(y_end & 0xFF);     // YEND

	lcd_write_reg(ST7789_RAMWR); // write to RAM
}

// 画像素点
void drawPixel(IPS_TypeDef *ips, int16_t x, int16_t y, uint16_t color) {

	if((x < 0) ||(x >= ips->_width) || (y < 0) || (y >= ips->_height)) return;

	setAddrWindow(ips, x,y,x+1,y+1);

	PIN_DC = 1;
	SPI2_ReadWriteByte(color >> 8);
	SPI2_ReadWriteByte(color);
}

// Bresenham's algorithm - thx wikpedia
void drawLine(IPS_TypeDef *ips, int16_t x0, int16_t y0,
			    int16_t x1, int16_t y1,
			    uint16_t color) {
  int16_t dx, dy, err, ystep;				
  int16_t steep = LG_abs(y1 - y0) > LG_abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }


  dx = x1 - x0;
  dy = LG_abs(y1 - y0);

  err = dx / 2;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(ips, y0, x0, color);
    } else {
      drawPixel(ips, x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
				

/*画水平线
x：x起点
y: y起点
w: 水平线长度*/
void drawFastHLine(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t w,
  uint16_t color) {

  // Rudimentary clipping
  if((x >= ips->_width) || (y >= ips->_height)) return;
  if((x+w-1) >= ips->_width)  w = ips->_width-x;
  setAddrWindow(ips,x, y, x+w-1, y);

  //uint8_t hi = color >> 8, lo = color;

  PIN_DC = 1;

  while (w--) {
    SPI2_ReadWriteByte(color >> 8);
    SPI2_ReadWriteByte(color);
  }
}
  
/*画竖线
x：x起点
y: y起点
h: 竖线长度*/
void drawFastVLine(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t h,
 uint16_t color) {

  // Rudimentary clipping
  if((x >= ips->_width) || (y >= ips->_height)) return;
  if((y+h-1) >= ips->_height) h = ips->_height-y;
  setAddrWindow(ips, x, y, x, y+h-1);
 
  //uint8_t hi = color >> 8, lo = color;
    
   PIN_DC = 1;

  while (h--) {
    SPI2_ReadWriteByte(color >> 8);
    SPI2_ReadWriteByte(color);
  }
}
 
//矩形，填充矩形
void drawRect(IPS_TypeDef *ips, int16_t x, int16_t y,
			    int16_t w, int16_t h,
			    uint16_t color) {
  drawFastHLine(ips, x, y, w, color);
  drawFastHLine(ips, x, y+h-1, w, color);
  drawFastVLine(ips, x, y, h, color);
  drawFastVLine(ips, x+w-1, y, h, color);
}
				
void fillRect(IPS_TypeDef *ips, u16 x, u16 y, u16 w, u16 h, u16 color) {
	  

    u8 hi,lo;	  
	  
	// rudimentary clipping (drawChar w/big text requires this)
	if((x >= ips->_width) || (y >= ips->_height)) return;
	if((x + w - 1) >= ips->_width)  w = ips->_width  - x;
	if((y + h - 1) >= ips->_height) h = ips->_height - y;

	setAddrWindow(ips, x, y, x+w-1, y+h-1);

	hi = color >> 8;
	lo = color;

	PIN_DC = 1;
	for(y=h; y>0; y--) {
	for(x=w; x>0; x--) {
	  SPI2_ReadWriteByte(hi);
	  SPI2_ReadWriteByte(lo);
	}
	}
}

//圆，填充圆
void drawCircle(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r,
    uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(ips, x0  , y0+r, color);
  drawPixel(ips, x0  , y0-r, color);
  drawPixel(ips, x0+r, y0  , color);
  drawPixel(ips, x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(ips, x0 + x, y0 + y, color);
    drawPixel(ips, x0 - x, y0 + y, color);
    drawPixel(ips, x0 + x, y0 - y, color);
    drawPixel(ips, x0 - x, y0 - y, color);
    drawPixel(ips, x0 + y, y0 + x, color);
    drawPixel(ips, x0 - y, y0 + x, color);
    drawPixel(ips, x0 + y, y0 - x, color);
    drawPixel(ips, x0 - y, y0 - x, color);
  }
}
	
/* 绘制1/4圆弧：
cornername: 0x01,0x02,0x04,0x08: 顺时针1,2,3,4
*/
void drawCircleHelper( IPS_TypeDef *ips, int16_t x0, int16_t y0,
               int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(ips, x0 + x, y0 + y, color);
      drawPixel(ips, x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      drawPixel(ips, x0 + x, y0 - y, color);
      drawPixel(ips, x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(ips, x0 - y, y0 + x, color);
      drawPixel(ips, x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(ips, x0 - y, y0 - x, color);
      drawPixel(ips, x0 - x, y0 - y, color);
    }
  }
}
			   
void fillCircle(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r,
			      uint16_t color) {
  drawFastVLine(ips, x0, y0-r, 2*r+1, color);
  fillCircleHelper(ips, x0, y0, r, 3, 0, color);
}

void fillCircleHelper(IPS_TypeDef *ips, int16_t x0, int16_t y0, int16_t r,
    uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {//右半圆
      drawFastVLine(ips, x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(ips, x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {//左半圆
      drawFastVLine(ips, x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(ips, x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

//三角形，填充三角形
// Draw a triangle
void drawTriangle(IPS_TypeDef *ips, int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				int16_t x2, int16_t y2, uint16_t color) {
  drawLine(ips, x0, y0, x1, y1, color);
  drawLine(ips, x1, y1, x2, y2, color);
  drawLine(ips, x2, y2, x0, y0, color);
}
				
// Fill a triangle
void fillTriangle (IPS_TypeDef *ips, int16_t x0, int16_t y0,
				  int16_t x1, int16_t y1,
				  int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;
  int16_t dx01, dy01, dx02, dy02, dx12, dy12, sa, sb;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(ips, a, y0, b-a+1, color);
    return;
  }

  
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(ips, a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(ips, a, y, b-a+1, color);
  }
}
				  
//圆角，填充圆角
// Draw a rounded rectangle
void drawRoundRect(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r, uint16_t color) {
  // smarter version
  drawFastHLine(ips, x+r  , y    , w-2*r, color); // Top
  drawFastHLine(ips, x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(ips, x    , y+r  , h-2*r, color); // Left
  drawFastVLine(ips, x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(ips, x+r    , y+r    , r, 1, color);
  drawCircleHelper(ips, x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(ips, x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(ips, x+r    , y+h-r-1, r, 8, color);
}
  
// Fill a rounded rectangle
void fillRoundRect(IPS_TypeDef *ips, int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint16_t color) {
  // smarter version
  fillRect(ips, x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(ips, x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(ips, x+r    , y+r, r, 2, h-2*r-1, color);
}
				 
//Bitmap


//全屏操作
/*全屏刷新颜色*/
void fillScreen(IPS_TypeDef *ips, uint16_t color) {
  fillRect(ips, 0, 0,  ips->_width, ips->_height, color);
}


void setRotation(IPS_TypeDef *ips, uint8_t r) {
  lcd_write_reg(ST7789_MADCTL);
  ips->_rotation = r % 4; // can't be higher than 3
  switch (ips->_rotation) {
   case 0:
     lcd_write_data(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);

     ips->_xstart = ips->_colstart + 0;
     ips->_ystart = ips->_rowstart + 80;//???
     break;
   
   case 1:
     lcd_write_data(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);

     ips->_ystart = ips->_colstart;
     ips->_xstart = ips->_rowstart+ 80;//???
     break;
   
  case 2:
     lcd_write_data(ST7789_MADCTL_RGB);
 
     ips->_xstart = ips->_colstart;
     ips->_ystart = ips->_rowstart;
     break;

   case 3:
     lcd_write_data(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);

     ips->_ystart = ips->_colstart;
     ips->_xstart = ips->_rowstart;
     break;
  }
}

void invertDisplay(u8 i) {
  lcd_write_reg(i ? ST7789_INVON : ST7789_INVOFF);
}


// Draw a character
void drawChar(IPS_TypeDef *ips, int16_t x, int16_t y, unsigned char c,
			    uint16_t color, uint16_t bg, uint8_t size) {

  int8_t i,j,line;
					
  if((x >= ips->_width)            || // Clip right
     (y >= ips->_height)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;

  for (i=0; i<6; i++ ) {

    if (i == 5) 
      line = 0x0;
    else 
      line = pgm_read_byte(font+(c*5)+i);
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          drawPixel(ips, x+i, y+j, color);
        else {  // big size
          fillRect(ips, x+(i*size), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1) // default size
          drawPixel(ips, x+i, y+j, bg);
        else {  // big size
          fillRect(ips, x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}
				
///////////////
void Shield(IPS_TypeDef *ips)
{
	fillScreen(ips,WHITE);
	fillCircle(ips,120,120,120,RED);
	fillCircle(ips,120,120,100,WHITE);
	fillCircle(ips,120,120,80,RED);
	fillCircle(ips,120,120,60,BLUE);
}

void drawArc(IPS_TypeDef *ips, int x, int y, int r, float start_angle_Deg, float end_angle_Deg, u16 color)
{
	for (float i = start_angle_Deg; i < end_angle_Deg; i = i + 1)
	{
	 drawPixel(ips, x + cos((i + 90.0)*DEG2RAD) * r, y + sin((i + 90.0)*DEG2RAD) * r, color); // center point is (50,100)
	}
}

void fillArc(IPS_TypeDef *ips, int x, int y, int start_angle, int seg_count, int rx, int ry, int w, u16 color)
{

  float seg = 1.0; // Segments are 3 degrees wide = 120 segments for 360 degrees
  float inc = 1.0; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i + 90.0) * DEG2RAD);
    float sy = sin((i + 90.0) * DEG2RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg + 90.0) * DEG2RAD);
    float sy2 = sin((i + seg + 90.0) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    fillTriangle(ips, x0, y0, x1, y1, x2, y2, color);
    fillTriangle(ips, x1, y1, x2, y2, x3, y3, color);
  }
}


u16 RGB24toRGB16(u32 RGB32)
{
	u8 r = (RGB32>>16)&0xFF;
	u8 g = (RGB32>>8)&0xFF;
	u8 b = RGB32&0xFF;
	u16 tmp;
	r=(r>>3)&0x1f;
	g=(g>>2)&0x3f;
	b=(b>>3)&0x1f;
	tmp=(r<<11)+(g<<5)+b;
	return tmp;
}

/**************************************************************
函数名称 : lcd_show_char
函数功能 : lcd显示一个字符
输入参数 : x,y:起始坐标
		   num:要显示的字符:" "--->"~"
		   size:字体大小
		   mode:叠加方式(1)还是非叠加方式(0)
返回值  	 : 无
备注		 : 无
**************************************************************/
void lcd_show_char(IPS_TypeDef *ips, u16 x, u16 y, u8 num, u8 size, u8 mode)
{  							  
    u16 temp, t1, t;
	u16 y0 = y;
	u16 csize = ((size / 8) + ((size % 8) ? 1 : 0)) * (size/2);	/* 得到字体一个字符对应点阵集所占的字节数	 */
	
 	num = num - ' ';	/* 得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库） */
	
	for(t = 0; t < csize; t++)	/*遍历打印所有像素点到LCD */
	{   
     	if(16 == size)
		{
			temp = asc2_1608[num][t];	/* 调用1608字体 */
     	}
		else if(24 == size)
		{
			temp = asc2_2412[num][t];	/* 调用2412字体 */
		}
		else if(32 == size)
		{
			temp = asc2_3216[num][t];	/* 调用3216数码管字体 */
		}
		else if(48 == size)
		{
			temp = asc2_4824[num][t];
		}
		else
		{	
			return;		/* 没有找到对应的字库 */
		}
		for(t1 = 0; t1 < 8; t1++)	/* 打印一个像素点到液晶 */
		{			    
			if(temp & 0x80)
			{
				drawPixel(ips, x, y, POINT_COLOR);
			}
			else if(0 == mode)
			{
				drawPixel(ips, x, y, BACK_COLOR);
			}
			temp <<= 1;
			y++;
			
			if(y >= ips->_height)
			{
				return;		/* 超区域了 */
			}
			if((y - y0) == size)
			{
				y = y0;
				x++;
				if(x >= ips->_width)
				{
					return;	/* 超区域了 */
				}
				break;
			}
		}  	 
	}  	    	   	 	  
} 


/**************************************************************
函数名称 : lcd_show_string
函数功能 : lcd显示字符串
输入参数 : x,y:起始坐标
		   width,height：区域大小
		   *p:字符串起始地址
		   size:字体大小
		   mode:叠加方式(1)还是非叠加方式(0)
返回值  	 : 无
备注		 : 无
**************************************************************/
void lcd_show_string(IPS_TypeDef *ips, u16 x, u16 y, u16 width, u16 height, u8 *p, u8 size, u8 mode)
{         
	u16 x0 = x;
	width += x;
	height += y;
	
    while((*p<='~') && (*p>=' '))		/* 判断是不是非法字符! */
    {       
        if(x >= width)
		{
			x = x0; 
			y += size;
		}
		
        if(y >= height)
		{	
			break;
        }
        lcd_show_char(ips, x, y, *p, size, mode);
        x += size/2;
        p++;
    }  
}

void lcd_show_pointer(IPS_TypeDef *ips, u16 x, u16 y, u16 length, float angle_DEG_last, float angle_DEG, uint16_t color)
{
	u16 x0,y0,x1,y1,x_last,y_last;
	x0 = x;
	y0 = y;
	x1 = x0 - length*sin(angle_DEG*DEG2RAD);
	y1 = y0 + length*cos(angle_DEG*DEG2RAD);
	
	x_last = x0 - length*sin(angle_DEG_last*DEG2RAD);
	y_last = y0 + length*cos(angle_DEG_last*DEG2RAD);
		
	drawLine(ips, x0, y0, x_last , y_last , BLACK);
	drawLine(ips, x0, y0, x1, y1, color);
	//fillTriangle(ips, x0, y0, x1, y1, x2, y2, color);
}

///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// reverses a string 'str' of length 'len' 
void reverse(char *str, int len) 
{ 
    int i=0, j=len-1, temp; 
    while (i<j) 
    { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; j--; 
    } 
} 
  
 // Converts a given integer x to string str[].  d is the number 
 // of digits required in output. If d is more than the number 
 // of digits in x, then 0s are added at the beginning. 
int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) 
    { 
        str[i++] = (x%10) + '0'; 
        x = x/10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 
  
// Converts a floating point number to string.
/*
ftoa(n, res, afterpoint)
n          --> Input Number
res[]      --> Array where output string to be stored
afterpoint --> Number of digits to be considered after point.

For example ftoa(1.555, str, 2) should store "1.55" in res and
ftoa(1.555, str, 0) should store "1" in res.
*/
void ftoa(float n, char *res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) 
    { 
        res[i] = '.';  // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter is needed 
        // to handle cases like 233.007 
        fpart = fpart * pow(10, afterpoint); 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    } 
}




