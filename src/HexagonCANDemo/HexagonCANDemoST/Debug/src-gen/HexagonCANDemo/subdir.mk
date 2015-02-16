################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/data/workspaces/github/de.protos.demos/src/HexagonCANDemo/etrice.HexagonCANDemo.demo/src-gen-st/HexagonCANDemo/nodeRef1_main.c \
C:/data/workspaces/github/de.protos.demos/src/HexagonCANDemo/etrice.HexagonCANDemo.demo/src-gen-st/HexagonCANDemo/nodeRef1_main_Runner.c 

OBJS += \
./src-gen/HexagonCANDemo/nodeRef1_main.o \
./src-gen/HexagonCANDemo/nodeRef1_main_Runner.o 

C_DEPS += \
./src-gen/HexagonCANDemo/nodeRef1_main.d \
./src-gen/HexagonCANDemo/nodeRef1_main_Runner.d 


# Each subdirectory must supply rules for building sources it contributes
src-gen/HexagonCANDemo/nodeRef1_main.o: C:/data/workspaces/github/de.protos.demos/src/HexagonCANDemo/etrice.HexagonCANDemo.demo/src-gen-st/HexagonCANDemo/nodeRef1_main.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=4503002 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.HexagonCANDemo.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\platforms\ST_XMC4500_Dave3_Hexagon" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC4500_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST\Dave\Generated\inc\MOTORLIBS" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST\Dave\Generated\inc\DAVESupport" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST\Dave\Generated\inc\LIBS" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/HexagonCANDemo/nodeRef1_main_Runner.o: C:/data/workspaces/github/de.protos.demos/src/HexagonCANDemo/etrice.HexagonCANDemo.demo/src-gen-st/HexagonCANDemo/nodeRef1_main_Runner.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=4503002 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.HexagonCANDemo.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\etrice.runtime.c\etRuntime\src\platforms\ST_XMC4500_Dave3_Hexagon" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC4500_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST\Dave\Generated\inc\MOTORLIBS" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST\Dave\Generated\inc\DAVESupport" -I"C:\data\workspaces\github\de.protos.demos\src\HexagonCANDemo\HexagonCANDemoST\Dave\Generated\inc\LIBS" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


