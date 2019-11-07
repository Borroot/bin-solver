SOLVERS_DIR=    solvers
SRC_DIR=        src
INC_DIR=        inc

SOLVERS_FILES=  $(wildcard $(SOLVERS_DIR)/*.cpp)
SRC_FILES=      $(wildcard $(SRC_DIR)/*.cpp)
INC_FILES=      $(wildcard $(INC_DIR)/*.h)

CFLAGS=         -Wall -Wextra -Werror -pedantic
IFLAGS=         -I $(INC_DIR)

#all: $(SOLVERS_FILES:.cpp=)

%: $(SOLVERS_DIR)/%.cpp $(SRC_FILES)
	$(CXX) -o $@.o $^ $(CFLAGS) $(IFLAGS)

clean:
	rm -f *.o

.PHONY: all clean
