################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/util/subdir.mk
-include src/platforms/MT_WIN_MinGW/subdir.mk
-include src/common/runtime/subdir.mk
-include src/common/modelbase/subdir.mk
-include src/common/messaging/subdir.mk
-include src/common/helpers/subdir.mk
-include src/common/etUnit/subdir.mk
-include src/common/debugging/subdir.mk
-include src/common/base/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: liborg.eclipse.etrice.runtime.c.a

# Tool invocations
liborg.eclipse.etrice.runtime.c.a: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Archiver'
	ar -r  "liborg.eclipse.etrice.runtime.c.a" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ARCHIVES) liborg.eclipse.etrice.runtime.c.a
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
