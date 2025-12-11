################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../startup/startup_mkl25z4.cpp 

CPP_DEPS += \
./startup/startup_mkl25z4.d 

OBJS += \
./startup/startup_mkl25z4.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.cpp startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/application" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mkl25z4.d ./startup/startup_mkl25z4.o

.PHONY: clean-startup

