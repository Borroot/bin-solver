CFLAGS=-Wall -Wextra -Werror -pedantic

make: coloring

all: coloring bruteforcing java

%: solver-%.cpp  
	$(CXX) -o solver.o $< $(CFLAGS)

java: Solver.java
	javac Solver.java

clean:
	rm -f *.o *.class
