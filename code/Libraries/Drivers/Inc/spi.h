/********************************************************************************
 *
 * @file      spi.h
 * @brief     header file for SPI module utilities
 * @author    Freescale
 * @date      2018-04-19
 *
 ********************************************************************************/

#ifndef SPI_H_
#define SPI_H_

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

/********************************************************************************
 * Macros
 ********************************************************************************/
/************************************************************
 * maximum number of SPIs
 ************************************************************/
#define MAX_SPI_NO 2

/************************************************************
 * SPI register default value
 ************************************************************/
#define SPI_C1_DEFAULT 0x04 /* C1 register */
#define SPI_C2_DEFAULT 0x00 /* C2 register */
#define SPI_BR_DEFAULT 0x00 /* BR register */
#define SPI_S_DEFAULT 0x20  /* S register */
#define SPI_M_DEFAULT 0x00  /* M register */

/************************************************************
 * SPI error status
 ************************************************************/
#define SPI_ERR_SUCCESS 0 /* success */
#define SPI_ERR_CODE_BASE \
  ((uint32)SPI0 - 0x40000000L) /* error code base for SPI */
#define SPI_ERR_TXBUF_NOT_EMPTY \
  (SPI_ERR_CODE_BASE + 1) /* failure due to SPTEF (empty) not set */
#define SPI_ERR_RXBUF_NOT_FULL \
  (SPI_ERR_CODE_BASE + 2) /* failure due to SPRF (full) not set */

/********************************************************************************
 * Types
 ********************************************************************************/
typedef uint8_t SPI_WidthType; /* width type */
typedef uint32_t ResultType;   /* routine result code */

/************************************************************
 * SPI callback type
 ************************************************************/
typedef void (*SPI_CallbackType)(void); /* SPI call back function */

/************************************************************
 * SPI setting type
 ************************************************************/
typedef struct {
  uint32_t bIntEn : 1;    /* 1: interrupt enable, 0: interrupt disable */
  uint32_t bModuleEn : 1; /* 1: SPI module enable, 0: SPI module disable */
  uint32_t bTxIntEn : 1;  /* 1: Tx interrupt enable, 0: Tx enterrupt disable */
  uint32_t bMasterMode : 1;     /* 1: master mode, 0: slave mode */
  uint32_t bClkPolarityLow : 1; /* 1: active-low SPI clock, 0: active-high SPI
                                   clock */
  uint32_t bClkPhase1 : 1;      /* set clock phase */
  uint32_t bMasterAutoDriveSS : 1; /* slave select output enable */
  uint32_t bShiftLSBFirst : 1;     /* 1: LSB first, 0: MSB first */
  uint32_t bMatchIntEn : 1;  /* 1: match interrupt enable, 0: match interrupt
                                disable */
  uint32_t bModeFaultEn : 1; /* master mode-fault function enable */
  uint32_t bBidirectionModeEn : 1; /* bidirectional mode output enable */
  uint32_t bPinAsOuput : 1;     /* enables bidirectional pin configurations */
  uint32_t bStopInWaitMode : 1; /* SPI stop in wait mode */
  uint32_t bRsvd : 19;
} SPI_SettingType;

/************************************************************
 * SPI configuration type
 ************************************************************/
typedef struct {
  SPI_SettingType sSettings; /* SPI settings */
  uint32_t u32BitRate;       /* set baud rate */
  uint32_t u32BusClkHz;      /* input bus clock */
} SPI_ConfigType;            /* SPI configuration structure */

/********************************************************************************
 * Inline functions
 ********************************************************************************/
/************************************************************
 * @brief     LSB first (shifter direction)
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_SetLSBFirst(SPI_MemMapPtr pSPI) {
  pSPI->C1 |= SPI_C1_LSBFE_MASK;
}

/************************************************************
 * @brief     MSB first (shifter direction)
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_SetMSBFirst(SPI_MemMapPtr pSPI) {
  pSPI->C1 &= ~SPI_C1_LSBFE_MASK;
}

/************************************************************
 * @brief     set SPI clock polarity
 * @param     pSPI point to SPI module type
 *            u8PolLow set clock polarity, 1 - active-low SPI clock (idles high)
 * @return    none
 ************************************************************/
static inline void SPI_SetClockPol(SPI_MemMapPtr pSPI, uint8_t u8PolLow) {
  if (u8PolLow) {
    pSPI->C1 |= SPI_C1_CPOL_MASK;
  } else {
    pSPI->C1 &= ~SPI_C1_CPOL_MASK;
  }
}

/************************************************************
 * @brief     set SPI clock phase
 * @param     pSPI point to SPI module type
 *            u8Phase set clock phase, 1 - First edge on SPSCK occurs at the
 *start of the first cycle of a data transfer
 * @return    none
 ************************************************************/
static inline void SPI_SetClockPhase(SPI_MemMapPtr pSPI, uint8_t u8Phase) {
  if (u8Phase) {
    pSPI->C1 |= SPI_C1_CPHA_MASK;
  } else {
    pSPI->C1 &= ~SPI_C1_CPHA_MASK;
  }
}

/************************************************************
 * @brief     enable SPI module
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_Enable(SPI_MemMapPtr pSPI) {
  pSPI->C1 |= SPI_C1_SPE_MASK;
}

/************************************************************
 * @brief     disable SPI module
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_Disable(SPI_MemMapPtr pSPI) {
  pSPI->C1 &= ~SPI_C1_SPE_MASK;
}

/************************************************************
 * @brief     enable SPI interrupt
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_IntEnable(SPI_MemMapPtr pSPI) {
  pSPI->C1 |= SPI_C1_SPIE_MASK;
}

/************************************************************
 * @brief     disable SPI interrupt
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_IntDisable(SPI_MemMapPtr pSPI) {
  pSPI->C1 &= ~SPI_C1_SPIE_MASK;
}

/************************************************************
 * @brief     set SPI to master mode
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_SetMasterMode(SPI_MemMapPtr pSPI) {
  pSPI->C1 |= SPI_C1_MSTR_MASK;
}

/************************************************************
 * @brief     set SPI to slave mode
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_SetSlaveMode(SPI_MemMapPtr pSPI) {
  pSPI->C1 &= ~SPI_C1_MSTR_MASK;
}

/************************************************************
 * @brief     SPI transmit interrupt enable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_TxIntEnable(SPI_MemMapPtr pSPI) {
  pSPI->C1 |= SPI_C1_SPTIE_MASK;
}

/************************************************************
 * @brief     SPI transmit interrupt disable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_TxIntDisable(SPI_MemMapPtr pSPI) {
  pSPI->C1 &= ~SPI_C1_SPTIE_MASK;
}

/************************************************************
 * @brief     slave select output enable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_SSOutputEnable(SPI_MemMapPtr pSPI) {
  pSPI->C1 |= SPI_C1_SSOE_MASK;
}

/************************************************************
 * @brief     slave select output disable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_SSOutputDisable(SPI_MemMapPtr pSPI) {
  pSPI->C1 &= ~SPI_C1_SSOE_MASK;
}

/************************************************************
 * @brief     SPI match interrupt enable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_MatchIntEnable(SPI_MemMapPtr pSPI) {
  pSPI->C2 |= SPI_C2_SPMIE_MASK;
}

/************************************************************
 * @brief     SPI match interrupt disable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_MatchIntDisable(SPI_MemMapPtr pSPI) {
  pSPI->C2 &= ~SPI_C2_SPMIE_MASK;
}

/************************************************************
 * @brief     master mode-fault function disable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_ModfDisable(SPI_MemMapPtr pSPI) {
  pSPI->C2 &= ~SPI_C2_MODFEN_MASK;
}

/************************************************************
 * @brief     master mode-fault function enable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_ModfEnable(SPI_MemMapPtr pSPI) {
  pSPI->C2 |= SPI_C2_MODFEN_MASK;
}

/************************************************************
 * @brief     bidirectional mode output enable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_BidirOutEnable(SPI_MemMapPtr pSPI) {
  pSPI->C2 |= SPI_C2_BIDIROE_MASK;
}

/************************************************************
 * @brief     bidirectional mode output disable
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_BidirOutDisable(SPI_MemMapPtr pSPI) {
  pSPI->C2 &= ~SPI_C2_BIDIROE_MASK;
}

/************************************************************
 * @brief     SPI stop in wait mode
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_ClockStopDisable(SPI_MemMapPtr pSPI) {
  pSPI->C2 &= ~SPI_C2_SPISWAI_MASK;
}

/************************************************************
 * @brief     SPI stop in wait mode
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_ClockStopEnable(SPI_MemMapPtr pSPI) {
  pSPI->C2 |= SPI_C2_SPISWAI_MASK;
}

/************************************************************
 * @brief     enables bidirectional pin configurations
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_BidirPinEnable(SPI_MemMapPtr pSPI) {
  pSPI->C2 |= SPI_C2_SPC0_MASK;
}

/************************************************************
 * @brief     enables bidirectional pin configurations
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
static inline void SPI_BidirPinDisable(SPI_MemMapPtr pSPI) {
  pSPI->C2 &= ~SPI_C2_SPC0_MASK;
}

/************************************************************
 * @brief     check SPI read buffer full flag
 * @param     pSPI point to SPI module type
 * @return    true or false
 ************************************************************/
static inline uint8_t SPI_IsSPRF(SPI_MemMapPtr pSPI) {
  return (pSPI->S & SPI_S_SPRF_MASK);
}

/************************************************************
 * @brief     check SPI match flag
 * @param     pSPI point to SPI module type
 * @return    true or false
 ************************************************************/
static inline uint8_t SPI_IsSPMF(SPI_MemMapPtr pSPI) {
  return (pSPI->S & SPI_S_SPMF_MASK);
}

/************************************************************
 * @brief     check SPI transmit buffer empty flag
 * @param     pSPI point to SPI module type
 * @return    true or false
 ************************************************************/
static inline uint8_t SPI_IsSPTEF(SPI_MemMapPtr pSPI) {
  return (pSPI->S & SPI_S_SPTEF_MASK);
}

/************************************************************
 * @brief     check master mode fault flag
 * @param     pSPI point to SPI module type
 * @return    true or false
 ************************************************************/
static inline uint8_t SPI_IsMODF(SPI_MemMapPtr pSPI) {
  return (pSPI->S & SPI_S_MODF_MASK);
}

/************************************************************
 * @brief     read SPI data register
 * @param     pSPI point to SPI module type
 * @return    data register value
 ************************************************************/
static inline uint8_t SPI_ReadDataReg(SPI_MemMapPtr pSPI) { return pSPI->D; }

/************************************************************
 * @brief     write SPI data register
 * @param     pSPI point to SPI module type
 *            u8WrBuff data buffer write to spi data register
 * @return    none
 ************************************************************/
static inline void SPI_WriteDataReg(SPI_MemMapPtr pSPI, uint8_t u8WrBuff) {
  pSPI->D = u8WrBuff;
}

/************************************************************
 * @brief     write SPI match  register
 * @param     pSPI point to SPI module type
 *            u8WrBuff data buffer write to match register
 * @return    none
 ************************************************************/
static inline void SPI_WriteMatchValue(SPI_MemMapPtr pSPI, uint8_t u8WrBuff) {
  pSPI->M = u8WrBuff;
}

/********************************************************************************
 * Global functions
 ********************************************************************************/
void SPI_Enable(SPI_MemMapPtr pSPI);
void SPI_Disable(SPI_MemMapPtr pSPI);
void SPI_SetLSBFirst(SPI_MemMapPtr pSPI);
void SPI_SetMSBFirst(SPI_MemMapPtr pSPI);
void SPI_IntEnable(SPI_MemMapPtr pSPI);
void SPI_IntDisable(SPI_MemMapPtr pSPI);
void SPI_SetMasterMode(SPI_MemMapPtr pSPI);
void SPI_SetSlaveMode(SPI_MemMapPtr pSPI);
void SPI_TxIntEnable(SPI_MemMapPtr pSPI);
void SPI_TxIntDisable(SPI_MemMapPtr pSPI);
void SPI_SSOutputEnable(SPI_MemMapPtr pSPI);
void SPI_SSOutputDisable(SPI_MemMapPtr pSPI);
void SPI_MatchIntEnable(SPI_MemMapPtr pSPI);
void SPI_MatchIntDisable(SPI_MemMapPtr pSPI);
void SPI_ModfDisable(SPI_MemMapPtr pSPI);
void SPI_ModfEnable(SPI_MemMapPtr pSPI);
void SPI_BidirOutEnable(SPI_MemMapPtr pSPI);
void SPI_BidirOutDisable(SPI_MemMapPtr pSPI);
void SPI_ClockStopDisable(SPI_MemMapPtr pSPI);
void SPI_ClockStopEnable(SPI_MemMapPtr pSPI);
void SPI_BidirPinEnable(SPI_MemMapPtr pSPI);
void SPI_BidirPinDisable(SPI_MemMapPtr pSPI);
void SPI_SetClockPol(SPI_MemMapPtr pSPI, uint8_t u8PolLow);
void SPI_SetClockPhase(SPI_MemMapPtr pSPI, uint8_t u8Phase);
void SPI_SetBaudRate(SPI_MemMapPtr pSPI, uint32_t u32BusClock, uint32_t u32Bps);
uint8_t SPI_IsSPRF(SPI_MemMapPtr pSPI);
uint8_t SPI_IsSPMF(SPI_MemMapPtr pSPI);
uint8_t SPI_IsSPTEF(SPI_MemMapPtr pSPI);
uint8_t SPI_IsMODF(SPI_MemMapPtr pSPI);
uint8_t SPI_ReadDataReg(SPI_MemMapPtr pSPI);
void SPI_WriteDataReg(SPI_MemMapPtr pSPI, uint8_t u8WrBuff);
void SPI_WriteMatchValue(SPI_MemMapPtr pSPI, uint8_t u8WrBuff);
void SPI_Init(SPI_MemMapPtr pSPI, SPI_ConfigType *pConfig);
void SPI_DeInit(SPI_MemMapPtr pSPI);
ResultType SPI_TransferWait(SPI_MemMapPtr pSPI, SPI_WidthType *pRdBuff,
                            SPI_WidthType *pWrBuff, uint32_t uiLength);
void SPI_SetCallback(SPI_MemMapPtr pSPI, SPI_CallbackType pfnCallback);
void SPI_QuickInit(SPI_MemMapPtr pSPI, uint32_t bitRate);
uint8_t SPI_ReadWriteByte(SPI_MemMapPtr pSPI, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* SPI_H_ */
