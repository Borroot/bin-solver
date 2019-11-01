CFLAGS=-Wall -Wextra -Werror -pedantic

make: coloring

%: solver-%.cpp  
	$(CXX) -o solver.o $< $(CFLAGS)

java: Solver.java
	javac Solver.java

clean:
	rm -f *.o *.class
