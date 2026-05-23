################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpsci.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpsci.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpsci.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/2019-2020/Equipe2/NXP-DRY-2023/application" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_flash.d ./drivers/fsl_flash.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpsci.d ./drivers/fsl_lpsci.o ./drivers/fsl_smc.d ./drivers/fsl_smc.o ./drivers/fsl_uart.d ./drivers/fsl_uart.o

.PHONY: clean-drivers

