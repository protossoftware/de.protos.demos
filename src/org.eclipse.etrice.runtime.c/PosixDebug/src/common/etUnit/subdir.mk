################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common/etUnit/etUnit.c 

OBJS += \
./src/common/etUnit/etUnit.o 

C_DEPS += \
./src/common/etUnit/etUnit.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/etUnit/%.o: ../src/common/etUnit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\platforms\MT_POSIX_GENERIC_GCC" -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\config" -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


