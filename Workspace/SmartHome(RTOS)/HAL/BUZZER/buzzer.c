/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: source file for the buzzer driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/
#include "buzzer.h"
#include "../../MCAL/DIO/DIO_interface.h"

/***************************************************
 * Description : Initialize the buzzer to be off
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_init(void){
	/* first set the 2 pin of the buzzer to be output
	 * then connect them to login low (GND) to be off */
	DIO_voidSetPinDir(BUZZER_portID,BUZZER_positive_PinID,OUTPUT);
	DIO_voidSetPinDir(BUZZER_portID,BUZZER_negative_PinID,OUTPUT);

	DIO_voidSetPinVal(BUZZER_portID,BUZZER_positive_PinID,LOW);
	DIO_voidSetPinVal(BUZZER_portID,BUZZER_negative_PinID,LOW);
}

/***************************************************
 * Description : Turn on the buzzer
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_on(void){
	/* connect the positive terminal to +ve and the negative terminal to ground */
	DIO_voidSetPinVal(BUZZER_portID,BUZZER_positive_PinID,HIGH);
	DIO_voidSetPinVal(BUZZER_portID,BUZZER_negative_PinID,LOW);
}

/***************************************************
 * Description : Turn on the buzzer
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_off(void){
	/* connect the positive terminal to -ve and the negative terminal to ground
	 * (open circuit) */
	DIO_voidSetPinVal(BUZZER_portID,BUZZER_positive_PinID,LOW);
	DIO_voidSetPinVal(BUZZER_portID,BUZZER_negative_PinID,LOW);
}
