.PHONY: all clean

all: code

code: code.cpp
	g++ -O2 -o code code.cpp

clean:
	rm -f code
