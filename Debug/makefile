################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wake/subdir.mk
-include bsp/subdir.mk
-include Libraries/StdPeripheralDriver/src/subdir.mk
-include Libraries/CMSIS/subdir.mk
-include FreeRTOS/Source/portable/MemMang/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS/Source/subdir.mk
-include FreeModbus/tcp/subdir.mk
-include FreeModbus/stm32/subdir.mk
-include FreeModbus/rtu/subdir.mk
-include FreeModbus/functions/subdir.mk
-include FreeModbus/ascii/subdir.mk
-include FreeModbus/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Snack_stm32_drv_modbus.hex \

SECONDARY_LIST += \
Snack_stm32_drv_modbus.lst \

SECONDARY_SIZE += \
Snack_stm32_drv_modbus.siz \


# All Target
all: Snack_stm32_drv_modbus.elf secondary-outputs

# Tool invocations
Snack_stm32_drv_modbus.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"D:\pall\workspace\Snack_stm32_drv_modbus\stm32f100rb.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,Snack_stm32_drv_modbus.map -mcpu=cortex-m3 -mthumb -g3 -ggdb -o"Snack_stm32_drv_modbus.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Snack_stm32_drv_modbus.hex: Snack_stm32_drv_modbus.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex Snack_stm32_drv_modbus.elf "Snack_stm32_drv_modbus.hex"
	@echo 'Finished building: $@'
	@echo ' '

Snack_stm32_drv_modbus.lst: Snack_stm32_drv_modbus.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S Snack_stm32_drv_modbus.elf >"Snack_stm32_drv_modbus.lst"
	@echo 'Finished building: $@'
	@echo ' '

Snack_stm32_drv_modbus.siz: Snack_stm32_drv_modbus.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley Snack_stm32_drv_modbus.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Snack_stm32_drv_modbus.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
