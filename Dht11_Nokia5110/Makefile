
PATH_EXE			:= Exe
PATH_LIB_INC		:= Lib\\Inc
PATH_LIB_SRC		:= Lib\\Src
PATH_OBJ			:= Obj

FILEMAIN   			:= main

FILE_FONT	 		:= font
FILE_NOKIA5110		:= nokia5110
FILE_SPI		 	:= spi
FILE_WELCOME		:= welcome
FILE_DHT11			:= dht11

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
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_FONT).c -o $(PATH_OBJ)\\$(FILE_FONT).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_NOKIA5110).c -o $(PATH_OBJ)\\$(FILE_NOKIA5110).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_SPI).c -o $(PATH_OBJ)\\$(FILE_SPI).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_WELCOME).c -o $(PATH_OBJ)\\$(FILE_WELCOME).o
	$(COMPILE) -c $(PATH_LIB_SRC)\\$(FILE_DHT11).c -o $(PATH_OBJ)\\$(FILE_DHT11).o


	$(COMPILE) -o $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_OBJ)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)\\$(FILEMAIN).elf $(PATH_EXE)\\$(FILEMAIN).hex 
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).hex
	$(COMPILE_SIZE) $(PATH_EXE)\\$(FILEMAIN).elf

end:
	@echo Finish