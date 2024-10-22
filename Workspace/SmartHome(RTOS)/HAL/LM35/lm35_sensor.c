/******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../LIB/STD_TYPE.h"


/*
 * Description : Function responsible for calculate the temperature from the ADC digital value.
 * Argument    : None
 * Return      : Temperature value
 */
u8 LM35_getTemperature(void)
{
	u8 temp_value = 0;

	u16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_u16ReadChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (u8)(((u32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

