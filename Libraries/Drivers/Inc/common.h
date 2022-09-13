/********************************************************************************
 *
 * @file      common.h
 * @brief     header file for common.c
 * @author    SJX
 * @date      2018-04-13
 *
 ********************************************************************************/

#ifndef COMMON_H_
#define COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdint.h>
#include "derivative.h"

/********************************************************************************
 * Global functions
 ********************************************************************************/
void Delay_Init(void);
void DelayMs(uint16_t ms);
void Disable_Interrupt(IRQn_Type vector_number);
void Enable_Interrupt(IRQn_Type vector_number);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H_ */
