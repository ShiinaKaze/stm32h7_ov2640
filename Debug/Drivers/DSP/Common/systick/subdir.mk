################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Common/systick/systick.c 

OBJS += \
./Drivers/DSP/Common/systick/systick.o 

C_DEPS += \
./Drivers/DSP/Common/systick/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Common/systick/%.o Drivers/DSP/Common/systick/%.su Drivers/DSP/Common/systick/%.cyclo: ../Drivers/DSP/Common/systick/%.c Drivers/DSP/Common/systick/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP/Common/systick -I../Drivers/DSP/Components/ov2640 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Common-2f-systick

clean-Drivers-2f-DSP-2f-Common-2f-systick:
	-$(RM) ./Drivers/DSP/Common/systick/systick.cyclo ./Drivers/DSP/Common/systick/systick.d ./Drivers/DSP/Common/systick/systick.o ./Drivers/DSP/Common/systick/systick.su

.PHONY: clean-Drivers-2f-DSP-2f-Common-2f-systick

