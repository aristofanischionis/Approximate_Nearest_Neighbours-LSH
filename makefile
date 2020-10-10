HEADER = src/headers/handle-input.hpp src/headers/distances.hpp
SOURCE =  src/main.cpp src/modules/manhattan-distance.cpp src/modules/handle-input.cpp
OBJS = main.o manhattan-distance.o handle-input.o
CXX = g++
FLAGS = -g -c -Wall
OUT = lsh

all: $(OUT)

lsh : $(OBJS)
	$(CXX) -g $(OBJS) -o $(OUT)

manhattan-distance.o : src/modules/manhattan-distance.cpp
	$(CXX) $(FLAGS) src/modules/manhattan-distance.cpp

handle-input.o : src/modules/handle-input.cpp
	$(CXX) $(FLAGS) src/modules/handle-input.cpp

main.o : $(SOURCE) $(HEADER)
	$(CXX) $(FLAGS) $(SOURCE)

clean:
	rm -f $(OBJS) $(OUT)