################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../User/Poly.cpp \
../User/driver.cpp \
../User/object.cpp \
../User/video.cpp 

OBJS += \
./User/Poly.o \
./User/driver.o \
./User/object.o \
./User/video.o 

CPP_DEPS += \
./User/Poly.d \
./User/driver.d \
./User/object.d \
./User/video.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o User/%.su: ../User/%.cpp User/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/Poly.d ./User/Poly.o ./User/Poly.su ./User/driver.d ./User/driver.o ./User/driver.su ./User/object.d ./User/object.o ./User/object.su ./User/video.d ./User/video.o ./User/video.su

.PHONY: clean-User

