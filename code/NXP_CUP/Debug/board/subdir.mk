################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\drivers" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\utilities" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\CMSIS" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\board" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\source" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\startup" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\CMSIS" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\drivers" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\utilities" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


