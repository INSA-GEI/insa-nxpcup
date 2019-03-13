################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/camera.c" \
"../Sources/main.c" \
"../Sources/movement.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/camera.c \
../Sources/main.c \
../Sources/movement.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/camera.o \
./Sources/main.o \
./Sources/movement.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/camera.d \
./Sources/main.d \
./Sources/movement.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/camera.o" \
"./Sources/main.o" \
"./Sources/movement.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/camera.d" \
"./Sources/main.d" \
"./Sources/movement.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/camera.o \
./Sources/main.o \
./Sources/movement.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/camera.o: ../Sources/camera.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/camera.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/camera.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/movement.o: ../Sources/movement.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/movement.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/movement.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


