################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Evolvables/Evolvable.cpp 

OBJS += \
./src/Evolvables/Evolvable.o 

CPP_DEPS += \
./src/Evolvables/Evolvable.d 


# Each subdirectory must supply rules for building sources it contributes
src/Evolvables/%.o: ../src/Evolvables/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


