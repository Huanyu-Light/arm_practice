
#include <common.h>

extern  pwm_timer4_flag;

void pwm_delay_init(void)
{
	/* 1. Clock (PERI-L: 100MHz) -> PCLK: 100MHz 
	 *	Timer Input Clock Frequency = PCLK/({prescaler value + 1})/{divider value}
	 *  {prescaler value} = 1 to 255
	 *  {divider value} = 1, 2, 4, 8, 16, 	//0x2 --> 4, 0x1 --> 2
	 *  Dead zone length = 0 to 254
	 *  1M = 100MHz / (49+1)/ 2, 1 000 000
	 */
	PWM.TCFG0 = (PWM.TCFG0 & (~(0xFF << 8)) | (49 << 8));
	PWM.TCFG1 = (PWM.TCFG1 & (~(0xF << 16)) | (0x1 << 16));

	/* 2. Write the initial value into TCNTBn and TCMPBn, actually only setting
	 *    the Timer count, and default disable the interrupt.
	 */
	PWM.TCNTB4 = 1;

	/* 3. Enable Timer 4 manual update & Disable the manual & Enable autoload */
	PWM.TCON |= (0x1 << 21);
	PWM.TCON &= (~(0x1 << 21));
	PWM.TCON |= (0x1 << 22);

	/* 4. Enable the interrupt at timer */
	PWM.TINT_CSTAT |= (0x1 << 4);

	/* 5. Enable the interrupt at GIC, SPI:41 -- ID:73 -- ICDISER2_CPU0 << 9 */
	ICDISER.ICDISER2 |= (0x1 << 9);

	/* 6. Set the interrupt priority */
	ICDIPR.ICDIPR18 |= (0xf << 1*8);

	/* 7. Set CPU0 priority mask register */
	CPU0.ICCPMR |= (0xff<<0);

	/* 8. Give the interrupt ID_73 to the CPU0,  73/4 = 18 -- 1 */
	ICDIPTR.ICDIPTR18 = ICDIPTR.ICDIPTR14 & (~(0xff<<8)) | (0x1<<8);

	/* 9. Global enable the interrupt to arrive at the CPU interface */
	ICDDCR |= (0x1<<0);

	/* 10. Global enable the interrupt to arrive at the CPU */
	CPU0.ICCICR |= (0x1<<0);

	/* 11. start the timer */
	PWM.TCON |= (0x1 << 20);
}


/* PWM Time4 */
void pwm_udelay(volatile unsigned int t)
{
	pwm_timer4_flag = 0;
	
	/* 2. Write the initial value into TCNTBn and TCMPBn, actually only setting
	 *    the Timer count, and default disable the interrupt.
	 */
	PWM.TCNTB4 = t;

	/* 3. Enable Timer 4 manual update & Disable the manual & Enable autoload */
	PWM.TCON |= (0x1 << 21);
	PWM.TCON &= (~(0x1 << 21));
	PWM.TCON |= (0x1 << 22);

	/* 11. start the timer */
	PWM.TCON |= (0x1 << 20);

	while (pwm_timer4_flag != 1){;}

}

void pwm_sdelay(volatile unsigned int t)
{
	pwm_udelay(1000*1000*t);
}


