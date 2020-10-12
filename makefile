HEADER = src/headers/handle-input.hpp src/headers/distances.hpp src/headers/manhattan-hashing.hpp src/headers/modulo.hpp src/headers/process.hpp
SOURCE =  src/main.cpp src/modules/manhattan-distance.cpp src/modules/handle-input.cpp src/modules/read-file.cpp src/modules/manhattan-hashing.cpp src/modules/modulo.cpp src/modules/process.cpp
OBJS = main.o manhattan-distance.o handle-input.o read-file.o manhattan-hashing.o modulo.o process.o
CXX = g++
FLAGS = -g -c -Wall
OUT = lsh

all: $(OUT)

lsh : $(OBJS)
	$(CXX) -g $(OBJS) -o $(OUT)

main.o : $(SOURCE) $(HEADER)
	$(CXX) $(FLAGS) $(SOURCE)

manhattan-distance.o : src/modules/manhattan-distance.cpp
	$(CXX) $(FLAGS) src/modules/manhattan-distance.cpp

handle-input.o : src/modules/handle-input.cpp
	$(CXX) $(FLAGS) src/modules/handle-input.cpp

read-file.o : src/modules/read-file.cpp
	$(CXX) $(FLAGS) src/modules/read-file.cpp

manhattan-hashing.o : src/modules/manhattan-hashing.cpp
	$(CXX) $(FLAGS) src/modules/manhattan-hashing.cpp

modulo.o : src/modules/modulo.cpp
	$(CXX) $(FLAGS) src/modules/modulo.cpp

process.o : src/modules/process.cpp
	$(CXX) $(FLAGS) src/modules/process.cpp

clean:
	rm -f $(OBJS) $(OUT)