//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project - Lesson 2
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
// Lesson   : The goal of this lesson is to familiarize the user with simple
//            use of ChinookLib and to help understand the interface between
//            software and hardware.
//
//            In this second lesson, you must communicate with your
//            microcontroller using the UART protocol via a USB interface.
//
//            Your program must echo what you send to it, meaning that any 
//            character received on the UART channel must be sent back. You will
//            know that your program is working when you see what you type in
//            your terminal
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Hints    : You must look in the documentation of the Chipkit MAX32, available
//            online or in the folder of this project, to find which UART
//            channel to use. You also need to look in the PIC32 family
//            datasheet to know which ports to set.
//
//            You must init the right UART channel to be able to use it and set
//            the I/O ports as inputs and/or ouputs.
//            
//            You need a serial interface software. A good one is Tera Term,
//            which you can download here:
//                https://en.osdn.jp/projects/ttssh2/releases/
//
//            The functions needed for this lesson are in the libraries "Uart"
//            and "Port" of ChinookLib. To view the different functions
//            available, type "Uart." or "Port." and a description with
//            examples of all functions will appear on screen.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Solution : The solution of this lesson is in the branch 
//            "ChipkitMax32Leson2Solution" of the repository 
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
  
  
	while(1)  //infinite loop
	{
    
	}
} //END MAIN CODE