################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/System_LibcStubs.c 

OBJS += \
./Lib/System_LibcStubs.o 

C_DEPS += \
./Lib/System_LibcStubs.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o: ../Lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


