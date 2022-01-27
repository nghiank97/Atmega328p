
PATH_EXE			:= Exe
PATH_OBJ			:= Obj

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL
HEXFORMAT			:= ihex

COM_PORT			:= COM4
BAUDRATE			:= 115200
PROGRAMMER_TYPE		:= arduino

PATH_COMPILE		:= C:\\avr-gcc-11.1.0-x64-windows\\bin
COMPILE    			:= $(PATH_COMPILE)\\avr-gcc -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) $(LDFLAGS)  
COMPILE_SIZE    	:= $(PATH_COMPILE)\\avr-size
COMPILE_OBJ_COPY   	:= $(PATH_COMPILE)\\avr-objcopy
COMPILE_OBJ_DUMP   	:= $(PATH_COMPILE)\\avr-objdump
COMPILE_AVRDUDE		:= $(PATH_COMPILE)\\avrdude

SOURCE_NAME 		= memory

build: pre_delete compile end

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_OBJ)\\*.* $(PATH_EXE)\\*.*
	@echo "finish delete..."

compile: 
	$(COMPILE) -c main.c -I. -o $(PATH_OBJ)\\$(SOURCE_NAME).o
	$(COMPILE) -o $(PATH_EXE)\\$(SOURCE_NAME).map $(PATH_OBJ)\\*.o
	$(COMPILE) -o $(PATH_EXE)\\$(SOURCE_NAME).lst $(PATH_OBJ)\\*.o
	$(COMPILE) -o $(PATH_EXE)\\$(SOURCE_NAME).eep $(PATH_OBJ)\\*.o
	$(COMPILE) -o $(PATH_EXE)\\$(SOURCE_NAME).elf $(PATH_OBJ)\\*.o
	
	$(COMPILE_OBJ_COPY) -j .text -j .data -O $(HEXFORMAT) $(PATH_EXE)\\$(SOURCE_NAME).elf $(PATH_EXE)\\$(SOURCE_NAME).hex 


	$(COMPILE_SIZE) $(PATH_EXE)\\$(SOURCE_NAME).hex
	$(COMPILE_SIZE) $(PATH_EXE)\\$(SOURCE_NAME).elf

	$(COMPILE_OBJ_DUMP) -S -l -C -h -t $(PATH_EXE)\\$(SOURCE_NAME).elf > test1.txt
	$(COMPILE_OBJ_DUMP) -S -l -C -h -t $(PATH_OBJ)\\$(SOURCE_NAME).o > test2.txt
end:
	@echo Finish

	

