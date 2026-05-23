################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpadc.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpit.c \
../drivers/fsl_lpspi.c \
../drivers/fsl_lptmr.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_msmc.c \
../drivers/fsl_mu.c \
../drivers/fsl_tpm.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpadc.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpit.d \
./drivers/fsl_lpspi.d \
./drivers/fsl_lptmr.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_msmc.d \
./drivers/fsl_mu.d \
./drivers/fsl_tpm.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpadc.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpit.o \
./drivers/fsl_lpspi.o \
./drivers/fsl_lptmr.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_msmc.o \
./drivers/fsl_mu.o \
./drivers/fsl_tpm.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_K32L3A60VPJ1A -DCPU_K32L3A60VPJ1A_cm0plus -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -D__MULTICORE_M0SLAVE -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/portable/GCC/ARM_CM0" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS_driver" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/sensors" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/accel" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/platform/k32l3a6" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/environment/bm" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/environment/freertos" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/mcmgr" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/portable/GCC/ARM_CM0" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS_driver" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/sensors" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/accel" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dmamux.d ./drivers/fsl_dmamux.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpadc.d ./drivers/fsl_lpadc.o ./drivers/fsl_lpi2c.d ./drivers/fsl_lpi2c.o ./drivers/fsl_lpit.d ./drivers/fsl_lpit.o ./drivers/fsl_lpspi.d ./drivers/fsl_lpspi.o ./drivers/fsl_lptmr.d ./drivers/fsl_lptmr.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_msmc.d ./drivers/fsl_msmc.o ./drivers/fsl_mu.d ./drivers/fsl_mu.o ./drivers/fsl_tpm.d ./drivers/fsl_tpm.o

.PHONY: clean-drivers

