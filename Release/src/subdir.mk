################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Chromosome.cpp \
../src/Population.cpp \
../src/crossover.cpp \
../src/main.cpp 

OBJS += \
./src/Chromosome.o \
./src/Population.o \
./src/crossover.o \
./src/main.o 

CPP_DEPS += \
./src/Chromosome.d \
./src/Population.d \
./src/crossover.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


