CXXFLAGS=-W -Wall -pedantic -std=c++14 -MD -MP

main: main.o
	$(CXX) -o $@ $^

clean:
	rm -f *.o *.d main

-include *.d
