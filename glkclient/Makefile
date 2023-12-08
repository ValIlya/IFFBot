
all: run


clean:
	rm -f ./a.out



build:
	gcc -std=c++17 -Icheapglk -L. -lcheapglk client.cpp
	
run: clean build
	./a.out
