make: solver.cpp
	g++ -o solver solver.cpp

java: Solver.java
	javac Solver.java
	chmod +x Solver.class

clean:
	rm -f solver Solver.class
