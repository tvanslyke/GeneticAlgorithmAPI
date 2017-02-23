################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Evolution/NewGenerationPolicies/NewGenerationPolicy.cpp 

OBJS += \
./Evolution/NewGenerationPolicies/NewGenerationPolicy.o 

CPP_DEPS += \
./Evolution/NewGenerationPolicies/NewGenerationPolicy.d 


# Each subdirectory must supply rules for building sources it contributes
Evolution/NewGenerationPolicies/%.o: ../Evolution/NewGenerationPolicies/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -std=c++11 -pg -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


