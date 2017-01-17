################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Misc/StringTable.cpp \
../src/Misc/StringTableEntry.cpp 

OBJS += \
./src/Misc/StringTable.o \
./src/Misc/StringTableEntry.o 

CPP_DEPS += \
./src/Misc/StringTable.d \
./src/Misc/StringTableEntry.d 


# Each subdirectory must supply rules for building sources it contributes
src/Misc/%.o: ../src/Misc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


