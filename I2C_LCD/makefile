

PATH_BUILD			:= Build

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL

COM_PORT			:= COM4
BAUDRATE			:= 115200
PROGRAMMER_TYPE		:= arduino

CFLAGS 				= -g -w -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
CFLAGS 				+= -Wl,-u,vfprintf -lprintf_flt

PATH_COMPILE		:= C:\\avr-gcc-11.1.0-x64-windows\\bin
COMPILE    			:= $(PATH_COMPILE)\\avr-gcc $(CFLAGS) 
COMPILE_SIZE    	:= $(PATH_COMPILE)\\avr-size
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)\\avr-objcopy -j .text -j .data -O ihex
COMPILE_AVRDUDE		:= $(PATH_COMPILE)\\avrdude

MAIN_FILE			:= source
SRC_FILE 			= main.c
SRC_FILE 			+= serial.c
SRC_FILE 			+= i2c.c
SRC_FILE 			+= pcf8574.c

OBJS				= $(patsubst %.c,Build/%.o,$(SRC_FILE))

load: info compile end

flash: build push

info:
	@echo $(DEVICE) $(F_CPU)

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_BUILD)\\*.o $(PATH_BUILD)\\*.hex $(PATH_BUILD)\\*.elf
	@echo "finish delete..."

compile: $(OBJS)
	$(COMPILE) $(PATH_BUILD)\\*.o -o $(PATH_BUILD)\\$(MAIN_FILE).elf
	
	$(COMPILE_OBJ_COPY) $(PATH_BUILD)\\$(MAIN_FILE).elf $(PATH_BUILD)\\$(MAIN_FILE).hex 
	$(COMPILE_SIZE) $(PATH_BUILD)\\$(MAIN_FILE).hex
	$(COMPILE_SIZE) $(PATH_BUILD)\\$(MAIN_FILE).elf

Build/%.o: Drive/%.c
	$(COMPILE) -c $< -I. -o $@

push:
	@echo "Loading ..........."
	$(COMPILE_AVRDUDE) -p $(DEVICE) -b $(BAUDRATE) -c $(PROGRAMMER_TYPE) -P $(COM_PORT) -U flash:w:$(PATH_BUILD)\\$(MAIN_FILE).hex:a

end:
	@echo Finish
