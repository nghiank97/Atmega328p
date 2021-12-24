
PATH_EXE			:= Exe
PATH_LIB_INC		:= Lib//Inc
PATH_LIB_SRC		:= Lib//Src
PATH_OBJ			:= Obj

FILEMAIN   			:= main

FILE_ADC			:= adc
FILE_LCD			:= lcd4
FILE_MMA			:= modbus_ascii
FILE_UART			:= serial

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL
HEXFORMAT			:= ihex

PATH_COMPILE		:= C://avr_gcc//bin
COMPILE    			:= $(PATH_COMPILE)//avr-gcc -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)//avr-objcopy
COMPILE_SIZE    	:= $(PATH_COMPILE)//avr-size
COMPILE_OBJDUMP		:= $(PATH_COMPILE)//avr-objdump
 
build: info pre_delete compile end

info:
	@echo $(DEVICE) $(F_CPU)

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_OBJ)\\*.o $(PATH_EXE)\\$(FILEMAIN).hex $(PATH_EXE)\\$(FILEMAIN).elf
	@echo "finish delete..."

compile:
	@echo Building...
	
	$(COMPILE) -c $(FILEMAIN).c -o $(PATH_OBJ)//$(FILEMAIN).o
	$(COMPILE) -c $(PATH_LIB_SRC)//$(FILE_LCD).c -o $(PATH_OBJ)//$(FILE_LCD).o
	$(COMPILE) -c $(PATH_LIB_SRC)//$(FILE_MMA).c -o $(PATH_OBJ)//$(FILE_MMA).o
	$(COMPILE) -c $(PATH_LIB_SRC)//$(FILE_ADC).c -o $(PATH_OBJ)//$(FILE_ADC).o
	$(COMPILE) -c $(PATH_LIB_SRC)//$(FILE_UART).c -o $(PATH_OBJ)//$(FILE_UART).o
	
	$(COMPILE) -o $(PATH_EXE)//$(FILEMAIN).elf $(PATH_OBJ)//*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)//$(FILEMAIN).elf $(PATH_EXE)//$(FILEMAIN).hex 
	$(COMPILE_SIZE) $(PATH_EXE)//$(FILEMAIN).hex
	$(COMPILE_SIZE) $(PATH_EXE)//$(FILEMAIN).elf

end:
	@echo Finish