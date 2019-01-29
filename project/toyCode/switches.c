#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

char switch_state_down, switch_state_changed, buzzer_on, all_switches_up, button_pressed_once; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

static char
switch_update_interrupt_sense_button1()
{
  char p1val = P2IN;

  P2IES |= (p1val & SW1);
  P2IES &= (p1val & ~SW1);
  return p1val;
}

static char
switch_update_interrupt_sense_button2()
{
  char p2val = P2IN;

  P2IES |= (p2val & SW2);
  P2IES &= (p2val & ~SW2);
  return p2val;
}

static char
switch_update_interrupt_sense_button3()
{
  char p3val = P2IN;

  P2IES |= (p3val & SW3);
  P2IES &= (p3val & ~SW3);
  return p3val;
}

static char
switch_update_interrupt_sense_button4()
{
  char p4val = P2IN;

  P2IES |= (p4val & SW4);
  P2IES &= (p4val & ~SW4);
  return p4val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense_button1();
  char p2val = switch_update_interrupt_sense_button2();
  char p3val = switch_update_interrupt_sense_button3();
  char p4val = switch_update_interrupt_sense_button4();

  buzzer_on = 0;
  all_switches_up = 1;
  
  if(p1val) {
    switch_state_down = (p1val & SW1) ? 0 : 1; /* 0 when SW1 is up */
    switch_state_changed = 1;
    //led_update();
    if(switch_state_down && !buzzer_on) {
      buzzer_set_period(4000);
      buzzer_on = 1;
      all_switches_up = 0;
      if (button_pressed_once) {
	led_update();
	button_pressed_once = 0;
      } else {
	off_led_update();
	button_pressed_once = 1;
      }
    } else if(!switch_state_down && !buzzer_on) {
      buzzer_on = 0;
    }
  }
  if(p2val) {
    switch_state_down = (p2val & SW2) ? 0 : 1;
    switch_state_changed = 1;
    green_led_update();

    if(switch_state_down && !buzzer_on) {
      buzzer_set_period(3500);
      buzzer_on = 1;
      all_switches_up = 0;
    } else if(!switch_state_down && !buzzer_on) {
      buzzer_on = 0;
    }
  }
  if(p3val) {
    switch_state_down = (p3val & SW3) ? 0 : 1;
    switch_state_changed = 1;
    both_led_update();

    if(switch_state_down && !buzzer_on) {
      buzzer_set_period(3000);
      buzzer_on = 1;
      all_switches_up = 0;
    } else if(!buzzer_on) {
      buzzer_on = 0;
    }
  }
  if(p4val) {
    switch_state_down = (p4val & SW4) ? 0 : 1;
    if (!switch_state_down && button_pressed_once) {
      button_pressed_once = 0;
      toggle_off();
      buzzer_on = 0;
    } else if (!switch_state_down && !button_pressed_once) {
      button_pressed_once = 1;
      enableWDTInterrupts();
      blink_led_update();
      buzzer_on = 0;
    } else if (switch_state_down) {
      buzzer_set_period(4500);
      buzzer_on = 1;
      all_switches_up = 0;
    }
  }

  if(all_switches_up) {
    buzzer_set_period(0);
  }
  //switch_state_changed = 1;
  //led_update();
}
