
PATH_BUILD			:= Build

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL
HEXFORMAT			:= ihex

COM_PORT			:= COM4
BAUDRATE			:= 115200
PROGRAMMER_TYPE		:= arduino

CFLAGS 				= -g -w -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
CFLAGS 				+= -Wl,-u,vfprintf -lprintf_flt

PATH_COMPILE		:= C:\\avr-gcc-11.1.0-x64-windows\\bin
COMPILE    			:= $(PATH_COMPILE)\\avr-gcc $(CFLAGS) 
COMPILE_SIZE    	:= $(PATH_COMPILE)\\avr-size
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)\\avr-objcopy
COMPILE_AVRDUDE		:= $(PATH_COMPILE)\\avrdude

MAIN_FILE 			= main
SRC_FILE 			= main.c
SRC_FILE 			+= serial.c

OBJS				= $(patsubst %.c,$(PATH_BUILD)/%.o,$(SRC_FILE))

build: info pre_delete compile end
flash: build push

info:
	@echo $(DEVICE) $(F_CPU)

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_BUILD)\*.o $(PATH_BUILD)\*.hex $(PATH_BUILD)\*.elf
	@echo "finish delete..."

compile: $(OBJS) $(PATH_BUILD)/$(MAIN_FILE).o
	$(COMPILE) -o $(PATH_BUILD)\\$(MAIN_FILE).elf $(PATH_BUILD)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_BUILD)\\$(MAIN_FILE).elf $(PATH_BUILD)\\$(MAIN_FILE).hex 
	$(COMPILE_SIZE) $(PATH_BUILD)\\$(MAIN_FILE).hex
	$(COMPILE_SIZE) $(PATH_BUILD)\\$(MAIN_FILE).elf

$(PATH_BUILD)/%.o: %.c
	$(COMPILE) -c $< -I. -o $@

$(PATH_BUILD)/$(MAIN_FILE).o: $(MAIN_FILE).c
	$(COMPILE) -c $< -o $@

push:
	@echo "Loading ..........."
	$(COMPILE_AVRDUDE) -p $(DEVICE) -b $(BAUDRATE) -c $(PROGRAMMER_TYPE) -P $(COM_PORT) -U flash:w:$(PATH_BUILD)\\$(MAIN_FILE).hex

end:
	@echo Finish

	

