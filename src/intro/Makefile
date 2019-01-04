SOURCE  := Main.cpp Core.cpp
CC      := g++
FLAGS   := -O3 -std=c++11 -w
TARGET  := LoadSim

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm $(TARGET)
