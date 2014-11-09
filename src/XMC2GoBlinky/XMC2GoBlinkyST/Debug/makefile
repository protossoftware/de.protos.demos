################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src-gen/room/basic/service/timing/subdir.mk
-include src-gen/XMC2GoDemoModel/subdir.mk
-include src-gen/DaveInterface/subdir.mk
-include Startup/subdir.mk
-include Lib/subdir.mk
-include Dave/Generated/src/UART001/subdir.mk
-include Dave/Generated/src/SYSTM001/subdir.mk
-include Dave/Generated/src/PWMSP001/subdir.mk
-include Dave/Generated/src/IO004/subdir.mk
-include Dave/Generated/src/DAVESupport/subdir.mk
-include Dave/Generated/src/CLK002/subdir.mk
-include Dave/Generated/src/CCU4GLOBAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
XMC2GOBlinkyST.hex \

SECONDARY_LIST += \
XMC2GOBlinkyST.lst \

SECONDARY_SIZE += \
XMC2GOBlinkyST.siz \


# All Target
all: XMC2GOBlinkyST.elf secondary-outputs

# Tool invocations
XMC2GOBlinkyST.elf: $(OBJS) ../XMC2GOBlinkyST.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -T"../XMC2GOBlinkyST.ld" -nostartfiles -L"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Lib" -L"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\Debug" -L"C:\DAVE-3.1.10\eclipse\/../Examples/Lib" -L"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI" -Wl,-Map,"XMC2GOBlinkyST.map" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "XMC2GOBlinkyST.elf" "@makefile.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

XMC2GOBlinkyST.hex: XMC2GOBlinkyST.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-objcopy" -O ihex "XMC2GOBlinkyST.elf"  "XMC2GOBlinkyST.hex"
	@echo 'Finished building: $@'
	@echo ' '

XMC2GOBlinkyST.lst: XMC2GOBlinkyST.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-objdump" -h -S "XMC2GOBlinkyST.elf" > "XMC2GOBlinkyST.lst"
	@echo 'Finished building: $@'
	@echo ' '

XMC2GOBlinkyST.siz: XMC2GOBlinkyST.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-size"  --format=berkeley XMC2GOBlinkyST.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(SECONDARY_FLASH)$(S_DEPS)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(SECONDARY_LIST) XMC2GOBlinkyST.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
