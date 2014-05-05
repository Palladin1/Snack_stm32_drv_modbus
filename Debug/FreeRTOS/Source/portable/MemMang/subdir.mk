################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/MemMang/heap_1.c 

OBJS += \
./FreeRTOS/Source/portable/MemMang/heap_1.o 

C_DEPS += \
./FreeRTOS/Source/portable/MemMang/heap_1.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/MemMang/%.o: ../FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\CMSIS" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\functions" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\rtu" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\stm32" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\Peripherals" -I"D:\pall\workspace\Snack_stm32_drv_modbus\bsp" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\StdPeripheralDriver\inc" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\MemMang" -I"D:\pall\workspace\Snack_stm32_drv_modbus" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


