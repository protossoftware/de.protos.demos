################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../etRuntime/src/common/messaging/etMessage.c \
../etRuntime/src/common/messaging/etMessageQueue.c \
../etRuntime/src/common/messaging/etMessageService.c \
../etRuntime/src/common/messaging/etSystemProtocol.c 

OBJS += \
./etRuntime/src/common/messaging/etMessage.o \
./etRuntime/src/common/messaging/etMessageQueue.o \
./etRuntime/src/common/messaging/etMessageService.o \
./etRuntime/src/common/messaging/etSystemProtocol.o 

C_DEPS += \
./etRuntime/src/common/messaging/etMessage.d \
./etRuntime/src/common/messaging/etMessageQueue.d \
./etRuntime/src/common/messaging/etMessageService.d \
./etRuntime/src/common/messaging/etSystemProtocol.d 


# Each subdirectory must supply rules for building sources it contributes
etRuntime/src/common/messaging/%.o: ../etRuntime/src/common/messaging/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DUC_ID=4503002 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\platforms\ST_XMC4500_Dave3_Hexagon" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC4500_series/Include" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


