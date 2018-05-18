CXXFLAGS ?= -g -std=c++17 -Isrc -Itest
TARGET = pos
TEST_TARGET = run-test

SRC = $(wildcard src/controller/*.cpp) \
	  $(wildcard src/integration/*.cpp) \
	  $(wildcard src/model/*.cpp) \
	  $(wildcard src/util/*.cpp) \
	  $(wildcard src/view/*.cpp)
STARTUP = $(wildcard src/startup/*.cpp)

TEST = $(wildcard test/*.cpp) \
	   $(wildcard test/controller/*.cpp) \
	   $(wildcard test/integration/*.cpp) \
	   $(wildcard test/model/*.cpp) \
	   $(wildcard test/util/*.cpp)

SRC_OBJ = $(SRC:.cpp=.o)
STARTUP_OBJ = $(STARTUP:.cpp=.o)
TEST_OBJ = $(TEST:.cpp=.o)

DEP = $(SRC_OBJ:.o=.d) \
	  $(STARTUP_OBJ:.o=.d) \
	  $(TEST_OBJ:.o=.d)

$(TARGET): $(SRC_OBJ) $(STARTUP_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(DEP)

%.d : %.cpp
	$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(SRC_OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

.PHONY: clean
clean: cleandep
	$(RM) $(TARGET)
	$(RM) $(TEST_TARGET)
	$(RM) $(SRC_OBJ)
	$(RM) $(STARTUP_OBJ)
	$(RM) $(TEST_OBJ)
