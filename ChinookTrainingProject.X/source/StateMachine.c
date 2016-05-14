//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateMachine.c
// Author  : Frederic Chasse
// Date    : 2016-05-13
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the C file for the state machine of the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : State names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "..\headers\StateMachine.h"


//==============================================================================
//	VARIABLES
//==============================================================================
BOOL oSendData      = 0
    ,oLedToggleUart = 0
    ,oSendSwitchMsg = 0
    ,oSwitchLeds    = 0
    ;

extern volatile BOOL oLedToggle500Ms;

sUartLineBuffer_t uart1Data =  
{
  .buffer = {0}
 ,.length =  0
};

const UINT8 switchMsg[] = "\n\rLEDs behavior switch occured\n\r\0";


//==============================================================================
//	STATES OF STATE MACHINE
//==============================================================================

//===============================================================
// Name     : StateScheduler
// Purpose  : Decides which state is next depending on current
//            state and flags. Used as a function
//===============================================================
void StateScheduler(void)
{

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateInit
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  if (pState == &StateInit)
  {
    if (INIT_2_ACQ)
    {
      pState = &StateAcq;
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateAcq
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateAcq)
  {
    if (ACQ_2_LED_TOGGLE)
    {
      pState = &StateLedToggle;
    }
    else if (ACQ_2_SEND_DATA)
    {
      pState = &StateSendData;
    }
    else if (ACQ_2_ACQ)
    {
      pState = &StateAcq;
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateLedToggle
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateLedToggle)
  {
    if (LED_TOGGLE_2_ACQ)
    {
      pState = &StateAcq;
    }
    else if (LED_TOGGLE_2_SEND_DATA)
    {
      pState = &StateSendData;
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state == StateSendData
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else if (pState == &StateSendData)
  {
    if (SEND_DATA_2_LED_TOGGLE)
    {
      pState = &StateAcq;
    }
    else if (SEND_DATA_2_ACQ)
    {
      pState = &StateLedToggle;
    }
    else
    {
      pState = &StateError;   // Go to Error state by default
    }
  }

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Current state undetermined
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  else
  {
    pState = &StateError;   // Go to Error state by default
  }

}


//===============================================================
// Name     : StateInit
// Purpose  : Initialization of the system.
//===============================================================
void StateInit(void)
{

  INTDisableInterrupts();   // Disable all interrupts of the system.

  INIT_PORTS;
  INIT_TIMER;
  INIT_UART;
  START_INTERRUPTS;

}


//===============================================================
// Name     : StateAcq
// Purpose  : Check flags and UART RX buffer.
//===============================================================
void StateAcq(void)
{
  
  INT32 err = 0;
  
  if (Uart.Var.oIsRxDataAvailable[UART1])                 // Check if RX interrupt occured
  {
    err = Uart.GetRxFifoBuffer(UART1, &uart1Data, FALSE); // put received data in uart2Data
    if (err >= 0)                                         // If no error occured
    {
      oSendData = 1;
      oLedToggleUart = 1;      
      
      if (uart1Data.buffer[0] == 'A')
      {
        oSendSwitchMsg = 1;
        oSwitchLeds    = !oSwitchLeds;
      }
    }
  }

}


//===============================================================
// Name     : StateLedToggle
// Purpose  : Toggle a LED
//===============================================================
void StateLedToggle(void)
{
  if (oLedToggle500Ms)
  {
    oLedToggle500Ms = 0;
    
    if (oSwitchLeds)
    {
      LED5_TOGGLE;
    }
    else
    {
      LED4_TOGGLE;
    }
  }
  
  if (oLedToggleUart)
  {
    oLedToggleUart = 0;
    
    if (oSwitchLeds)
    {
      LED4_TOGGLE;
    }
    else
    {
      LED5_TOGGLE;
    }
  }
  
}


//===============================================================
// Name     : StateSendData
// Purpose  : Send data on UART1
//===============================================================
void StateSendData(void)
{
  oSendData = 0;
  
  if (oSendSwitchMsg)
  {
    oSendSwitchMsg = 0;
    memcpy(&uart1Data.buffer[uart1Data.length], &switchMsg[0], sizeof(switchMsg));
    uart1Data.length += sizeof(switchMsg);
  }
  
  Uart.PutTxFifoBuffer(UART1, &uart1Data);            // Put data received in TX FIFO buffer
}


//===============================================================
// Name     : StateError
// Purpose  : Error state
//===============================================================
void StateError(void)
{
  if (oLedToggle500Ms)
  {
    oLedToggle500Ms = 0;
    LED4_TOGGLE;
    LED5_TOGGLE;
  }
}