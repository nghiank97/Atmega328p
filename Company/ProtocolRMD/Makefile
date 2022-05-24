
PATH_EXE			:= Exe
PATH_OBJ			:= Obj

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL
HEXFORMAT			:= ihex

COM_PORT			:= COM4
BAUDRATE			:= 115200
PROGRAMMER_TYPE		:= arduino

PRINTF_LIB_FLOAT 	:= -Wl,-u,vfprintf -lprintf_flt
PRINTF_LIB 			:= $(PRINTF_LIB_FLOAT)

PATH_COMPILE		:= C:\\avr-gcc-11.1.0-x64-windows\\bin
COMPILE    			:= $(PATH_COMPILE)\\avr-gcc -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) $(PRINTF_LIB) 
COMPILE_SIZE    	:= $(PATH_COMPILE)\\avr-size
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)\\avr-objcopy
COMPILE_AVRDUDE		:= $(PATH_COMPILE)\\avrdude

MAIN_FILE 			= main

SRC_FILE 			+= serial.c
SRC_FILE 			+= protocol.c
SRC_FILE 			+= rmd_motor.c

OBJS				= $(patsubst %.c,Obj/%.o,$(SRC_FILE))

build: info pre_delete compile end
flash: build push

info:
	@echo $(DEVICE) $(F_CPU)

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_OBJ)\\*.o $(PATH_EXE)\\*.hex $(PATH_EXE)\\*.elf
	@echo "finish delete..."

compile: $(OBJS) $(PATH_OBJ)/$(MAIN_FILE).o
	$(COMPILE) -o $(PATH_EXE)\\$(MAIN_FILE).elf $(PATH_OBJ)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)\\$(MAIN_FILE).elf $(PATH_EXE)\\$(MAIN_FILE).hex 
	$(COMPILE_SIZE) $(PATH_EXE)\\$(MAIN_FILE).hex
	$(COMPILE_SIZE) $(PATH_EXE)\\$(MAIN_FILE).elf

Obj/%.o: %.c
	$(COMPILE) -c $< -I. -o $@

$(PATH_OBJ)/$(MAIN_FILE).o: $(MAIN_FILE).c
	$(COMPILE) -c $< -o $@

push:
	$(COMPILE_AVRDUDE) -p $(DEVICE) -b $(BAUDRATE) -c $(PROGRAMMER_TYPE) -P $(COM_PORT) -U flash:w:$(PATH_EXE)\\$(MAIN_FILE).hex

end:
	@echo Finish

	

