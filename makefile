LSH_HEADERS = src/headers/
LSH_MODULES = src/modules/

CUBE_PATH = src/headers/cube/
CUBE_MODULES = src/modules/cube/

COMMONOBJS = manhattan-hashing.o manhattan-distance.o modulo.o handle-input.o read-file.o hashtable.o

HEADER = $(LSH_HEADERS)handle-input.hpp $(LSH_HEADERS)distances.hpp $(LSH_HEADERS)manhattan-hashing.hpp $(LSH_HEADERS)modulo.hpp $(LSH_HEADERS)hashtable.hpp $(LSH_HEADERS)search.hpp $(LSH_HEADERS)common.hpp
SOURCE =  src/lsh.cpp $(LSH_MODULES)manhattan-distance.cpp $(LSH_MODULES)handle-input.cpp $(LSH_MODULES)read-file.cpp $(LSH_MODULES)manhattan-hashing.cpp $(LSH_MODULES)modulo.cpp $(LSH_MODULES)hashtable.cpp $(LSH_MODULES)search.cpp
OBJS = lsh.o search.o $(COMMONOBJS)

HEADERCUBE = $(CUBE_PATH)handle-cube-input.hpp $(CUBE_PATH)projection.hpp $(CUBE_PATH)read-cube-file.hpp $(LSH_HEADERS)common.hpp
SOURCECUBE = src/cube.cpp $(CUBE_MODULES)handle-cube-input.cpp $(CUBE_MODULES)read-cube-file.cpp $(CUBE_MODULES)projection.cpp
OBJCUBE = cube.o handle-cube-input.o projection.o read-cube-file.o $(COMMONOBJS)

OBJCLUSTER = cluster.o handle-cube-input.o projection.o read-cube-file.o search.o $(COMMONOBJS)

CXX = g++
FLAGS = -std=c++11 -O3 -g -c -Wall
OUT = lsh cube cluster

all: $(OUT)

# Executables
lsh : $(OBJS)
	$(CXX) -g $(OBJS) -o lsh

cube : $(OBJCUBE)
	$(CXX) -g $(OBJCUBE) -o cube

cluster : $(OBJCLUSTER)
	$(CXX) -g $(OBJCLUSTER) -o cluster

# Final object files
lsh.o : $(SOURCE) $(HEADER)
	$(CXX) $(FLAGS) $(SOURCE)

cube.o : $(SOURCECUBE) $(HEADERCUBE)
	$(CXX) $(FLAGS) $(SOURCECUBE)

# $(HEADER) $(CUBE_PATH)handle-cube-input.hpp $(CUBE_PATH)projection.hpp $(CUBE_PATH)read-cube-file.hpp
# $(HEADER) $(CUBE_PATH)handle-cube-input.hpp $(CUBE_PATH)projection.hpp $(CUBE_PATH)read-cube-file.hpp
cluster.o : src/cluster.cpp
	$(CXX) $(FLAGS) src/cluster.cpp

# FOR LSH
manhattan-distance.o : $(LSH_MODULES)manhattan-distance.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)manhattan-distance.cpp

handle-input.o : $(LSH_MODULES)handle-input.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)handle-input.cpp

read-file.o : $(LSH_MODULES)read-file.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)read-file.cpp

manhattan-hashing.o : $(LSH_MODULES)manhattan-hashing.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)manhattan-hashing.cpp

modulo.o : $(LSH_MODULES)modulo.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)modulo.cpp

hashtable.o : $(LSH_MODULES)hashtable.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)hashtable.cpp

search.o : $(LSH_MODULES)search.cpp
	$(CXX) $(FLAGS) $(LSH_MODULES)search.cpp

# FOR CUBE
handle-cube-input.o : $(CUBE_MODULES)handle-cube-input.cpp
	$(CXX) $(FLAGS) $(CUBE_MODULES)handle-cube-input.cpp

read-cube-file.o : $(CUBE_MODULES)read-cube-file.cpp
	$(CXX) $(FLAGS) $(CUBE_MODULES)read-cube-file.cpp

projection.o : $(CUBE_MODULES)projection.cpp
	$(CXX) $(FLAGS) $(CUBE_MODULES)projection.cpp

clean:
	rm -f $(OBJS) $(OBJCUBE) $(OUT)