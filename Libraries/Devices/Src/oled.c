/********************************************************************************
 *
 * @file      oled.c
 * @brief     driver for OLED
 * @author    SJX
 * @date      2018-05-03
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "oled.h"
#include <stdarg.h>
#include <stdio.h>
#include "common.h"
#include "font.h"

/********************************************************************************
 * Local variables
 ********************************************************************************/
static font_t fontList[] = {
    {"Font_8x16", 8, 16, Font_8x16},
};

/********************************************************************************
 * Local functions
 ********************************************************************************/

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     initialize OLED
 * @param     none
 * @return    none
 * @note      OLED_SCK PTB2
 *            OLED_SDA PTB3
 *            OLED_DC PTB1
 *            OLED_RESET PTB0
 ************************************************************/
void OLED_Init(void) {
  /* 初始化 GPIO */
  CONFIG_PIN_AS_GPIO(OLED_DC_PORT, OLED_DC_PIN, OUTPUT);
  CONFIG_PIN_AS_GPIO(OLED_RESET_PORT, OLED_RESET_PIN, OUTPUT);

  /* 初始化 SPI ，SPI 的最高波特率等于总线时钟除以 2 */
  SPI_QuickInit(OLED_SPI, BUS_CLOCK / 2);

  /* 硬件复位 OLED */
  OLED_RESET_LOW;
  DelayMs(100);
  OLED_RESET_HIGH;
  DelayMs(100);

  /* OLED 初始化序列 */
  /* 关显示 */
  OLED_WriteCmd(0xAE);
  /* 设置列地址 */
  OLED_WriteCmd(0x00);
  OLED_WriteCmd(0x10);
  /* set mapping RAM display start line */
  OLED_WriteCmd(0x40);  // 0x00 ~ 0x3F
  /* 亮度 */
  OLED_WriteCmd(0x81);
  OLED_WriteCmd(0xCF);
  /* 设置列映射，0xA0 左右反置，0xA1 正常 */
  OLED_WriteCmd(0xA1);
  /* 设置行扫描方向，0xC0 上下反置，0xC8 正常 */
  OLED_WriteCmd(0xC8);
  /* inverse display on, 0xA6 disable, 0xA7 enable */
  OLED_WriteCmd(0xA6);
  /* set multiplex ratio, 1/64 duty */
  OLED_WriteCmd(0xA8);
  OLED_WriteCmd(0x3F);  // 0x0F ~ 0x3F
  /* set display offset shift mapping RAM counter */
  OLED_WriteCmd(0xD3);
  OLED_WriteCmd(0x00);  // no offset, 0x00 ~ 0x3F
  /* 帧率 100 */
  OLED_WriteCmd(0xD5);
  OLED_WriteCmd(0x80);
  /* set pre-charge period */
  OLED_WriteCmd(0xD9);
  OLED_WriteCmd(0xF1);  // pre-charge 15 clocks and discharge 1 clock
  /* set sequential configuration */
  OLED_WriteCmd(0xDA);
  OLED_WriteCmd(0X12);  // 0x02 / 0x12
  /* set VCOM deselect level */
  OLED_WriteCmd(0xDB);
  OLED_WriteCmd(0x40);
  /* set page addressing mode */
  OLED_WriteCmd(0x20);
  OLED_WriteCmd(0x02);  // 0x00 / 0x01 / 0x02
  /* charge pump, 0x10 disable, 0x14 enable */
  OLED_WriteCmd(0x8D);
  OLED_WriteCmd(0x14);
  /* entire display on, 0xA4 disable, 0xA5 enable */
  OLED_WriteCmd(0xA4);
  /* 开显示 */
  OLED_WriteCmd(0xAF);

  OLED_Clear();
  OLED_SetPos(0, 0);
}

/************************************************************
 * @brief     turn on display
 * @param     none
 * @return    none
 ************************************************************/
void OLED_On(void) {
  OLED_WriteCmd(0x8D);
  OLED_WriteCmd(0x14);
  OLED_WriteCmd(0xAF);
}

/************************************************************
 * @brief     turn off display
 * @param     none
 * @return    none
 ************************************************************/
void OLED_Off(void) {
  OLED_WriteCmd(0x8D);
  OLED_WriteCmd(0x10);
  OLED_WriteCmd(0xAE);
}

/************************************************************
 * @brief     clear OLED
 * @param     none
 * @return    none
 ************************************************************/
void OLED_Clear(void) {
  uint8_t page, i;
  for (page = 0; page < OLED_PAGE_NUM; page++) {
    OLED_WriteCmd(0xB0 + page);
    OLED_WriteCmd(0x00);  // 列低地址
    OLED_WriteCmd(0x10);  // 列高地址
    for (i = 0; i < OLED_X_SIZE; i++) {
      OLED_WriteData(0x00);
    }
  }
}

/************************************************************
 * @brief     display character on OLED
 * @param     x horizontal coordinate
 *            y vertical coordinate
 *            c character to be displayed
 * @return    none
 ************************************************************/
void OLED_DisplayChar(uint8_t x, uint8_t y, char c) {
  if (c < ' ') {
    return;
  }

  uint8_t i = 0;
  c = c - ' ';
  if (x >= OLED_X_SIZE) {
    x %= OLED_X_SIZE;
    y += fontList[0].y_size;
  }
  y = (y % OLED_Y_SIZE) / OLED_PAGE_SIZE;

  if (fontList[0].y_size <= OLED_PAGE_SIZE) {
    OLED_SetPos(x, y);
    for (i = 0; i < fontList[0].x_size; i++) {
      OLED_WriteData(fontList[0].data[c * fontList[0].x_size + i]);
    }
  } else if (fontList[0].y_size <= OLED_PAGE_SIZE * 2) {
    OLED_SetPos(x, y);
    for (i = 0; i < fontList[0].y_size / 2; i++) {
      OLED_WriteData(fontList[0].data[c * fontList[0].y_size + i]);
    }
    OLED_SetPos(x, y + 1);
    for (i = 0; i < fontList[0].y_size / 2; i++) {
      OLED_WriteData(fontList[0].data[c * fontList[0].y_size + i +
                                      fontList[0].y_size / 2]);
    }
  } else {
  }
}

/************************************************************
 * @brief     display string on OLED
 * @param     x horizontal coordinate
 *            y vertical coordinate
 *            format data format
 * @return    number of characters
 ************************************************************/
uint16_t OLED_Printf(uint8_t x, uint8_t y, const char *format, ...) {
  __va_list ap;
  char printBuffer[64];
  va_start(ap, format);
  uint16_t charCnt = vsprintf(printBuffer, format, ap);
  va_end(ap);

  for (uint16_t i = 0; i < charCnt; i++) {
    OLED_DisplayChar(x + i * fontList[0].x_size, y, printBuffer[i]);
  }

  return charCnt;
}
