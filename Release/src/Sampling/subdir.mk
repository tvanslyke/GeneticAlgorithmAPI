################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Sampling/FitnessProportionatePolicy.cpp \
../src/Sampling/SamplingPolicy.cpp \
../src/Sampling/sampling.cpp 

OBJS += \
./src/Sampling/FitnessProportionatePolicy.o \
./src/Sampling/SamplingPolicy.o \
./src/Sampling/sampling.o 

CPP_DEPS += \
./src/Sampling/FitnessProportionatePolicy.d \
./src/Sampling/SamplingPolicy.d \
./src/Sampling/sampling.d 


# Each subdirectory must supply rules for building sources it contributes
src/Sampling/%.o: ../src/Sampling/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


