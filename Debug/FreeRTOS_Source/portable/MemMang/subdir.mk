################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_Source/portable/MemMang/heap_1.c 

OBJS += \
./FreeRTOS_Source/portable/MemMang/heap_1.o 

C_DEPS += \
./FreeRTOS_Source/portable/MemMang/heap_1.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/portable/MemMang/%.o: ../FreeRTOS_Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DGCC_ARMCM3 -DUSE_STDPERIPH_DRIVER -I"D:\PALL\workspace\freertos_stm32_d" -I"D:\PALL\workspace\freertos_stm32_d\Libraries\CMSIS" -I"D:\PALL\workspace\freertos_stm32_d\Libraries\StdPeripheralDriver\inc" -I"D:\PALL\workspace\freertos_stm32_d\Libraries\Peripherals" -I"D:\PALL\workspace\freertos_stm32_d\FreeRTOS_Source\include" -I"D:\PALL\workspace\freertos_stm32_d\FreeRTOS_Source\portable\MemMang" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


