/*
 * temperature meter with h and air c.c
 *
 * Created: 9/30/2020 12:32:51 PM
 * Author : mustafa
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define  F_CPU   1000000UL
#include<ADC init.c>
#include <lcd driver.c>
#include <GPIOs driver.c>
#define  A 0x39
#define  B 0x36
#define  C 0x33
#define  D 0x30
#define  output 1
#define input 0

int main(void)
{
    /* Replace with your application code */
	Port_Direction(B,output);                                        //make port B as output (LCD)
	Pin_Direction(A,0,input);                                         //make pin A0 as input (sensor)
	Pin_Direction(A,6,output);                                     //make pin   A6 as output (RS-LCD)
	Pin_Direction(A,7,output);                                     //make pin   A7 as output (E-LCD)
	Pin_Direction(D,0,output);                                    //make pin   D0 as output ( Air Conditioner)
	Pin_Direction(D,7,output);                                    //make pin   D7 as output ( Heater)
	Pin_Direction(C,0,output);                                   //make pin   C0 as output ( Red led)
	Pin_Direction(C,1,output);                                    //make pin   C1 as output ( Green led)
	Pin_Direction(C,2,output);                                  //make pin   C0 as output ( Blue led)
   lcd_init();                                                                    //function which initialize LCD
   ADC_init();                                                                //function which initialize ADC
 volatile uint8_t   result;                                          //var which store ADCH in it
    while (1) 
    {
		
		 ADCSRA|=(1<<ADSC);                                                                //start conversion 
		while((ADCSRA &(1<<ADIF))==0);                                        //wait the conversion stop
		result=ADCH;
		if(result>20 && result <30)                                                        //Default mood
		{
			               Bin_Rest(C,0);                                                              //Red led off
						   Bin_Set(C,1);                                                                  //Green led on
							_delay_ms(500);
			               Bin_Rest(C,1);                                                                //toggle  Green led
							_delay_ms(0.01);
			               Bin_Rest(C,2);                                                                //blue led off
							lcd_go_to(1,1);
							lcd_print("temperature=");
							lcd_go_to(1,13);
							lcd_num(result);                                                        //print the read of sensor on LCD
							lcd_go_to(1,15);
							lcd_print("c'");
							lcd_command(0x0c);                                             //command which display on , cursor off
			               Bin_Rest(D,0);                                                            //Air Conditioner off
			               Bin_Rest(D,7);                                                            //Heater off
							lcd_go_to(3,-2);
							lcd_print(" Default Mood  ");
							lcd_go_to(4,3);
							lcd_print("           ");

		}
		else if(result>=30)                                                                    //Air Conditioner mood
		{
						 Bin_Rest(C,0);                                                          //Red led off
						 Bin_Rest(C,1);                                                            //Green led off
						 Bin_Set(C,2);                                                             //Blue led on
						 _delay_ms(500);                                                     //toggle Blue led
						 Bin_Rest(C,2);
						 _delay_ms(0.01);			
						lcd_go_to(1,1);
						lcd_print("temperature=");
						lcd_go_to(1,13);
						lcd_num(result);                                                   //print the read of sensor on LCD
						lcd_go_to(1,15);
						lcd_print("c'");
					   Bin_Rest(D,7);                                                        //Heater off
					   Bin_Set(D,0);                                                         //Air Conditioner on
						lcd_go_to(3,-2);
						lcd_print("Air Conditioner");
						lcd_go_to(4,3);
						lcd_print("mood");
						lcd_command(0x0c);                                     //command which display on , cursor off
		}
	else	if(result<=20)                                                                 //Heater mood
		{
						Bin_Set(C,0);                                                     //Red led on
						_delay_ms(500);
						Bin_Rest(C,0);                                                  //toggle Red led
						_delay_ms(0.01);
						 Bin_Rest(C,2);                                                 //Green led off
						 Bin_Rest(C,1);                                                  //blue led off
						 Bin_Set(D,7);                                                   //Heater on
						 Bin_Rest(D,0);                                                //Air Conditioner off
						lcd_go_to(1,1);
						lcd_print("temperature=");
						lcd_go_to(1,13);
						lcd_num(result);                                         //print the read of sensor on LCD
						lcd_go_to(1,15);
						lcd_print("c'");
						lcd_go_to(3,-2);
						lcd_print(" Heater Mood   ");
						lcd_command(0x0c);                           //command which display on , cursor off
				}
    }
	return 0;
}
