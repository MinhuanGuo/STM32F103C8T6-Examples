# 1.3寸IPS液晶屏示例程序

V1:2019.04.19

<<<<<<< HEAD
### 硬件：
=======
@[STM32F103C8T5最小系统板](https://hacktronics.co.in/arm-microcontroller/stm32f103c8t6-arm-stm32-minimum-system-learning-evaluation-development-board-module)
<p align="center">
	<img src=".\pic\stm32f103c8t6 .jpg width="400">
    <br>
    <em>Fig. 1: STM32F103C8T5最小系统板</em>
</p>

IPS240x240液晶屏，ST7789驱动，SPI接口，依次定义为：GND，VCC，SCL，SDA，RES，DC，BLK.
>>>>>>> 1d7723b754692654bb1f4882205345f3b60ccf06

[STM32F103C8T5最小系统板](https://hacktronics.co.in/arm-microcontroller/stm32f103c8t6-arm-stm32-minimum-system-learning-evaluation-development-board-module)，STLINK下载程序，miniUSB供电。

[IPS240x240液晶屏](<https://www.banggood.com/1_3-Inch-IPS-TFT-LCD-Display-240240-Color-HD-LCD-Screen-3_3V-ST7789-Driver-Module-p-1383404.html?cur_warehouse=CN>)，ST7789驱动，SPI接口，依次定义为：GND，VCC，SCL，SDA，RES，DC，BLK.

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

1. 正点原子的模板程序《STM32F1开发指南(精英版)-库函数版本_V1.0》

<<<<<<< HEAD
2. [Arduino版的ST7789和Adafruit_GFX程序](https://github.com/ananevilya/Arduino-ST7789-Library.git)
=======
2. 
>>>>>>> 1d7723b754692654bb1f4882205345f3b60ccf06
