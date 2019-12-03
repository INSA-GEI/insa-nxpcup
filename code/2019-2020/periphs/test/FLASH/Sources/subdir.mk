################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Debug.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/Debug.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/Debug.o \
./Sources/main.o \
./Sources/sa_mtb.o \

OBJS_QUOTED += \
"./Sources/Debug.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS += \
./Sources/Debug.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_OS_FORMAT += \
./Sources/Debug.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS_QUOTED += \
"./Sources/Debug.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Debug.o: ../Sources/Debug.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Debug.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Debug.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


