/********************************************************************************
 *
 * @file      oled.h
 * @brief     header file for oled.c
 * @author    SJX
 * @date      2018-05-03
 *
 ********************************************************************************/

#ifndef OLED_H_
#define OLED_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdint.h>
#include "derivative.h"
#include "gpio.h"
#include "spi.h"

/********************************************************************************
 * Macros
 ********************************************************************************/
/************************************************************
 * screen size
 ************************************************************/
#define OLED_PAGE_NUM 8
#define OLED_PAGE_SIZE 8
#define OLED_X_SIZE 128
#define OLED_Y_SIZE (OLED_PAGE_NUM * OLED_PAGE_SIZE)

/************************************************************
 * pins
 ************************************************************/
#define OLED_SPI SPI0
#define OLED_DC_PORT PTB
#define OLED_DC_PIN PTB1
#define OLED_RESET_PORT PTB
#define OLED_RESET_PIN PTB0

#define OLED_DC_LOW OUTPUT_CLEAR(OLED_DC_PORT, OLED_DC_PIN)
#define OLED_DC_HIGH OUTPUT_SET(OLED_DC_PORT, OLED_DC_PIN)
#define OLED_RESET_LOW OUTPUT_CLEAR(OLED_RESET_PORT, OLED_RESET_PIN)
#define OLED_RESET_HIGH OUTPUT_SET(OLED_RESET_PORT, OLED_RESET_PIN)

/********************************************************************************
 * Inline functions
 ********************************************************************************/
/************************************************************
 * @brief     write command to OLED
 * @param     cmd command to be sent
 * @return    none
 ************************************************************/
static inline void OLED_WriteCmd(uint8_t cmd) {
  OLED_DC_LOW;
  SPI_ReadWriteByte(OLED_SPI, cmd);
  OLED_DC_HIGH;
}

/************************************************************
 * @brief     write data to OLED
 * @param     data byte to be sent
 * @return    none
 ************************************************************/
static inline void OLED_WriteData(uint8_t data) {
  OLED_DC_HIGH;
  SPI_ReadWriteByte(OLED_SPI, data);
}

/************************************************************
 * @brief     set display position
 * @param     col column number
 *            page page number
 * @return    none
 ************************************************************/
static inline void OLED_SetPos(uint8_t col, uint8_t page) {
  OLED_WriteCmd(0xB0 + page);
  OLED_WriteCmd(((col & 0xF0) >> 4) | 0x10);
  OLED_WriteCmd((col & 0x0F) | 0x01);
}

/********************************************************************************
 * Global functions
 ********************************************************************************/
void OLED_Init(void);
void OLED_On(void);
void OLED_Off(void);
void OLED_Clear(void);
void OLED_DisplayChar(uint8_t x, uint8_t y, char c);
uint16_t OLED_Printf(uint8_t x, uint8_t y, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* OLED_H_ */
