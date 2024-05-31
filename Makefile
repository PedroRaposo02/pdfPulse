
EXECUTABLE_NAME = pdf_pulse_main
LIBRARY_NAME = pdf_pulse

.PHONY: all clean run

all: clean create 
	@cd build && cmake -DCMAKE_VERBOSE_MAKEFILE=ON .. && cmake --build .

create:
	@mkdir -p build

main:
	@cd build && cmake --build .

run:
	@if [ -f "./build/src/Debug/${EXECUTABLE_NAME}.exe" ]; then \
		./build/src/Debug/${EXECUTABLE_NAME} "$(DOCX_FILE)"; \
	else \
		make all && ./build/src/Debug/${EXECUTABLE_NAME} "$(DOCX_FILE)"; \
	fi

run_no_args:
	@if [ -f "./build/src/Debug/${EXECUTABLE_NAME}.exe" ]; then \
		./build/src/Debug/${EXECUTABLE_NAME}; \
	else \
		make all && ./build/src/Debug/${EXECUTABLE_NAME}; \
	fi

build_lib:
	@echo "Building library ${LIBRARY_NAME}"
	@cd build && cmake --build . --target ${LIBRARY_NAME}

build_exe:
	@echo "Executable: ${EXECUTABLE_NAME}"
	@cd build && cmake --build . --target ${EXECUTABLE_NAME}

build_both: build_lib build_exe

clean:
	@cd build && rm -v !("_deps")
