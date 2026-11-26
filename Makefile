.PHONY: all clean

all: code

code: code.cpp
	@if command -v gcc-13 >/dev/null 2>&1; then \
		gcc-13 -O2 -o code code.cpp; \
	elif command -v g++-13 >/dev/null 2>&1; then \
		g++-13 -O2 -o code code.cpp; \
	elif command -v gcc >/dev/null 2>&1; then \
		gcc -O2 -o code code.cpp; \
	elif command -v g++ >/dev/null 2>&1; then \
		g++ -O2 -o code code.cpp; \
	else \
		echo "No C compiler found"; \
		exit 1; \
	fi

clean:
	rm -f code
