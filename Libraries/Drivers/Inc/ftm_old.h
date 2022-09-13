/********************************************************************************
 *
 * @file      ftm.h
 * @brief     header file for FTM
 * @author    Freescale
 * @date      2018-04-07
 *
 ********************************************************************************/

#ifndef FTM_H_
#define FTM_H_

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
// #define FTM_Type FTM_MemMapPtr

/************************************************************
 * FTM return status
 ************************************************************/
#define FTM_ERR_SUCCESS 0       /* return ok */
#define FTM_ERR_INVALID_PARAM 1 /* return invalid parameter */

/************************************************************
 * FTM channel number
 ************************************************************/
#define FTM_CHANNEL_CHANNEL0 0 /* channel 0 */
#define FTM_CHANNEL_CHANNEL1 1 /* channel 1 */
#define FTM_CHANNEL_CHANNEL2 2 /* channel 2 */
#define FTM_CHANNEL_CHANNEL3 3 /* channel 3 */
#define FTM_CHANNEL_CHANNEL4 4 /* channel 4 */
#define FTM_CHANNEL_CHANNEL5 5 /* channel 5 */

#define FTM_CHANNELPAIR0 0 /* channel pair 0: ch0 & ch1 */
#define FTM_CHANNELPAIR1 2 /* channel pair 1: ch2 & ch3 */
#define FTM_CHANNELPAIR2 4 /* channel pair 2: ch4 & ch5 */

/************************************************************
 * FTM channel modes
 ************************************************************/
#define FTM_PWMMODE_EDGEALLIGNED 1   /* EPWM */
#define FTM_PWMMODE_CENTERALLIGNED 2 /* CPWM */
#define FTM_PWMMODE_COMBINE 3        /* Combine PWM */
#define FTM_INPUT_CAPTURE 4          /* Input capture */
#define FTM_OUTPUT_COMPARE 5         /* Output compare */
#define FTM_INPUTCAPTURE_DUALEDGE 6  /* Dual Edge Capture */

/************************************************************
 * FTM init value
 ************************************************************/
#define FTM_MOD_INIT (20000 - 1) /* MOD inite value */
#define FTM_C0V_INIT 1000        /* C0V inite value */
#define FTM_C1V_INIT 1000        /* C1V inite value */
#define FTM_C2V_INIT 1000        /* C2V inite value */
#define FTM_C3V_INIT 1000        /* C3V inite value */
#define FTM_C4V_INIT 1000        /* C4V inite value */
#define FTM_C5V_INIT 1000        /* C5V inite value */

/************************************************************
 * FTM combine feature
 ************************************************************/
#define FTM_COMBINE_FAULTEN_MASK 0x40 /* fault enable */
#define FTM_COMBINE_SYNCEN_MASK 0x20  /* sync enable */
#define FTM_COMBINE_DTEN_MASK 0x10    /* dead time insertion enable */
#define FTM_COMBINE_DECAP_MASK 0x08   /* dual capture status */
#define FTM_COMBINE_DECAPEN_MASK 0x04 /* dual capture enable */
#define FTM_COMBINE_COMP_MASK 0x02    /* complementary enable */
#define FTM_COMBINE_COMBINE_MASK 0x01 /* combine enable */

/************************************************************
 * FTM clock sources
 ************************************************************/
#define FTM_CLOCK_NOCLOCK 0        /* No Clock */
#define FTM_CLOCK_SYSTEMCLOCK 1    /* System clock/2 */
#define FTM_CLOCK_FIXEDFREQCLOCK 2 /* Fixed Freq Clock */
#define FTM_CLOCK_EXTERNALCLOCK 3  /* External Clock */

/* clock prescale */
#define FTM_CLOCK_PS_DIV1 0   /* DIV 1 */
#define FTM_CLOCK_PS_DIV2 1   /* DIV 2 */
#define FTM_CLOCK_PS_DIV4 2   /* DIV 4 */
#define FTM_CLOCK_PS_DIV8 3   /* DIV 8 */
#define FTM_CLOCK_PS_DIV16 4  /* DIV 16 */
#define FTM_CLOCK_PS_DIV32 5  /* DIV 32 */
#define FTM_CLOCK_PS_DIV64 6  /* DIV 64 */
#define FTM_CLOCK_PS_DIV128 7 /* DIV 128 */

/************************************************************
 * FTM dead time clock prescale
 ************************************************************/
#define FTM_DEADTIME_DTPS_DIV1 0  /* DIV 1 */
#define FTM_DEADTIME_DTPS_DIV4 2  /* DIV 4 */
#define FTM_DEADTIME_DTPS_DIV16 3 /* DIV 16 */

/************************************************************
 * FTM output mode
 ************************************************************/
/* output mode */
#define FTM_OUTPUT_TOGGLE 1 /* toggle output on match */
#define FTM_OUTPUT_CLEAR 2  /* clear output on match */
#define FTM_OUTPUT_SET 3    /* set output on match */

/************************************************************
 * FTM input capture edge
 ************************************************************/
/* mode edge select */
#define FTM_INPUTCAPTURE_RISINGEDGE 1  /* rising edge */
#define FTM_INPUTCAPTURE_FALLINGEDGE 2 /* falling edge */
#define FTM_INPUTCAPTURE_BOTHEDGE 3    /* both edge */

#define FTM_INPUTCAPTURE_DUALEDGE_NOEDGE 0      /* none */
#define FTM_INPUTCAPTURE_DUALEDGE_RISINGEDGE 1  /* rising edge */
#define FTM_INPUTCAPTURE_DUALEDGE_FALLINGEDGE 2 /* falling edge */
#define FTM_INPUTCAPTURE_DUALEDGE_BOTHEDGE 3    /* both edge */

/************************************************************
 * FTM dual edge capture mode
 ************************************************************/
#define FTM_INPUTCAPTURE_DUALEDGE_ONESHOT 2    /* one shot mode */
#define FTM_INPUTCAPTURE_DUALEDGE_CONTINUOUS 1 /* continuouse mode */

/************************************************************
 * FTM PWM edge
 ************************************************************/
#define FTM_PWM_HIGHTRUEPULSE 2 /* high true pulses */
#define FTM_PWM_LOWTRUEPULSE 1  /* low true pulses */

/************************************************************
 * FTM sync trigger source
 ************************************************************/
#define FTM_SYNC_TRIGGER_SOFTWARE 1 /* software synchronization */
#define FTM_SYNC_TRIGGER_TRIGGER2 \
  2 /* tigger2 synchronization, SIM_SOPT[FTMSYNC] */
#define FTM_SYNC_TRIGGER_TRIGGER1 3 /* tigger1 synchronization, FTM0CH0 */
#define FTM_SYNC_TRIGGER_TRIGGER0 4 /* tigger0 synchronization, ACMP0 */

/************************************************************
 * FTM SW output control
 ************************************************************/
#define FTM_SWOCTRL_HIGH 1 /* software output high */
#define FTM_SWOCTRL_LOW 0  /* software output low */

/************************************************************
 * FTM  polarity definition
 ************************************************************/
#define FTM_POLARITY_HIGHACTIVE 0 /* active high */
#define FTM_POLARITY_LOWACTIVE 1  /* active low */

/********************************************************************************
 * Types
 ********************************************************************************/
/************************************************************
 * FTM_CALLBACK function
 ************************************************************/
typedef void (*FTM_CallbackPtr)(void);

/************************************************************
 * FTM configure struct
 ************************************************************/
typedef struct {
  uint8_t clk_source; /* clock source */
  uint8_t prescaler;  /* clock prescaler */
  uint8_t cpwms;      /* up-down counting mode */
  uint8_t toie;       /* enable overflow interrupt */
  uint16_t modulo;    /* counter mod */
  uint16_t cnt;       /* counter value */
  uint16_t cntin;     /* counter inite */
  uint8_t mode;       /* features mode selction */
  uint8_t sync;       /* synchronization */
  uint8_t outinit;    /* initial state for channels output */
  uint8_t outmask;    /* output mask */
  uint32_t combine;   /* function for linked channels */
  uint16_t deadtime;  /* dead time insertion control */
  uint8_t exttrig;    /* external trigger */
  uint8_t pol;        /* channels polarity */
  uint16_t filter;    /* input filter control */
  uint8_t fms;        /* fault mode status */
  uint16_t fltctrl;   /* fault control */
  uint8_t fltpol;     /* fault input polarity */
  uint16_t conf;      /* FTM configuration */
  uint32_t synconf;   /* synchronization configuration */
  uint8_t invctrl;    /* inverting control */
  uint16_t swoctrl;   /* software output control */
  uint16_t pwmload;   /* pwm load control */
} FTM_ConfigType, *FTM_ConfigPtr;

/************************************************************
 * FTM channel configure struct
 ************************************************************/
typedef struct {
  uint16_t u16CnV; /* FTM channel value control */
  union {
    struct {
      uint32_t bMode : 6;   /* flextimer mode: INPUT_CAPTURE, OUTPUT_COMPARE,
                               EDGE_ALIGNED_PWM, CENTER_ALIGNED_PWM, COMBINE_PWM,
                               DUAL_EDGE_CAPTURE */
      uint32_t bEdge : 2;   /* edge select */
      uint32_t bOutCmp : 2; /* toggle, clear, set */
      uint32_t bPWMPol : 2; /* high-true pulse, low-true pulses */
      uint32_t bDualCapMode : 2; /* dual edge capture mode: one-shot, continuous
                                    mode */
      uint32_t bCHIE : 1;        /* enable channel interrupt */
    } bits;
  } ctrl; /* FTM channel feature control */
} FTM_ChParamsType;

/********************************************************************************
 * Global variables
 ********************************************************************************/

/********************************************************************************
 * Inline functions
 ********************************************************************************/
/************************************************************
 * @brief     enable the over flow interrupt
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_DisableOverflowInt
 ************************************************************/
static inline void FTM_EnableOverflowInt(FTM_Type* pFTM) {
  if (pFTM->SC & FTM_SC_TOF_MASK) {
    pFTM->SC &= ~FTM_SC_TOF_MASK;
  }
  pFTM->SC |= FTM_SC_TOIE_MASK;
}

/************************************************************
 * @brief     disable the over flow interrupt
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_EnableOverflowInt
 ************************************************************/
static inline void FTM_DisableOverflowInt(FTM_Type* pFTM) {
  pFTM->SC &= ~FTM_SC_TOIE_MASK;
}

/************************************************************
 * @brief     enable the channel interrupt
 * @param     pFTM point to one of three FTM base register address
 *            u8FTM_Channel channel number
 * @return    none
 * @see       FTM_DisableChannelInt
 ************************************************************/
static inline void FTM_EnableChannelInt(FTM_Type* pFTM, uint8_t u8FTM_Channel) {
  pFTM->CONTROLS[u8FTM_Channel].CnSC |= FTM_CnSC_CHIE_MASK;
}

/************************************************************
 * @brief     disable the channel interrupt
 * @param     pFTM point to one of three FTM base register address
 *            u8FTM_Channel channel number
 * @return    none
 * @see       FTM_EnableChannelInt
 ************************************************************/
static inline void FTM_DisableChannelInt(FTM_Type* pFTM,
                                         uint8_t u8FTM_Channel) {
  pFTM->CONTROLS[u8FTM_Channel].CnSC &= ~FTM_CnSC_CHIE_MASK;
}

/************************************************************
 * @brief     get the over flow flag
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_ClrOverFlowFlag
 ************************************************************/
static inline uint8_t FTM_GetOverFlowFlag(FTM_Type* pFTM) {
  return (pFTM->SC & FTM_SC_TOF_MASK);
}

/************************************************************
 * @brief     clear the over flow flag
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_GetOverFlowFlag
 ************************************************************/
static inline void FTM_ClrOverFlowFlag(FTM_Type* pFTM) {
  if (pFTM->SC & FTM_SC_TOF_MASK) {
    pFTM->SC &= ~FTM_SC_TOF_MASK;
  }
}

/************************************************************
 * @brief     get the channel flag
 * @param     pFTM point to one of three FTM base register address
 *            u8FTM_Channel channel number
 * @return    none
 * @see       FTM_ClrChannelFlag
 ************************************************************/
static inline uint8_t FTM_GetChannelFlag(FTM_Type* pFTM,
                                         uint8_t u8FTM_Channel) {
  return (pFTM->CONTROLS[u8FTM_Channel].CnSC & FTM_CnSC_CHF_MASK);
}

/************************************************************
 * @brief     clear the channel flag
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_GetChannelFlag
 ************************************************************/
static inline void FTM_ClrChannelFlag(FTM_Type* pFTM, uint8_t u8FTM_Channel) {
  (void)pFTM->CONTROLS[u8FTM_Channel].CnSC; /* dummy read while CHF is set */
  pFTM->CONTROLS[u8FTM_Channel].CnSC &= ~FTM_CnSC_CHF_MASK;
}

/************************************************************
 * @brief     enable the write protection function, write protected bits cannot
 *be written
 * @param     pFTM point to one of three FTM base registeraddress
 * @return    none
 * @see       FTM_WriteProtectionDisable
 ************************************************************/
static inline void FTM_WriteProtectionEnable(FTM_Type* pFTM) {
  pFTM->FMS |= FTM_FMS_WPEN_MASK;
}

/************************************************************
 * @brief     disable the write protection function, write protected bits can be
 *written
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_WriteProtectionDisable
 ************************************************************/
static inline void FTM_WriteProtectionDisable(FTM_Type* pFTM) {
  if (pFTM->FMS & FTM_FMS_WPEN_MASK) {
    pFTM->MODE |= FTM_MODE_WPDIS_MASK;
  }
}

/************************************************************
 * @brief     set FTMEN bit to enable FTM-specific register
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_SetFTMBasic
 ************************************************************/
static inline void FTM_SetFTMEnhanced(FTM_Type* pFTM) {
  if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not write protected */
  {
    pFTM->MODE |= FTM_MODE_FTMEN_MASK;
  } else {
    FTM_WriteProtectionDisable(pFTM);
    pFTM->MODE |= FTM_MODE_FTMEN_MASK;
    FTM_WriteProtectionEnable(pFTM);
  }
}

/************************************************************
 * @brief     clear FTMEN bit to disable FTM-specific registers, only
 *TPM-compatible registers can be used
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_SetFTMEnhanced
 ************************************************************/
static inline void FTM_SetFTMBasic(FTM_Type* pFTM) {
  if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not write protected */
  {
    pFTM->MODE &= ~FTM_MODE_FTMEN_MASK;
  } else {
    FTM_WriteProtectionDisable(pFTM);
    pFTM->MODE &= ~FTM_MODE_FTMEN_MASK;
    FTM_WriteProtectionEnable(pFTM);
  }
}

/************************************************************
 * @brief     set the ftm mod value
 * @param     pFTM point to one of three FTM base register address
 *            u16ModValue the mod value required to set
 * @return    none
 * @see       FTM_SetChannelValue
 ************************************************************/
static inline void FTM_SetModValue(FTM_Type* pFTM, uint16_t u16ModValue) {
  pFTM->CNT = 0;
  pFTM->MOD = u16ModValue;
  if ((FTM_Type*)FTM2 == pFTM) {
    if (pFTM->MODE & FTM_MODE_FTMEN_MASK) {
      pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
    } else {
    }
  } else {
  }
}

/************************************************************
 * @brief     set the ftm channel value
 * @param     pFTM point to one of three FTM base register address
 *            u16ChannelValue the CnV value required to set
 *            u8FTM_Channel ftm channel number
 * @return    none
 * @see       FTM_SetModValue
 ************************************************************/
static inline void FTM_SetChannelValue(FTM_Type* pFTM, uint8_t u8FTM_Channel,uint16_t u16ChannelValue) 
	{
  pFTM->CONTROLS[u8FTM_Channel].CnV = u16ChannelValue;
  if ((FTM_Type*)FTM2 == pFTM) 
		{
    if (pFTM->MODE & FTM_MODE_FTMEN_MASK) 
			{
      if (u8FTM_Channel < 2) 
				{
        pFTM->COMBINE |=  FTM_COMBINE_SYNCEN0_MASK; /* enable the sync function */
      } 
				else if (u8FTM_Channel < 4) 
			{
        pFTM->COMBINE |= FTM_COMBINE_SYNCEN1_MASK;
      } 
					else 
			{
        pFTM->COMBINE |= FTM_COMBINE_SYNCEN2_MASK;
      }
      pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
      } 
			else 
				{
        }
        } 
		else 
			{
  }
//			if ((FTM_Type*)FTM1 == pFTM) 
//		{
//    if (pFTM->MODE & FTM_MODE_FTMEN_MASK) 
//			{
//      if (u8FTM_Channel < 2) 
//				{
//        pFTM->COMBINE |=
//            FTM_COMBINE_SYNCEN0_MASK; /* enable the sync function */
//      } 
//				else if (u8FTM_Channel < 4) 
//			{
//        pFTM->COMBINE |= FTM_COMBINE_SYNCEN1_MASK;
//      } 
//					else 
//			{
//        pFTM->COMBINE |= FTM_COMBINE_SYNCEN2_MASK;
//      }
//      pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
//      } 
//			else 
//				{
//        }
//        } 
//		else 
//			{
//  }
}

/************************************************************
 * @brief     set the ftm channel value
 * @param     pFTM point to one of three FTM base register address
 *            u16CounterValue the CNTIN value required to set
 * @return    none
 * @see       FTM_SetModValue
 ************************************************************/
static inline void FTM_SetCounterInitValue(FTM_Type* pFTM,
                                           uint16_t u16CounterValue) {
  pFTM->CNTIN = u16CounterValue;
  if (pFTM->MODE & FTM_MODE_FTMEN_MASK) {
    pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
  } else {
  }
}

/************************************************************
 * @brief     set the channel output mask value, FTM2 used only
 * @param     pFTM   point to one of three FTM base register address
 *            u16ChMask the CNTIN value required to set
 * @return    none
 * @see       FTM_UnMaskChannels
 ************************************************************/
static inline void FTM_MaskChannels(FTM_Type* pFTM, uint16_t u16ChMask) {
  pFTM->OUTMASK |= u16ChMask;
}

/************************************************************
 * @brief     clear the channel output mask value, FTM2 used only
 * @param     pFTM point to one of three FTM base register address
 *            u16ChMask the CNTIN value required to set
 * @return    none
 * @see       FTM_MaskChannels
 ************************************************************/
static inline void FTM_UnMaskChannels(FTM_Type* pFTM, uint16_t u16ChMask) {
  pFTM->OUTMASK &= ~u16ChMask;
}

/************************************************************
 * @brief     set FTM channels polarity
 * @param     pFTM point to one of three FTM base register address
 *            u8ChsPolValue the channels value need to be set
 * @return    none
 * @see       FTM_GetChannelsPolarity
 ************************************************************/
static inline void FTM_SetChannelsPolarity(FTM_Type* pFTM,
                                           uint8_t u8ChsPolValue) {
  pFTM->POL = u8ChsPolValue;
}

/************************************************************
 * @brief     get FTM channels polarity
 * @param     pFTM point to one of three FTM base register address
 * @return    uint8_t the channels polarity
 * @see       FTM_SetChannelsPolarity
 ************************************************************/
static inline uint8_t FTM_GetChannelsPolarity(FTM_Type* pFTM) {
  return (pFTM->POL);
}

/************************************************************
 * @brief     select the enhanced SYNC mode
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_DisableEnhancedSYNCMode
 ************************************************************/
static inline void FTM_EnableEnhancedSYNCMode(FTM_Type* pFTM) {
  pFTM->SYNCONF |= FTM_SYNCONF_SYNCMODE_MASK; /* recommend enhanced sync mode */
}

/************************************************************
 * @brief     select the legacy SYNC mode
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_EnableEnhancedSYNCMode
 ************************************************************/
static inline void FTM_DisableEnhancedSYNCMode(FTM_Type* pFTM) {
  pFTM->SYNCONF &=
      ~FTM_SYNCONF_SYNCMODE_MASK; /* recommend enhanced sync mode */
}

/************************************************************
 * @brief     set the external trigger source
 * @param     pFTM point to one of three FTM base register address
 * @param     u8TirggerSource initial trigger or CHn(0~5)trigger
 * @return    none
 * @see       FTM_GetExternalTriggerFlag
 ************************************************************/
static inline void FTM_SetExternalTrigger(FTM_Type* pFTM,
                                          uint8_t u8TirggerSource) {
  pFTM->EXTTRIG = u8TirggerSource;
}

/************************************************************
 * @brief     get the external trigger flag
 * @param     pFTM point to one of three FTM base register address
 * @return    ex trigger flag
 * @see       FTM_SetExternalTrigger
 ************************************************************/
static inline uint8_t FTM_GetExternalTriggerFlag(FTM_Type* pFTM) {
  return (pFTM->EXTTRIG & FTM_EXTTRIG_TRIGF_MASK);
}

/************************************************************
 * @brief     set LDOK bit
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_SetLoadMatchChannel
 ************************************************************/
static inline void FTM_SetLoadEnable(FTM_Type* pFTM) {
  pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
}

/************************************************************
 * @brief     set the channel in the matching process
 * @param     pFTM point to one of three FTM base register address
 * @param     u8Matchchannel the channel in the matching process
 * @return    none
 * @see       FTM_SetLoadEnable
 ************************************************************/
static inline void FTM_SetLoadMatchChannel(FTM_Type* pFTM,
                                           uint8_t u8Matchchannel) {
  pFTM->PWMLOAD |= u8Matchchannel;
}

/************************************************************
 * @brief     disable the channel input capture filter
 * @param     pFTM point to one of three FTM base register address
 * @param     u8FTM_Channel the channel number: 0~3
 * @return    none
 * @see       FTM_InputCaptureFilterSet
 ************************************************************/
static inline void FTM_InputCaptureFilterClr(FTM_Type* pFTM,
                                             uint8_t u8FTM_Channel) {
  pFTM->FILTER &= ~(0x000F << (u8FTM_Channel << 2));
}

/************************************************************
 * @brief     set the channel input capture filter value *
 * @param     pFTM point to one of three FTM base register address
 * @param     u8FTM_Channel the channel number: 0~3
 *            u8FilterValue fliter cycles:1~15, 0: disable channel filter
 * @return    none
 * @see       FTM_InputCaptureFilterClr
 ************************************************************/
static inline void FTM_InputCaptureFilterSet(FTM_Type* pFTM,
                                             uint8_t u8FTM_Channel,
                                             uint8_t u8FilterValue) {
  if (u8FilterValue) {
    pFTM->FILTER |= (u8FilterValue << (u8FTM_Channel << 2));
  } else {
    FTM_InputCaptureFilterClr(pFTM, u8FTM_Channel);
  }
}

/************************************************************
 * @brief     enable the fault input pin
 * @param     pFTM point to one of three FTM base register address
 * @param     u8FaultPin the fault input channel number: 0~3
 * @return    none
 * @see       FTM_FaultPinDisable
 ************************************************************/
static inline void FTM_FaultPinEnable(FTM_Type* pFTM, uint8_t u8FaultPin) {
  if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
  {
    pFTM->FLTCTRL |= (1 << u8FaultPin);
  } else /* if protected */
  {
    FTM_WriteProtectionDisable(pFTM);
    pFTM->FLTCTRL |= (1 << u8FaultPin);
    FTM_WriteProtectionEnable(pFTM);
  }
}

/************************************************************
 * @brief     disable the fault input pin
 * @param     pFTM point to one of three FTM base register address
 * @param     u8FaultPin the fault input channel number: 0~3
 * @return    none
 * @see       FTM_FaultPinEnable
 ************************************************************/
static inline void FTM_FaultPinDisable(FTM_Type* pFTM, uint8_t u8FaultPin) {
  if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
  {
    pFTM->FLTCTRL &= ~(1 << u8FaultPin);
  } else /* if protected */
  {
    FTM_WriteProtectionDisable(pFTM);
    pFTM->FLTCTRL &= ~(1 << u8FaultPin);
    FTM_WriteProtectionEnable(pFTM);
  }
}

/************************************************************
 * @brief     enable the fault pin filter
 * @param     pFTM point to one of three FTM base register address
 * @param     u8FaultPin the fault input channel number: 0~3
 * @return    none
 * @see       FTM_FaultPinFilterDisable
 ************************************************************/
static inline void FTM_FaultPinFilterEnable(FTM_Type* pFTM,
                                            uint8_t u8FaultPin) {
  if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
  {
    pFTM->FLTCTRL |= (0x10 << u8FaultPin);
  } else /* if protected */
  {
    FTM_WriteProtectionDisable(pFTM);
    pFTM->FLTCTRL |= (0x10 << u8FaultPin);
    FTM_WriteProtectionEnable(pFTM);
  }
}

/************************************************************
 * @brief     disable the fault pin filter
 * @param     pFTM point to one of three FTM base register address
 *            u8FaultPin the fault input channel number: 0~3
 * @return    none
 * @see       FTM_FaultPinFilterDisable
 ************************************************************/
static inline void FTM_FaultPinFilterDisable(FTM_Type* pFTM,
                                             uint8_t u8FaultPin) {
  if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
  {
    pFTM->FLTCTRL &= ~(0x10 << u8FaultPin);
  } else /* if protected */
  {
    FTM_WriteProtectionDisable(pFTM);
    pFTM->FLTCTRL &= ~(0x10 << u8FaultPin);
    FTM_WriteProtectionEnable(pFTM);
  }
}

/************************************************************
 * @brief     disable all the fault pins filter together
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_FaultPinFilterSet
 ************************************************************/
static inline void FTM_FaultPinFilterCDisableAll(FTM_Type* pFTM) {
  pFTM->FLTCTRL &= ~FTM_FLTCTRL_FFVAL_MASK;
}

/************************************************************
 * @brief     set the fault filter value All channels share the same filter
 *value
 * @param     pFTM point to one of three FTM base register address
 *            u8FilterValue the fault input filter value: 1~15, 0 disable the
 *filter
 * @return    none
 * @see       FTM_FaultPinFilterCDisableAll
 ************************************************************/
static inline void FTM_FaultPinFilterSet(FTM_Type* pFTM,
                                         uint8_t u8FilterValue) {
  if (u8FilterValue) {
    pFTM->FLTCTRL |= FTM_FLTCTRL_FFVAL(u8FilterValue);
  } else {
    FTM_FaultPinFilterCDisableAll(pFTM);
  }
}

/************************************************************
 * @brief     get the logic OR of all the fault detection flags
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 * @see       FTM_GetFaultDetectionFlag
 ************************************************************/
static inline uint8_t FTM_GetFaultDetectionLogicORFlag(FTM_Type* pFTM) {
  return (pFTM->FMS & FTM_FMS_FAULTF_MASK);
}

/************************************************************
 * @brief     get the fault detection flag
 * @param     pFTM point to one of three FTM base register address
 * @param     u8FaultPin fault input pin number: 0~3
 * @return    none
 * @see       FTM_GetFaultDetectionLogicORFlag
 ************************************************************/
static inline uint8_t FTM_GetFaultDetectionFlag(FTM_Type* pFTM,
                                                uint8_t u8FaultPin) {
  return (pFTM->FMS & (1 << u8FaultPin));
}

/************************************************************
 * @brief     get the logic OR value of the fault inputs
 * @param     pFTM point to one of three FTM base register address
 * @return    none
 ************************************************************/
static inline uint8_t FTM_GetFaultInputsLogicORValue(FTM_Type* pFTM) {
  return (pFTM->FMS & FTM_FMS_FAULTIN_MASK);
}

/************************************************************
 * @brief     Get the current count value of the FTM
 * @param     pFTM point to one of three FTM base register address
 * @return    uint16_t
 ************************************************************/
static inline uint16_t FTM_GetCountValue(FTM_Type* pFTM) {
  return (uint16_t)pFTM->CNT;
}

/******************************************************************************
 * Global functions
 ******************************************************************************/
void FTM_ClockSet(FTM_Type* pFTM, uint8_t u8ClockSource,
                  uint8_t u8ClockPrescale);
void FTM_PWMInit(FTM_Type* pFTM, uint8_t u8PWMModeSelect,
                 uint8_t u8PWMEdgeSelect);
void FTM_InputCaptureInit(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                          uint8_t u8CaptureMode);
void FTM_DualEdgeCaptureInit(FTM_Type* pFTM, uint8_t u8ChannelPair,
                             uint8_t u8CaptureMode, uint8_t u8Channel_N_Edge,
                             uint8_t u8Channel_Np1_Edge);
void FTM_OutputCompareInit(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                           uint8_t u8CompareMode);
void FTM_SoftwareSync(FTM_Type* pFTM);
void FTM_HardwareSync(FTM_Type* pFTM, uint8_t u8TriggerN);
void FTM_HardwareSyncCombine(FTM_Type* pFTM, uint8_t u8TriggerMask);
void FTM_GenerateTrig2(FTM_Type* pFTM);
void FTM_PWMDeadtimeSet(FTM_Type* pFTM, uint8_t u8PrescalerValue,
                        uint8_t u8DeadtimeValue);
void FTM_OutputMaskSet(FTM_Type* pFTM, uint8_t u8FTM_Channel);
void FTM_SWOutputControlSet(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                            uint8_t u8ChannelValue);
void FTM_SetDebugModeBehavior(FTM_Type* pFTM, uint8_t u8DebugMode);
void FTM_SetTOFFrequency(FTM_Type* pFTM, uint8_t u8TOFNUM);
void FTM_PolaritySet(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                     uint8_t u8ActiveValue);
void FTM_InvertChannel(FTM_Type* pFTM, uint8_t u8ChannelPair);
void FTM_Init(FTM_Type* pFTM, FTM_ConfigType* pConfig);
void FTM_DeInit(FTM_Type* pFTM);
void FTM_ChannelInit(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                     FTM_ChParamsType pFTM_ChParams);
void FTM_SetCallback(FTM_Type* pFTM, FTM_CallbackPtr pfnCallback);
void FTM_SyncConfigActivate(FTM_Type* pFTM, uint32_t u32ConfigValue);
void FTM_SyncConfigDeactivate(FTM_Type* pFTM, uint32_t u32ConfigValue);
uint8_t FTM_GetFaultDetectionLogicORFlag(FTM_Type* pFTM);
uint8_t FTM_GetFaultDetectionFlag(FTM_Type* pFTM, uint8_t u8FaultPin);
uint8_t FTM_GetFaultInputsLogicORValue(FTM_Type* pFTM);
void FTM_WriteProtectionEnable(FTM_Type* pFTM);
void FTM_WriteProtectionDisable(FTM_Type* pFTM);
void FTM_FaultPinFilterCDisableAll(FTM_Type* pFTM);
void FTM_FaultPinFilterSet(FTM_Type* pFTM, uint8_t u8FilterValue);
void FTM_FaultPinFilterDisable(FTM_Type* pFTM, uint8_t u8FaultPin);
void FTM_FaultPinFilterEnable(FTM_Type* pFTM, uint8_t u8FaultPin);
void FTM_FaultPinEnable(FTM_Type* pFTM, uint8_t u8FaultPin);
void FTM_FaultPinDisable(FTM_Type* pFTM, uint8_t u8FaultPin);
void FTM_InputCaptureFilterClr(FTM_Type* pFTM, uint8_t u8FTM_Channel);
void FTM_InputCaptureFilterSet(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                               uint8_t u8FilterValue);
void FTM_SetLoadMatchChannel(FTM_Type* pFTM, uint8_t u8Matchchannel);
void FTM_SetLoadEnable(FTM_Type* pFTM);
uint8_t FTM_GetExternalTriggerFlag(FTM_Type* pFTM);
void FTM_DisableEnhancedSYNCMode(FTM_Type* pFTM);
void FTM_EnableEnhancedSYNCMode(FTM_Type* pFTM);
uint8_t FTM_GetChannelsPolarity(FTM_Type* pFTM);
void FTM_SetChannelsPolarity(FTM_Type* pFTM, uint8_t u8ChsPolValue);
void FTM_UnMaskChannels(FTM_Type* pFTM, uint16_t u16ChMask);
void FTM_MaskChannels(FTM_Type* pFTM, uint16_t u16ChMask);
void FTM_SetCounterInitValue(FTM_Type* pFTM, uint16_t u16CounterValue);
void FTM_SetChannelValue(FTM_Type* pFTM, uint8_t u8FTM_Channel,
                         uint16_t u16ChannelValue);
void FTM_SetModValue(FTM_Type* pFTM, uint16_t u16ModValue);
void FTM_SetFTMBasic(FTM_Type* pFTM);
void FTM_SetFTMEnhanced(FTM_Type* pFTM);
void FTM_ClrChannelFlag(FTM_Type* pFTM, uint8_t u8FTM_Channel);
uint8_t FTM_GetChannelFlag(FTM_Type* pFTM, uint8_t u8FTM_Channel);
void FTM_ClrOverFlowFlag(FTM_Type* pFTM);
uint8_t FTM_GetOverFlowFlag(FTM_Type* pFTM);
void FTM_DisableChannelInt(FTM_Type* pFTM, uint8_t u8FTM_Channel);
void FTM_EnableChannelInt(FTM_Type* pFTM, uint8_t u8FTM_Channel);
void FTM_DisableOverflowInt(FTM_Type* pFTM);
void FTM_EnableOverflowInt(FTM_Type* pFTM);
uint16_t FTM_GetCountValue(FTM_Type* pFTM);
void FTM_QuickInit(FTM_Type* pFTM, uint8_t u8Channel, uint8_t FTMChMode,
                   uint16_t freq);

#ifdef __cplusplus
}
#endif

#endif /* FTM_H_ */
