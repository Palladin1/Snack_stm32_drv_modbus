################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeModbus/functions/mbfunccoils.c \
../FreeModbus/functions/mbfunccoils_m.c \
../FreeModbus/functions/mbfuncdiag.c \
../FreeModbus/functions/mbfuncdisc.c \
../FreeModbus/functions/mbfuncdisc_m.c \
../FreeModbus/functions/mbfuncholding.c \
../FreeModbus/functions/mbfuncholding_m.c \
../FreeModbus/functions/mbfuncinput.c \
../FreeModbus/functions/mbfuncinput_m.c \
../FreeModbus/functions/mbfuncother.c \
../FreeModbus/functions/mbutils.c 

OBJS += \
./FreeModbus/functions/mbfunccoils.o \
./FreeModbus/functions/mbfunccoils_m.o \
./FreeModbus/functions/mbfuncdiag.o \
./FreeModbus/functions/mbfuncdisc.o \
./FreeModbus/functions/mbfuncdisc_m.o \
./FreeModbus/functions/mbfuncholding.o \
./FreeModbus/functions/mbfuncholding_m.o \
./FreeModbus/functions/mbfuncinput.o \
./FreeModbus/functions/mbfuncinput_m.o \
./FreeModbus/functions/mbfuncother.o \
./FreeModbus/functions/mbutils.o 

C_DEPS += \
./FreeModbus/functions/mbfunccoils.d \
./FreeModbus/functions/mbfunccoils_m.d \
./FreeModbus/functions/mbfuncdiag.d \
./FreeModbus/functions/mbfuncdisc.d \
./FreeModbus/functions/mbfuncdisc_m.d \
./FreeModbus/functions/mbfuncholding.d \
./FreeModbus/functions/mbfuncholding_m.d \
./FreeModbus/functions/mbfuncinput.d \
./FreeModbus/functions/mbfuncinput_m.d \
./FreeModbus/functions/mbfuncother.d \
./FreeModbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
FreeModbus/functions/%.o: ../FreeModbus/functions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\CMSIS" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\functions" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\rtu" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\stm32" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\Peripherals" -I"D:\pall\workspace\Snack_stm32_drv_modbus\bsp" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\StdPeripheralDriver\inc" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\MemMang" -I"D:\pall\workspace\Snack_stm32_drv_modbus" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


