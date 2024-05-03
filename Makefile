
EXECUTABLE_NAME = pdf_pulse_main

.PHONY: all clean run

all: clean build
	@cd build && cmake -DCMAKE_VERBOSE_MAKEFILE=ON .. && cmake --build .

build:
	@mkdir -p build

run:
	@if [ -f "./build/src/Debug/${EXECUTABLE_NAME}.exe" ]; then \
		./build/src/Debug/${EXECUTABLE_NAME} "$(DOCX_FILE)"; \
	else \
		make all && ./build/src/Debug/${EXECUTABLE_NAME} "$(DOCX_FILE)"; \
	fi

build_exe:
	@echo "Executable: ${EXECUTABLE_NAME}"
	@cd build && cmake --build . --target ${EXECUTABLE_NAME}


clean:
	@rm -rf build out 