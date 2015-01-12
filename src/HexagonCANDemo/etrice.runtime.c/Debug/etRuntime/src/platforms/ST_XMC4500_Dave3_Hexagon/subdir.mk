################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etLogger.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etMutex.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etPlatform.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etPlatformLifecycle.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etSema.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etThread.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etTime.c \
../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etTimer.c 

OBJS += \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etLogger.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etMutex.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etPlatform.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etPlatformLifecycle.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etSema.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etThread.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etTime.o \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etTimer.o 

C_DEPS += \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etLogger.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etMutex.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etPlatform.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etPlatformLifecycle.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etSema.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etThread.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etTime.d \
./etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/etTimer.d 


# Each subdirectory must supply rules for building sources it contributes
etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/%.o: ../etRuntime/src/platforms/ST_XMC4500_Dave3_Hexagon/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DUC_ID=4503002 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\platforms\ST_XMC4500_Dave3_Hexagon" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC4500_series/Include" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


