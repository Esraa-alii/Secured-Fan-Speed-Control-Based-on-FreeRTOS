/*
 * TaskHandeller.c
 *
 * Created: 12/10/2024 18:38:22
 *  Author: Esraa Ali
 */ 
#include "TaskHandler.h"
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LCD/LCD_config.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../FreeRtos/FreeRTOS.h"
#include "../FreeRtos/task.h"
#include "../FreeRtos/FreeRTOSConfig.h"
#include "../FreeRtos/semphr.h"
#include "../FreeRtos/queue.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/BUZZER/buzzer.h"
#define  F_CPU 16000000UL
#include <util/delay.h>


SemaphoreHandle_t lcdSemaphore;
QueueHandle_t passQueue;
QueueHandle_t tempQueue;
QueueHandle_t PassCheckQueue;
TaskHandle_t xLCDHandle = NULL;

/*********************************************************************/
void recievePassTask(){
	u8 recievedPass = 0;
	u8 actualPass = ACTUAL_PASS;
	u8 state = UNDEFINED_PASS;
	recievedPass = UART_u8RX();
	xQueueSend(passQueue,&recievedPass,100);
	LCD_voidSendCommand(1);
	while (1)
	{
		if(recievedPass == actualPass){
			LED_voidLedOn(DIO_PORTC,DIO_PIN0);
			state = CORRECT_PASS;
		}
		else{
			Buzzer_on();
			
			state = WRONG_PASS;
		}
		xQueueSend(PassCheckQueue,&state,100);
		vTaskDelay(600);

	}
}
/*********************************************************************/

/*********************************************************************/
void lcdPassTask(){
	u8 state = UNDEFINED_PASS;
	LCD_voidSendCommand(1);
	LCD_voidGotoxy(0,0);
	while (1)
	{
		xQueueReceive(PassCheckQueue, &state,100);
		if(state == CORRECT_PASS){
		LCD_voidSendString("welcome");}
		else if (state == WRONG_PASS){
			LCD_voidSendString("Wrong Pass!");
		}
		vTaskDelay(600);
	}
}
/*********************************************************************/

/*********************************************************************/
void GetTempTask(){
	u8 tempValue=0;
	while(1){
		tempValue = (ADC_u16ReadChannel(DIO_PIN0))/2;
		xQueueSend(tempQueue,&tempValue,100);
		vTaskDelay(600);
	}
}

/*********************************************************************/

/*********************************************************************/
void DisplayTempTask(){
	u8 tempValue = 0;
	u8 state = UNDEFINED_PASS;
	vTaskDelete(xLCDHandle);
	while(1){
		xQueueReceive(tempQueue,&tempValue,100);
		xQueueReceive(PassCheckQueue, &state,100);
		if(state == CORRECT_PASS){
			LCD_voidGotoxy(0,0);
			LCD_voidSendString("Welcome Back!!");
			LCD_voidGotoxy(0,1);
			LCD_voidSendString("Temp = ");
			LCD_voidSendNumber(tempValue);
			LCD_voidSendString("C");
		}
		else if( state == WRONG_PASS){
			LCD_voidGotoxy(0,0);
			LCD_voidSendString("Wrong pass!!");
		}
		vTaskDelay(600);
	}
}
/*********************************************************************/

/*********************************************************************/
void MotorControlTask(){
	u8 state = UNDEFINED_PASS;
	u8 tempValue=0;
	while (1)
	{
		xQueueReceive(PassCheckQueue, &state,100);
		xQueueReceive(tempQueue,&tempValue,100);
		if (state == CORRECT_PASS)
		{
			if (tempValue < 30)
			{
				TIMER0_voidFastPWM(MOTOR_MIN_SPEED);
			}
			
			if (tempValue >= 30 && tempValue <40)
			{
				TIMER0_voidFastPWM(MOTOR_MIDDLE_SPEED);
			}
			
			if (tempValue >= 50)
			{
				TIMER0_voidFastPWM(MOTOR_MAX_SPEED);
			}
		}
		
		vTaskDelay(600);
	}
}
/*********************************************************************/

/*********************************************************************/
void lcdInitTask() {
	while(1) {
		LCD_voidGotoxy(0, 0);
		LCD_voidSendString("Enter Your Pass");
		vTaskDelay(500);
	}
}
/*********************************************************************/

/*********************************************************************/
void TaskRunner(void){
	DIO_voidSetPortDir(DIO_PORTA,0XFF);
	DIO_voidSetPinDir(DIO_PORTA,DIO_PIN0,INPUT);//ADC
	DIO_voidSetPinDir(DIO_PORTD,DIO_PIN0,INPUT);//LED
	DIO_voidSetPinDir(DIO_PORTB,DIO_PIN3,OUTPUT);//MOTOER
	DIO_voidSetPinDir(DIO_PORTC,DIO_PIN0,OUTPUT);//RX
	
	LCD_voidInit();
	ADC_voidInit();
	UART_voidInit();
	Buzzer_init();
	
	xTaskCreate(lcdInitTask,"LCD Initialization ",80,NULL,PRIORITY_5,&xLCDHandle);
	xTaskCreate(recievePassTask,"Pass Received and compared with the true pass",80,NULL,PRIORITY_4,NULL);
	xTaskCreate(GetTempTask,"Measure temp",80,NULL,PRIORITY_3,NULL);
	xTaskCreate(DisplayTempTask,"Display temp value ",80,NULL,PRIORITY_3,NULL);
	xTaskCreate(MotorControlTask,"Motor control based on temp value",80,NULL,PRIORITY_1,NULL);
	
	passQueue = xQueueCreate(SINGLE_VAR,sizeof(u8));
	tempQueue = xQueueCreate(SINGLE_VAR,sizeof(u8));
	PassCheckQueue = xQueueCreate(SINGLE_VAR,sizeof(u8));
	
	vTaskStartScheduler();
}

/*********************************************************************/