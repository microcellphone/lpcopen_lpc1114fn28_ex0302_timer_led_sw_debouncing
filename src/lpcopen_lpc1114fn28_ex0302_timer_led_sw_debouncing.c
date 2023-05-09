/*
===============================================================================
 Name        : lpcopen_lpc1114fn28_ex03_timer_led_sw.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "led.h"
#include "sw.h"
#include "sw_debouncing.h"

// TODO: insert other definitions and declarations here
#define TICKRATE_HZ (100)

void TIMER16_0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, TIMER0)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, TIMER0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, TIMER1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, TIMER1);

		Update_SW_State();
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, TIMER2)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, TIMER2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, TIMER3)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, TIMER3);
	}
}

void TIMER16_1_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, TIMER0)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, TIMER0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, TIMER1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, TIMER1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, TIMER2)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, TIMER2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, TIMER3)) {
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, TIMER3);
	}
}

void TIMER32_0_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, TIMER0)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, TIMER0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, TIMER1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, TIMER1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, TIMER2)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, TIMER2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, TIMER3)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, TIMER3);
	}
}

void TIMER32_1_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, TIMER0)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, TIMER0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, TIMER1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, TIMER1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, TIMER2)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, TIMER2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, TIMER3)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, TIMER3);
	}
}


int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    sw_status_t sw_status;
    bool led1_state,led2_state,led3_state,led4_state;

    IOCON_Config_Request();
    LED1_Config_Request();
    LED2_Config_Request();
    LED3_Config_Request();
    LED4_Config_Request();
    SW1_Config_Request();
    SW2_Config_Request();
    SW3_Config_Request();
    SW4_Config_Request();
    SW_Debouncing_Request();
    TIMER_Config_Request(LPC_TIMER16_0, TIMER1, TICKRATE_HZ);

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	sw_status = Read_SW_Status(SW1);
    	if(sw_status == ON){
    		led1_state ^= 1;
    		LED_Set_Request(LED1, led1_state);
    	}
    	sw_status = Read_SW_Status(SW2);
    	if(sw_status == ON){
    		led2_state ^= 1;
    		LED_Set_Request(LED2, led2_state);
    	}
    	sw_status = Read_SW_Status(SW3);
    	if(sw_status == ON){
    		led3_state ^= 1;
    		LED_Set_Request(LED3, led3_state);
    	}
    	sw_status = Read_SW_Status(SW4);
    	if(sw_status == ON){
    		led4_state ^= 1;
    		LED_Set_Request(LED4, led4_state);
    	}
		  i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
