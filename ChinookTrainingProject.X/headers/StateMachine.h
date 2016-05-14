//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : StateMachine.h
// Author  : Frederic Chasse
// Date    : 2016-05-13
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This is the header file for the state machine of the system.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : State names can and should be renamed by the user to improve the
//           readability of the code.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __STATE_MACHINE_H__
#define	__STATE_MACHINE_H__

#include "Setup.h"


//==============================================================================
// State Machine public function prototypes
//==============================================================================
void StateInit      (void);   // Initialization state of the system
void StateAcq       (void);   // First state. User can rename it as needed
void State2         (void);   // Second state. User can rename it as needed
void StateError     (void);   // Error state. User should assess and corret errors in this state
void StateScheduler (void);   // State Scheduler. Decides which state is next
                              // depending on current state and flags. Used as a function


//==============================================================================
// Macro definitions
//==============================================================================

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// State scheduler flags
// The state scheduler is at the end of each state and
// decides which state is next. Following flags
// are used in this decision. The names used can and
// should be renamed to improve readability. Also, the
// conditions tested in the defines should be changed
// to proper tests
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define INIT_2_ACQ     1               // StateInit to StateAcq
#define INIT_2_ERROR   dummyVariable   // StateInit to StateError
#define INIT_2_TWO    !dummyVariable   // StateInit to State2

#define ACQ_2_TWO     !dummyVariable   // StateAcq to State2
#define ACQ_2_ACQ      dummyVariable   // StateAcq to StateAcq
#define ACQ_2_ERROR   !dummyVariable   // StateAcq to StateError

#define TWO_2_ACQ      dummyVariable   // State2 to StateAcq
#define TWO_2_TWO     !dummyVariable   // State2 to State2
#define TWO_2_ERROR    dummyVariable   // State2 to StateError

#define ERROR_2_ACQ   !dummyVariable   // StateError to StateAcq
#define ERROR_2_TWO   !dummyVariable   // StateError to State2
#define ERROR_2_ERROR  dummyVariable   // StateError to StateError
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//==============================================================================
// Variable declarations
//==============================================================================
void (*pState)(void);       // State pointer, used to navigate between states

UINT8 dummyVariable;        // To change

#endif	/* __STATE_MACHINE_H__ */

