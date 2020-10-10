HEADER = src/headers/handle-input.hpp src/headers/distances.hpp
SOURCE =  src/main.cpp src/modules/manhattan-distance.cpp src/modules/handle-input.cpp src/modules/read-file.cpp
OBJS = main.o manhattan-distance.o handle-input.o read-file.o
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

clean:
	rm -f $(OBJS) $(OUT)