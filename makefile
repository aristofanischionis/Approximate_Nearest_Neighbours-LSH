HEADER = src/headers/handle-input.hpp src/headers/distances.hpp src/headers/manhattan-hashing.hpp src/headers/modulo.hpp src/headers/hashtable.hpp src/headers/search.hpp
HEADERCUBE = src/headers/cube/handle-cube-input.hpp src/headers/cube/projection.hpp src/headers/manhattan-hashing.hpp src/headers/distances.hpp src/headers/modulo.hpp src/headers/search.hpp src/headers/hashtable.hpp
SOURCE =  src/lsh.cpp src/modules/manhattan-distance.cpp src/modules/handle-input.cpp src/modules/read-file.cpp src/modules/manhattan-hashing.cpp src/modules/modulo.cpp src/modules/hashtable.cpp src/modules/search.cpp
SOURCECUBE = src/cube.cpp src/modules/cube/handle-cube-input.cpp src/modules/cube/projection.cpp src/modules/manhattan-hashing.cpp src/modules/modulo.cpp src/modules/hashtable.cpp src/modules/search.cpp src/modules/manhattan-distance.cpp
OBJS = lsh.o manhattan-distance.o handle-input.o read-file.o manhattan-hashing.o modulo.o hashtable.o search.o
OBJCUBE = cube.o handle-cube-input.o projection.o manhattan-hashing.o modulo.o search.o hashtable.o manhattan-distance.o

CXX = g++
FLAGS = -std=c++11 -O3 -g -c -Wall
OUT = lsh cube

all: $(OUT)

lsh : $(OBJS)
	$(CXX) -g $(OBJS) -o lsh

cube : $(OBJCUBE)
	$(CXX) -g $(OBJCUBE) -o cube

lsh.o : $(SOURCE) $(HEADER)
	$(CXX) $(FLAGS) $(SOURCE)

cube.o : $(SOURCECUBE) $(HEADERCUBE)
	$(CXX) $(FLAGS) $(SOURCECUBE)

manhattan-distance.o : src/modules/manhattan-distance.cpp
	$(CXX) $(FLAGS) src/modules/manhattan-distance.cpp

handle-cube-input.o : src/modules/cube/handle-cube-input.cpp
	$(CXX) $(FLAGS) src/modules/cube/handle-cube-input.cpp

projection.o : src/modules/cube/projection.cpp
	$(CXX) $(FLAGS) src/modules/cube/projection.cpp

handle-input.o : src/modules/handle-input.cpp
	$(CXX) $(FLAGS) src/modules/handle-input.cpp

read-file.o : src/modules/read-file.cpp
	$(CXX) $(FLAGS) src/modules/read-file.cpp

manhattan-hashing.o : src/modules/manhattan-hashing.cpp
	$(CXX) $(FLAGS) src/modules/manhattan-hashing.cpp

modulo.o : src/modules/modulo.cpp
	$(CXX) $(FLAGS) src/modules/modulo.cpp

hashtable.o : src/modules/hashtable.cpp
	$(CXX) $(FLAGS) src/modules/hashtable.cpp

search.o : src/modules/search.cpp
	$(CXX) $(FLAGS) src/modules/search.cpp

clean:
	rm -f $(OBJS) $(OBJCUBE) $(OUT)