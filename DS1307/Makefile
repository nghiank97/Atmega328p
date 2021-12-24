
PATH_EXE			:= Exe
PATH_LIB_INC		:= Lib\\Inc
PATH_LIB_SRC		:= Lib\\Src
PATH_OBJ			:= Obj

FILEMAIN   			:= main

FILE_LCD4	 		:= lcd4
FILE_I2C		 	:= i2c
FILE_DS1307		 	:= ds1307

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

	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_LCD4).c -o $(PATH_OBJ)\\$(FILE_LCD4).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_I2C).c -o $(PATH_OBJ)\\$(FILE_I2C).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_DS1307).c -o $(PATH_OBJ)\\$(FILE_DS1307).o

	$(COMPILE) -o $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_OBJ)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_EXE)\\$(FILEMAIN).hex 
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).hex
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).elf

end:
	@echo Finish