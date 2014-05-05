################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_Source/_timers.c \
../FreeRTOS_Source/list.c \
../FreeRTOS_Source/port.c \
../FreeRTOS_Source/queue.c \
../FreeRTOS_Source/tasks.c 

OBJS += \
./FreeRTOS_Source/_timers.o \
./FreeRTOS_Source/list.o \
./FreeRTOS_Source/port.o \
./FreeRTOS_Source/queue.o \
./FreeRTOS_Source/tasks.o 

C_DEPS += \
./FreeRTOS_Source/_timers.d \
./FreeRTOS_Source/list.d \
./FreeRTOS_Source/port.d \
./FreeRTOS_Source/queue.d \
./FreeRTOS_Source/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/%.o: ../FreeRTOS_Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_MD_VL -DGCC_ARMCM3 -DUSE_STDPERIPH_DRIVER -I"D:\PALL\workspace\freertos_stm32_d" -I"D:\PALL\workspace\freertos_stm32_d\Libraries\CMSIS" -I"D:\PALL\workspace\freertos_stm32_d\Libraries\StdPeripheralDriver\inc" -I"D:\PALL\workspace\freertos_stm32_d\Libraries\Peripherals" -I"D:\PALL\workspace\freertos_stm32_d\FreeRTOS_Source\include" -I"D:\PALL\workspace\freertos_stm32_d\FreeRTOS_Source\portable\MemMang" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


