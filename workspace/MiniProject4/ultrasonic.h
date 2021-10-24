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

#define ULTRASONIC_TRIGGRT_PORT_ID PORTB_ID
#define ULTRASONIC_TRIGGRT_PIN_ID (5u)
#define ULTRASONIC_ECHO_PORT_ID PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID (6u)
#define ULTRASONIC_SONIC_SPEED_X1000 (343333U)
extern volatile Icu_ConfigType g_Ultrasonic_config;

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
