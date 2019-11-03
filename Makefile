CFLAGS=-Wall -Wextra -Werror -pedantic

default: coloring

all: coloring bruteforcing java

%: solver-%.cpp  
	$(CXX) -o $@.o $< $(CFLAGS)

java: Solver.java
	javac Solver.java

clean:
	rm -f *.o *.class
