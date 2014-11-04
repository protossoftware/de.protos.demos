################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common/debugging/etDataLogger.c \
../src/common/debugging/etMSCLogger.c 

OBJS += \
./src/common/debugging/etDataLogger.o \
./src/common/debugging/etMSCLogger.o 

C_DEPS += \
./src/common/debugging/etDataLogger.d \
./src/common/debugging/etMSCLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/debugging/%.o: ../src/common/debugging/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\platforms\MT_POSIX_GENERIC_GCC" -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\config" -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


