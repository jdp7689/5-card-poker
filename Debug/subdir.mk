################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CS404_HW8.cpp \
../Card.cpp \
../ComputerPlayer.cpp \
../Deck.cpp \
../HumanPlayer.cpp \
../Player.cpp \
../PokerGame.cpp \
../PokerHand.cpp \
../PokerRound.cpp 

OBJS += \
./CS404_HW8.o \
./Card.o \
./ComputerPlayer.o \
./Deck.o \
./HumanPlayer.o \
./Player.o \
./PokerGame.o \
./PokerHand.o \
./PokerRound.o 

CPP_DEPS += \
./CS404_HW8.d \
./Card.d \
./ComputerPlayer.d \
./Deck.d \
./HumanPlayer.d \
./Player.d \
./PokerGame.d \
./PokerHand.d \
./PokerRound.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


