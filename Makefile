# Compiler & Flags:
CXX      := g++
CXXFLAGS := -std=c++17 -lstdc++fs -Wall

TARGET = degenerate

# Extension:
SRC_EXT := cpp

# Directories:
BUILD   := ./build
SRC_DIR := ./src

OBJ_DIR := $(BUILD)/objects
BIN_DIR := $(BUILD)/bin

# Source & Objects:
SRC_FILES := $(wildcard ${SRC_DIR}/*.cpp)
OBJECT_FILES := $(patsubst ${SRC_DIR}/%.cpp, ${OBJ_DIR}/%.o, ${SRC_FILES})

# Dependencies & Includes:
DEPENDENCIES := $(OBJECT_FILES:.o=.d)
INCLUDE := -I include

all: build $(BIN_DIR)/$(TARGET)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

# Main:
${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	@mkdir -p ${@D}
	${CXX} ${CXXFLAGS} ${INCLUDE} -c $< -MMD -o $@

${BIN_DIR}/${TARGET}: ${OBJECT_FILES}
	@mkdir -p ${@D}
	${CXX} ${CXXFLAGS} -o $(BIN_DIR)/$(TARGET) $^


# Build:
build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)


# Debug Targes:
debug: CXXFLAGS += -DDEBUG -g -pedantic-errors -Wextra -Werror
debug: all

# Release Targets:
release: CXXFLAGS += -O3 -DNDEBUG -s
release: all

# Clean Target:
clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -rvf $(BIN_DIR)

# Information Target:
info:
	@echo "[*] Application dir: ${BIN_DIR}      "
	@echo "[*] Objects dir:     ${OBJ_DIR}      "
	@echo "[*] Sources:         ${SRC_FILES}    "
	@echo "[*] Objects:         ${OBJECT_FILES} "
	@echo "[*] Dependencies:    ${DEPENDENCIES} "