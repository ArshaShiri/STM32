/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#include "main.h"
#include "led.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

uint32_t global_tick_count = 0;
uint8_t current_task = 1; // task 1 is running

// Task control block.
typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	void(*task_handler)(void);
}TCB_T;

TCB_T user_tasks[MAX_TASKS];

void idle_task(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void init_tasks_control_block();
void schedule(void);

void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start);
void init_tasks_stack(void);
void enable_processor_faults(void);
__attribute ((naked)) void switch_sp_to_psp(void);

void task_delay(uint32_t tick_count);

// Semihosting init function.
extern void initialise_monitor_handles();

int main(void)
{
	enable_processor_faults();
	init_scheduler_stack(SCHEDULER_STACK_START);

    init_tasks_control_block();

	initialise_monitor_handles();

	printf("Implementation of simple task scheduler\n");

	init_tasks_stack();

	led_init_all();

	init_systick_timer(TICK_HZ);

	switch_sp_to_psp();
	task1_handler();

	for(;;);
}

void idle_task(void)
{
	while(1)
	{
		//printf("Idle!!!\n");
	}
}

void task1_handler(void)
{
	while (1)
	{
		printf("Task 1 is executing.\n");
		led_on(LED_GREEN);
		task_delay(TICK_HZ);
		led_off(LED_GREEN);
		task_delay(TICK_HZ);
	}
}

void task2_handler(void)
{
	while (1)
	{
		printf("Task 2 is executing.\n");
		led_on(LED_ORANGE);
		task_delay(TICK_HZ / 2);
		led_off(LED_ORANGE);
		task_delay(TICK_HZ / 2);
	}
}

void task3_handler(void)
{
	while (1)
	{
		printf("Task 3 is executing.\n");
		led_on(LED_BLUE);
		task_delay(TICK_HZ / 4);
		led_off(LED_BLUE);
		task_delay(TICK_HZ / 4);
	}
}

void task4_handler(void)
{
	while (1)
	{
		printf("Task 4 is executing.\n");
		led_on(LED_RED);
		task_delay(TICK_HZ / 8);
		led_off(LED_RED);
		task_delay(TICK_HZ / 8);
	}
}

void init_tasks_control_block()
{
	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[4].current_state = TASK_READY_STATE;

	user_tasks[0].psp_value = T_IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;

	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;
}

void init_systick_timer(uint32_t tick_hz)
{
	uint32_t count_value = SYSTICK_TIME_CLK / tick_hz - 1;

	// SVR
	uint32_t *p_sys_tick_reload_vlue_register = (uint32_t *) 0xE000E014;

	// SCSR
	uint32_t *p_sys_tick_control_and_status_register = (uint32_t *) 0xE000E010;


	// Clear the value of SVR register (only 24 bits are valid)
	*p_sys_tick_reload_vlue_register &= ~(0x00FFFFFFFF);


	// Load the value in SVR register.
	*p_sys_tick_reload_vlue_register |= count_value;

	// Do some settings

	// Enable systik exception request.
	*p_sys_tick_control_and_status_register |= (1 << 1);

	// Indicates the clock source, processor clock source.
	*p_sys_tick_control_and_status_register |= (1 << 2);

	// Enables the counter.
	*p_sys_tick_control_and_status_register |= 1;

	// The three operations above are equivalent to *p_sys_tick_control_and_status_register |= 7;

	// Enable the systick
}

// We want to change the value of the MSP register. This is a special register that can only be modified by assembly code.
__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start)
{
	__asm volatile("MSR MSP, %0": : "r" (scheduler_stack_start) :);
	// Or (Arg 1 of the function (scheduler_stack_start) is stored in R0 based on the documentation.)
	// __asm volatile("MSR MSP,R0");

	// Return to main. (LR has the return address)
	__asm volatile("Bx LR");
}

void init_tasks_stack(void)
{
	uint32_t *pPSP;

	for (int i = 0; i < MAX_TASKS; ++i)
	{
		pPSP = (uint32_t *)user_tasks[i].psp_value;

		// Start initializing the stack:
		// This is done based on the design of the stacks and what register values should be pushed.
		pPSP--;
		*pPSP =  DUMMY_XPSR; // 0x01000000

		pPSP--;
		*pPSP =  (uint32_t)user_tasks[i].task_handler; // pc

		pPSP--;
		*pPSP =  0xFFFFFFFD; // LR Return mode: return to the return address and use psp as the stack pointer.

		int number_of_other_registers = 13;
		for (int j = 0; j < number_of_other_registers; ++j)
		{
			pPSP--;
			*pPSP =  0;
		}

		// Store the value of psp
		user_tasks[i].psp_value = (uint32_t)pPSP;
	}
}

void enable_processor_faults(void)
{
	//1. enable all configurable exceptions : usage fault, mem manage fault and bus fault

	uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

	*pSHCSR |= ( 1 << 16); //mem manage
	*pSHCSR |= ( 1 << 17); //bus fault
	*pSHCSR |= ( 1 << 18); //usage fault
}

uint32_t get_psp_value(void)
{
	return user_tasks[current_task].psp_value;
}

void save_psp_value(uint32_t psp_value)
{
	user_tasks[current_task].psp_value = psp_value;
}

void update_next_task(void)
{
	int state = TASK_BLOCKED_STATE;

	for(int i= 0 ; i < (MAX_TASKS) ; i++)
	{
		current_task++;
	    current_task %= MAX_TASKS;
		state = user_tasks[current_task].current_state;
		if( (state == TASK_READY_STATE) && (current_task != 0) )
			break;
	}

	if(state != TASK_READY_STATE)
		current_task = 0;
}

__attribute ((naked)) void switch_sp_to_psp(void)
{
	// Initialize psp with task 1 stack start.

	// Get the psp value of the current task.
	// BL branch and link (come back to this function)
	// The return value is stored in R0
	// The LR receives the return address from PC when a Branch and Link (BL) or Branch and Link with Exchange (BLX) instruction is executed.
	__asm volatile ("PUSH {LR}"); // Push the return value to main since after calling get_psp_value, LR is going to be corrupted.
	__asm volatile ("BL get_psp_value");
	__asm volatile ("MSR PSP,R0"); // Initialize psp
	__asm volatile ("POP {LR}");

	// Change sp to psp using control registers.
	// Set second bit of control register to 1
	__asm volatile ("MOV R0,#0X02");
	__asm volatile ("MSR CONTROL,R0");

	// Return to main. (LR has the return address)
	__asm volatile("Bx LR");
}

void unblock_tasks()
{
	// Skip the idle task.
	for (int i = 1; i < MAX_TASKS; ++i)
	{
      if(user_tasks[i].current_state != TASK_READY_STATE)
      {
    	  if(user_tasks[i].block_count == global_tick_count)
    	  {
    		  user_tasks[i].current_state = TASK_READY_STATE;
    	  }
      }
	}
}

void  SysTick_Handler(void)
{
	global_tick_count++;
	unblock_tasks();
	schedule();
}

__attribute__((naked)) void PendSV_Handler(void)
{

	// Save the context of the current task

	// 1. Get current running task's psp value.
	__asm volatile ("MRS R0,PSP");

	// 2. Using that PSP value store SF2(R4 to R11).
	// We cannot use push here cause the handler is using the msp as stack and we want to push the values
	// in the stack pointed by psp. Use STMDB instead, decrement first and store (like push!)
	// ! returns the last address back to R0
	__asm volatile ("STMDB R0!,{R4-R11}");

	__asm volatile ("PUSH {LR}");

	// 3. Save the current value of PSP.
	// R0 already has the first argument of save_psp_value
	__asm volatile ("BL save_psp_value");

	// Retrieve the next tasks

	// 1. Decide next task to run.
	__asm volatile ("BL update_next_task");

	// 2. Get its past psp value
	__asm volatile ("BL get_psp_value");

	// 3. Using that psp value retrieve SF2(R4 to R11).
	__asm volatile ("LDMIA R0!,{R4-R11}");

	// 4. Update psp and exit.
	__asm volatile ("MSR PSP,R0");

	__asm volatile ("POP {LR}");

	__asm volatile("BX LR");
}

void schedule(void)
{
	// Using interrupt control register.
	uint32_t *pICSR = (uint32_t*)0xE000ED04;

	//pend the pendsv exception
	*pICSR |= ( 1 << 28);
}

void task_delay(uint32_t tick_count)
{
	// Careful when accessing global variables in thread mode.
	// In this case, user_tasks is also accessed from handlers which can cause
	// race conditions.

	//disable interrupt
	INTERRUPT_DISABLE();

    if (current_task)
    {
    	user_tasks[current_task].block_count = global_tick_count + tick_count;
    	user_tasks[current_task].current_state = TASK_BLOCKED_STATE;
    	schedule();
    }

	//enable interrupt
	INTERRUPT_ENABLE();
}

//2. implement the fault handlers
void HardFault_Handler(void)
{
	printf("Exception : Hardfault\n");
	while(1);
}


void MemManage_Handler(void)
{
	printf("Exception : MemManage\n");
	while(1);
}

void BusFault_Handler(void)
{
	printf("Exception : BusFault\n");
	while(1);
}
