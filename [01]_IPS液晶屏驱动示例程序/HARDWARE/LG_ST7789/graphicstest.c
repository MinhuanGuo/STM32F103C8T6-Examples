#include "graphicstest.h"


void testlines(IPS_TypeDef *ips, uint16_t color) {
	int16_t x,y;
	
	fillScreen(ips, BLACK);
	for (x = 0; x <  ips->_width; x += 6) {
	 drawLine(ips, 0, 0, x,  ips->_height - 1, color);
	}
	for (y = 0; y <  ips->_height; y += 6) {
	 drawLine(ips, 0, 0,  ips->_width - 1, y, color);
	}

	fillScreen(ips, BLACK);
	for (x = 0; x <  ips->_width; x += 6) {
	 drawLine(ips,  ips->_width - 1, 0, x,  ips->_height - 1, color);
	}
	for (y = 0; y <  ips->_height; y += 6) {
	 drawLine(ips,  ips->_width - 1, 0, 0, y, color);
	}

	fillScreen(ips, BLACK);
	for (x = 0; x <  ips->_width; x += 6) {
	 drawLine(ips, 0,  ips->_height - 1, x, 0, color);
	}
	for (y = 0; y <  ips->_height; y += 6) {
	 drawLine(ips, 0,  ips->_height - 1,  ips->_width - 1, y, color);
	}

	fillScreen(ips, BLACK);
	for (x = 0; x <  ips->_width; x += 6) {
	 drawLine(ips,  ips->_width - 1,  ips->_height - 1, x, 0, color);
	}
	for (y = 0; y <  ips->_height; y += 6) {
	 drawLine(ips,  ips->_width - 1,  ips->_height - 1, 0, y, color);
	}
}

void testfastlines(IPS_TypeDef *ips, uint16_t color1, uint16_t color2) {
  int16_t x,y;
  fillScreen(ips, BLACK);
	
  for (y = 0; y < ips->_height; y += 5) {
    drawFastHLine(ips, 0, y, ips->_width, color1);
  }
  for (x = 0; x < ips->_width; x += 5) {
    drawFastVLine(ips, x, 0, ips->_height, color2);
  }
}


void testdrawrects(IPS_TypeDef *ips, uint16_t color) {
  int16_t x;
  fillScreen(ips, BLACK);
  for (x = 0; x < ips->_width; x += 6) {
    drawRect(ips, ips->_width / 2 - x / 2, ips->_height / 2 - x / 2 , x, x, color);
  }
}

void testfillrects(IPS_TypeDef *ips, uint16_t color1, uint16_t color2) {
  int16_t x;
  fillScreen(ips, BLACK);
  for (x = ips->_width - 1; x > 6; x -= 6) {
    fillRect(ips, ips->_width / 2 - x / 2, ips->_height / 2 - x / 2 , x, x, color1);
    drawRect(ips, ips->_width / 2 - x / 2, ips->_height / 2 - x / 2 , x, x, color2);
  }
}

void testfillcircles(IPS_TypeDef *ips, uint8_t radius, uint16_t color) {
	int16_t x,y;
  for (x = radius; x <  ips->_width; x += radius * 2) {
    for (y = radius; y <  ips->_height; y += radius * 2) {
       fillCircle(ips, x, y, radius, color);
    }
  }
}

void testdrawcircles(IPS_TypeDef *ips, uint8_t radius, uint16_t color) {
	int16_t x,y;
  for (x = 0; x <  ips->_width + radius; x += radius * 2) {
    for (y = 0; y <  ips->_height + radius; y += radius * 2) {
       drawCircle(ips, x, y, radius, color);
    }
  }
}

void testtriangles(IPS_TypeDef *ips) {
  int color = 0xF800;
  int t;
  int w =  ips->_width / 2;
  int x =  ips->_height - 1;
  int y = 0;
  int z =  ips->_width;
  fillScreen(ips, BLACK);
  for (t = 0 ; t <= 15; t++) {
     drawTriangle(ips, w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects(IPS_TypeDef *ips) {
   
  int color = 100;
  int i;
  int t;
  fillScreen(ips, BLACK);
  for (t = 0 ; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w =  ips->_width - 2;
    int h =  ips->_height - 2;
    for (i = 0 ; i <= 16; i += 1) {
       drawRoundRect(ips, x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void mediabuttons(IPS_TypeDef *ips) {
  // play
   fillScreen(ips, BLACK);
   fillRoundRect(ips, 25, 10, 78, 60, 8, WHITE);
   fillTriangle(ips, 42, 20, 42, 60, 90, 40, RED);
  delay_ms(500);
  // pause
   fillRoundRect(ips, 25, 90, 78, 60, 8, WHITE);
   fillRoundRect(ips, 39, 98, 20, 45, 5, GREEN);
   fillRoundRect(ips, 69, 98, 20, 45, 5, GREEN);
  delay_ms(500);
  // play color
   fillTriangle(ips, 42, 20, 42, 60, 90, 40, BLUE);
  delay_ms(50);
  // pause color
   fillRoundRect(ips, 39, 98, 20, 45, 5, RED);
   fillRoundRect(ips, 69, 98, 20, 45, 5, RED);
  // play color
   fillTriangle(ips, 42, 20, 42, 60, 90, 40, GREEN);
}






