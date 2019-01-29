# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: Main.elf 

#additional rules for files
Main.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o wdInterruptHandler.o stateMachines.o led.o buzzer.o switches.o Main.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: Main.elf
	mspdebug rf2500 "prog Main.elf"

clean:
	rm -f *.o *.elf

led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h
