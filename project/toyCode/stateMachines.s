	.data
green_on: 	.byte 	0
red_on:		.byte	0
leds_changed:	.byte
changed:	.byte	0

	.text

toggle_off:
	mov.b	#0, &changed
	mov.b	#0, &green_on
	mov.b	#0, &red_on
	call	#blink_led
	ret

