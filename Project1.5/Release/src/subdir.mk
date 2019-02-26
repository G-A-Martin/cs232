################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Project1.5.cpp 

OBJS += \
./src/Project1.5.o 

CPP_DEPS += \
./src/Project1.5.d 


# Each subdirectory must supply rules for building sources it contributes
src/Project1.5.o: ../src/Project1.5.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/Project1.5.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


