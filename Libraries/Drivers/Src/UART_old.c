
/*
 * UART.c
 *
 *  Created on: Dec 18, 2013
 *      Author: B46911
 */
#include "UART.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/



/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/


/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/


/**********************************************************************************************
* Global functions
**********************************************************************************************/


/***********************************************************************************************
*
* @brief    UART_Init - Initalize the UART2 to run at 9600 bauds assuming bus clock of 20Mhz
* @param    none
* @return   none
*
************************************************************************************************/  
void UART_Init()
{
	SIM_SCGC |=  SIM_SCGC_UART1_MASK;		/* Enable bus clock in UART2*/
	SIM->PINSEL1 |= 0x2000u;
	UART1_BDH = 0;							/* One stop bit*/
	UART1_BDL = 13;						/* Baud rate at 115200*/
	UART1_C1  = 0;							/* No parity enable,8 bit format*/
	UART1_C2 = 0;
	UART1_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	UART1_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	//UART1_C2 |= UART_C2_RIE_MASK;			/* Enable Receiver interrupts*/
	
	
}


/***********************************************************************************************
*
* @brief    UART_SendChar - Send a single byte on UART2
* @param    byte to send
* @return   none
*
************************************************************************************************/  
void UART_SendChar(uint8_t send)
{
	while((UART1_S1 & UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/
	(void)UART1_S1;								/* Read UART2_S1 register*/
	UART1_D=send;								/* Send data*/
}

/***********************************************************************************************
*
* @brief    UART_GetChar - Retrieve the received char from the UART2 buffer (should be called from Interrupt)
* @param    none
* @return   received byte
*
************************************************************************************************/  
uint8_t UART_GetChar()
{
	
	uint8_t recieve;
	while(( UART1_S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/
	(void) UART1_S1;								/* Read UART2_S1 register*/
	recieve= UART1_D;								/* Read received data*/
	return recieve;

} 

/***********************************************************************************************
*
* @brief    UART_SendStr - Print the String on Terminal Window
* @param    String to be sent
* @return   none
*
************************************************************************************************/
void UART_SendStr(char data_string[])
{
	int i=0;
	while(data_string[i] != '\0')
	{
		UART_SendChar(data_string[i]);
		i++;
	}

}

void UART_Sendshu(int32_t data)
{
	int i=0;
	int j=0;
	char a[7];
	
	if(data<0)
	{
		j=1;
		data=-data;
	}
	
	while(data!=0)
	{
		a[i]=((uint32_t)data%10+'0');
		data=data/10;
		i++;
	}
	if(j==1)
	{
		a[i]='-';
		i++;
	}
	while(i!=0)
	{	
	 i--;
	 UART_SendChar(a[i]);
	}
   UART_SendChar(' ');
}
