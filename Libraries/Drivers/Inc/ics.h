/********************************************************************************
 *
 * @file      ics.h
 * @brief     header file for Internal Clock Source utilities
 * @author    Freescale
 * @date      2018-04-07
 *
 ********************************************************************************/

#ifndef ICS_H_
#define ICS_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "derivative.h"

/********************************************************************************
 * Constants
 ********************************************************************************/
/************************************************************
 * ICS clock modes
 ************************************************************/
enum {
  ICS_CLK_MODE_FEI = 1,    /* FEI mode using the factory IRC trim value */
  ICS_CLK_MODE_FEI_CUSTOM, /* FEI mode using a custom trim value provided by a
                              programming tool */
  ICS_CLK_MODE_FEE,        /* FEE mode */
  ICS_CLK_MODE_FBE,        /* FBE mode */
  ICS_CLK_MODE_FBI,        /* FBI mode */
  ICS_CLK_MODE_FBILP,      /* FBILP mode */
  ICS_CLK_MODE_FBELP,      /* FBELP mode */
};

/********************************************************************************
 * Macros
 ********************************************************************************/
#define DCO_DIVIDED_BY_1 0
#define DCO_DIVIDED_BY_2 1
#define DCO_DIVIDED_BY_4 2
#define DCO_DIVIDED_BY_8 3
#define DCO_DIVIDED_BY_16 4
#define DCO_DIVIDED_BY_32 5
#define DCO_DIVIDED_BY_64 6
#define DCO_DIVIDED_BY_128 7

/************************************************************
 * @brief     switch clock mode from current to new mode
 *
 *  The clock mode macros are as follows: FEI, FBI, FEE, FBE, FBILP, FBELP,
 *FEE_OSC, FBE_OSC, where FEE_OSC, FBE_OSC can not be used as current mode. The
 *valid combinationS of <CurMode, NewMode> pair are as follows: <FEI,FEE>,
 *<FEI,FBI>, <FEI,FBE>, <FEI,FBE_OSC>, <FEI,FEE_OSC>, <FEE,FEI>, <FEE,FBI>,
 *<FEE,FBE>, <FBI,FBE>, <FBI,FEE>, <FBI,FBILP>, <FBI,FEI>, <FBE,FBI>, <FBE,FEE>,
 *<FBE,FEI>, <FBE,FBELP>, <FBELP,FBE>, <FBILP,FBI>
 *
 * @param     CurMode   	current clock mode macro
 *            NewMode   	new clock mode macro
 *            ICS_Config  ICS_Config
 * @return    none
 * @warning   FEE_OSC, FBE_OSC can not be used as current mode
 ************************************************************/
#define ICS_SwitchMode(CurMode, NewMode, ICS_Config) \
  CurMode##_to_##NewMode(ICS_Config)

/********************************************************************************
 * Types
 ********************************************************************************/
/************************************************************
 * OSC configuration structure
 ************************************************************/
typedef struct {
  uint8_t bRange : 1;      /* 1: high range, 0: low range */
  uint8_t bGain : 1;       /* 1: high gain, 0: low gain */
  uint8_t bEnable : 1;     /* 1: enable XOSC, 0: disable XOSC */
  uint8_t bStopEnable : 1; /* 1: stop enable, 0: stop disable */
  uint8_t bIsCryst : 1;    /* 1: crystal input, 0: active clock input */
  uint8_t bWaitInit : 1;   /* 1: wait till XOSC init done, 0: no wait */
  uint32_t u32OscFreq;     /* oscillator clock frequency in KHz */
} OSC_ConfigType, *OSC_ConfigPtr;

/************************************************************
 * ICS configuration structure
 ************************************************************/
typedef struct {
  uint8_t u8ClkMode;        /* clock mode to be switched */
  uint8_t bLPEnable;        /* low power mode enable */
  uint8_t bdiv;             /* core fre = DCO */
  OSC_ConfigType oscConfig; /* OSC configuration */
} ICS_ConfigType;

/********************************************************************************
 * Global variables
 ********************************************************************************/

/********************************************************************************
 * Inline functions
 ********************************************************************************/
/************************************************************
 * @brief     enable interrupt
 * @param     none
 * @return    none
 * @see       ICS_DisableInt
 ************************************************************/
static __inline void ICS_EnableInt(void) { ICS_C4 |= (ICS_C4_LOLIE_MASK); }

/************************************************************
 * @brief     disable interrupt
 * @param     none
 * @return    none
 * @see       ICS_EnableInt
 ************************************************************/
static __inline void ICS_DisableInt(void) { ICS_C4 &= ~(ICS_C4_LOLIE_MASK); }

/************************************************************
 * @brief     enable clock monitor
 * @param     none
 * @return    none
 * @see       ICS_DisableClockMonitor
 ************************************************************/
static __inline void ICS_EnableClockMonitor(void) {
  ICS_C4 |= (ICS_C4_CME_MASK);
}

/************************************************************
 * @brief     disable clock monitor
 * @param     none
 * @return    none
 * @see       ICS_EnableClockMonitor
 ************************************************************/
static __inline void ICS_DisableClockMonitor(void) {
  ICS_C4 &= ~(ICS_C4_CME_MASK);
}

/************************************************************
 * @brief     set bus divider BDIV bit field
 * @param     busDivide BDIV value
 * @return    depends on commands
 ************************************************************/
static __inline void ICS_SetBusDivider(uint8_t u8BusDivide) {
  ICS_C2 = (ICS_C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(u8BusDivide);
}

/************************************************************
 * @brief     enable OSC
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_Enable(void) { OSC_CR |= (OSC_CR_OSCEN_MASK); }

/************************************************************
 * @brief     disable OSC
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_Disable(void) { OSC_CR &= ~(OSC_CR_OSCEN_MASK); }

/************************************************************
 * @brief     set low range of oscillator
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_SetLowRange(void) { OSC_CR &= ~(OSC_CR_RANGE_MASK); }

/************************************************************
 * @brief     set high range of oscillator
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_SetHighRange(void) { OSC_CR |= (OSC_CR_RANGE_MASK); }

/************************************************************
 * @brief     set high gain of oscillator
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_SetHighGain(void) { OSC_CR |= (OSC_CR_HGO_MASK); }

/************************************************************
 * @brief     set low gain of oscillator
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_SetLowGain(void) { OSC_CR &= ~(OSC_CR_HGO_MASK); }

/************************************************************
 * @brief     select crystal as clock source
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_SelectCrystal(void) { OSC_CR |= (OSC_CR_OSCOS_MASK); }

/************************************************************
 * @brief     select active clock as clock source
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_SelectClock(void) { OSC_CR &= ~(OSC_CR_OSCOS_MASK); }

/************************************************************
 * @brief     enable OSC in stop mode
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_ActiveInStop(void) { OSC_CR |= (OSC_CR_OSCSTEN_MASK); }

/************************************************************
 * @brief     disable OSC in stop mode
 * @param     none
 * @return    none
 ************************************************************/
static __inline void OSC_InactiveInStop(void) {
  OSC_CR &= ~(OSC_CR_OSCSTEN_MASK);
}

/************************************************************
 * @brief     disable OSC in stop mode
 * @param     none
 * @return    none
 ************************************************************/
static __inline void Stop(void) { __asm__("WFI"); }

/********************************************************************************
 * Global functions
 ********************************************************************************/
void ICS_Init(ICS_ConfigType *pConfig);
void ICS_SetOscDivider(uint32_t u32OscFreqKHz);
void ICS_SetCoreClk(uint32_t u32CoreFreqKHz);
void ICS_Trim(uint16_t u16TrimValue);
void OSC_Init(OSC_ConfigType *pConfig);
void OSC_DeInit(void);
void ICS_QuickInit(void);

/* inline functions */
void ICS_DisableClockMonitor(void);
void ICS_DisableInt(void);
void ICS_EnableClockMonitor(void);
void ICS_EnableInt(void);
void ICS_SetBusDivider(uint8_t u8BusDivide);
void OSC_ActiveInStop(void);
void OSC_Enable(void);
void OSC_Disable(void);
void OSC_InactiveInStop(void);
void OSC_SelectClock(void);
void OSC_SelectCrystal(void);
void OSC_SetHighGain(void);
void OSC_SetHighRange(void);
void OSC_SetLowGain(void);
void OSC_SetLowRange(void);
void Stop(void);

/* do not touch the following functions */
void FEI_to_FEE(ICS_ConfigType *pConfig);
void FEI_to_FBI(ICS_ConfigType *pConfig);
void FEI_to_FBE(ICS_ConfigType *pConfig);
void FEE_to_FBI(ICS_ConfigType *pConfig);
void FEE_to_FEI(ICS_ConfigType *pConfig);
void FEE_to_FBE(ICS_ConfigType *pConfig);
void FBE_to_FEE(ICS_ConfigType *pConfig);
void FBE_to_FEI(ICS_ConfigType *pConfig);
void FBE_to_FBI(ICS_ConfigType *pConfig);
void FBE_to_FBELP(ICS_ConfigType *pConfig);
void FBI_to_FEI(ICS_ConfigType *pConfig);
void FBI_to_FBE(ICS_ConfigType *pConfig);
void FBI_to_FEE(ICS_ConfigType *pConfig);
void FBI_to_FBILP(ICS_ConfigType *pConfig);
void FBILP_to_FBI(ICS_ConfigType *pConfig);
void FBELP_to_FBE(ICS_ConfigType *pConfig);

#ifdef __cplusplus
}
#endif

#endif /* ICS_H_ */
