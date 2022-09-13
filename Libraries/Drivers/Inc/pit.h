/********************************************************************************
 *
 * @file      pit.h
 * @brief     header file for Periodic Interrupt Timer (PIT)
 * @author    Freescale
 * @date      2018-04-07
 *
 ********************************************************************************/
#ifndef PIT_H_
#define PIT_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Includes
 ********************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "derivative.h"

/********************************************************************************
 * Constants
 ********************************************************************************/
/************************************************************
 * PIT channel number list
 ************************************************************/
enum {
  PIT_CHANNEL0 = 0, /* PIT channel 0 */
  PIT_CHANNEL1      /* PIT channel 1 */
};

/********************************************************************************
 * Macros
 ********************************************************************************/

/********************************************************************************
 * Types
 ********************************************************************************/
/************************************************************
 * PIT callback type
 ************************************************************/
typedef void (*PIT_CallbackType)(void);

/************************************************************
 * PIT configuration structure
 ************************************************************/
typedef struct {
  uint8_t bFreeze : 1; /* 1: stop in debug mode, 0: run in debug mode */
  uint8_t
      bModuleDis : 1; /* 1: PIT module is disable, 0: PIT module is enable */
  uint8_t bReserved0 : 1;   /* reserved bit */
  uint8_t bReserved1 : 5;   /* reserved bit */
  uint8_t bTimerEn : 1;     /* 1: channel timer is enable, 0: channel timer is
                               disable */
  uint8_t bInterruptEn : 1; /* 1: channel timer interrupt is enable, 0:
                               channel timer interrupt is disable */
  uint8_t
      bChainMode : 1; /* 1: chain mode is enable, 0: chain mode is disable */
  uint8_t bReserved2 : 5; /* reserved bit */
  uint8_t bFlag : 1; /* 1: flag is set,and write 1 to clear flag, 0: no flag
                        is set */
  uint8_t bReserved3 : 7; /* reserved bit */
  uint32_t u32LoadValue;  /* 32-bit channel load value */
} PIT_ConfigType, *PIT_ConfigPtr;

/********************************************************************************
 * Global variables
 ********************************************************************************/

/********************************************************************************
 * Inline functions
 ********************************************************************************/
/************************************************************
 * @brief     enable pit module
 * @param     none
 * @return    none
 ************************************************************/
static inline void PIT_Enable(void) { PIT->MCR &= ~PIT_MCR_MDIS_MASK; }

/************************************************************
 * @brief     disable pit module
 * @param     none
 * @return    none
 ************************************************************/
static inline void PIT_Disable(void) { PIT->MCR |= PIT_MCR_MDIS_MASK; }

/************************************************************
 * @brief     pit timers are stopped in debug mode
 * @param     none
 * @return    none
 ************************************************************/
static inline void PIT_SetDebugFreeze(void) { PIT->MCR |= PIT_MCR_FRZ_MASK; }

/************************************************************
 * @brief     pit timers are running in debug mode
 * @param     none
 * @return    none
 ************************************************************/
static inline void PIT_SetDebugOn(void) { PIT->MCR &= ~PIT_MCR_FRZ_MASK; }

/************************************************************
 * @brief     enable pit channel timer
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelEnable(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TCTRL |= PIT_TCTRL_TEN_MASK;
}

/************************************************************
 * @brief     disable pit channel timer
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelDisable(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}

/************************************************************
 * @brief     enable pit channel timer interrupt
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelEnableInt(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TCTRL |= PIT_TCTRL_TIE_MASK;
}

/************************************************************
 * @brief     disable pit channel timer interrupt
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelDisableInt(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TCTRL &= ~PIT_TCTRL_TIE_MASK;
}

/************************************************************
 * @brief     enable pit channel timer chain mode
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelEnableChain(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TCTRL |= PIT_TCTRL_CHN_MASK;
}

/************************************************************
 * @brief     disable pit channel timer chain mode
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelDisableChain(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TCTRL &= ~PIT_TCTRL_CHN_MASK;
}

/************************************************************
 * @brief     get pit channel timer interrrupt flag
 * @param     u8Channel
 * @return    bflag
 ************************************************************/
static inline uint8_t PIT_ChannelGetFlags(uint8_t u8Channel) {
  uint8_t bflag;

  bflag = (PIT->CHANNEL[u8Channel].TFLG & PIT_TFLG_TIF_MASK);

  return bflag;
}

/************************************************************
 * @brief     clear pit channel timer interrrupt flag
 * @param     u8Channel
 * @return    none
 ************************************************************/
static inline void PIT_ChannelClrFlags(uint8_t u8Channel) {
  PIT->CHANNEL[u8Channel].TFLG |= PIT_TFLG_TIF_MASK;
}

/********************************************************************************
 * Global functions
 ********************************************************************************/
void PIT_Init(uint8_t u8Channel, PIT_ConfigType *pConfig);
void PIT_SetLoadVal(uint8_t u8Channel, uint32_t u32loadvalue);
void PIT_SetCallback(uint8_t u8Channel, PIT_CallbackType pfnCallback);
void PIT_DeInit(void);
void PIT_QuickInit(uint8_t u8Channel, uint16_t period,
                   PIT_CallbackType pfnCallback);


#ifdef __cplusplus
}
#endif

#endif /* PIT_H_ */
