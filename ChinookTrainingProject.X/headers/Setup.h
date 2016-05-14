//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Setup.h
// Author  : Frederic Chasse
// Date    : 2016-05-13
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the setup header for the system. It contains function
//           prototypes as well as macros and the public structure of
//           ChinookLib functions.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : For ChinookLib to be useable, it must be cloned on your hard
//           drive so the path
//               "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"
//           references an existing file.
//
//           Function names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __SETUP_H__
#define	__SETUP_H__

//%%%%%%%%%%%%%%%%%%%%%%%%%
// ChinookLib files
//%%%%%%%%%%%%%%%%%%%%%%%%%
#include "..\..\..\ChinookLib\ChinookLib.X\headers\ChinookLib.h"

//==============================================================================
// ChinookLib functions
//==============================================================================
struct sChinook Chinook;            // Contains all ChinookLib functions


//==============================================================================
// State Machine public functions prototypes
//==============================================================================
void InitTimer        (void);
void InitPorts        (void);
void InitUart         (void);
void StartInterrupts  (void);


//==============================================================================
// Macro definitions
//==============================================================================
#define INIT_TIMER          InitTimer()
#define INIT_PORTS          InitPorts()
#define INIT_UART           InitUart()
#define START_INTERRUPTS    StartInterrupts()


//==============================================================================
// Variable definitions
//==============================================================================


#endif	/* __SETUP_H__ */