//uart1:PA10 PA9  RX TX
//uart2:PA3  PA2
//oled:PA8 PA11
#include "ebox.h"
#include "ultrasonic_wave_uart.h"
#include "led.h"
Led led1(&PA2,1);
UltrasonicWaveUart wave(&uart2);
void setup()
{
	ebox_init();
	led1.begin();
	uart1.begin(115200);
	wave.begin();
}
void main()
{
	setup(); 
	while(1)
	{
		wave.trig();
		uart1.printf("uart is ok!\n");
		delay_ms(500);
		uart1.printf("%d\n",wave.read());

		led1.toggle();
		delay_ms(500);
	}
}