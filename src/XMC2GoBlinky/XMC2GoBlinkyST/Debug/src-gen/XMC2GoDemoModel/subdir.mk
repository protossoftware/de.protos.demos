################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/ADimmer.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/MrPing.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/MrPong.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/PingPongData.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/PingPongProtocol.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/PingPongTop.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef.c \
C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef_Runner.c 

OBJS += \
./src-gen/XMC2GoDemoModel/ADimmer.o \
./src-gen/XMC2GoDemoModel/MrPing.o \
./src-gen/XMC2GoDemoModel/MrPong.o \
./src-gen/XMC2GoDemoModel/PingPongData.o \
./src-gen/XMC2GoDemoModel/PingPongProtocol.o \
./src-gen/XMC2GoDemoModel/PingPongTop.o \
./src-gen/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef.o \
./src-gen/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef_Runner.o 

C_DEPS += \
./src-gen/XMC2GoDemoModel/ADimmer.d \
./src-gen/XMC2GoDemoModel/MrPing.d \
./src-gen/XMC2GoDemoModel/MrPong.d \
./src-gen/XMC2GoDemoModel/PingPongData.d \
./src-gen/XMC2GoDemoModel/PingPongProtocol.d \
./src-gen/XMC2GoDemoModel/PingPongTop.d \
./src-gen/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef.d \
./src-gen/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef_Runner.d 


# Each subdirectory must supply rules for building sources it contributes
src-gen/XMC2GoDemoModel/ADimmer.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/ADimmer.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/MrPing.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/MrPing.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/MrPong.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/MrPong.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/PingPongData.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/PingPongData.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/PingPongProtocol.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/PingPongProtocol.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/PingPongTop.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/PingPongTop.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src-gen/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef_Runner.o: C:/data/workspaces/github/de.protos.demos/src/XMC2GoBlinky/etrice.XMC2GoBlinky.demo/src-gen-st/XMC2GoDemoModel/XMC2Go_PingPong_subSysRef_Runner.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"C:\DAVE-3.1.10\ARM-GCC/bin/arm-none-eabi-gcc" -DDAVE_CE -DUC_ID=11010010 -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.XMC2GoBlinky.demo\src-gen-st" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\common" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\config" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\etrice.runtime.c\eTriceRuntime\src\platforms\ST_XMC1100_Dave3_XMC2Go" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/Include" -I"C:\DAVE-3.1.10\ARM-GCC/arm-none-eabi/include" -I"C:\DAVE-3.1.10\eclipse\/../emWin/Start/GUI/inc" -I"C:\DAVE-3.1.10\eclipse\/../CMSIS/Infineon/XMC1100_series/Include" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\LIBS" -I"C:\data\workspaces\github\de.protos.demos\src\XMC2GoBlinky\XMC2GoBlinkyST\Dave\Generated\inc\DAVESupport" -O0 -ffunction-sections -Wall -std=gnu99 -mfloat-abi=soft -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


