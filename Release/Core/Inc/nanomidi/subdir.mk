################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/nanomidi/msgprint.c \
../Core/Inc/nanomidi/nanomidi_decoder.c \
../Core/Inc/nanomidi/nanomidi_decoder_usb.c \
../Core/Inc/nanomidi/nanomidi_encoder.c \
../Core/Inc/nanomidi/nanomidi_encoder_usb.c \
../Core/Inc/nanomidi/nanomidi_stream.c 

C_DEPS += \
./Core/Inc/nanomidi/msgprint.d \
./Core/Inc/nanomidi/nanomidi_decoder.d \
./Core/Inc/nanomidi/nanomidi_decoder_usb.d \
./Core/Inc/nanomidi/nanomidi_encoder.d \
./Core/Inc/nanomidi/nanomidi_encoder_usb.d \
./Core/Inc/nanomidi/nanomidi_stream.d 

OBJS += \
./Core/Inc/nanomidi/msgprint.o \
./Core/Inc/nanomidi/nanomidi_decoder.o \
./Core/Inc/nanomidi/nanomidi_decoder_usb.o \
./Core/Inc/nanomidi/nanomidi_encoder.o \
./Core/Inc/nanomidi/nanomidi_encoder_usb.o \
./Core/Inc/nanomidi/nanomidi_stream.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/nanomidi/%.o Core/Inc/nanomidi/%.su Core/Inc/nanomidi/%.cyclo: ../Core/Inc/nanomidi/%.c Core/Inc/nanomidi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-nanomidi

clean-Core-2f-Inc-2f-nanomidi:
	-$(RM) ./Core/Inc/nanomidi/msgprint.cyclo ./Core/Inc/nanomidi/msgprint.d ./Core/Inc/nanomidi/msgprint.o ./Core/Inc/nanomidi/msgprint.su ./Core/Inc/nanomidi/nanomidi_decoder.cyclo ./Core/Inc/nanomidi/nanomidi_decoder.d ./Core/Inc/nanomidi/nanomidi_decoder.o ./Core/Inc/nanomidi/nanomidi_decoder.su ./Core/Inc/nanomidi/nanomidi_decoder_usb.cyclo ./Core/Inc/nanomidi/nanomidi_decoder_usb.d ./Core/Inc/nanomidi/nanomidi_decoder_usb.o ./Core/Inc/nanomidi/nanomidi_decoder_usb.su ./Core/Inc/nanomidi/nanomidi_encoder.cyclo ./Core/Inc/nanomidi/nanomidi_encoder.d ./Core/Inc/nanomidi/nanomidi_encoder.o ./Core/Inc/nanomidi/nanomidi_encoder.su ./Core/Inc/nanomidi/nanomidi_encoder_usb.cyclo ./Core/Inc/nanomidi/nanomidi_encoder_usb.d ./Core/Inc/nanomidi/nanomidi_encoder_usb.o ./Core/Inc/nanomidi/nanomidi_encoder_usb.su ./Core/Inc/nanomidi/nanomidi_stream.cyclo ./Core/Inc/nanomidi/nanomidi_stream.d ./Core/Inc/nanomidi/nanomidi_stream.o ./Core/Inc/nanomidi/nanomidi_stream.su

.PHONY: clean-Core-2f-Inc-2f-nanomidi

