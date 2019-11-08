SRC=        src
INC=        inc
OBJ=        obj

CFLAGS=     -Wall -Wextra -Werror -pedantic
IFLAGS=     -I $(INC)

NAMES=      color brute hardc

COLOR_OBJ_FILES=$(OBJ)/coloring.o $(OBJ)/init_vectors.o $(OBJ)/filter.o $(OBJ)/remove_vertex.o
BRUTE_OBJ_FILES=$(OBJ)/bruteforcing.o $(OBJ)/init_vectors.o $(OBJ)/filter.o $(OBJ)/remove_vertex.o
HARDC_OBJ_FILES=$(OBJ)/hardcoded.o

all: $(NAMES)

color: $(COLOR_OBJ_FILES)
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

brute: $(BRUTE_OBJ_FILES)
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

hardc: $(HARDC_OBJ_FILES)
	$(CXX) -o $@ $^ $(CFLAGS) $(IFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p obj
	$(CXX) -o $@ -c $< $(CFLAGS) $(IFLAGS)

clean:
	rm -rf obj $(NAMES)

.PHONY: all clean
