CPP = g++
CPPFLAGS = -std=c++17 -Wall

DOCTEST_INCLUDE = test/doctest
SOURCE_INCLUDE = src

SOURCE := $(wildcard src/*.cpp)
OBJ := $(addprefix build/obj/, $(notdir $(SOURCE:.cpp=.o)))

TEST_SOURCE := $(wildcard test/src/*.cpp)
TEST_OBJ := $(addprefix build/test_obj/, $(notdir $(TEST_SOURCE:.cpp=.o)))

INIT_DOCTEST := test/src/init_doctest.cpp
INIT_DOCTEST_OBJ := build/test_obj/init_doctest.o

EXE := build/exe.out
TEST_EXE := build/test_exe.out

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): build $(OBJ)
	$(CPP) $(CPPFLAGS) -o $(EXE) $(OBJ)

build/obj/%.o: src/%.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

test: $(TEST_EXE)

run_test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): build $(INIT_DOCTEST_OBJ) $(OBJ) $(TEST_OBJ) 
	$(CPP) $(CPPFLAGS) -o $(TEST_EXE) $(TEST_OBJ)

$(INIT_DOCTEST_OBJ): build $(INIT_DOCTEST)
	$(CPP) $(CPPFLAGS) -I$(DOCTEST_INCLUDE) -c -o $(INIT_DOCTEST_OBJ) $(INIT_DOCTEST)

build/test_obj/%.o: test/src/%.cpp
	$(CPP) $(CPPFLAGS) -I$(SOURCE_INCLUDE) -I$(DOCTEST_INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	@if [ -d "build" ]; then rm -rf build; fi

.PHONY: build
build:
	@if [ ! -d "build" ]; then mkdir build && \
				   mkdir build/obj && mkdir build/test_obj; fi
