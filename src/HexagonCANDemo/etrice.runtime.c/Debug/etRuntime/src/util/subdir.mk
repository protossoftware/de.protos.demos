################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../etRuntime/src/util/RandomGenerator.c 

OBJS += \
./etRuntime/src/util/RandomGenerator.o 

C_DEPS += \
./etRuntime/src/util/RandomGenerator.d 


# Each subdirectory must supply rules for building sources it contributes
etRuntime/src/util/%.o: ../etRuntime/src/util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DUC_ID=4503002 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\platforms\ST_XMC4500_Dave3_Hexagon" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC4500_series/Include" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


