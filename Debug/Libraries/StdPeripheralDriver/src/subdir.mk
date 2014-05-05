################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/StdPeripheralDriver/src/misc.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_adc.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_bkp.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_can.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_cec.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_crc.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_dac.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_dbgmcu.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_dma.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_exti.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_flash.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_fsmc.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_gpio.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_i2c.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_iwdg.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_pwr.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_rcc.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_rtc.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_sdio.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_spi.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_tim.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_usart.c \
../Libraries/StdPeripheralDriver/src/stm32f10x_wwdg.c 

OBJS += \
./Libraries/StdPeripheralDriver/src/misc.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_adc.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_bkp.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_can.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_cec.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_crc.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_dac.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_dbgmcu.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_dma.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_exti.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_flash.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_fsmc.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_gpio.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_i2c.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_iwdg.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_pwr.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_rcc.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_rtc.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_sdio.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_spi.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_tim.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_usart.o \
./Libraries/StdPeripheralDriver/src/stm32f10x_wwdg.o 

C_DEPS += \
./Libraries/StdPeripheralDriver/src/misc.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_adc.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_bkp.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_can.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_cec.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_crc.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_dac.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_dbgmcu.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_dma.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_exti.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_flash.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_fsmc.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_gpio.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_i2c.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_iwdg.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_pwr.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_rcc.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_rtc.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_sdio.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_spi.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_tim.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_usart.d \
./Libraries/StdPeripheralDriver/src/stm32f10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/StdPeripheralDriver/src/%.o: ../Libraries/StdPeripheralDriver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\CMSIS" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\functions" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\rtu" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeModbus\stm32" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\Peripherals" -I"D:\pall\workspace\Snack_stm32_drv_modbus\bsp" -I"D:\pall\workspace\Snack_stm32_drv_modbus\Libraries\StdPeripheralDriver\inc" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\include" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\pall\workspace\Snack_stm32_drv_modbus\FreeRTOS\Source\portable\MemMang" -I"D:\pall\workspace\Snack_stm32_drv_modbus" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


