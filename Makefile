EXECUTABLE_NAME = PdfPulse.exe

DATA_DIR ?= data

DOCX_FILE ?= ${DATA_DIR}/teste_1.docx

.PHONY: all clean run

all: clean build
	@cd build && cmake -DCMAKE_VERBOSE_MAKEFILE=ON .. && cmake --build .

build:
	@mkdir -p build

run:
	@if [ -f "./build/src/Debug/${EXECUTABLE_NAME}" ]; then \
		./build/src/Debug/${EXECUTABLE_NAME} "$(DOCX_FILE)"; \
	else \
		make all && ./build/src/Debug/${EXECUTABLE_NAME} "$(DOCX_FILE)"; \
	fi

clean:
	@rm -rf build out 