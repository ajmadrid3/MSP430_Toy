#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();		/* initialize LEDs */
void led_update();		/* update leds */
void green_led_update();
void both_led_update();
void blink_led_update();
void blink_led();
void off_led_update();

// these are boolean flagsee
extern unsigned char leds_changed, green_led_state, red_led_state;
extern unsigned char red_on, green_on;
#endif
