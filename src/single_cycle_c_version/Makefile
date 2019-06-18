SOURCE	:= Main.c ../single_cycle/Config.cpp 
CC	:= g++
FLAGS	:= -O3 -std=c++14 -w
TARGET	:= RVSim

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm $(TARGET)
