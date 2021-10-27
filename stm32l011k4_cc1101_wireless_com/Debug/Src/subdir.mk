################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/cc1101.c \
../Src/gpio.c \
../Src/init_system.c \
../Src/main.c \
../Src/nvic.c \
../Src/spi.c \
../Src/system_stm32l0xx.c \
../Src/timers.c 

OBJS += \
./Src/cc1101.o \
./Src/gpio.o \
./Src/init_system.o \
./Src/main.o \
./Src/nvic.o \
./Src/spi.o \
./Src/system_stm32l0xx.o \
./Src/timers.o 

C_DEPS += \
./Src/cc1101.d \
./Src/gpio.d \
./Src/init_system.d \
./Src/main.d \
./Src/nvic.d \
./Src/spi.d \
./Src/system_stm32l0xx.d \
./Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32L011K4Tx -DSTM32L0 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

