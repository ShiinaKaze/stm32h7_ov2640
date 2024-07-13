################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Components/ov2640/ov2640.c \
../Drivers/DSP/Components/ov2640/ov2640_cfg.c \
../Drivers/DSP/Components/ov2640/sccb.c 

OBJS += \
./Drivers/DSP/Components/ov2640/ov2640.o \
./Drivers/DSP/Components/ov2640/ov2640_cfg.o \
./Drivers/DSP/Components/ov2640/sccb.o 

C_DEPS += \
./Drivers/DSP/Components/ov2640/ov2640.d \
./Drivers/DSP/Components/ov2640/ov2640_cfg.d \
./Drivers/DSP/Components/ov2640/sccb.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Components/ov2640/%.o Drivers/DSP/Components/ov2640/%.su Drivers/DSP/Components/ov2640/%.cyclo: ../Drivers/DSP/Components/ov2640/%.c Drivers/DSP/Components/ov2640/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/DSP/Common/systick -I../Drivers/DSP/Components/ov2640 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DSP-2f-Components-2f-ov2640

clean-Drivers-2f-DSP-2f-Components-2f-ov2640:
	-$(RM) ./Drivers/DSP/Components/ov2640/ov2640.cyclo ./Drivers/DSP/Components/ov2640/ov2640.d ./Drivers/DSP/Components/ov2640/ov2640.o ./Drivers/DSP/Components/ov2640/ov2640.su ./Drivers/DSP/Components/ov2640/ov2640_cfg.cyclo ./Drivers/DSP/Components/ov2640/ov2640_cfg.d ./Drivers/DSP/Components/ov2640/ov2640_cfg.o ./Drivers/DSP/Components/ov2640/ov2640_cfg.su ./Drivers/DSP/Components/ov2640/sccb.cyclo ./Drivers/DSP/Components/ov2640/sccb.d ./Drivers/DSP/Components/ov2640/sccb.o ./Drivers/DSP/Components/ov2640/sccb.su

.PHONY: clean-Drivers-2f-DSP-2f-Components-2f-ov2640

