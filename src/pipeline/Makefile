SOURCE	:= Main.cpp Config.cpp Assembler.cpp Instruction_Memory.cpp Core.cpp Stages.cpp Socket.cpp 
CC	:= g++
FLAGS	:= -O3 -std=c++14 -w
TARGET	:= RVSim

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm $(TARGET)
