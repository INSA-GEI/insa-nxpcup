################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/drivers_perso/Car_control.cpp \
../source/drivers_perso/Debug.cpp \
../source/drivers_perso/Encoder.cpp \
../source/drivers_perso/FreescaleIAP.cpp \
../source/drivers_perso/ImageProcessing.cpp \
../source/drivers_perso/Interrupt.cpp \
../source/drivers_perso/Motor.cpp \
../source/drivers_perso/Movement.cpp \
../source/drivers_perso/servo.cpp 

OBJS += \
./source/drivers_perso/Car_control.o \
./source/drivers_perso/Debug.o \
./source/drivers_perso/Encoder.o \
./source/drivers_perso/FreescaleIAP.o \
./source/drivers_perso/ImageProcessing.o \
./source/drivers_perso/Interrupt.o \
./source/drivers_perso/Motor.o \
./source/drivers_perso/Movement.o \
./source/drivers_perso/servo.o 

CPP_DEPS += \
./source/drivers_perso/Car_control.d \
./source/drivers_perso/Debug.d \
./source/drivers_perso/Encoder.d \
./source/drivers_perso/FreescaleIAP.d \
./source/drivers_perso/ImageProcessing.d \
./source/drivers_perso/Interrupt.d \
./source/drivers_perso/Motor.d \
./source/drivers_perso/Movement.d \
./source/drivers_perso/servo.d 


# Each subdirectory must supply rules for building sources it contributes
source/drivers_perso/%.o: ../source/drivers_perso/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\drivers" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\utilities" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\CMSIS" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\board" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\source" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\startup" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\CMSIS" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\drivers" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\utilities" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


