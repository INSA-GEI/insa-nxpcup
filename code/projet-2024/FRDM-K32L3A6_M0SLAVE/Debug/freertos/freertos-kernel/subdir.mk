################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos-kernel/croutine.c \
../freertos/freertos-kernel/event_groups.c \
../freertos/freertos-kernel/list.c \
../freertos/freertos-kernel/queue.c \
../freertos/freertos-kernel/stream_buffer.c \
../freertos/freertos-kernel/tasks.c \
../freertos/freertos-kernel/timers.c 

C_DEPS += \
./freertos/freertos-kernel/croutine.d \
./freertos/freertos-kernel/event_groups.d \
./freertos/freertos-kernel/list.d \
./freertos/freertos-kernel/queue.d \
./freertos/freertos-kernel/stream_buffer.d \
./freertos/freertos-kernel/tasks.d \
./freertos/freertos-kernel/timers.d 

OBJS += \
./freertos/freertos-kernel/croutine.o \
./freertos/freertos-kernel/event_groups.o \
./freertos/freertos-kernel/list.o \
./freertos/freertos-kernel/queue.o \
./freertos/freertos-kernel/stream_buffer.o \
./freertos/freertos-kernel/tasks.o \
./freertos/freertos-kernel/timers.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos-kernel/%.o: ../freertos/freertos-kernel/%.c freertos/freertos-kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_K32L3A60VPJ1A -DCPU_K32L3A60VPJ1A_cm0plus -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -D__MULTICORE_M0SLAVE -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/portable/GCC/ARM_CM0" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS_driver" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/sensors" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/accel" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/startup" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/platform/k32l3a6" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/environment/bm" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/rpmsg_lite/include/environment/freertos" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/mcmgr" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/board" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/source" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/include" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/freertos/freertos-kernel/portable/GCC/ARM_CM0" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/drivers" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS_driver" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/CMSIS" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/device" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/serial_manager" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/utilities" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/uart" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/sensors" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/accel" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/component/lists" -I"/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-freertos-2d-kernel

clean-freertos-2f-freertos-2d-kernel:
	-$(RM) ./freertos/freertos-kernel/croutine.d ./freertos/freertos-kernel/croutine.o ./freertos/freertos-kernel/event_groups.d ./freertos/freertos-kernel/event_groups.o ./freertos/freertos-kernel/list.d ./freertos/freertos-kernel/list.o ./freertos/freertos-kernel/queue.d ./freertos/freertos-kernel/queue.o ./freertos/freertos-kernel/stream_buffer.d ./freertos/freertos-kernel/stream_buffer.o ./freertos/freertos-kernel/tasks.d ./freertos/freertos-kernel/tasks.o ./freertos/freertos-kernel/timers.d ./freertos/freertos-kernel/timers.o

.PHONY: clean-freertos-2f-freertos-2d-kernel

