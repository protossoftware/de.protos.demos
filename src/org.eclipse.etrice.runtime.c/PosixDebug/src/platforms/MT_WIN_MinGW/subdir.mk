################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/platforms/MT_WIN_MinGW/etLogger.c \
../src/platforms/MT_WIN_MinGW/etMutex.c \
../src/platforms/MT_WIN_MinGW/etPlatformLifecycle.c \
../src/platforms/MT_WIN_MinGW/etSema.c \
../src/platforms/MT_WIN_MinGW/etTcpSockets.c \
../src/platforms/MT_WIN_MinGW/etThread.c \
../src/platforms/MT_WIN_MinGW/etTime.c \
../src/platforms/MT_WIN_MinGW/etTimer.c 

OBJS += \
./src/platforms/MT_WIN_MinGW/etLogger.o \
./src/platforms/MT_WIN_MinGW/etMutex.o \
./src/platforms/MT_WIN_MinGW/etPlatformLifecycle.o \
./src/platforms/MT_WIN_MinGW/etSema.o \
./src/platforms/MT_WIN_MinGW/etTcpSockets.o \
./src/platforms/MT_WIN_MinGW/etThread.o \
./src/platforms/MT_WIN_MinGW/etTime.o \
./src/platforms/MT_WIN_MinGW/etTimer.o 

C_DEPS += \
./src/platforms/MT_WIN_MinGW/etLogger.d \
./src/platforms/MT_WIN_MinGW/etMutex.d \
./src/platforms/MT_WIN_MinGW/etPlatformLifecycle.d \
./src/platforms/MT_WIN_MinGW/etSema.d \
./src/platforms/MT_WIN_MinGW/etTcpSockets.d \
./src/platforms/MT_WIN_MinGW/etThread.d \
./src/platforms/MT_WIN_MinGW/etTime.d \
./src/platforms/MT_WIN_MinGW/etTimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/platforms/MT_WIN_MinGW/%.o: ../src/platforms/MT_WIN_MinGW/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\platforms\MT_POSIX_GENERIC_GCC" -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\config" -I"C:\entw\projects\eTrice\workspaces\eTrice-rt\org.eclipse.etrice.runtime.c\src\common" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


