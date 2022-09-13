/********************************************************************************
 *
 * @file      common.c
 * @brief     provide common APIs
 * @author    SJX
 * @date      2018-04-13
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "common.h"

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     initialize delay module
 * @param     void
 * @return    none
 ************************************************************/
void Delay_Init(void) {
  SIM->SCGC |= SIM_SCGC_RTC_MASK;
  uint32_t u32rtc_src = RTC->SC;
  u32rtc_src &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
  u32rtc_src |=
      RTC_SC_RTCLKS(3) | RTC_SC_RTCPS(7); /* bus clock, prescaler is 1000 */
  RTC->SC = u32rtc_src;
  RTC->MOD = 0xFFFF;
}

/************************************************************
 * @brief     time delay
 * @param     ms millisecond for delay
 * @return    none
 ************************************************************/
void DelayMs(uint16_t ms) {
  if (ms <= 1000) {
    uint16_t freqMHz = BUS_CLOCK / 1000000;
    uint16_t startCnt = RTC->CNT;
    uint16_t endCnt = startCnt + ms * freqMHz;
    if (endCnt > startCnt) {
      while (RTC->CNT < endCnt)
        ;
    } else {
      while (RTC->CNT > endCnt)
        ;
      while (RTC->CNT < endCnt)
        ;
    }
  } else {
    uint16_t s = ms / 1000;
    ms -= s * 1000;
    for (uint16_t i = 0; i < s; i++) {
      DelayMs(1000);
    }
    DelayMs(ms);
  }
}

/************************************************************
 * @brief     disable interrupts for desired module
 * @param     module interrupt number from the interrupts vector table
 * @return    none
 ************************************************************/
void Disable_Interrupt(IRQn_Type vector_number) {
  NVIC_SetPendingIRQ(vector_number); /* set pending interrupt register */
  NVIC_DisableIRQ(vector_number);    /* disable interrupt */
}

/************************************************************
 * @brief     enable interrupts for desired module
 * @param     module interrupt number from the interrupts vector table
 * @return    none
 ************************************************************/
void Enable_Interrupt(IRQn_Type vector_number) {
  NVIC_ClearPendingIRQ(vector_number); /* clear pending interrupt register */
  NVIC_EnableIRQ(vector_number);       /* enable interrupt */
}
