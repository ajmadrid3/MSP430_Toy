#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "stateMachines.h"

unsigned char leds_changed, green_led_state, red_led_state;
unsigned char green_on = 0;
unsigned char red_on = 0;
unsigned char button_pressed = 0;

static char redVal[] = {0, LED_RED};
static char greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  leds_changed = 0;
  red_led_state = 0;
  green_led_state = 0;

  led_update();
}

void led_update(){
  leds_changed = 0;
  if (switch_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */
 
    ledFlags |= switch_state_down ? LED_RED : 0;
    ledFlags |= switch_state_down ? LED_RED : 0;

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  switch_state_changed = 0;
  leds_changed = 1;
}

void green_led_update() {
  leds_changed = 0;
  if (switch_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : 0;

    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  }
  switch_state_changed = 0;
  leds_changed = 1;
}

void both_led_update() {
  leds_changed = 0;
  if (switch_state_changed) {
    char ledFlags = 0;

    ledFlags |= switch_state_down ? LEDS : 0;
    ledFlags |= switch_state_down ? 0 : 0;

    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  }
  switch_state_changed = 0;
  leds_changed = 1;
}

void blink_led_update() {
  if (switch_state_changed) {
    state_advance();
  }
  switch_state_changed = 0;
}

void blink_led() {
  if (leds_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;
    leds_changed = 0;
  }
}

void off_led_update() {
  if (switch_state_changed) {
    char ledFlags = 0;

    P1OUT &= (0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
  }
  switch_state_changed = 0;
  leds_changed = 0;
}

