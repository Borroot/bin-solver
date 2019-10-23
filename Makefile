make: solver.cpp
	g++ -o solver solver.cpp

java: Solver.java
	javac Solver.java

clean:
	rm -f solver Solver.class
