
SERIAL_PORT ?= /dev/ttyUSB1

ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi


AOPS = --warn --fatal-warnings -mcpu=cortex-m0
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : notmain.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.hex
	rm -f *.srec
	rm -rf ../__pycache__


flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

notmain.o : notmain.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c notmain.c -o notmain.o

notmain.bin : flash.ld flash.o notmain.o
	$(ARMGNU)-ld -o notmain.elf -T flash.ld flash.o notmain.o
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy notmain.elf notmain.bin -O binary

	python3 ../create_cust_image_blob.py --bin notmain.bin --load-address 0xC000 --magic-num 0xCB -o main_nonsecure_ota --version 0x0
	python3 ../create_cust_wireupdate_blob.py --load-address 0x20000 --bin main_nonsecure_ota.bin -i 6 -o main_nonsecure_wire --options 0x1
	rm -rf ../__pycache__

prog :
	python3 ../uart_wired_update_sparkfun.py -b 921600 $(SERIAL_PORT) -r 1 -f main_nonsecure_wire.bin -i 6


