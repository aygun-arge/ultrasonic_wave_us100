#include "ebox.h"
#include "ebox_uart.h"
class UltrasonicWaveUart
{   
	Uart* uart;
	void rxEvent(void)
	{   
		char c = uart->read();
		if (flag==true)
		{
			low= c;
			if (dataEvent!=NULL)
			{
				dataEvent(getDistance());
			}
		}
		else if (flag==false)
		{
			high = c; 
		}
		flag = !flag;
	}
	void(*dataEvent)(uint16_t dis);
	bool flag;
	uint16_t d;
	uint8_t high, low;
public:
	UltrasonicWaveUart(Uart* uartx) :
		uart(uartx), flag(false), 
		d(0), high(0), low(0), dataEvent(NULL)
	{

	}
	void begin()
	{
		uart->begin(9600);
		uart->attach(this, &UltrasonicWaveUart::rxEvent, RxIrq);
	}
	void trig()
	{
		uart->write(0x55);
	}
	uint16_t getDistance()
	{
		d = high * 256 + low;

		return d;
	}

/*

	void errorHandler()
	{
		oled1.OLED_Init();
		delay_ms(200);
		oled1.OLED_CLS();
		oled1.OLED_printf(0, 0, "test error!");
	}
	void showDistance()
	{
		oled1.OLED_Init();
		delay_ms(200);
		oled1.OLED_CLS();
		oled1.OLED_printf(0, 0, "result:%d",d);
	}*/


	void attach(void(*dataEvent)(uint16_t dis))
	{
		this->dataEvent = dataEvent;
	}
	template<typename T>
	void attatch(T *pObj, void(T::*classDataEvent)(uint16_t dis))
	{
		this->dataEvent = pObj->classDataEvent;
	}
};