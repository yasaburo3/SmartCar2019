/********************************************************************************
 *
 * @file      init.c
 * @brief     initialize each module
 * @author    SJX
 * @date      2018-04-08
 *
 ********************************************************************************/

/********************************************************************************
 * Includes
 ********************************************************************************/
#include "init.h"
#include "adc.h"
#include "ftm.h"
#include "gpio.h"
#include "pwt.h"
#include "KEA128_irq.h"

/********************************************************************************
 * Local functions
 ********************************************************************************/

/********************************************************************************
 * Global functions
 ********************************************************************************/
/************************************************************
 * @brief     initialize LEDs
 * @param     none
 * @return    none
 ************************************************************/
void LED_Init(void) 
{
//  /* 红 */
//  CONFIG_PIN_AS_GPIO(PTB, PTA3, OUTPUT);
//  OUTPUT_CLEAR(PTB, PTA3);

//  /* 绿 */
//  CONFIG_PIN_AS_GPIO(PTB, PTB4, OUTPUT);
//  OUTPUT_CLEAR(PTB, PTB4);

//  /* 蓝 */
//  CONFIG_PIN_AS_GPIO(PTE, PTE5, OUTPUT);
//  OUTPUT_CLEAR(PTE, PTE5);
//	/*BI*/
//	 CONFIG_PIN_AS_GPIO(PTB, PTA7, OUTPUT);
//  OUTPUT_SET(PTB, PTA7);
	
	//绿灯
	CONFIG_PIN_AS_GPIO(PTG, PTG1, OUTPUT);
	OUTPUT_CLEAR(PTG, PTG1);
	
	//红灯
	CONFIG_PIN_AS_GPIO(PTG, PTG2, OUTPUT);
	OUTPUT_CLEAR(PTG, PTG2);
}

/************************************************************
 * @brief     initialize sensors
 * @param     none
 * @return    none
 ************************************************************/
void Sensor_Init(void) 
{
  /* 接口 1 */
  ADC_QuickInit(ADC_CHANNEL_AD2);
  ADC_QuickInit(ADC_CHANNEL_AD3);
  ADC_QuickInit(ADC_CHANNEL_AD4);
  ADC_QuickInit(ADC_CHANNEL_AD5);
  ADC_QuickInit(ADC_CHANNEL_AD6);

  /* 接口 2 */
//  ADC_QuickInit(ADC_CHANNEL_AD11);
//  ADC_QuickInit(ADC_CHANNEL_AD10);
//  ADC_QuickInit(ADC_CHANNEL_AD9);
//  ADC_QuickInit(ADC_CHANNEL_AD8);
//  ADC_QuickInit(ADC_CHANNEL_AD15);
	ADC_QuickInit(ADC_CHANNEL_AD13);
	ADC_QuickInit(ADC_CHANNEL_AD12);
	ADC_QuickInit(ADC_CHANNEL_AD7);
	//ADC_QuickInit(ADC_CHANNEL_AD5);
	
	ADC_QuickInit(ADC_CHANNEL_AD14);
}

/************************************************************
 * @brief     initialize motor(s)
 * @param     none
 * @return    none
 ************************************************************/
void Motor_Init(void) 
{
//  /* PWM 1 */
//  FTM_QuickInit(FTM2, FTM_CHANNEL_CHANNEL3, FTM_PWMMODE_EDGEALLIGNED, 5000);
//  SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);  // PTD 1

//  /* PWM 2 */
//  FTM_QuickInit(FTM2, FTM_CHANNEL_CHANNEL2, FTM_PWMMODE_EDGEALLIGNED, 5000);
//  SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);  // PTD 0

//  /* PWM 3 */
//  FTM_QuickInit(FTM2, FTM_CHANNEL_CHANNEL1, FTM_PWMMODE_EDGEALLIGNED, 5000);
//  SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);  // PTH 1

//  /* PWM 4 */
//  FTM_QuickInit(FTM2, FTM_CHANNEL_CHANNEL0, FTM_PWMMODE_EDGEALLIGNED, 5000);
//  SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);  // PTH 0
	
//    
//    FTM_PWM_init(CFTM1, FTM_CH1, FTM_PTC5, 12500, 0);//PWM1 PTC5
//    FTM_PWM_init(CFTM2, FTM_CH2, FTM_PTD0, 12500, 0);//PWM2  PTD0

    FTM_PWM_init(CFTM2, FTM_CH3, FTM_PTG5, 12500, 0);//PWM1 PTG5
    FTM_PWM_init(CFTM2, FTM_CH2, FTM_PTG4, 12500, 0);//PWM2  PTG4
    FTM_PWM_init(CFTM2, FTM_CH1, FTM_PTF1, 12500, 0);//PWM3  PTF1
    FTM_PWM_init(CFTM2, FTM_CH0, FTM_PTF0, 12500, 0);//PWM4  PTF0
}
/************************************************************
 * @brief     initialize steer(s)
 * @param     none
 * @return    none
 ************************************************************/
void Steer_Init(uint16_t frequence,uint16_t duty)
{
  /* PWM 1 */
//  FTM_QuickInit(FTM1, FTM_CHANNEL_CHANNEL0, FTM_PWMMODE_EDGEALLIGNED, frequence);
//  SIM_PINSEL0 |= SIM_PINSEL_FTM1PS0_MASK;  
//	FTM_SetChannelValue(FTM1, FTM_CHANNEL_CHANNEL0, duty);
	FTM_PWM_init(CFTM0, FTM_CH1,FTM_PTA1, frequence, duty);
}
void Encoder_Init()
{
	//FTM_InputCaptureInit(CFTM0, FTM_CH0, FTM_INPUTCAPTURE_RISINGEDGE); 
	CONFIG_PIN_AS_GPIO(PTE, PTE2, INPUT);
	ENABLE_INPUT(PTE,PTE2);
	
	CONFIG_PIN_AS_GPIO(PTA, PTA0, INPUT);
	ENABLE_INPUT(PTA,PTA0);
	
}
uint16_t read_speed()
{
	return FTM_count_get(CFTM0);
}

/*编码器初始化*/
void encoderFtmInit(void)
{
	/* 
	CLK -> PTE7
	DIR -> PTH5
	*/
//	PORT->PUE1 |= PORT_PUE1_PTEPE7_MASK;
//	SIM->SCGC |= SIM_SCGC_FTM1_MASK;
//	SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);
	
	FTM_count_init(CFTM0);//输入用E7
//	
//	GPIOB->PIDR &= ~(1 << 29);

//	FTM_ClockSet(FTM1, 3, 0);
//	FTM1->SC |= FTM_SC_PS(0);	            //分频系数	
//  FTM1->SC |= FTM_SC_CLKS(3);                //选择外部时钟作为FTM输入时钟
//	FTM1->CNT = 0;
}

///*PWT初始化*/
//void PWTInit(void)
//{
//	PWT_ConfigType  PWTConfig = {0};
//    PWTConfig.bOverflowIntEn      = 1;    				  /* enable overflow interrupt*/
//    PWTConfig.bReadyIntEn         = 1;                     /*enable data ready interrupt*/
//    PWTConfig.bPWTIntEn           = 1;                     /*enable PWT module interrupt*/
//    PWTConfig.bPWTEn              = 1;                     /*enable PWT module */
//    PWTConfig.bClockPrescaler     = PWT_CLK_PRESCALER_128;    /*PWT clock source prescaler is 128 */
//    PWTConfig.bEdgeSensitivity    = FALLING_START_CAPTURE_ALL; /*start to measure pulse from first falling-edge and all edge */
//    PWTConfig.bPinSelect          = PWT_PINSEL_PTD5;          /*PWT input clock pin is PTD5 */
//    PWTConfig.bClockSource        = PWT_PCLKS_BUS;            /*PWT clock source is bus clock */
//    PWT_SetCallback(PWT_Task);
//    PWT_Init(&PWTConfig);

//    /*inital PTD0 near PWT_IN0 input(PTD5) on board*/
//    CONFIG_PIN_AS_GPIO(PTD,PTD0,OUTPUT); /* Configure pin PTD0 as an output to connect to PTD5 */
//    CONFIG_PIN_AS_GPIO(PTE,PTE7,OUTPUT); /* Configure BLUE LED at PTE7 as an output */
//}



/*超声模块初始化*/
void Echo_Init(void)
{
	CONFIG_PIN_AS_GPIO(PTE, PTE0, OUTPUT);
	OUTPUT_CLEAR(PTE, PTE0);
	
	CONFIG_PIN_AS_GPIO(PTE, PTE1, INPUT);
	ENABLE_INPUT(PTE, PTE1);
};

/*蜂鸣器初始化*/
void Beep_Init(void)
{
	CONFIG_PIN_AS_GPIO(PTI, PTI5, OUTPUT);
	OUTPUT_SET(PTI, PTI5);
}
/*干簧管初始化*/
void ghg_Init(void)
{
	irq_init();
	set_irq_priority(IRQ_IRQn,1);					//设置优先级,根据自己的需求设置 可设置范围为 0 - 3
	enable_irq(IRQ_IRQn);							//打开pit0的中断开关
	EnableInterrupts;								//打开总的中断开关  
}


/*拨码开关初始化*/
void Coding_Init(void){
	CONFIG_PIN_AS_GPIO(PTD, PTD5, INPUT);
	ENABLE_INPUT(PTD, PTD5);
	CONFIG_PIN_AS_GPIO(PTD, PTD6, INPUT);
	ENABLE_INPUT(PTD, PTD6);
	CONFIG_PIN_AS_GPIO(PTD, PTD7, INPUT);
	ENABLE_INPUT(PTD, PTD7);
	CONFIG_PIN_AS_GPIO(PTC, PTC3, INPUT);
	ENABLE_INPUT(PTC, PTC3);
	CONFIG_PIN_AS_GPIO(PTB, PTB4, INPUT);
	ENABLE_INPUT(PTB, PTB4);
}