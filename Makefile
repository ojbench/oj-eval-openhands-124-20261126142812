.PHONY: all clean

all: code

code: main.cpp
	g++ -O2 -o code main.cpp

clean:
	rm -f code
