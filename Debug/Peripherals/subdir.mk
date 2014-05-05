################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/uart.c 

OBJS += \
./Peripherals/uart.o 

C_DEPS += \
./Peripherals/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/%.o: ../Peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"D:\PALL\workspace\freertos_stm32_d\CMSIS" -I"D:\PALL\workspace\freertos_stm32_d\StdPeripheralDriver\inc" -I"D:\PALL\workspace\freertos_stm32_d\Peripherals" -I"D:\PALL\workspace\freertos_stm32_d" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


