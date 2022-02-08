

PATH_BUILD			:= Build

DEVICE     			:= atmega328p
F_CPU				:= 16000000UL

COM_PORT			:= COM13
BAUDRATE			:= 115200
PROGRAMMER_TYPE		:= arduino

PATH_CC				:= C:\\avr-gcc-11.1.0-x64-windows\\bin
CC    				:= $(PATH_CC)\\avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
GCC    				:= $(PATH_CC)\\avr-gcc -g -w -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -Wl,-u,vfprintf -lprintf_flt
CC_SIZE    			:= $(PATH_CC)\\avr-size
CC_OBJ_COPY   		:= $(PATH_CC)\\avr-objcopy -j .text -j .data -O ihex
CC_AVRDUDE			:= $(PATH_CC)\\avrdude

MAIN_FILE			:= source

SRC_FILE 			= main.cpp
SRC_FILE 			+= bldc_motor.cpp
SRC_FILE 			+= encoder.cpp
SRC_FILE 			+= pid.cpp
SRC_FILE 			+= lowpass_filter.cpp
SRC_FILE 			+= serial.cpp
SRC_FILE 			+= system.cpp
SRC_FILE 			+= pwm.cpp
SRC_FILE 			+= defaults.cpp

OBJS				= $(patsubst %.cpp,Build/%.o,$(SRC_FILE))

all: info pre_delete compile end

flash: all push

info:
	@echo $(DEVICE) $(F_CPU)

pre_delete:
	@echo "predeleting..."
	del -f $(PATH_BUILD)\\*.o $(PATH_BUILD)\\*.hex $(PATH_BUILD)\\*.elf
	@echo "finish delete..."

compile: $(OBJS)
	$(GCC) $(PATH_BUILD)\\*.o -o $(PATH_BUILD)\\$(MAIN_FILE).elf
	$(CC_OBJ_COPY) $(PATH_BUILD)\\$(MAIN_FILE).elf $(PATH_BUILD)\\$(MAIN_FILE).hex 
	$(CC_SIZE) $(PATH_BUILD)\\$(MAIN_FILE).hex
	$(CC_SIZE) $(PATH_BUILD)\\$(MAIN_FILE).elf

Build/%.o: %.cpp
	$(CC) -c $< -o $@

push:
	@echo "Loading ..........."
	$(CC_AVRDUDE) -p $(DEVICE) -b $(BAUDRATE) -c $(PROGRAMMER_TYPE) -P $(COM_PORT) -U flash:w:$(PATH_BUILD)\\$(MAIN_FILE).hex:a

end:
	@echo Finish