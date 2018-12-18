
#include <common.h>

volatile uint8_t pwm_timer4_flag = 0;

void do_irq(void)
{
	/* 1. Get the interrupt ID */
	int irqno = CPU0.ICCIAR & (0x3ff << 0);
	
	/* 2. Judge the interrupt ID */
	switch (irqno) {
		case IRQ_TIMER4_ID73:
			/* 1. clear the Timer4 interrupt */
			PWM.TINT_CSTAT |= (0x1 << 9);

			/* 2. Set the gflag */
			pwm_timer4_flag = 1;

			/* 3. Disable the PWM Timer4 */
			PWM.TCON &= ((~0x1 << 20));
		break;

		default:
			break;
	}

	/* Write The ACKINTID value from the corresponding ICCIAR access to */
	CPU0.ICCEOIR = (CPU0.ICCEOIR & (~(0x3ff << 0))) | irqno;
}



