/*
 * main.c
 *
 *  Created on: Oct 23, 2021
 *      Author: Kyrillos
 * TODO Description: note down description
 */


/*Software dependences*/
#include "common_macros.h"
#include "std_types.h"
#include <stdlib.h>

/*Hardware dependences*/
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include <avr/interrupt.h>
char buffer[20]={0};
int main(){
	/*	setup section	*/
	LCD_init();
	Ultrasonic_init();
	LCD_displayStringRowColumn(0,0,"Distance is   cm");
	sei();
	_delay_ms(1000);
	/*------------------*/

	/*super loop section*/
	register uint16 distance=0;
	loop_for_ever{
		/* implementation */
		Ultrasonic_Trigger();
		distance=Ultrasonic_readDistance();
		/*
		 * the following line to solve approximation to sonic speed value
		 * to just 342.2m/s only so the final result to real one not perfect so always
		 * the final result less than real with few fractions which neglected but integer
		 * so i round it up by adding 1
		 * */
		itoa(distance+1,buffer,10);

		LCD_displayStringRowColumn(0,11,"   ");
		LCD_displayStringRowColumn(0,11,buffer);
		_delay_ms(2000);
	}
	/*------------------*/

}
