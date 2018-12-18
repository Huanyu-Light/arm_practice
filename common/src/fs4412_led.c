
#include <common.h>

/* LED_2: GPX2_7
 * LED_3: GPX1_0
 * LED_4: GPF3_4
 * LED_5: GPF3_5
 */
void led_init(void)
{
	GPX2.CON |= (0x1 << 7*4);
	GPX2.DAT &= (~(0x1 << 7));
	
	GPX1.CON |= (0x1 << 0*4);
	GPX1.DAT &= (~(0x1 << 0));
	
	GPF3.CON |= (0x11 << 4*4);	
	GPF3.DAT &= (~(0x11 << 4));
}


void led_on(unsigned char led_no)
{
	switch (led_no) {
		case LED_2:
				GPX2.DAT |= (0x1 << 7);
			break;
			
		case LED_3:
				GPX1.DAT |= (0x1 << 0);
			break;
			
		case LED_4:
				GPF3.DAT |= (0x1 << 4);
			break;
			
		case LED_5:
				GPF3.DAT |= (0x1 << 5);
			break;
			
		default:
				break;
	}
		
}

void led_off(unsigned char led_no)
{
	switch (led_no) {
		case LED_2:
				GPX2.DAT &= (~(0x1 << 7));
			break;
			
		case LED_3:
				GPX1.DAT &= (~(0x1 << 0));
			break;
			
		case LED_4:
				GPF3.DAT &= (~(0x1 << 4));
			break;
			
		case LED_5:
				GPF3.DAT &= (~(0x1 << 5));
			break;
			
		default:
				break;
	}
		
}

void led_flow_test(void)
{
	led_init();
	pwm_sdelay(5);

	while (1) {
		led_on(LED_2);
		pwm_sdelay(1);
		led_off(LED_2);
		
		led_on(LED_3);
		pwm_sdelay(1);
		led_off(LED_3);
		
		led_on(LED_4);
		pwm_sdelay(1);
		led_off(LED_4);
		
		led_on(LED_5);
		pwm_sdelay(1);
		led_off(LED_5);
	}
}

void led3_test(void)
{
	led_on(LED_3);
	pwm_sdelay(1);
	led_off(LED_3);
	pwm_sdelay(1);
}

