.PHONY: all clean

all: code

code: code.cpp
	gcc -O2 -o code code.cpp

clean:
	rm -f code
