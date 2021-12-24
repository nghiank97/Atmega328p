
PATH_EXE			:= Exe
PATH_LIB_INC		:= Lib\\Inc
PATH_LIB_SRC		:= Lib\\Src
PATH_OBJ			:= Obj

FILEMAIN   			:= main

FILE_ENCODER	 	:= encoder
FILE_LCD		 	:= lcd4
FILE_SERIAL		 	:= serial
FILE_ADC		 	:= adc
FILE_PWM		 	:= pwm

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL
HEXFORMAT			:= ihex

PRINTF_LIB_FLOAT 	:= -Wl,-u,vfprintf -lprintf_flt
PRINTF_LIB 			:= $(PRINTF_LIB_FLOAT)

PATH_COMPILE		:= C:\\avr_gcc\\bin
COMPILE    			:= $(PATH_COMPILE)\\avr-gcc -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) $(PRINTF_LIB) 
COMPILE_SIZE    	:= $(PATH_COMPILE)\\avr-size
COMPILE_OBJDUMP		:= $(PATH_COMPILE)\\avr-objdump
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)\\avr-objcopy

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
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_ENCODER).c -o $(PATH_OBJ)\\$(FILE_ENCODER).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_LCD).c -o $(PATH_OBJ)\\$(FILE_LCD).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_SERIAL).c -o $(PATH_OBJ)\\$(FILE_SERIAL).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_ADC).c -o $(PATH_OBJ)\\$(FILE_ADC).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_PWM).c -o $(PATH_OBJ)\\$(FILE_PWM).o

	$(COMPILE) -o $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_OBJ)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_EXE)\\$(FILEMAIN).hex 
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).hex
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).elf

end:
	@echo Finish