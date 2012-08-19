################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp \
../src/parser.cpp \
../src/tweet.cpp \
../src/twitter.cpp 

OBJS += \
./src/main.o \
./src/parser.o \
./src/tweet.o \
./src/twitter.o 

CPP_DEPS += \
./src/main.d \
./src/parser.d \
./src/tweet.d \
./src/twitter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


