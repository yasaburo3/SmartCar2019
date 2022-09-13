/********************************************************************************
 *
 * @file      main.h
 * @brief     header file for main.c
 * @author    SJX
 * @date      2018-04-08
 *
 ********************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "gpio.h"

/********************************************************************************
 * Macros
 ********************************************************************************/
/************************************************************
 * LED on KEA128 board
 ************************************************************/
#define RED_LED_ON OUTPUT_SET(PTB, PTA3)
#define RED_LED_OFF OUTPUT_CLEAR(PTC, PTC2)
#define RED_LED_Toggle OUTPUT_TOGGLE(PTC, PTC2)

#define GREEN_LED_ON OUTPUT_SET(PTB, PTB4)
#define GREEN_LED_OFF OUTPUT_CLEAR(PTB, PTB4)
#define GREEN_LED_Toggle OUTPUT_TOGGLE(PTB, PTB4)

#define BLUE_LED_ON OUTPUT_SET(PTE, PTE5)
#define BLUE_LED_OFF OUTPUT_CLEAR(PTE, PTE5)
#define BLUE_LED_Toggle OUTPUT_TOGGLE(PTE, PTE5)

#define BI_OFF OUTPUT_SET(PTB, PTA7)
#define BI_ON OUTPUT_CLEAR(PTB, PTA7)
#define BI_Toggle OUTPUT_TOGGLE(PTB, PTA7)

void BEEP_ON(void);
void BEEP_OFF(void);
extern int spdL_loop;
extern int spdR_loop;
extern int left_speed;
extern int right_speed;


/********************************************************************************
 * Global functions
 ********************************************************************************/

#endif /* MAIN_H_ */
