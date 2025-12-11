################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include sdmmc/template/usdhc/subdir.mk
-include sdmmc/src/subdir.mk
-include sdmmc/osa/subdir.mk
-include sdmmc/host/subdir.mk
-include rpmsg_lite/virtio/subdir.mk
-include rpmsg_lite/rpmsg_lite/porting/platform/k32l3a6/subdir.mk
-include rpmsg_lite/rpmsg_lite/porting/environment/subdir.mk
-include rpmsg_lite/rpmsg_lite/subdir.mk
-include rpmsg_lite/common/subdir.mk
-include mcmgr/subdir.mk
-include freertos/freertos-kernel/portable/MemMang/subdir.mk
-include freertos/freertos-kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos-kernel/subdir.mk
-include fatfs/source/fsl_sd_disk/subdir.mk
-include fatfs/source/fsl_ram_disk/subdir.mk
-include fatfs/source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/osa/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := FRDM-K32L3A60_MASTER
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: FRDM-K32L3A60_MASTER.axf

# Tool invocations
FRDM-K32L3A60_MASTER.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS) /home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/Debug/FRDM-K32L3A6_M0SLAVE.axf.o
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="FRDM-K32L3A60_MASTER.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T FRDM-K32L3A60_MASTER_Debug.ld -o "FRDM-K32L3A60_MASTER.axf" $(OBJS) $(USER_OBJS) $(LIBS) "/home/dimercur/Travail/git/insa-nxpcup/code/projet-2024/FRDM-K32L3A6_M0SLAVE/Debug/FRDM-K32L3A6_M0SLAVE.axf.o"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) FRDM-K32L3A60_MASTER.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "FRDM-K32L3A60_MASTER.axf"; # arm-none-eabi-objcopy -v -O binary "FRDM-K32L3A60_MASTER.axf" "FRDM-K32L3A60_MASTER.bin" ; # checksum -p K32L3A60xxx -d "FRDM-K32L3A60_MASTER.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
