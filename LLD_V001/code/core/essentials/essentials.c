/**
 ****************************************************************************
 *
 *		@file		essentials.c
 *  	@author 	Daniel Joseph Alapat
 *  	@date 		08-02-2023
 *  	@brief		Essential functions to be used through this project
 *
 *****************************************************************************/

#include "essentials.h"

 /**
 * @brief   Function for software delay
 * @param   Time in milli seconds
 * @return	void
 */
void msDelay(u32_t msTime){
	// "For loop" takes 4 clock cycles to get executed. Clock frequency is 16MHz
	// 16MHz/4=4MHz. If we want 1000ms (1second) delay, 4MHz/1000=4000, so we have to multiply by 4000 to get a delay of 1s
	for (u32_t i=0; i<(msTime*4000); i++){
	    __NOP();
	}
}