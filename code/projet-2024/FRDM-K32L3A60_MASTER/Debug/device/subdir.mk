################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_K32L3A60_cm4.c 

C_DEPS += \
./device/system_K32L3A60_cm4.d 

OBJS += \
./device/system_K32L3A60_cm4.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_K32L3A60VPJ1A -DCPU_K32L3A60VPJ1A_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__MULTICORE_MASTER -D__MULTICORE_MASTER_SLAVE_M0SLAVE -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/freertos/freertos-kernel/portable/GCC/ARM_CM4F" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/fatfs/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/fatfs/source/fsl_sd_disk" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/host" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/inc" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/fatfs/source/fsl_ram_disk" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/osa" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include/platform/k32l3a6" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include/environment/bm" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include/environment/freertos" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/osa" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/template/usdhc" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/mcmgr" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_K32L3A60_cm4.d ./device/system_K32L3A60_cm4.o

.PHONY: clean-device

