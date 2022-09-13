/********************************************************************************
 *
 * @file      adc.c
 * @brief     provide APIs for configuring ADC module
 * @author    Freescale
 * @date      2018-04-06
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "adc.h"

/********************************************************************************
 * Local variables
 ********************************************************************************/
ADC_CallbackType ADC_Callback[1] = {(0)};

/********************************************************************************
 * Local function prototypes
 ********************************************************************************/

/********************************************************************************
 * Local functions
 ********************************************************************************/
/************************************************************
 * @brief       ADC interrupt service routine
 * @param       none
 * @return      none
 ************************************************************/
void ADC_IRQHandler(void) {
  if (ADC_Callback[0]) {
    ADC_Callback[0]();
  }
}

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     initialize ADC module
 * @param     pADC point to ADC module type
 *            pADC_Config point to ADC configuration structure
 * @return    none
 ************************************************************/
void ADC_Init(ADC_MemMapPtr pADC, ADC_ConfigTypePtr pADC_Config) {
  if (pADC == ADC) {
    SIM->SCGC |= SIM_SCGC_ADC_MASK;
  }

  /* set clock cource for ADC */
  ADC_SelectClock(pADC, pADC_Config->u8ClockSource);

  /* set clock divide */
  ADC_SelectClockDivide(pADC, pADC_Config->u8ClockDiv);

  /* set ADC mode */
  ADC_SetMode(pADC, pADC_Config->u8Mode);

  /* set FIFO level */
  ADC_SetFifoLevel(pADC, pADC_Config->u8FiFoLevel);

  /* set pin control */
  pADC->APCTL1 = pADC_Config->u16PinControl;

  if (pADC_Config->sSetting.bCompareEn) {
    ADC_CompareEnable(pADC);
  }

  if (pADC_Config->sSetting.bCompareGreaterEn) {
    ADC_CompareGreaterFunction(pADC);
  }

  if (pADC_Config->sSetting.bContinuousEn) {
    ADC_ContinuousConversion(pADC);
  }

  if (pADC_Config->sSetting.bCompareAndEn) {
    ADC_CompareFifoAnd(pADC);
  }

  if (pADC_Config->sSetting.bFiFoScanModeEn) {
    ADC_FifoScanModeEnable(pADC);
  }

  if (pADC_Config->sSetting.bHardwareTriggerEn) {
    ADC_SetHardwareTrigger(pADC);
  }

  if (pADC_Config->sSetting.bIntEn) {
    ADC_IntEnable(pADC);
    NVIC_ClearPendingIRQ(ADC_IRQn);
    NVIC_EnableIRQ(ADC_IRQn);
  }

  if (pADC_Config->sSetting.bLongSampleEn) {
    ADC_SetLongSample(pADC);
  }

  if (pADC_Config->sSetting.bLowPowerEn) {
    ADC_SetLowPower(pADC);
  }

  if (pADC_Config->sSetting.bHTRGMEn) {
    ADC_HardwareTriggerMultiple(pADC);
  } else {
    ADC_HardwareTriggerSingle(pADC);
  }

  if (pADC_Config->sSetting.bHTRGMASKEn) {
    ADC_HardwareTriggerMaskEnable(pADC);
  } else {
    ADC_HardwareTriggerMaskDisable(pADC);
  }
  if (pADC_Config->sSetting.bHTRGMASKSEL) {
    ADC_HardwareTriggerMaskAuto(pADC);
  } else {
    ADC_HardwareTriggerMaskNonAuto(pADC);
  }
}

/************************************************************
 * @brief     disable ADC module
 * @param     pADC point to ADC module type
 * @return    none
 ************************************************************/
void ADC_DeInit(ADC_MemMapPtr pADC) {
  ADC_SetChannel(pADC, ADC_CHANNEL_DISABLE);

  SIM->SCGC &= ~SIM_SCGC_ADC_MASK;
}

/************************************************************
 * @brief     start a conversion and get conversion result
 * @param     pADC point to ADC module type
 *            u8Channel adc channel to conversion
 * @return    ADC conversion result
 ************************************************************/
unsigned int ADC_PollRead(ADC_MemMapPtr pADC, uint8_t u8Channel) {
  ADC_SetChannel(pADC, u8Channel);
  while (!ADC_IsCOCOFlag(pADC))
    ;
  return ADC_ReadResultReg(pADC);
}

/************************************************************
 * @brief     install ADC call back function
 * @param	    pADC_CallBack point to address of  adc call back function
 * @return    none
 ************************************************************/
void ADC_SetCallBack(ADC_CallbackType pADC_CallBack) {
  ADC_Callback[0] = pADC_CallBack;
}

/************************************************************
 * @brief     set ADC channel
 * @param     pADC point to ADC module type
 *            u8Channel adc channel to conversion
 * @return    none
 ************************************************************/
void ADC_SetChannel(ADC_MemMapPtr pADC, uint8_t u8Channel) {
  uint32_t u32temp;
  u32temp = pADC->SC1;
  u32temp &= ~ADC_SC1_ADCH_MASK;
  pADC->SC1 = u32temp | ADC_SC1_ADCH(u8Channel);
}

/************************************************************
 * @brief     voltage reference selection
 * @param     pADC point to ADC module type
 *            u8Vref adc reference voltage selection
 * @return    none
 ************************************************************/
void ADC_VrefSelect(ADC_MemMapPtr pADC, uint8_t u8Vref) {
  uint32_t u32Temp;
  u32Temp = pADC->SC2;
  u32Temp &= ~ADC_SC2_REFSEL_MASK;
  pADC->SC2 = u32Temp | ADC_SC2_REFSEL(u8Vref);
}

/************************************************************
 * @brief     select clock divide
 * @param     pADC point to ADC module type
 *            u8Div Clock Divide Select
 * @return    none
 ************************************************************/
void ADC_SelectClockDivide(ADC_MemMapPtr pADC, uint8_t u8Div) {
  uint32_t u32Temp;
  u32Temp = pADC->SC3;
  u32Temp &= ~ADC_SC3_ADIV_MASK;
  pADC->SC3 = u32Temp | ADC_SC3_ADIV(u8Div);
}

/************************************************************
 * @brief     set ADC mode
 * @param     pADC point to ADC module type
 *            u8Mode conversion mode selection
 * @return    none
 ************************************************************/
void ADC_SetMode(ADC_MemMapPtr pADC, uint8_t u8Mode) {
  uint32_t u32Temp;
  u32Temp = pADC->SC3;
  u32Temp &= ~ADC_SC3_MODE_MASK;
  pADC->SC3 = u32Temp | ADC_SC3_MODE(u8Mode);
}

/************************************************************
 * @brief     input clock select
 * @param     pADC point to ADC module type
 *            u8Clock input clock select
 * @return    none
 ************************************************************/
void ADC_SelectClock(ADC_MemMapPtr pADC, uint8_t u8Clock) {
  uint32_t u32Temp;
  u32Temp = pADC->SC3;
  u32Temp &= ~ADC_SC3_ADICLK_MASK;
  pADC->SC3 = u32Temp | ADC_SC3_ADICLK(u8Clock);
}

/************************************************************
 * @brief     set FIFO depth
 * @param     pADC point to ADC module type
 *            u8FifoLevel set FIFO level
 * @return    none
 ************************************************************/
void ADC_SetFifoLevel(ADC_MemMapPtr pADC, uint8_t u8FifoLevel) {
  uint32_t u32Temp;
  u32Temp = pADC->SC4;
  u32Temp &= ~ADC_SC4_AFDEP_MASK;
  pADC->SC4 = u32Temp | ADC_SC4_AFDEP(u8FifoLevel);
}

/************************************************************
 * @brief     quickly initialize ADC module
 * @param     u8Channel ADC channel number
 * @return    none
 ************************************************************/
void ADC_QuickInit(uint8_t u8Channel) {
  ADC_ConfigType ADC_Config = {0};
  ADC_Config.u8ClockDiv = ADC_ADIV_DIVIDE_2;
  ADC_Config.u8ClockSource = CLOCK_SOURCE_BUS_CLOCK;
  ADC_Config.u8Mode = ADC_MODE_12BIT;
  ADC_Config.sSetting.bContinuousEn = 0;
  ADC_Config.u16PinControl = u8Channel;

  ADC_Init(ADC, &ADC_Config);
}
