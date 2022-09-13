/********************************************************************************
 *
 * @file      lcd.h
 * @brief     header file for lcd.c
 * @author    SJX
 * @date      2018-04-19
 *
 ********************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "derivative.h"
#include "gpio.h"

/********************************************************************************
 * Macros
 ********************************************************************************/
/************************************************************
 * pins
 ************************************************************/
#define LCD_SPI SPI1
#define LCD_A0_PORT PTD
#define LCD_A0_PIN PTD5
#define LCD_RESET_PORT PTD
#define LCD_RESET_PIN PTD6
#define LCD_CS_PORT PTF
#define LCD_CS_PIN PTF3

#define LCD_A0_LOW OUTPUT_CLEAR(LCD_A0_PORT, LCD_A0_PIN)
#define LCD_A0_HIGH OUTPUT_SET(LCD_A0_PORT, LCD_A0_PIN)
#define LCD_RESET_LOW OUTPUT_CLEAR(LCD_RESET_PORT, LCD_RESET_PIN)
#define LCD_RESET_HIGH OUTPUT_SET(LCD_RESET_PORT, LCD_RESET_PIN)
#define LCD_CS_LOW OUTPUT_CLEAR(LCD_CS_PORT, LCD_CS_PIN)
#define LCD_CS_HIGH OUTPUT_SET(LCD_CS_PORT, LCD_CS_PIN)

/************************************************************
 * colors
 ************************************************************/
#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430

/********************************************************************************
 * Global variables
 ********************************************************************************/
extern bool display_on_LCD;

/********************************************************************************
 * Global functions
 ********************************************************************************/
void LCD_Init(void);
void LCD_Sleep(void);
void LCD_WakeUp(void);
void LCD_DisplayBackgroundColor(uint16_t color);
void LCD_DrawPoint(uint8_t x, uint8_t y, uint16_t color);
int LCD_Printf(int x, int y, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif /* LCD_H_ */
