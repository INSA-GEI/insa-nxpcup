################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 6
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
FRDM_Blink_TriLED.elf \

EXECUTABLES_QUOTED += \
"FRDM_Blink_TriLED.elf" \

EXECUTABLES_OS_FORMAT += \
FRDM_Blink_TriLED.elf \

SECONDARY_SIZE += \
FRDM_Blink_TriLED.siz \

SECONDARY_SIZE_QUOTED += \
"FRDM_Blink_TriLED.siz" \

SECONDARY_SIZE_OS_FORMAT += \
FRDM_Blink_TriLED.siz \


# All Target
all: warning-messages explicit-dependencies FRDM_Blink_TriLED.elf secondary-outputs

# Tool invocations
FRDM_Blink_TriLED.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/MKL25Z128_flash.ld
	@echo 'Building target: $@'
	@echo 'Executing target #7 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"FRDM_Blink_TriLED.args" -o"FRDM_Blink_TriLED.elf"
	@echo 'Finished building target: $@'
	@echo ' '

FRDM_Blink_TriLED.siz: FRDM_Blink_TriLED.elf
	@echo 'Executing target #8 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Print Size'
	"$(ARMSourceryDirEnv)/arm-none-eabi-size"  --format=berkeley FRDM_Blink_TriLED.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*/*.o" "./*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(SECONDARY_SIZE_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*.d"  $(ProjDirPath)/FLASH/FRDM_Blink_TriLED.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/MKL25Z128_flash.ld FRDM_Blink_TriLED.elf 

warning-messages: 

