# 1.3寸IPS液晶屏示例程序

V1:2019.04.19

### 硬件：

1. [STM32F103C8T5最小系统板](<https://detail.tmall.com/item.htm?spm=a230r.1.14.23.1fe0479ebRMkwz&id=559305712053&ns=1&abbucket=10>)，STLINK下载程序，miniUSB供电。

2. [IPS240x240液晶屏](<https://item.taobao.com/item.htm?spm=a230r.1.14.20.139e4e1e7bdjz0&id=565591692266&ns=1&abbucket=10#detail>)，ST7789驱动，SPI接口，依次定义为：GND，VCC，SCL，SDA，RES，DC，BLK，65K色彩，即16位色彩，RGB565，参考色彩工具：[16 bit color generator](<https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html>)

3. ST-LINK下载器。

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
2. [Arduino版的ST7789和Adafruit_GFX程序](https://github.com/ananevilya/Arduino-ST7789-Library.git)
