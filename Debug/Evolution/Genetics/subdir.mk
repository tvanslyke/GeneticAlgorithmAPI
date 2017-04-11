################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Evolution/Genetics/DynamicChromosome.cpp \
../Evolution/Genetics/Gene.cpp 

OBJS += \
./Evolution/Genetics/DynamicChromosome.o \
./Evolution/Genetics/Gene.o 

CPP_DEPS += \
./Evolution/Genetics/DynamicChromosome.d \
./Evolution/Genetics/Gene.d 


# Each subdirectory must supply rules for building sources it contributes
Evolution/Genetics/%.o: ../Evolution/Genetics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -std=c++1y -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


