################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/007spi_rxonly_arduino.c 

OBJS += \
./Src/007spi_rxonly_arduino.o 

C_DEPS += \
./Src/007spi_rxonly_arduino.d 


# Each subdirectory must supply rules for building sources it contributes
Src/007spi_rxonly_arduino.o: ../Src/007spi_rxonly_arduino.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -c -I"E:/Knowledge/Stm32f407xx Discovery/workspace/stm32f4xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/007spi_rxonly_arduino.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

