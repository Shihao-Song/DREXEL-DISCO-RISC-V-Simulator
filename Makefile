SOURCE	:= Main.cpp Assembler.cpp Instruction_Memory.cpp 
CC	:= g++
FLAGS	:= -O3 -std=c++11 -w
TARGET	:= RVSim

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm $(TARGET)
