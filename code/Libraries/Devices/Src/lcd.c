/********************************************************************************
 *
 * @file      lcd.c
 * @brief     driver for LCD
 * @author    SJX
 * @date      2018-04-19
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "lcd.h"
#include <stdarg.h>
#include <stdio.h>
#include "common.h"
#include "font.h"
#include "spi.h"

/********************************************************************************
 * Global variables
 ********************************************************************************/
bool display_on_LCD = true;

/********************************************************************************
 * Local variables
 ********************************************************************************/
static font_t fontList[] = {
    {"Font_6x12", 6, 12, Font_6x12},
};

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     initialize LCD
 * @param     none
 * @return    none
 * @note      LCD_SCK PTB2
 *            LCD_SDA PTB3
 *            LCD_A0 PTB1
 *            LCD_RESET PTB0
 *            LCD_CS PTF3
 ************************************************************/
void LCD_Init(void) {
  /* 初始化 GPIO */
	
  CONFIG_PIN_AS_GPIO(LCD_A0_PORT, LCD_A0_PIN, OUTPUT);
  CONFIG_PIN_AS_GPIO(LCD_RESET_PORT, LCD_RESET_PIN, OUTPUT);
  CONFIG_PIN_AS_GPIO(LCD_CS_PORT, LCD_CS_PIN, OUTPUT);

  /* 初始化 SPI ，SPI 的最高波特率等于总线时钟除以 2 */
  SPI_QuickInit(LCD_SPI, BUS_CLOCK / 2);

  /* 硬件复位 LCD */
  LCD_RESET_LOW;
  DelayMs(100);
  LCD_RESET_HIGH;
  DelayMs(100);

  /* LCD 初始化序列 */
  /* 片选 */
  LCD_CS_LOW;

  /* 退出睡眠模式 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x11);
  DelayMs(20);

  /* 设置默认 Gamma 值 */
  SPI_ReadWriteByte(LCD_SPI, 0x26);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x04);

  /* 设置帧率 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xB1);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x0E);
  SPI_ReadWriteByte(LCD_SPI, 0x10);

  /* 设置 VRH1[4:0] & VC[2:0] for VCI1&GVDD */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xC0);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x08);
  SPI_ReadWriteByte(LCD_SPI, 0x00);

  /* 设置 BT[2:0] for AVDD & VCL & VGH & VGL */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xC1);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x05);

  /* 设置 VMH[6:0] & VML[6:0] for VOMH & VCOML */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xC5);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x38);
  SPI_ReadWriteByte(LCD_SPI, 0x40);

  /* 设置颜色格式 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x3A);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x05);

  /* 设置存储通道控制 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x36);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0xC8);

  /* 设置列地址 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x2A);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x00);
  SPI_ReadWriteByte(LCD_SPI, 0x00);
  SPI_ReadWriteByte(LCD_SPI, 0x00);
  SPI_ReadWriteByte(LCD_SPI, 0x80);

  /* 设置页地址 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x2B);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x00);
  SPI_ReadWriteByte(LCD_SPI, 0x20);
  SPI_ReadWriteByte(LCD_SPI, 0x00);
  SPI_ReadWriteByte(LCD_SPI, 0xA0);

  /* 设置显示翻转控制 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xB4);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x00);

  /* 使能 Gamma 位 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xF2);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x01);

  /* 设置正 Gamma 校正参数 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xE0);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x3F);
  SPI_ReadWriteByte(LCD_SPI, 0x22);
  SPI_ReadWriteByte(LCD_SPI, 0x20);
  SPI_ReadWriteByte(LCD_SPI, 0x30);
  SPI_ReadWriteByte(LCD_SPI, 0x29);
  SPI_ReadWriteByte(LCD_SPI, 0x0C);
  SPI_ReadWriteByte(LCD_SPI, 0x4E);
  SPI_ReadWriteByte(LCD_SPI, 0xB7);
  SPI_ReadWriteByte(LCD_SPI, 0x3C);
  SPI_ReadWriteByte(LCD_SPI, 0x19);
  SPI_ReadWriteByte(LCD_SPI, 0x22);
  SPI_ReadWriteByte(LCD_SPI, 0x1E);
  SPI_ReadWriteByte(LCD_SPI, 0x02);
  SPI_ReadWriteByte(LCD_SPI, 0x01);
  SPI_ReadWriteByte(LCD_SPI, 0x00);

  /* 设置负 Gamma 校正参数 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0xE1);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, 0x00);
  SPI_ReadWriteByte(LCD_SPI, 0x1B);
  SPI_ReadWriteByte(LCD_SPI, 0x1F);
  SPI_ReadWriteByte(LCD_SPI, 0x0F);
  SPI_ReadWriteByte(LCD_SPI, 0x16);
  SPI_ReadWriteByte(LCD_SPI, 0x13);
  SPI_ReadWriteByte(LCD_SPI, 0x31);
  SPI_ReadWriteByte(LCD_SPI, 0x84);
  SPI_ReadWriteByte(LCD_SPI, 0x43);
  SPI_ReadWriteByte(LCD_SPI, 0x06);
  SPI_ReadWriteByte(LCD_SPI, 0x1D);
  SPI_ReadWriteByte(LCD_SPI, 0x21);
  SPI_ReadWriteByte(LCD_SPI, 0x3D);
  SPI_ReadWriteByte(LCD_SPI, 0x3E);
  SPI_ReadWriteByte(LCD_SPI, 0x3F);

  /* 开显示 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x29);

  /* 取消片选 */
  LCD_CS_HIGH;

  /* 全白背景色 */
  LCD_DisplayBackgroundColor(WHITE);
}

/************************************************************
 * @brief     put LCD to sleep
 * @param     none
 * @return    none
 ************************************************************/
void LCD_Sleep(void) {
  LCD_CS_LOW;

  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x28);
  SPI_ReadWriteByte(LCD_SPI, 0x10);

  LCD_CS_HIGH;
}

/************************************************************
 * @brief     wakeup LCD
 * @param     none
 * @return    none
 ************************************************************/
void LCD_WakeUp(void) {
  LCD_CS_LOW;

  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x11);
  SPI_ReadWriteByte(LCD_SPI, 0x29);

  LCD_CS_HIGH;
}

/************************************************************
 * @brief     display background color
 * @param     color to be displayed
 * @return    none
 ************************************************************/
void LCD_DisplayBackgroundColor(uint16_t color) {
  LCD_CS_LOW;

  uint8_t i, j;

  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x2C);
  LCD_A0_HIGH;

  for (i = 0; i < 160; i++) {
    for (j = 0; j < 128; j++) {
      SPI_ReadWriteByte(LCD_SPI, color >> 8);
      SPI_ReadWriteByte(LCD_SPI, color);
    }
  }

  LCD_CS_HIGH;
}

/************************************************************
 * @brief     draw point on LCD
 * @param     x horizontal coordinate
 *            y vertical coordinate
 *            color color of the point
 * @return    none
 ************************************************************/
void LCD_DrawPoint(uint8_t x, uint8_t y, uint16_t color) {
  y += 32;

  LCD_CS_LOW;

  /* 设置列地址 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x2A);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, x);
  SPI_ReadWriteByte(LCD_SPI, x);

  /* 设置页地址 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x2B);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, y);
  SPI_ReadWriteByte(LCD_SPI, y);

  /* 写入数据 */
  LCD_A0_LOW;
  SPI_ReadWriteByte(LCD_SPI, 0x2C);
  LCD_A0_HIGH;
  SPI_ReadWriteByte(LCD_SPI, color >> 8);
  SPI_ReadWriteByte(LCD_SPI, color);

  LCD_CS_HIGH;
}

/************************************************************
 * @brief     display character
 * @param
 * @return    none
 ************************************************************/
void LCD_DispChar(char c, int x, int y, const char *pdata, int font_xsize,
                  int font_ysize, int fcolor, int bcolor) {
  uint8_t j, pos, t;
  uint8_t temp;
  uint8_t XNum;
  uint32_t base;
  XNum = (font_xsize / 8) + 1;

  if (font_ysize % 8 == 0) {
    XNum--;
  }
  if (c < ' ') {
    return;
  }

  c = c - ' ';
  base = (c * XNum * font_ysize);

  for (j = 0; j < XNum; j++) {
    for (pos = 0; pos < font_ysize; pos++) {
      temp = (uint8_t)pdata[base + pos + j * font_ysize];
      if (j < XNum) {
        for (t = 0; t < 8; t++) {
          if ((temp >> t) & 0x01) {
            LCD_DrawPoint(x + t, y + pos, fcolor);
          } else {
            LCD_DrawPoint(x + t, y + pos, bcolor);
          }
        }
      } else {
        for (t = 0; t < font_xsize % 8; t++) {
          if ((temp >> t) & 0x01) {
            LCD_DrawPoint(x + t, y + pos, fcolor);
          } else {
            LCD_DrawPoint(x + t, y + pos, bcolor);
          }
        }
      }
    }
    x += 8;
  }
}

/************************************************************
 * @brief     print string on LCD
 * @param     x horizontal coordinate
 *            y vertical coordinate
 *            format data format
 * @return    number of characters
 ************************************************************/
int LCD_Printf(int x, int y, const char *format, ...) {
  int chars;
  int i;
  __va_list ap;
  char printbuffer[64];
  va_start(ap, format);
  chars = vsprintf(printbuffer, format, ap);
  va_end(ap);

  for (i = 0; i < chars; i++) {
    LCD_DispChar(printbuffer[i], x + i * fontList[0].x_size, y,
                 fontList[0].data, fontList[0].x_size, fontList[0].y_size,
                 0xFFFF, 0x0000);
  }
  return chars;
}
