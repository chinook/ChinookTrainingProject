//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project - Lesson 4 - Solution
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File     : main.c
// Author   : Frederic Chasse
// Date     : 2016-05-13
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose  : This is the main C file of the training project for the
//            developpers of Chinook. It uses ChinookLib, which is another
//            repository on Github.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Lesson   : The goal of this lesson is to familiarize the user with the
//            use of interrupts for the different communication protocols used
//            in the Chinook projects. In the case of this lesson, the UART
//            interrupts will be used.
//
//            In this fourth lesson, you must echo 8 times any character sent
//            from a terminal console on a computer. For example, if the 
//            character received is 'a', then you must send back the string
//            "aaaaaaaa\n\r". You must use the receive and transmit interrupt
//            functions, as described in the documentation of ChinookLib.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Hints    : You must look in the documentation of the Chipkit MAX32, available
//            online or in the folder of this project, to find which I/Os to
//            use for the LEDs and the UART channel.
//
//            You must configure the UART and its interrupt settings.
//            Put your initialization functions between the lines:
//
//                INTDisableInterrupts();
//            and
//                INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
//                INTEnableInterrupts();
//
//            The priority of the interrupt is already defined in the file
//            "Interrupts.h". The FIFO mode of the UART must be:
//              UartFifoMode_t oFifoMode = UART_INTERRUPT_ON_TX_BUFFER_EMPTY 
//                                       | UART_INTERRUPT_ON_RX_NOT_EMPTY
//                                       ;
//            Also note that the RX interrupts must first be ENABLED and that 
//            the TX interrupt must first be DISABLED.
//
//            Note that the interrupt routine is already written. You only need
//            to use the necessary functions as defined in ChinookLib.
//              
//            The functions needed for this lesson are in the libraries "Uart"
//            and "Port" of ChinookLib. To view the different functions
//            available, type "Uart." or "Port." and a description with
//            examples of all functions will appear on screen.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Solution : The solution of this lesson is in the branch 
//            "ChipkitMax32Lesson4Solution" of the repository 
//            "ChinookTrainingProject".
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes    : For ChinookLib to be useable, it must be cloned on your hard
//            drive so the path
//                "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//            references an existing file.
//
//            Depending on the microcontroller used, the project settings must
//            be set accordingly. For the Chipkit MAX32 development board, the
//            uC used is a PIC32MX795F512L.
//
//            To set the correct setting, you must 
//            -> right-click on your project name
//            -> Properties
//            -> Device: PIC32MX795F512L
//
//            The settings of ChinookLib and your project must match.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#include "..\headers\Setup.h"
#include "..\headers\Interrupts.h"
#include "..\headers\HardwareProfile.h"


//==============================================================================
// FUNCTION PROTOTYPES
//==============================================================================


//==============================================================================
// VARIABLE DECLARATIONS
//==============================================================================


//==============================================================================
// MAIN CODE
//==============================================================================
void main(void)
{

//==============================================================================
// Following memcopies are used to be able to use the form 
// Chinook.LibraryX.FunctionX in case the developper wants to see the available
// functions.
// IMPORTANT NOTE : the variables structures (example : Adc.Var...) WON'T be
//                  updated. Only use Chinook.Lib.Function format for the
//                  functions.
//==============================================================================
  memcpy( &Chinook.Port  , &Port  , sizeof ( struct sChinookPort  ) );
  memcpy( &Chinook.Uart  , &Uart  , sizeof ( struct sChinookUart  ) );
  memcpy( &Chinook.Pwm   , &Pwm   , sizeof ( struct sChinookPwm   ) );
  memcpy( &Chinook.Timer , &Timer , sizeof ( struct sChinookTimer ) );
  memcpy( &Chinook.Spi   , &Port  , sizeof ( struct sChinookSpi   ) );
  memcpy( &Chinook.Wdt   , &Wdt   , sizeof ( struct sChinookWdt   ) );
  memcpy( &Chinook.Adc   , &Adc   , sizeof ( struct sChinookAdc   ) );
  memcpy( &Chinook.Can   , &Can   , sizeof ( struct sChinookCan   ) );
  memcpy( &Chinook.I2c   , &I2c   , sizeof ( struct sChinookI2c   ) );
  memcpy( &Chinook.Skadi , &Skadi , sizeof ( struct sChinookSkadi ) );
  memcpy( &Chinook.InputCapture , &InputCapture , sizeof ( struct sChinookInputCapture ) );
//==============================================================================


//==============================================================================
// The next line disables the JTAG for the PIC. If the JTAG is enabled, pins
// RB10-13 can't be used as I/Os. If you want to use the JTAG, comment or
// remove this line.
//==============================================================================
  DDPCONbits.JTAGEN = 0;
//==============================================================================


//==============================================================================
// Configure the device for maximum performance but do not change the PBDIV
// Given the options, this function will change the flash wait states, RAM
// wait state and enable prefetch cache but will not change the PBDIV.
// The PBDIV value is already set via the pragma FPBDIV option in HardwareProfile.h.
//==============================================================================
  SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
//==============================================================================
  
  
//==============================================================================
// USER CODE STARTS HERE
//==============================================================================
  
  INTDisableInterrupts();   // Disable all interrupts of the system. Put your initialization
                            // functions after this line.
  
  Port.F.SetPinsDigitalOut(BIT_8);    // U1TX
  Port.F.SetPinsDigitalIn (BIT_2);    // U1RX
  
  UartModule_t        uartModule    = UART1; 
  BaudRate_t          baudRate      = BAUD9600; 
  UartConfig_t        oConfig       = UART_ENABLE_PINS_TX_RX_ONLY;
  UartFifoMode_t      oFifoMode     = UART_INTERRUPT_ON_TX_BUFFER_EMPTY 
                                    | UART_INTERRUPT_ON_RX_NOT_EMPTY
                                    ;
  UartLineCtrlMode_t  oLineControl  = UART_DATA_SIZE_8_BITS 
                                    | UART_PARITY_NONE 
                                    | UART_STOP_BITS_1
                                    ;
  
  Uart.Open(uartModule, baudRate, oConfig, oFifoMode, oLineControl); 
  
  Uart.EnableRx(uartModule); 
  Uart.EnableTx(uartModule);
  
  Uart.ConfigInterrupt(UART1, UART1_INTERRUPT_PRIORITY, UART1_INTERRUPT_SUBPRIORITY);
  Uart.EnableRxInterrupts(UART1);
  Uart.DisableTxInterrupts(UART1);
  
  //============================================
  // Enable multi-vector interrupts
  // Do your initialization before these lines.
  //============================================
  INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
  INTEnableInterrupts();
  
  sUartLineBuffer_t buffer =  // UART buffer
  { 
    .buffer = {0} 
   ,.length =  0 
  }; 
  
  INT32 err        = 0;
  UINT8  i         = 0
        ,character = 0
        ;
  
	while(1)  //infinite loop
	{
    err = Uart.GetRxFifoBuffer(UART1, &buffer, FALSE);  // Look for received characters
    
    if (err < 0)  // Nothing received
    {
      err = 0;
    }
    else
    {
      if (buffer.length == 1) // If only a character was received
      {
        character = buffer.buffer[0];   // Put it in memory
        
        for (i = 1; i < 8; i++)         // Multiply it 8 times
        {
          buffer.buffer[i] = character;
          buffer.length++;
        }
        
        buffer.buffer[8] = '\n';        // Line feed
        buffer.buffer[9] = '\r';        // Carriage return
        buffer.length += 2;
        
        Uart.PutTxFifoBuffer(UART1, &buffer);   // Send data
      }
      else  // More than one character received
      {
        buffer.buffer[buffer.length] = '\n';    // Line feed
        buffer.length++;
        buffer.buffer[buffer.length] = '\r';    // Carriage return
        buffer.length++;
        
        Uart.PutTxFifoBuffer(UART1, &buffer);   // Send data
      }
    }
    
	}
} //END MAIN CODE