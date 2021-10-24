/*
 * ultrasonic.c
 *
 *  Created on: Oct 23, 2021
 *      Author: Kyrillos
 */


#include "ultrasonic.h"
#include "common_macros.h"

volatile Icu_ConfigType g_Ultrasonic_config={F_CPU_8,RISING};
volatile static uint8 Ultrasonic_processingFlag=0;
void Ultrasonic_init(void){
	GPIO_setupPinDirection(ULTRASONIC_TRIGGRT_PORT_ID,ULTRASONIC_TRIGGRT_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(ULTRASONIC_ECHO_PORT_ID,ULTRASONIC_ECHO_PIN_ID,PIN_INPUT);
	Icu_init((const Icu_ConfigType *)& g_Ultrasonic_config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
}
void Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRASONIC_TRIGGRT_PORT_ID,ULTRASONIC_TRIGGRT_PIN_ID,LOGIC_HIGH);
	_delay_us(11);
	GPIO_writePin(ULTRASONIC_TRIGGRT_PORT_ID,ULTRASONIC_TRIGGRT_PIN_ID,LOGIC_LOW);
	Ultrasonic_processingFlag=1;
}
uint16 Ultrasonic_readDistance(void){
	/*wait while triggering and edge processing are taking place*/
	while(Ultrasonic_processingFlag);
	return (uint16)((uint64)((uint64)(ICR1 * ULTRASONIC_SONIC_SPEED_X1000))/((uint64) (F_CPU)* 20));

}
void Ultrasonic_edgeProcessing(void){
	if(BIT_IS_SET(TCCR1B,ICES1)){
	/*if detect rising edge*/
		/*just clear Timer counter incrementing register*/
		TCNT1=0;
		CLEAR_BIT(TCCR1B,ICES1);
	}
	else{
	/*if detect falling edge*/
		Ultrasonic_processingFlag=0;
		SET_BIT(TCCR1B,ICES1);
	}

}
