
#include <common.h>

int main(int argc, char **argv)
{
	pwm_delay_init();
	led_init();
	led_on(LED_5);

	pwm_sdelay(2);

	led_off(LED_5);

	while (1) {
		led3_test();
	}

	return 0;
}
