#ifndef _GRAPHICSTEST_H
#define _GRAPHICSTEST_H

#include "LG_ST7789.h"
#include "delay.h"

void testlines(IPS_TypeDef *ips, uint16_t color);
void testfastlines(IPS_TypeDef *ips, uint16_t color1, uint16_t color2);
void testdrawrects(IPS_TypeDef *ips, uint16_t color);
void testfillrects(IPS_TypeDef *ips, uint16_t color1, uint16_t color2);
void testfillcircles(IPS_TypeDef *ips, uint8_t radius, uint16_t color);
void testdrawcircles(IPS_TypeDef *ips, uint8_t radius, uint16_t color);
void testtriangles(IPS_TypeDef *ips);
void testroundrects(IPS_TypeDef *ips);
void mediabuttons(IPS_TypeDef *ips);

#endif
