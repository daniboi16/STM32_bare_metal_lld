/**
 ****************************************************************************
 *
 *		@file		i2c.c
 *  	@author 	Daniel Joseph Alapat
 *  	@date 		08-02-2023
 *  	@brief		Driver functions for I2C communication
 *
 *****************************************************************************/
#include "i2c.h"

 /**
 * @brief   to configure the GPIO pins PB6 and PB7, SDA - PB7, SCL - PB6
 * @param   void
 * @return	void
 */
void config_GPIOB_I2C(void){
	RCC -> AHB1ENR |= (0x1<<1);				    //Enable clock for port B
	GPIOB -> MODER |= (0x2<<(6*2));			    //PB6 to alternate function pin "10"
	GPIOB -> MODER |= (0x2<<(7*2));			    //PB7 to alternate function pin "10"
	GPIOB -> PUPDR |= (0x5<<(6*2));			    //Set PB6 and PB7 as pull up pins "01"
	GPIOB -> OTYPER |= (0x3<<6);			    //Set PB6 and PB7 as open drain "1"
	GPIOB -> OSPEEDR |= (0xA<<(6*2));		    //Set PB6 and PB7 as high speed "10"
	GPIOB -> AFR[0] |= (0x44<<(6*4));		    //Set PB6 and PB7 to alternate function 4 "0100"
}

 /**
 * @brief   To configure the I2C registers
 * @param   void
 * @return	void
 */
void config_I2C(void){
	RCC -> APB1ENR |=(1<<21);				    //Enable I2C clock
	I2C1 -> CR1 |= (1<<15);					    //Reset I2C
	I2C1 -> CR1 &= ~(1<<15);				    //Set I2C
	I2C1 -> CR2 |=(16<<0);					    //Set peripheral clock at 16MHz
	I2C1 -> OAR1 |=(1<<14);					    //Should be set high
	I2C1 -> CCR |=(0x50<<0);				    //Set SCL as 100KHz
	I2C1 -> TRISE |=(17<<0);				    //Configure maximum rise time
	I2C1 -> CR1 |= (1<<0);					    //Enable I2C
}

 /**
 * @brief   To send the I2C start bit
 * @param   void
 * @return	void
 */
void I2C_send_startbit(void){ 
	I2C1 -> CR1 |= (1<<10);					    //Enable the ACK Bit
	I2C1 -> CR1 |= (1<<8);					    //Send the start bit
	while (!(I2C1->SR1 & (1<<0)));			    //Wait for SB bit to set
}

 /**
 * @brief   To send the I2C address
 * @param   i2c_address I2C address of the slave
 * @return	void
 */
void I2C_send_address(u8_t i2c_address){
	I2C1 -> DR = I2C_address;  				    //Send the slave address
	while (!(I2C1->SR1 & (1<<1))); 			    //Wait for ADDR bit to set
	i2c_read_temp = ((I2C1->SR1) | (I2C1->SR2));//Read SR1 and SR2 to clear the ADDR bit
}

 /**
 * @brief   To send data to the I2C device
 * @param   i2c_data I2C data to be sent
 * @return	void
 */
void I2C_send(u8_t i2c_data){
	while (!(I2C1->SR1 & (1<<7)));				//Wait till TX buffer is empty
	I2C1 -> DR = i2c_data;						//Write data to I2C slave
	while (!(I2C1->SR1 & (1<<2)));				//Wait till Byte transfer is completed
}

 /**
 * @brief   To send the I2C stop bit
 * @param   void
 * @return	void
 */
void I2C_stop(void){
	I2C1 -> CR1 |= (1<<9);  					//Send the stop bit
}