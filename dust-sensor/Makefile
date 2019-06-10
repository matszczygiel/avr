MCU=atmega8
F_CPU=1000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS= -Wall -Os -mmcu=${MCU} -DF_CPU=${F_CPU}
TARGET=main
SRCS=main.c led-disp/leddisp.c adc/adc.c gp2y1010au0f/gp2y1010au0f.c

all:
		${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
		${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
		avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

clean:
		rm -f *.bin *.hex