/*
 * ultrasonic.h
 *
 *  Created on: Oct 23, 2021
 *      Author: Kyrillos
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "icu.h"
#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>

/****************************************************
 *  			Module macros constants	         	*
 ****************************************************/
#define ULTRASONIC_TRIGGRT_PORT_ID PORTB_ID
#define ULTRASONIC_TRIGGRT_PIN_ID (5u)
#define ULTRASONIC_ECHO_PORT_ID PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID (6u)
#define ULTRASONIC_SONIC_SPEED_X1000 (343333U)
/*--------------------------------------------------*/


/****************************************************
 *  			Module global variable	         	*
 ****************************************************/
extern volatile Icu_ConfigType g_Ultrasonic_config;
/*--------------------------------------------------*/


/****************************************************
 *				Functions deceleration				*
 ****************************************************/

/*
 * Description : to configure GPIO and ICU for Ultrasonic
 * 				 depending on what engineer statically configured in ultrasonic.h
 * 		   args: no inputs or output
 */
void Ultrasonic_init(void);

/*
 * Description : just signal ultrasonic to generate 8 pulses
 *         args: no inputs or output
 */
void Ultrasonic_Trigger(void);


/*
 * Description : read distance feeded back from ultrasonic in cm
 *        args :
 *        		in : on inputs
 *        		out: unsigned 2 bytes of integer neglecting any fraction
 *        			 rounded down
 */
uint16 Ultrasonic_readDistance(void);


/*
 * Description : the implementation of the callback function that
 * 				 must handle the interrupt triggered by ICU to recored spent time
 *         args: no inputs or output
 */
void Ultrasonic_edgeProcessing(void);
/*--------------------------------------------------*/


#endif /* ULTRASONIC_H_ */
