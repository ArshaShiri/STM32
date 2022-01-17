/*
 * main.h
 *
 *  Created on: Jun 17, 2021
 *      Author: arsha
 */

#ifndef MAIN_H_
#define MAIN_H_


// We allocate 1kb of stack to each task and the scheduler itself(total of 5kb)
// The stack is given from the top address in descending order.
#define SIZE_TASK_STACK         1024U
#define SIZE_SCHEDULER_STACK    1024U

#define SRAM_START_ADDRESS      0x20000000U
#define SIZE_OF_SRAM            ( (128) * (1024) )
#define SRAM_END_ADDRESS        ( (SRAM_START_ADDRESS) + (SIZE_OF_SRAM) )

// Task's 1 stack starts from the end of the ram.
#define T1_STACK_START          SRAM_END_ADDRESS
#define T2_STACK_START          ( (T1_STACK_START) - (SIZE_TASK_STACK) )
#define T3_STACK_START          ( (T2_STACK_START) - (SIZE_TASK_STACK) )
#define T4_STACK_START          ( (T3_STACK_START) - (SIZE_TASK_STACK) )
#define T_IDLE_STACK_START      ( (T4_STACK_START) - (SIZE_TASK_STACK) )
#define SCHEDULER_STACK_START   ( (T_IDLE_STACK_START) - (SIZE_TASK_STACK) )

// We want an exception occurring in each millisecond which then triggers the context switch.
// This means, a clock of 1kHZ
#define TICK_HZ                 1000U

#define HSI_CLOCK               16000000U
#define SYSTICK_TIME_CLK        HSI_CLOCK
#define MAX_TASKS               5
#define DUMMY_XPSR              0x01000000U

#define TASK_READY_STATE        0x00
#define TASK_BLOCKED_STATE      0xFF

// Use PREMASK register.
#define INTERRUPT_DISABLE()     do{__asm volatile ("MOV R0,#0x1"); asm volatile("MSR PRIMASK,R0"); } while(0)
#define INTERRUPT_ENABLE()      do{__asm volatile ("MOV R0,#0x0"); asm volatile("MSR PRIMASK,R0"); } while(0)

#endif /* MAIN_H_ */
