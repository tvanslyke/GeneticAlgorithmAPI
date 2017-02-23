################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Evolution/Genetics/Mutation/Mutators/Mutator.cpp 

OBJS += \
./Evolution/Genetics/Mutation/Mutators/Mutator.o 

CPP_DEPS += \
./Evolution/Genetics/Mutation/Mutators/Mutator.d 


# Each subdirectory must supply rules for building sources it contributes
Evolution/Genetics/Mutation/Mutators/%.o: ../Evolution/Genetics/Mutation/Mutators/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -std=c++11 -pg -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


