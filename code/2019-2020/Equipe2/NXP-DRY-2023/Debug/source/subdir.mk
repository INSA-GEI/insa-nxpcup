################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/NXP-DRY-2023.cpp \
../source/cpp_config.cpp 

C_SRCS += \
../source/mtb.c \
../source/semihost_hardfault.c 

CPP_DEPS += \
./source/NXP-DRY-2023.d \
./source/cpp_config.d 

C_DEPS += \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/NXP-DRY-2023.o \
./source/cpp_config.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/application" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/application" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/NXP-DRY-2023.d ./source/NXP-DRY-2023.o ./source/cpp_config.d ./source/cpp_config.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

