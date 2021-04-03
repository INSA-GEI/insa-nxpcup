################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_dac.c \
../drivers/fsl_dma.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_i2c_dma.c \
../drivers/fsl_lpsci.c \
../drivers/fsl_lpsci_dma.c \
../drivers/fsl_lptmr.c \
../drivers/fsl_pit.c \
../drivers/fsl_pmc.c \
../drivers/fsl_rcm.c \
../drivers/fsl_rtc.c \
../drivers/fsl_sim.c \
../drivers/fsl_smc.c \
../drivers/fsl_spi.c \
../drivers/fsl_tpm.c \
../drivers/fsl_uart.c \
../drivers/fsl_uart_dma.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dac.o \
./drivers/fsl_dma.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_i2c_dma.o \
./drivers/fsl_lpsci.o \
./drivers/fsl_lpsci_dma.o \
./drivers/fsl_lptmr.o \
./drivers/fsl_pit.o \
./drivers/fsl_pmc.o \
./drivers/fsl_rcm.o \
./drivers/fsl_rtc.o \
./drivers/fsl_sim.o \
./drivers/fsl_smc.o \
./drivers/fsl_spi.o \
./drivers/fsl_tpm.o \
./drivers/fsl_uart.o \
./drivers/fsl_uart_dma.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dac.d \
./drivers/fsl_dma.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_i2c_dma.d \
./drivers/fsl_lpsci.d \
./drivers/fsl_lpsci_dma.d \
./drivers/fsl_lptmr.d \
./drivers/fsl_pit.d \
./drivers/fsl_pmc.d \
./drivers/fsl_rcm.d \
./drivers/fsl_rtc.d \
./drivers/fsl_sim.d \
./drivers/fsl_smc.d \
./drivers/fsl_spi.d \
./drivers/fsl_tpm.d \
./drivers/fsl_uart.d \
./drivers/fsl_uart_dma.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\drivers" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\utilities" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\CMSIS" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\board" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\source" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\startup" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\CMSIS" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\drivers" -I"C:\Users\rapha\Desktop\NXP_CUP\GIT\MCUxpresso\NXP_CUP\utilities" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


