# 1.3寸IPS液晶屏示例程序

### 硬件：

STM32F103C8T5最小系统板，STLINK下载程序，miniUSB供电。

@[STM32F103C8T5最小系统板](https://hacktronics.co.in/arm-microcontroller/stm32f103c8t6-arm-stm32-minimum-system-learning-evaluation-development-board-module)
<p align="center">
	<img src=".\pic\stm32f103c8t6 .jpg width="400">
    <br>
    <em>Fig. 1: STM32F103C8T5最小系统板</em>
</p>

IPS240x240液晶屏，ST7789驱动，SPI接口，依次定义为：GND，VCC，SCL，SDA，RES，DC，BLK.



ST-LINK下载器。

### 硬件引脚连接:

STM32F103C8T6最小系统板<--------->IPS

5V<--------->VCC

GND<--------->GND

PB13(SPI2-SCK) <---------> SCL

PB15(SPI2-MOSI) <---------> SDA

PB0 <--- >DC

PB1 <--- > RST

### 程序功能：

程序下载之后，IPS屏将点亮，并依次运行示例程序。

### 参考：

1. STM32F103C8T5参考正点原子的模板程序：

2. 
