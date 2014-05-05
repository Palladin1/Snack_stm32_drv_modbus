################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PeripheralInit/uart.c 

OBJS += \
./PeripheralInit/uart.o 

C_DEPS += \
./PeripheralInit/uart.d 


# Each subdirectory must supply rules for building sources it contributes
PeripheralInit/%.o: ../PeripheralInit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"D:\PALL\workspace\STM32_d\CMSIS" -I"D:\PALL\workspace\STM32_d\PeripheralInit" -I"D:\PALL\workspace\STM32_d\StdPeripheralDriver\inc" -I"D:\PALL\workspace\STM32_d" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


