################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../startup/startup_mkl25z4.cpp 

OBJS += \
./startup/startup_mkl25z4.o 

CPP_DEPS += \
./startup/startup_mkl25z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

