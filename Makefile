CXX=g++
WARNINGS=-pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
INCLUDE=-Ilib/ -Isrc/ -Itests/ 
CXXFLAGS=-std=c++14 -O0 -MMD -MP $(WARNINGS) $(INCLUDE) -g -c
LDFLAGS=-std=c++14

all: main

SRC = util.cpp Logger.cpp K.cpp GraphBuilder.cpp

OBJS = $(patsubst %.cpp, .obj/%.o, $(SRC))

main: .obj/main.o $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

test: .obj/test.o $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

.obj/%.o: src/%.cpp $(wildcard src/*.h src/*.hpp) | .obj
	$(CXX) $(CXXFLAGS) $< -o $@

.obj: 
	mkdir -p .obj/

clean:
	rm -rf *.o *.d .obj/ main test
	
.PHONY: all clean
