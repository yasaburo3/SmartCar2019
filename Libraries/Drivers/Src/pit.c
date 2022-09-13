/********************************************************************************
 *
 * @file      pit.c
 * @brief     provide APIs for configuring Periodic Interrupt Timer (PIT)
 * @author    Freescale
 * @date      2018-04-07
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "pit.h"


/********************************************************************************
 * Global variables
 ********************************************************************************/

/********************************************************************************
 * Constants and macros
 ********************************************************************************/

/********************************************************************************
 * Local types
 ********************************************************************************/

/********************************************************************************
 * Local function prototypes
 ********************************************************************************/

/********************************************************************************
 * Local variables
 ********************************************************************************/
/************************************************************
 * PIT initial callback
 ************************************************************/
PIT_CallbackType PIT_Callback[2] = {(0)};

/********************************************************************************
 * Local functions
 ********************************************************************************/
/************************************************************
 * @brief     pit module channel 0 isr
 * @param     none
 * @return    none
 ************************************************************/
void PIT_CH0_IRQHandler(void) {
  PIT_ChannelClrFlags(0);

  if (PIT_Callback[0]) {
    PIT_Callback[0]();
  }
}

/************************************************************
 * @brief     pit module channel 1 isr
 * @param     none
 * @return    none
 ************************************************************/
void PIT_CH1_IRQHandler(void) {
  PIT_ChannelClrFlags(1);

  if (PIT_Callback[1]) {
    PIT_Callback[1]();
  }
}

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     nitialize pit module
 * @param     u8Channel channel number
 *            pConfig point to configuration
 * @return    none
 ************************************************************/
void PIT_Init(uint8_t u8Channel, PIT_ConfigType *pConfig) {
  SIM->SCGC |= SIM_SCGC_PIT_MASK; /* enable clock to PIT */

  if (pConfig->bFreeze) {
    PIT_SetDebugFreeze();
  }

  if (pConfig->bModuleDis == 0) {
    PIT_Enable(); /* enable pit module */
  }

  PIT_SetLoadVal(u8Channel, pConfig->u32LoadValue);

  if (pConfig->bInterruptEn) {
    if (u8Channel) {
      NVIC_ClearPendingIRQ(PIT_CH1_IRQn);
      NVIC_EnableIRQ(PIT_CH1_IRQn);
    } else {
      NVIC_ClearPendingIRQ(PIT_CH0_IRQn);
      NVIC_EnableIRQ(PIT_CH0_IRQn);
    }
    PIT_ChannelEnableInt(u8Channel);
  } else {
    NVIC_SetPendingIRQ(PIT_CH0_IRQn);
    NVIC_DisableIRQ(PIT_CH0_IRQn);
  }

  if (pConfig->bChainMode) {
    PIT_ChannelEnableChain(u8Channel);
  }

  if (pConfig->bTimerEn) {
    PIT_ChannelEnable(u8Channel);
  }
}

/************************************************************
 * @brief     initialize pit module
 * @param     u8Channel channel number
 *            u32loadvalue load value for pit register
 * @return    none
 ************************************************************/
void PIT_SetLoadVal(uint8_t u8Channel, uint32_t u32loadvalue) {
  PIT->CHANNEL[u8Channel].LDVAL = u32loadvalue;
}

/************************************************************
 * @brief     pit module set call back
 * @param     u8Channel channel number
 *            pfnCallback point to call back
 * @return    none
 ************************************************************/
void PIT_SetCallback(uint8_t u8Channel, PIT_CallbackType pfnCallback) {
  PIT_Callback[u8Channel] = pfnCallback;
}

/************************************************************
 * @brief     pit module de-initialize, reset pit register
 * @param     none
 * @return    none
 ************************************************************/
void PIT_DeInit(void) {
  NVIC_SetPendingIRQ(PIT_CH0_IRQn);
  NVIC_DisableIRQ(PIT_CH0_IRQn);
  NVIC_SetPendingIRQ(PIT_CH1_IRQn);
  NVIC_DisableIRQ(PIT_CH1_IRQn);
  PIT_SetLoadVal(0, 0);
  PIT_SetLoadVal(1, 0);
  PIT_ChannelDisable(0);
  PIT_ChannelDisable(1);
  PIT_ChannelDisableInt(0);
  PIT_ChannelDisableInt(1);
  PIT_ChannelDisableChain(0);
  PIT_ChannelDisableChain(1);
  PIT_ChannelClrFlags(0);
  PIT_ChannelClrFlags(1);
  PIT_SetDebugOn();
  PIT_Disable();
  SIM->SCGC &= ~SIM_SCGC_PIT_MASK;
}

/************************************************************
 * @brief     quickly initialize PIT module
 * @param     u8Channel channel number
 *            timeOutUs timeout period for PIT interrupts (us)
 *            pfnCallback point to call back
 * @return    none
 ************************************************************/
void PIT_QuickInit(uint8_t u8Channel, uint16_t timeoutUs,
                   PIT_CallbackType pfnCallback) {
  uint16_t freqMHz = BUS_CLOCK / 1000000;

  PIT_ConfigType PIT_Config = {0};
  PIT_Config.u32LoadValue =
      timeoutUs * freqMHz - 1; /* PIT clock source is bus clock, 24 MHz */
  PIT_Config.bFreeze = false;
  PIT_Config.bModuleDis = false;
  PIT_Config.bInterruptEn = true;
  PIT_Config.bChainMode = false;
  PIT_Config.bTimerEn = true;

  PIT_SetCallback(u8Channel, pfnCallback);
  PIT_Init(u8Channel, &PIT_Config);
}
				   

