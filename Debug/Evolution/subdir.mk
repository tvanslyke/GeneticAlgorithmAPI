################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Evolution/Evolvable.cpp 

OBJS += \
./Evolution/Evolvable.o 

CPP_DEPS += \
./Evolution/Evolvable.d 


# Each subdirectory must supply rules for building sources it contributes
Evolution/%.o: ../Evolution/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -std=c++11  -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


