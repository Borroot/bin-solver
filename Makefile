CFLAGS=-Wall -Wextra -Werror -pedantic

make: coloring

%: solver-%.cpp  
	g++ -o solver $< $(CFLAGS)

java: Solver.java
	javac Solver.java

clean:
	rm -f solver Solver.class
