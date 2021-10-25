/*
 * ultrasonic.c
 *
 *  Created on: Oct 23, 2021
 *      Author: Kyrillos
 */


#include "ultrasonic.h"
#include "common_macros.h"

/*******************************************************************************
 *                       Shared Variable initialization                        *
 *******************************************************************************/
volatile Icu_ConfigType g_Ultrasonic_config={F_CPU_8,RISING};
/*-----------------------------------------------------------------------------*/


/*******************************************************************************
 *           Static global Variable deceleration and initialization            *
 *******************************************************************************/
volatile static uint8 Ultrasonic_processingFlag=0;
/*-----------------------------------------------------------------------------*/


/*
 * Description : to configure GPIO and ICU for Ultrasonic
 * 				 depending on what engineer statically configured in ultrasonic.h
 * 		   args: no inputs or output
 */
void Ultrasonic_init(void){
	GPIO_setupPinDirection(ULTRASONIC_TRIGGRT_PORT_ID,ULTRASONIC_TRIGGRT_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(ULTRASONIC_ECHO_PORT_ID,ULTRASONIC_ECHO_PIN_ID,PIN_INPUT);
	Icu_init((const Icu_ConfigType *)& g_Ultrasonic_config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
}

/*
 * Description : just signal ultrasonic to generate 8 pulses
 *         args: no inputs or output
 */
void Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRASONIC_TRIGGRT_PORT_ID,ULTRASONIC_TRIGGRT_PIN_ID,LOGIC_HIGH);
	_delay_us(11);
	GPIO_writePin(ULTRASONIC_TRIGGRT_PORT_ID,ULTRASONIC_TRIGGRT_PIN_ID,LOGIC_LOW);
	Ultrasonic_processingFlag=1;
}


/*
 * Description : read distance feeded back from ultrasonic in cm
 *        args :
 *        		in : on inputs
 *        		out: unsigned 2 bytes of integer neglecting any fraction
 *        			 rounded down
 */
uint16 Ultrasonic_readDistance(void){
	/*wait while triggering and edge processing are taking place*/
	while(Ultrasonic_processingFlag);
	/*calculate and return the distance in cm*/
	return (uint16)((uint64)((uint64)(ICR1 * ULTRASONIC_SONIC_SPEED_X1000))/((uint64) (F_CPU)* 20));
}

/*
 * Description : the implementation of the callback function that
 * 				 must handle the interrupt triggered by ICU to recored spent time
 *         args: no inputs or output
 */
void Ultrasonic_edgeProcessing(void){
	if(BIT_IS_SET(TCCR1B,ICES1)){
	/*if detect rising edge*/
		/*just clear Timer counter incrementing register*/
		TCNT1=0;
		/*reconfiger ICU edge detector on falling edge*/
		CLEAR_BIT(TCCR1B,ICES1);
	}
	else{
	/*if detect falling edge*/
		/*to tell Ultrasonic_readDistance function its okay to calculate distance */
		Ultrasonic_processingFlag=0;
		/*reconfiger ICU edge detector on rising edge for new usage*/
		SET_BIT(TCCR1B,ICES1);

	}

}
