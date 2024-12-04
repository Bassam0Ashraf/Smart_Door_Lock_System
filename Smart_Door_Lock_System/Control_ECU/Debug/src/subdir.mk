################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Buzzer.c \
../src/Control_ECU.c \
../src/dcmotor.c \
../src/external_eeprom.c \
../src/gpio.c \
../src/pir.c \
../src/pwm.c \
../src/timer.c \
../src/twi.c \
../src/uart.c 

OBJS += \
./src/Buzzer.o \
./src/Control_ECU.o \
./src/dcmotor.o \
./src/external_eeprom.o \
./src/gpio.o \
./src/pir.o \
./src/pwm.o \
./src/timer.o \
./src/twi.o \
./src/uart.o 

C_DEPS += \
./src/Buzzer.d \
./src/Control_ECU.d \
./src/dcmotor.d \
./src/external_eeprom.d \
./src/gpio.d \
./src/pir.d \
./src/pwm.d \
./src/timer.d \
./src/twi.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


