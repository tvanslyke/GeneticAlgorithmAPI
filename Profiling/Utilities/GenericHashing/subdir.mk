################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utilities/GenericHashing/GenericHashing.cpp \
../Utilities/GenericHashing/GenericStrongKey.cpp \
../Utilities/GenericHashing/GenericWeakKey.cpp 

OBJS += \
./Utilities/GenericHashing/GenericHashing.o \
./Utilities/GenericHashing/GenericStrongKey.o \
./Utilities/GenericHashing/GenericWeakKey.o 

CPP_DEPS += \
./Utilities/GenericHashing/GenericHashing.d \
./Utilities/GenericHashing/GenericStrongKey.d \
./Utilities/GenericHashing/GenericWeakKey.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/GenericHashing/%.o: ../Utilities/GenericHashing/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -std=c++11 -pg -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


