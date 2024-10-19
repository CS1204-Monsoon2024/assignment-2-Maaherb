CXX = g++
CXXFLAGS = -Wall -g -std=c++11

TARGET = main.out

all: $(TARGET)

$(TARGET): main.o HashTable.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o HashTable.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

HashTable.o: HashTable.cpp
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

clean:
	rm -f *.o $(TARGET)
