/********************************************************************************
 *
 * @file      spi.c
 * @brief     provide APIs for configuring SPI module
 * @author    Freescale
 * @date      2018-04-19
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "spi.h"
#include "common.h"

/********************************************************************************
 * Local variables
 ********************************************************************************/
SPI_CallbackType SPI_Callback[MAX_SPI_NO] = {(SPI_CallbackType)(0)};

/********************************************************************************
 * Local function prototypes
 ********************************************************************************/

/********************************************************************************
 * Local functions
 ********************************************************************************/
/************************************************************
 * @brief     SPI0 interrupt service routine
 * @param     none
 * @return    none
 ************************************************************/
void SPI0_IRQHandler(void) {
  if (SPI_Callback[0]) {
    SPI_Callback[0]();
  }
}

/************************************************************
 * @brief     SPI1 interrupt service routine
 * @param     none
 * @return    none
 ************************************************************/
void SPI1_IRQHandler(void) {
  if (SPI_Callback[1]) {
    SPI_Callback[1]();
  }
}

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     initialize SPI as per params
 * @param     pSPI point to SPI module type
 *            pConfig point to configuration parameters
 * @return    none
 ************************************************************/
void SPI_Init(SPI_MemMapPtr pSPI, SPI_ConfigType *pConfig) {
  /* enable SPI clock gating on */
  if (pSPI == SPI0) {
    SIM_SCGC |= SIM_SCGC_SPI0_MASK;
  } else {
    SIM_SCGC |= SIM_SCGC_SPI1_MASK;
  }
  SIM->PINSEL1 |= SIM_PINSEL1_SPI1PS_MASK;
  /* configure other control bits */
  if (pConfig->sSettings.bIntEn) {
    SPI_IntEnable(pSPI);

    if (pSPI == SPI0) {
      Enable_Interrupt(SPI0_IRQn);
    } else {
      Enable_Interrupt(SPI1_IRQn);
    }
  }

  if (pConfig->sSettings.bTxIntEn) {
    SPI_TxIntEnable(pSPI);

    if (pSPI == SPI0) {
      Enable_Interrupt(SPI0_IRQn);
    } else {
      Enable_Interrupt(SPI1_IRQn);
    }
  }
  if (pConfig->sSettings.bMasterMode) {
    SPI_SetMasterMode(pSPI);
  } else {
    SPI_SetSlaveMode(pSPI);
  }

  if (pConfig->sSettings.bClkPolarityLow) {
    SPI_SetClockPol(pSPI, 1);
  } else {
    SPI_SetClockPol(pSPI, 0);
  }
  if (pConfig->sSettings.bClkPhase1) {
    SPI_SetClockPhase(pSPI, 1);
  } else {
    SPI_SetClockPhase(pSPI, 0);
  }

  if (pConfig->sSettings.bShiftLSBFirst) {
    SPI_SetLSBFirst(pSPI);
  }
  if (pConfig->sSettings.bMatchIntEn) {
    SPI_MatchIntEnable(pSPI);
  }
  if (pConfig->sSettings.bModeFaultEn) {
    SPI_ModfEnable(pSPI);
  }
  if (pConfig->sSettings.bMasterAutoDriveSS) {
    /* set both SSOE and MODFEN bits when auto drive slave SS is enabled */
    SPI_SSOutputEnable(pSPI);
    SPI_ModfEnable(pSPI);
  }

  if (pConfig->sSettings.bPinAsOuput) {
    SPI_BidirPinEnable(pSPI);
  }

  if (pConfig->sSettings.bBidirectionModeEn) {
    SPI_BidirOutEnable(pSPI);
  }
  if (pConfig->sSettings.bStopInWaitMode) {
    SPI_ClockStopEnable(pSPI);
  }

  if (pConfig->sSettings.bMasterMode) {
    SPI_SetBaudRate(pSPI, pConfig->u32BusClkHz, pConfig->u32BitRate);
  }

  /* enable SPI module */
  if (pConfig->sSettings.bModuleEn) {
    SPI_Enable(pSPI);
  }
}

/************************************************************
 * @brief     SPI set baud rate
 * @param     pSPI point to SPI module type
 *            u32BusClock bus clock
 *            u32Bps set spi's baudrate
 * @return    none
 ************************************************************/
void SPI_SetBaudRate(SPI_MemMapPtr pSPI, uint32_t u32BusClock,
                     uint32_t u32Bps) {
  uint32_t u32BitRateDivisor;
  uint8_t u8Sppr;
  uint8_t u8Spr;
  uint8_t u8ReadFlag;
  u32BitRateDivisor = u32BusClock / u32Bps; /* calculate bit rate divisor */

  u8ReadFlag = 0;
  /* find best fit SPPR and SPR */
  for (u8Spr = 0; u8Spr <= 8; u8Spr++) {
    for (u8Sppr = 0; u8Sppr <= 7; u8Sppr++) {
      if ((u32BitRateDivisor >> (u8Spr + 1)) <= (u8Sppr + 1)) {
        u8ReadFlag = 1;
        break;
      }
    }
    if (u8ReadFlag) {
      break;
    }
  }
  if (u8Sppr >= 8) {
    u8Sppr = 7;
  }
  if (u8Spr > 8) {
    u8Spr = 8;
  }
  /* set bit rate */
  pSPI->BR = SPI_BR_SPPR(u8Sppr) | SPI_BR_SPR(u8Spr);
}

/************************************************************
 * @brief     implement write data to SPI
 * @param     pSPI point to SPI module type
 *            pRdBuff read data buffer pointer
 *            pWrBuff write data buffer pointer
 *            uiLength read / write data length
 * @return    < 0, means error, = 0: success
 ************************************************************/
ResultType SPI_TransferWait(SPI_MemMapPtr pSPI, SPI_WidthType *pRdBuff,
                            SPI_WidthType *pWrBuff, uint32_t uiLength) {
  ResultType err = SPI_ERR_SUCCESS;
  uint32_t i;

  if (!uiLength) {
    return (err);
  }
  for (i = 0; i < uiLength; i++) {
    while (!SPI_IsSPTEF(pSPI))
      ;
    SPI_WriteDataReg(pSPI, pWrBuff[i]);
    while (!SPI_IsSPRF(pSPI))
      ;
    pRdBuff[i] = SPI_ReadDataReg(pSPI);
  }
  return (err);
}

/************************************************************
 * @brief     deinitialize SPI to the default state (reset value)
 * @param     pSPI point to SPI module type
 * @return    none
 ************************************************************/
void SPI_DeInit(SPI_MemMapPtr pSPI) {
  int16_t i;
  pSPI->C1 = SPI_C1_DEFAULT;
  pSPI->C2 = SPI_C2_DEFAULT;
  pSPI->BR = SPI_BR_DEFAULT;
  pSPI->M = SPI_M_DEFAULT;
  for (i = 0; i < 100; i++)
    ; /* wait for some cycles for the ISR exit */
}

/************************************************************
 * @brief     set up SPI callback routines to be called by interrupt service
 *routine
 * @param     pSPI point to SPI module type
 *            pfnCallback callback routine
 * @return    none
 ************************************************************/
void SPI_SetCallback(SPI_MemMapPtr pSPI, SPI_CallbackType pfnCallback) {
  uint32_t u32Port = ((uint32_t)pSPI - (uint32_t)SPI0) >> 12;
  SPI_Callback[u32Port] = pfnCallback;
}

/************************************************************
 * @brief     quickly initialize SPI module
 * @param     pSPI point to SPI module type
 *            bitRate set spi's baudrate
 * @return    none
 ************************************************************/
void SPI_QuickInit(SPI_MemMapPtr pSPI, uint32_t bitRate) {
  SPI_ConfigType sSPIConfig = {{0}};
  sSPIConfig.u32BitRate = bitRate;
  sSPIConfig.u32BusClkHz = BUS_CLOCK;
  sSPIConfig.sSettings.bModuleEn = 1;
  sSPIConfig.sSettings.bMasterMode = 1;
  sSPIConfig.sSettings.bClkPolarityLow = 1;
  sSPIConfig.sSettings.bClkPhase1 = 1;
  sSPIConfig.sSettings.bMasterAutoDriveSS = 1;

  SPI_Init(pSPI, &sSPIConfig);
}

/************************************************************
 * @brief     read and write one byte
 * @param     pSPI point to SPI module type
 *            data byte to be sent to SPI
 * @return    none
 ************************************************************/
uint8_t SPI_ReadWriteByte(SPI_MemMapPtr pSPI, uint8_t data) {
  uint8_t rxData = 0;
  uint8_t txData = data;
  SPI_TransferWait(pSPI, &rxData, &txData, 1);
  return rxData;
}
