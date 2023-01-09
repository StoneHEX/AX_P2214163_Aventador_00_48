################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/AppMain.c \
../Libraries/Irqs.c \
../Libraries/PowerStateMachine.c 

OBJS += \
./Libraries/AppMain.o \
./Libraries/Irqs.o \
./Libraries/PowerStateMachine.o 

C_DEPS += \
./Libraries/AppMain.d \
./Libraries/Irqs.d \
./Libraries/PowerStateMachine.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o Libraries/%.su: ../Libraries/%.c Libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Libraries -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/AppMain.d ./Libraries/AppMain.o ./Libraries/AppMain.su ./Libraries/Irqs.d ./Libraries/Irqs.o ./Libraries/Irqs.su ./Libraries/PowerStateMachine.d ./Libraries/PowerStateMachine.o ./Libraries/PowerStateMachine.su

.PHONY: clean-Libraries

