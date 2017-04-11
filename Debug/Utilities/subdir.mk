################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utilities/GenericWeakKey.cpp \
../Utilities/TypeNum.cpp 

OBJS += \
./Utilities/GenericWeakKey.o \
./Utilities/TypeNum.o 

CPP_DEPS += \
./Utilities/GenericWeakKey.d \
./Utilities/TypeNum.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -std=c++1y -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


