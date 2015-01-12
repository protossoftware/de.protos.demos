################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src-gen/room/basic/service/timing/subdir.mk
-include src-gen/room/basic/service/can/subdir.mk
-include src-gen/HexagonCANDemo/subdir.mk
-include Startup/subdir.mk
-include Lib/subdir.mk
-include Dave/Generated/src/SYSTM001/subdir.mk
-include Dave/Generated/src/RESET001/subdir.mk
-include Dave/Generated/src/LIBS/subdir.mk
-include Dave/Generated/src/DAVESupport/subdir.mk
-include Dave/Generated/src/CLK001/subdir.mk
-include Dave/Generated/src/CANGLOBAL/subdir.mk
-include Dave/Generated/src/CAN001/subdir.mk
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
HexagonCANDemoST.hex \

SECONDARY_LIST += \
HexagonCANDemoST.lst \

SECONDARY_SIZE += \
HexagonCANDemoST.siz \


# All Target
all: HexagonCANDemoST.elf secondary-outputs

# Tool invocations
HexagonCANDemoST.elf: $(OBJS) ../HexagonCANDemoST.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -T"../HexagonCANDemoST.ld" -nostartfiles -L"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Lib" -L"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\Debug" -L"C:\DAVE-3.1.10\eclipse\/../Examples/Lib" -L"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI" -Wl,-Map,"HexagonCANDemoST.map" -mcpu=cortex-m4 -mthumb -g3 -gdwarf-2 -o "HexagonCANDemoST.elf" "@makefile.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

HexagonCANDemoST.hex: HexagonCANDemoST.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-objcopy" -O ihex "HexagonCANDemoST.elf"  "HexagonCANDemoST.hex"
	@echo 'Finished building: $@'
	@echo ' '

HexagonCANDemoST.lst: HexagonCANDemoST.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-objdump" -h -S "HexagonCANDemoST.elf" > "HexagonCANDemoST.lst"
	@echo 'Finished building: $@'
	@echo ' '

HexagonCANDemoST.siz: HexagonCANDemoST.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-size"  --format=berkeley HexagonCANDemoST.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(SECONDARY_FLASH)$(S_DEPS)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(SECONDARY_LIST) HexagonCANDemoST.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
