CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
QEMU    = qemu-system-arm
CFLAGS  = -mcpu=cortex-m3 -mthumb -Wall -O0 -nostdlib -ffreestanding
OBJS    = startup.o uart.o main.o
TARGET  = firmware


all: $(TARGET).bin

startup.o: startup.s
	$(AS) -mcpu=cortex-m3 -mthumb startup.s -o startup.o

uart.o: uart.c
	$(CC) $(CFLAGS) -c uart.c -o uart.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

$(TARGET).elf: $(OBJS) linker.ld
	$(CC) $(CFLAGS) -T linker.ld $(OBJS) -o $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin


run: $(TARGET).bin
	$(QEMU) -M lm3s6965evb -nographic -kernel $(TARGET).bin

clean:
	rm -f *.o *.elf *.bin