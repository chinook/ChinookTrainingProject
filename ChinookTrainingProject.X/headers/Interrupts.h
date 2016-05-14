//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Chinook Training Project
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// File    : Interrupts.h
// Author  : Frederic Chasse
// Date    : 2016-05-13
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Purpose : This file declares all interrupt subroutines used.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Notes   : All priorities must be set and verified by the developper. All
//           priorities and subpriorities used are there as example. Also, note
//           that interrupt can be defined as iplnauto, iplnsrs and iplnsoft,
//           where n can be from 0 to 7. 7 is the highest priority, while 1 is
//           the lowest. A priority of 0 will disable the interrupt.
//           Subpriorities can go from (lowest to highest) 0 to 3.
//           SRS mode uses the shadow registers, soft uses the software
//           registers and auto is an automatic assignment.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


#ifndef __INTERRUPT_H__
#define	__INTERRUPT_H__

#include "Setup.h"

//==============================================================================
// DEFINITIONS
//==============================================================================

/*
 *  ==========================================
 *            Table of interrupts
 *  ==========================================
 * 
 * +--------------------------------------------+
 * | Priority | Subpriority | Interrupt handler |
 * |----------+-------------+-------------------|
 * | 1        | 0           | TIMER1            |
 * | 1        | 1           | TIMER2            |
 * | 1        | 2           | TIMER3            |
 * | 1        | 3           | TIMER4            |
 * |----------+-------------+-------------------|
 * | 2        | 0           | TIMER5            |
 * | 2        | 1           |                   |
 * | 2        | 2           |                   |
 * | 2        | 3           |                   |
 * |----------+-------------+-------------------|
 * | 3        | 0           | UART1             |
 * | 3        | 1           |                   |
 * | 3        | 2           |                   |
 * | 3        | 3           |                   |
 * |----------+-------------+-------------------|
 * | 4        | 0           |                   |
 * | 4        | 1           |                   |
 * | 4        | 2           |                   |
 * | 4        | 3           |                   |
 * |----------+-------------+-------------------|
 * | 5        | 0           |                   |
 * | 5        | 1           |                   |
 * | 5        | 2           |                   |
 * | 5        | 3           |                   |
 * |----------+-------------+-------------------|
 * | 6        | 0           |                   |
 * | 6        | 1           |                   |
 * | 6        | 2           |                   |
 * | 6        | 3           |                   |
 * |----------+-------------+-------------------|
 * | 7        | 0           |                   |
 * | 7        | 1           |                   |
 * | 7        | 2           |                   |
 * | 7        | 3           |                   |
 * +----------+-------------+-------------------+
 * 
 */


//===============================================
// Timer interrupts priorities and subpriorities
//===============================================
#define TIMER1_INTERRUPT_PRIORITY       1
#define T1_INTERRUPT_PRIORITY           ipl1auto
#define TIMER2_INTERRUPT_PRIORITY       1
#define T2_INTERRUPT_PRIORITY           ipl1auto
#define TIMER3_INTERRUPT_PRIORITY       1
#define T3_INTERRUPT_PRIORITY           ipl1auto
#define TIMER4_INTERRUPT_PRIORITY       1
#define T4_INTERRUPT_PRIORITY           ipl1auto
#define TIMER5_INTERRUPT_PRIORITY       2
#define T5_INTERRUPT_PRIORITY           ipl2auto

#define TIMER1_INTERRUPT_SUBPRIORITY    0
#define TIMER2_INTERRUPT_SUBPRIORITY    1
#define TIMER3_INTERRUPT_SUBPRIORITY    2
#define TIMER4_INTERRUPT_SUBPRIORITY    3
#define TIMER5_INTERRUPT_SUBPRIORITY    0
//===============================================


//===============================================
// UART interrupts priorities and subpriorities
//===============================================
#define UART1_INTERRUPT_PRIORITY        3         // Used in ChinookLib function
#define U1_INTERRUPT_PRIORITY           ipl3auto  // Used in ISR

#define UART1_INTERRUPT_SUBPRIORITY     0         // Lowest subpriority
//===============================================


//===============================================
// SPI interrupts priorities and subpriorities
//===============================================


//===============================================


//===============================================
// ADC interrupts priorities and subpriorities
//===============================================


//===============================================


//===============================================
// Input Capture interrupts priorities and subpriorities
//===============================================


//===============================================


//===============================================
// CAN interrupts priorities and subpriorities
//===============================================


//===============================================


//===============================================
// I2C interrupts priorities and subpriorities
//===============================================


//===============================================


//==============================================================================
// VARIABLES
//==============================================================================


#endif	/* __INTERRUPT_H__ */

