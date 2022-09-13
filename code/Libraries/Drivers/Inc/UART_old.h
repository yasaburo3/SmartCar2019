/*
 * UART.h
 *
 *  Created on: Dec 18, 2013
 *      Author: B46911
 */

#ifndef UART_H_
#define UART_H_
/*******************************************************************************
* Includes
********************************************************************************/
#include "derivative.h"


/*******************************************************************************
* Constants
********************************************************************************/


/*******************************************************************************
* Macros
********************************************************************************/

                
/*******************************************************************************
* Types
********************************************************************************/


/*******************************************************************************
* Variables
********************************************************************************/


/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/

/***********************************************************************************************
*
* @brief    UART_Init - Initalizes the Uart 1 to run at 9600 bauds assuming bus clock of 20Mhz
* @param    none
* @return   none
*
************************************************************************************************/  
void UART_Init(void);


/***********************************************************************************************
*
* @brief    UART_SendChar - Send a single byte on Uart1
* @param    byte to send
* @return   none
*
************************************************************************************************/  
void UART_SendChar(uint8_t send);

/***********************************************************************************************
*
* @brief    UART_GetChar - Retrieve the received char from the Uart1 buffer (should be called from Interrupt)
* @param    none
* @return   received byte
*
************************************************************************************************/
uint8_t UART_GetChar(void);

/***********************************************************************************************
*
* @brief    UART_SendStr - Print the String on Terminal Window
* @param    String to be sent
* @return   none
*
************************************************************************************************/
void UART_SendStr(char data_string[]);
void UART_Sendshu(int data);
#endif /* UART_H_ */