################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rpmsg_lite/rpmsg_lite/rpmsg_lite.c \
../rpmsg_lite/rpmsg_lite/rpmsg_ns.c \
../rpmsg_lite/rpmsg_lite/rpmsg_queue.c 

C_DEPS += \
./rpmsg_lite/rpmsg_lite/rpmsg_lite.d \
./rpmsg_lite/rpmsg_lite/rpmsg_ns.d \
./rpmsg_lite/rpmsg_lite/rpmsg_queue.d 

OBJS += \
./rpmsg_lite/rpmsg_lite/rpmsg_lite.o \
./rpmsg_lite/rpmsg_lite/rpmsg_ns.o \
./rpmsg_lite/rpmsg_lite/rpmsg_queue.o 


# Each subdirectory must supply rules for building sources it contributes
rpmsg_lite/rpmsg_lite/%.o: ../rpmsg_lite/rpmsg_lite/%.c rpmsg_lite/rpmsg_lite/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_K32L3A60VPJ1A -DCPU_K32L3A60VPJ1A_cm0plus -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -D__MULTICORE_M0SLAVE -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/portable/GCC/ARM_CM0" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS_driver" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/sensors" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/accel" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/platform/k32l3a6" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/environment/bm" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/environment/freertos" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/mcmgr" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/portable/GCC/ARM_CM0" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS_driver" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/sensors" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/accel" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-rpmsg_lite-2f-rpmsg_lite

clean-rpmsg_lite-2f-rpmsg_lite:
	-$(RM) ./rpmsg_lite/rpmsg_lite/rpmsg_lite.d ./rpmsg_lite/rpmsg_lite/rpmsg_lite.o ./rpmsg_lite/rpmsg_lite/rpmsg_ns.d ./rpmsg_lite/rpmsg_lite/rpmsg_ns.o ./rpmsg_lite/rpmsg_lite/rpmsg_queue.d ./rpmsg_lite/rpmsg_lite/rpmsg_queue.o

.PHONY: clean-rpmsg_lite-2f-rpmsg_lite

