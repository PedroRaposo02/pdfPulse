CXX       := g++
CXXFLAGS  := -std=c++11 -O3
INCLUDE   := -Isrc/extLibs/RapidXml -Isrc/extLibs/ZipLib
BUILD     := ./build
APP_DIR   := $(BUILD)/apps

TARGET    := src
SRC       := src/main.cpp

ZIP_LIB_BUILD_DIR := build/ZipLib

all: build $(APP_DIR)/$(TARGET)

$(APP_DIR)/$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

build:
	@mkdir -p $(APP_DIR)

clean:
	-@rm -rvf $(APP_DIR)/

zip_lib:
	@mkdir -p $(ZIP_LIB_BUILD_DIR)
	cd $(ZIP_LIB_BUILD_DIR) && cmake .
	cd $(ZIP_LIB_BUILD_DIR) && make

.PHONY: all clean zip_lib
