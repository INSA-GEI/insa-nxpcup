################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../.metadata/.plugins/org.eclipse.cdt.make.core/specs.c" \

C_SRCS += \
../.metadata/.plugins/org.eclipse.cdt.make.core/specs.c \

OBJS += \
./.metadata/.plugins/org.eclipse.cdt.make.core/specs.o \

OBJS_QUOTED += \
"./.metadata/.plugins/org.eclipse.cdt.make.core/specs.o" \

C_DEPS += \
./.metadata/.plugins/org.eclipse.cdt.make.core/specs.d \

OBJS_OS_FORMAT += \
./.metadata/.plugins/org.eclipse.cdt.make.core/specs.o \

C_DEPS_QUOTED += \
"./.metadata/.plugins/org.eclipse.cdt.make.core/specs.d" \


# Each subdirectory must supply rules for building sources it contributes
.metadata/.plugins/org.eclipse.cdt.make.core/specs.o: ../.metadata/.plugins/org.eclipse.cdt.make.core/specs.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @".metadata/.plugins/org.eclipse.cdt.make.core/specs.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o".metadata/.plugins/org.eclipse.cdt.make.core/specs.o"
	@echo 'Finished building: $<'
	@echo ' '


