################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_flexbus.c \
../drivers/fsl_flexio.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpadc.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpit.c \
../drivers/fsl_lpspi.c \
../drivers/fsl_lptmr.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_msmc.c \
../drivers/fsl_mu.c \
../drivers/fsl_tpm.c \
../drivers/fsl_usdhc.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_flexbus.d \
./drivers/fsl_flexio.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpadc.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpit.d \
./drivers/fsl_lpspi.d \
./drivers/fsl_lptmr.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_msmc.d \
./drivers/fsl_mu.d \
./drivers/fsl_tpm.d \
./drivers/fsl_usdhc.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_flexbus.o \
./drivers/fsl_flexio.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpadc.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpit.o \
./drivers/fsl_lpspi.o \
./drivers/fsl_lptmr.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_msmc.o \
./drivers/fsl_mu.o \
./drivers/fsl_tpm.o \
./drivers/fsl_usdhc.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_K32L3A60VPJ1A -DCPU_K32L3A60VPJ1A_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__MULTICORE_MASTER -D__MULTICORE_MASTER_SLAVE_M0SLAVE -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/freertos/freertos-kernel/portable/GCC/ARM_CM4F" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/fatfs/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/fatfs/source/fsl_sd_disk" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/host" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/inc" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/fatfs/source/fsl_ram_disk" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/osa" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include/platform/k32l3a6" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include/environment/bm" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/rpmsg_lite/include/environment/freertos" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/component/osa" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/sdmmc/template/usdhc" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A60_MASTER/mcmgr" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dmamux.d ./drivers/fsl_dmamux.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_flexbus.d ./drivers/fsl_flexbus.o ./drivers/fsl_flexio.d ./drivers/fsl_flexio.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpadc.d ./drivers/fsl_lpadc.o ./drivers/fsl_lpi2c.d ./drivers/fsl_lpi2c.o ./drivers/fsl_lpit.d ./drivers/fsl_lpit.o ./drivers/fsl_lpspi.d ./drivers/fsl_lpspi.o ./drivers/fsl_lptmr.d ./drivers/fsl_lptmr.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_msmc.d ./drivers/fsl_msmc.o ./drivers/fsl_mu.d ./drivers/fsl_mu.o ./drivers/fsl_tpm.d ./drivers/fsl_tpm.o ./drivers/fsl_usdhc.d ./drivers/fsl_usdhc.o

.PHONY: clean-drivers

