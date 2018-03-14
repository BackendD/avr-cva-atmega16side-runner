/*
 * main.cpp
 *
 *  Created on: Mar 14, 2018
 *      Author: hasan
 */




#define F_CPU 8000000

#include <avr/io.h>
#include <cva.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

int main(void)
{
	sei();

	Modem modem = Modem(F_CPU, 32);
	modem.begin();

	lcd_init(LCD_DISP_ON_BLINK);
	char s[32];
	DDRD |= (1<<7);
	int i = 0;
	while (1)
	{
		if(modem.available())
		{

			sprintf(s,"%c", modem.read());
			lcd_puts(s);
			i++;
			if (i > 15)
			{
				lcd_clrscr();
				i = 0;
			}
		}

		_delay_ms(100);
		PORTD &= ~(1<<7);
		_delay_ms(100);
		PORTD |= (1<<7);
	}
}
