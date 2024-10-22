/*
 * LED_prog.c
 *
 * Created: 26/09/2024 11:03:56
 *  Author: Esraa Ali
 */ 

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"
 #include "LED_interface.h"
 #include "../../MCAL/DIO/DIO_interface.h"
 
 void LED_voidLedOn( u8 copy_u8Port,u8 copy_u8Pin){
	DIO_voidSetPinVal(copy_u8Port,copy_u8Pin,HIGH);
 }
 void LED_voidLedOff( u8 copy_u8Port,u8 copy_u8Pin){
	 	DIO_voidSetPinVal(copy_u8Port,copy_u8Pin,LOW);
 }
 void LED_voidLedToggle( u8 copy_u8Port,u8 copy_u8Pin){
	 DIO_voidTogglePinVal(copy_u8Port,copy_u8Pin);
 }