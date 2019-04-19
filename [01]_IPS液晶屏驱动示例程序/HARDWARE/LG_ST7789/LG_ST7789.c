#include "LG_ST7789.h"
#include "spi.h"
#include "delay.h"

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
	
	//��һ����ST7789�˿�����DC,RST��
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //PB0/1������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB

 	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);  //PB0/1����

	//�ڶ�����SPI2����,ʹ�ܣ�
	SPI2_Init();		   			//��ʼ��SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);		//����Ϊ21Mʱ��,����ģʽ :SPI_BaudRatePrescaler_4	
	
	ST7789_init();
}


///////////////////////////////////////////////////////////////////
///////// ������
///////////////////////////////////
/**************************************************************
�������� : lcd_write_reg
�������� : ��lcd����оƬдһ������
������� : reg��Ҫд�������
����ֵ  	 : ��
��ע		 : LCD_WRΪ0ʱ��ʾд����
**************************************************************/
void lcd_write_reg(u8 reg)
{
	PIN_DC = 0;
	SPI2_ReadWriteByte(reg);	
}

/**************************************************************
�������� : lcd_write_data
�������� : ��lcd����оƬдһ������
������� : data��Ҫд�������
����ֵ  	 : ��
��ע		 : LCD_WRΪ1ʱ��ʾд����
**************************************************************/
void lcd_write_data(u8 data)
{
	PIN_DC = 1;
	SPI2_ReadWriteByte(data);
}


/**************************************************************
�������� : lcd_init
�������� : lcd��ʼ��
������� : ��
����ֵ  	 : ��
��ע		 : ��
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
	/*����ʾ*/
	// LCD_PWR=1; ����	
}


/**************************************************************
�������� : lcd_display_on
�������� : ����ʾ
������� : ��
����ֵ  	 : ��
��ע		 : ��
**************************************************************/
void lcd_display_on(void)
{
    //LCD_PWR(1);
	lcd_write_reg(0x29);
}

/**************************************************************
�������� : lcd_display_off
�������� : �ر���ʾ
������� : ��
����ֵ  	 : ��
��ע		 : ��
**************************************************************/
void lcd_display_off(void)
{
   // LCD_PWR(0);
	lcd_write_reg(0x28);
}

/**************************************************************
�������� : lcd_clear
�������� : lcd��������
������� : color��Ҫ��������ɫ
����ֵ  	 : ��
��ע		 : �ȹر���ʾ���ȵ�������ɫ����д�뵽RAM���ٴ���ʾ
**************************************************************/
void lcd_clear(IPS_TypeDef *ips, u16 color)
{	
    u16 i, j;

	lcd_display_off();		/* �ر���ʾ */
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
	lcd_display_on();		/* ����ʾ */
}

/**************************************************************
�������� : lcd_write_ram
�������� : ʹ��д�����ݵ�RAM
������� : ��
����ֵ  	 : ��
��ע		 : ��
**************************************************************/
void lcd_write_ram(void)
{
	lcd_write_reg(0x2C);
}

/**************************************************************
�������� : lcd_set_address
�������� : ��������
������� : x1,y1����ʼ��ַ��x2,y2���յ��ַ
����ֵ  	 : ��
��ע		 : ��
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

// �����ص�
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
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }


  dx = x1 - x0;
  dy = abs(y1 - y0);

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
				

/*��ˮƽ��
x��x���
y: y���
w: ˮƽ�߳���*/
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
  
/*������
x��x���
y: y���
h: ���߳���*/
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
 
//���Σ�������
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

//Բ�����Բ
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
	
/* ����1/4Բ����
cornername: 0x01,0x02,0x04,0x08: ˳ʱ��1,2,3,4
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

    if (cornername & 0x1) {//�Ұ�Բ
      drawFastVLine(ips, x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(ips, x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {//���Բ
      drawFastVLine(ips, x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(ips, x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

//�����Σ����������
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
				  
//Բ�ǣ����Բ��
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


//ȫ������
/*ȫ��ˢ����ɫ*/
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


