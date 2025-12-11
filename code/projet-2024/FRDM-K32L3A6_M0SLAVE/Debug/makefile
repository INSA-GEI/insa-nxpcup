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
-include rpmsg_lite/virtio/subdir.mk
-include rpmsg_lite/rpmsg_lite/porting/platform/k32l3a6/subdir.mk
-include rpmsg_lite/rpmsg_lite/porting/environment/subdir.mk
-include rpmsg_lite/rpmsg_lite/subdir.mk
-include rpmsg_lite/common/subdir.mk
-include mcmgr/subdir.mk
-include freertos/freertos-kernel/portable/MemMang/subdir.mk
-include freertos/freertos-kernel/portable/GCC/ARM_CM0/subdir.mk
-include freertos/freertos-kernel/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include accel/subdir.mk
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


BUILD_ARTIFACT_NAME := FRDM-K32L3A6_M0SLAVE
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: FRDM-K32L3A6_M0SLAVE.axf

# Tool invocations
FRDM-K32L3A6_M0SLAVE.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="FRDM-K32L3A6_M0SLAVE.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m0plus -mthumb -T FRDM-K32L3A6_M0SLAVE_Debug.ld -o "FRDM-K32L3A6_M0SLAVE.axf" $(OBJS) $(USER_OBJS) $(LIBS) && arm-none-eabi-objcopy --target elf32-littlearm --verbose --strip-all --remove-section=.ARM.attributes --redefine-sym __vectors_start__=__vectors_start___core_m0slave --keep-symbol __vectors_start___core_m0slave --redefine-sym _data=__start_data_core_m0slave --keep-symbol __start_data_core_m0slave --redefine-sym _edata=__end_data_core_m0slave --keep-symbol __end_data_core_m0slave --remove-section=".bss*" --remove-section=".noinit*" --rename-section .ARM.exidx=".core_m0slave.ARM.exidx" --rename-section .ARM.extab=".core_m0slave.ARM.extab" --rename-section .text=".core_m0slave" --rename-section .data=".core_m0slave.data" --rename-section .data_RAM2=".core_m0slave.data_RAM2" --rename-section .data_RAM3=".core_m0slave.data_RAM3" --rename-section .data_RAM4=".core_m0slave.data_RAM4" --rename-section .data_RAM5=".core_m0slave.data_RAM5" "FRDM-K32L3A6_M0SLAVE.axf" "FRDM-K32L3A6_M0SLAVE.axf.o" && mcux-fixelf "FRDM-K32L3A6_M0SLAVE.axf.o"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) FRDM-K32L3A6_M0SLAVE.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "FRDM-K32L3A6_M0SLAVE.axf"; # arm-none-eabi-objcopy -v -O binary "FRDM-K32L3A6_M0SLAVE.axf" "FRDM-K32L3A6_M0SLAVE.bin" ; # checksum -p K32L3A60xxx -d "FRDM-K32L3A6_M0SLAVE.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
