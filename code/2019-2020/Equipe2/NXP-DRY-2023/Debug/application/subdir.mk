################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../application/Encoder.cpp \
../application/FreescaleIAP.cpp \
../application/ImageProcessing.cpp \
../application/Movement.cpp \
../application/application.cpp 

C_SRCS += \
../application/Debug.c \
../application/Motor.c \
../application/servo.c 

CPP_DEPS += \
./application/Encoder.d \
./application/FreescaleIAP.d \
./application/ImageProcessing.d \
./application/Movement.d \
./application/application.d 

C_DEPS += \
./application/Debug.d \
./application/Motor.d \
./application/servo.d 

OBJS += \
./application/Debug.o \
./application/Encoder.o \
./application/FreescaleIAP.o \
./application/ImageProcessing.o \
./application/Motor.o \
./application/Movement.o \
./application/application.o \
./application/servo.o 


# Each subdirectory must supply rules for building sources it contributes
application/%.o: ../application/%.c application/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/application" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

application/%.o: ../application/%.cpp application/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/application" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-application

clean-application:
	-$(RM) ./application/Debug.d ./application/Debug.o ./application/Encoder.d ./application/Encoder.o ./application/FreescaleIAP.d ./application/FreescaleIAP.o ./application/ImageProcessing.d ./application/ImageProcessing.o ./application/Motor.d ./application/Motor.o ./application/Movement.d ./application/Movement.o ./application/application.d ./application/application.o ./application/servo.d ./application/servo.o

.PHONY: clean-application

