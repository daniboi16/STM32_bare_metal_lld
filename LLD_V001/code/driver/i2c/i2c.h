/**
 ****************************************************************************
 *
 *		@file		i2c.h
 *  	@author 	Daniel Joseph Alapat
 *  	@date 		08-02-2023
 *  	@brief		Driver functions for I2C communication
 *
 *****************************************************************************/

/* INCLUDES */
#include "essentials.h"

u16_t i2c_read_temp

/* PROTOTYPES */
void config_GPIOB_I2C(void);
void config_I2C(void);
void I2C_send_startbit(void);