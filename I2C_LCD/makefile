
PATH_EXE			:= Exe
PATH_LIB_INC		:= Lib\\Inc
PATH_LIB_SRC		:= Lib\\Src
PATH_OBJ			:= Obj

FILEMAIN   			:= main

FILE_SERIAL	 		:= serial
FILE_I2C	 		:= i2c
FILE_PCF8574	 	:= pcf8574

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
COMPILE_OBJDUMP		:= $(PATH_COMPILE)\\avr-objdump
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)\\avr-objcopy
COMPILE_AVRDUDE		:= $(PATH_COMPILE)\\avrdude

build: info pre_delete compile end

info:
	@echo $(DEVICE) $(F_CPU)

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_OBJ)\\*.o $(PATH_EXE)\\$(FILEMAIN).hex $(PATH_EXE)\\$(FILEMAIN).elf
	@echo "finish delete..."

compile:
	@echo Building...
	
	$(COMPILE) -c $(FILEMAIN).c -o $(PATH_OBJ)\\$(FILEMAIN).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_I2C).c -o $(PATH_OBJ)\\$(FILE_I2C).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_PCF8574).c -o $(PATH_OBJ)\\$(FILE_PCF8574).o

	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_SERIAL).c -o $(PATH_OBJ)\\$(FILE_SERIAL).o

	$(COMPILE) -o $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_OBJ)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_EXE)\\$(FILEMAIN).hex 
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).hex
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).elf

push:
	@echo "Loading ..........."
	$(COMPILE_AVRDUDE) -p $(DEVICE) -b $(BAUDRATE) -c $(PROGRAMMER_TYPE) -P $(COM_PORT) -U flash:w:$(PATH_EXE)\\main.hex

end:
	@echo Finish