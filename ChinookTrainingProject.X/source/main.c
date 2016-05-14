//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project - Lesson 5
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
//            state machines used in all the projects done in Chinook.
//
//            In this fifth lesson, you must implement a state machine that has
//            the following states:
//              Initialization state: Initialize all needed peripherals and I/Os
//              Acquisition/Idle state: Check the flags and the UART buffer
//              LED toggle state: Toggle the LED(s)
//              Send data state: Send UART messages when needed
//
//            The State machine must act as follows:
//              Both LEDs are initially OFF
//              LED4 toggles at every 500 ms using the TIMER1 interrupt
//              LED5 toggles when a character is received on UART1
//              All received characters must be echoed back
//              If the character 'A' is received, both LEDs switch behavior,
//                i.e. LED5 toggles every 500 ms using TIMER1 and LED4 toggles 
//                everytime a character is received. When another character 'A'
//                is received, the LEDs behavior switch again.
//                Moreover, the string "LEDs behavior switch occured\n\r" must
//                be sent when this occurs.
//
//            All UART msgs must be sent in the "Send Data" state.
//            All the LED toggling must occur in the "LED Toggle" state.
//            All the UART reads must be performed in the "Acquisition" state.
//
//            The states change using a State Scheduler, of which a template is
//            already available in "StateMachine.c".
//
//            All "Enable Interrupt" functions must be done in the function
//            "StartInterrupts" located in "Setup.c".
//
//            ABSOLUTELY NO CODE must be added to "main.c".
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Hints    : You must look in the documentation of the Chipkit MAX32, available
//            online or in the folder of this project, to find which I/Os to
//            use for the LEDs and the UART channel.
//              
//            The functions needed for this lesson are in the libraries "Uart",
//            "Timer" and "Port" of ChinookLib. To view the different functions
//            available, type "Uart.", "Timer" or "Port." and a description with
//            examples of all functions will appear on screen.
//
//            The interrupts and their priorities are already defined in 
//            "Interrupts.c" and "Interrupts.h".
//
//            A template of the state machine is available in "StateMachine.c".
//
//            
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Solution : The solution of this lesson is in the branch 
//            "ChipkitMax32Lesson5Solution" of the repository 
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
#include "..\headers\StateMachine.h"
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

  
// State machine init
//=================================================================
  pState = &StateInit;  // First state is StateInit
//=================================================================
  
	while(1)  //infinite loop
	{
    
  // State machine entry & exit point
  //===========================================================
		(*pState)();          // jump to next state
  //===========================================================

  // State scheduler
  //===========================================================
    StateScheduler();     // Decides which state will be next
	//===========================================================
    
	}
} //END MAIN CODE