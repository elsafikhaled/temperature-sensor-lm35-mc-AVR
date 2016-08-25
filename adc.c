/*
 * adc.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: El-safi
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/*******************                   ADC         ************************/
void  ADC_Init(void)
{
	ADMUX=(1<<REFS0)|(1<<MUX0);   // voltage reference  = 5v Vcc ** ADC1 activated
    ADCSRA=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS2); // divide factor 64 for clock
}


 unsigned int ADC_Read(void)
{
	 ADCSRA|=(1<<ADSC); // start conversion to get digital value IN ADC registers
	 while(ADCSRA & (1<<ADSC));

     return ADC ;
}
/**********************    7 SEGMENT        *****************************/

 void segments_init(int temp)
 {
  unsigned int temp_tens,temp_ones;
   DDRB|=(1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3);
   DDRC=(1<<PC4)|(1<<PC5);

   if(temp>34){PORTD=(1<<PD5);}// buzzer on
   else {PORTD&=~(1<<PD5);}

   // show temperature on 7segments

    PORTC|=(1<<PC4);
    PORTC&=~(1<<PC5);
    temp_ones=temp%10;
    PORTB=temp_ones;
    _delay_ms(400);

   PORTC&=~(1<<PC4);
   PORTC|=(1<<PC5);
   temp_tens=temp/10;
   PORTB=temp_tens;
   _delay_ms(400);

 }

int  main(void)
{

	int temp=0;
	volatile int degitalValue;
	DDRD=(1<<PD5);
	PORTD&=~(1<<PD5);

	ADC_Init();

	while(1)
	{

		degitalValue=ADC_Read();
       temp=(degitalValue*5)/10;  //  :) finally
       segments_init(temp);
       _delay_ms(500);


	}

return 0;

}

