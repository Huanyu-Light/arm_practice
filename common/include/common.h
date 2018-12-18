#ifndef __FS4412_COMMON_H
#define	__FS4412_COMMON_H

#include <exynos_4412.h>

#define IRQ_TIMER4_ID73 73

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

/* IRQ */
void do_irq(void);


/* PWM Timer4 */
void pwm_delay_init(void);
void pwm_udelay(volatile uint32_t t);
void pwm_sdelay(volatile uint32_t t);


/* LED */
#define LED_2	2
#define LED_3	3
#define LED_4	4
#define LED_5	5

void led_init(void);
void led_on(uint8_t led_no);
void led_off(uint8_t led_no);
void led_flow_test(void);
void led3_test(void);

#endif