make: coloring

%: solver-%.cpp  
	g++ -o solver $<

java: Solver.java
	javac Solver.java

clean:
	rm -f solver Solver.class
