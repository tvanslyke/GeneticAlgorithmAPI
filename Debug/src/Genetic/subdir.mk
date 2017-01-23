################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Genetic/Chromosome.cpp \
../src/Genetic/ChromosomeBuilder.cpp \
../src/Genetic/Gene.cpp \
../src/Genetic/crossover.cpp 

OBJS += \
./src/Genetic/Chromosome.o \
./src/Genetic/ChromosomeBuilder.o \
./src/Genetic/Gene.o \
./src/Genetic/crossover.o 

CPP_DEPS += \
./src/Genetic/Chromosome.d \
./src/Genetic/ChromosomeBuilder.d \
./src/Genetic/Gene.d \
./src/Genetic/crossover.d 


# Each subdirectory must supply rules for building sources it contributes
src/Genetic/%.o: ../src/Genetic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


