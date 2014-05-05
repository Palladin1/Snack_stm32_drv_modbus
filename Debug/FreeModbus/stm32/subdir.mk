################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeModbus/stm32/portevent.c \
../FreeModbus/stm32/portevent_m.c \
../FreeModbus/stm32/portserial.c \
../FreeModbus/stm32/portserial_m.c \
../FreeModbus/stm32/porttimer.c \
../FreeModbus/stm32/porttimer_m.c \
../FreeModbus/stm32/user_mb_app.c \
../FreeModbus/stm32/user_mb_app_m.c 

OBJS += \
./FreeModbus/stm32/portevent.o \
./FreeModbus/stm32/portevent_m.o \
./FreeModbus/stm32/portserial.o \
./FreeModbus/stm32/portserial_m.o \
./FreeModbus/stm32/porttimer.o \
./FreeModbus/stm32/porttimer_m.o \
./FreeModbus/stm32/user_mb_app.o \
./FreeModbus/stm32/user_mb_app_m.o 

C_DEPS += \
./FreeModbus/stm32/portevent.d \
./FreeModbus/stm32/portevent_m.d \
./FreeModbus/stm32/portserial.d \
./FreeModbus/stm32/portserial_m.d \
./FreeModbus/stm32/porttimer.d \
./FreeModbus/stm32/porttimer_m.d \
./FreeModbus/stm32/user_mb_app.d \
./FreeModbus/stm32/user_mb_app_m.d 


# Each subdirectory must supply rules for building sources it contributes
FreeModbus/stm32/%.o: ../FreeModbus/stm32/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\CMSIS" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\functions" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\rtu" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\stm32" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\Peripherals" -I"D:\pall\workspace\Snack_stm32_drv_modbus\bsp" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\StdPeripheralDriver\inc" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\MemMang" -I"D:\pall\workspace\Snack_stm32_drv_modbus" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


