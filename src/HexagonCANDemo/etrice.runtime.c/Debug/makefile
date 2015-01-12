################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/subdir.mk
-include etRuntime/src/common/runtime/subdir.mk
-include etRuntime/src/common/modelbase/subdir.mk
-include etRuntime/src/common/messaging/subdir.mk
-include etRuntime/src/common/helpers/subdir.mk
-include etRuntime/src/common/debugging/subdir.mk
-include etRuntime/src/common/base/subdir.mk
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

# All Target
all: libHexagonCANDemo.etrice.runtime.c.a

# Tool invocations
libHexagonCANDemo.etrice.runtime.c.a: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC Archiver'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-ar" -r  "libHexagonCANDemo.etrice.runtime.c.a" "@makefile.rsp"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ARCHIVES)$(S_DEPS) libHexagonCANDemo.etrice.runtime.c.a
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
