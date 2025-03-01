CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Iinclude

BIN_DIR := bin
SRC_DIR := src
TEST_DIR := test

SRCS := $(filter-out $(SRC_DIR)/main.cc, $(wildcard $(SRC_DIR)/*.cc))
OBJS := $(patsubst $(SRC_DIR)/%.cc, $(BIN_DIR)/%.o, $(SRCS))
MAIN_SRC := $(SRC_DIR)/main.cc
MAIN_OBJ := $(BIN_DIR)/main.o
MAIN_BIN := $(BIN_DIR)/main
TEST_SRCS := $(wildcard $(TEST_DIR)/*_test.cc)
TEST_BINS := $(patsubst $(TEST_DIR)/%.cc, $(BIN_DIR)/%, $(TEST_SRCS))

all: $(MAIN_BIN) $(TEST_BINS)

$(MAIN_BIN): $(MAIN_OBJ) $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%: $(BIN_DIR)/%.o $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cc | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BIN_DIR)/%: $(TEST_DIR)/%.cc $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgtest -lgtest_main -lpthread

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)

format:
	clang-format -style=file:../.clang-format -i include/*.hpp $(SRC_DIR)/*.cc

.PHONY: all clean format

