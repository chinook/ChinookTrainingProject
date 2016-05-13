//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project - Lesson 3
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
//            principles of interrupts and variable sharing between files.
//
//            In this third lesson, you must toggle LED4 and LED5 of the MAX32
//            at different rates using the timer interrupts. Flags from the file
//            "Interrupts.c" must be used to toggle the LEDs in the infinite 
//            loop of "main.c".
//
//            LED4 must toggle at a rate of 200 ms, whereas LED5 must toggle at
//            a rate of 500 ms.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Hints    : You must look in the documentation of the Chipkit MAX32, available
//            online or in the folder of this project, to find which I/Os to
//            use for the LEDs.
//
//            You must configure the Timers 1 and 2 and their interrupt settings.
//            Put your initialization functions between the lines:
//
//                INTDisableInterrupts();
//            and
//                INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
//                INTEnableInterrupts();
//
//            The priorities of the interrupts are already defined in the file
//            "Interrupts.h".
//              
//
//            The functions needed for this lesson are in the libraries "Timer"
//            and "Port" of ChinookLib. To view the different functions
//            available, type "Timer." or "Port." and a description with
//            examples of all functions will appear on screen.
//
//            The keyword "extern" is used when a file needs to access a variable
//            that was defined in another file. Ex: extern BOOL oToggleLed4;
//
//            The keyword "volatile" is used to declare a variable that is shared
//            between interrupts and normal functions.
//
//            DO NOT USE THE FILES "StateMachine.c/.h".
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Solution : The solution of this lesson is in the branch 
//            "ChipkitMax32Lesson3Solution" of the repository 
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
  
  
  /* User code */
  
  
  //============================================
  // Enable multi-vector interrupts
  // Do your initialization before these lines.
  //============================================
  INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
  INTEnableInterrupts();
  
  
	while(1)  //infinite loop
	{
    
	}
} //END MAIN CODE