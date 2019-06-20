#
# **************************************************************
# *                Simple C++ Makefile Template                *
# *                                                            *
# * Author: Arash Partow (2003)                                *
# * URL: http://www.partow.net/programming/makefile/index.html *
# *                                                            *
# * Copyright notice:                                          *
# * Free use of this C++ Makefile template is permitted under  *
# * the guidelines and in accordance with the the MIT License  *
# * http://www.opensource.org/licenses/MIT                     *
# *                                                            *
# **************************************************************
#

CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -std=c++0x
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := program
INCLUDE  := -Iinclude/ -Iinclude/dlgo/ -Iinclude/dlgo/agent/
SRC      :=                      \
   $(wildcard src/*.cpp)         \
  # $(wildcard src/module1/*.cpp) \
  # $(wildcard src/module2/*.cpp) \
  # $(wildcard src/module3/*.cpp) \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release gz

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)


debug: CXXFLAGS += -DDEBUG -g -rdynamic 
debug: all

release: CXXFLAGS += -O3
release: all

#gz: TARGET   := gen_zob
#gz: 
#SRC      :=                      \
#   $(wildcard src/module1/*.cpp) \

#gz: OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
#gz: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
