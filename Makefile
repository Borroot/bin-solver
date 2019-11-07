SOLVERS_DIR=    solvers
SRC_DIR=        src
INC_DIR=        inc

SOLVERS_FILES=  $(wildcard $(SOLVERS_DIR)/*.cpp)
SRC_FILES=      $(wildcard $(SRC_DIR)/*.cpp)
INC_FILES=      $(wildcard $(INC_DIR)/*.h)

SOLVERS_BASES=  $(basename $(SOLVERS_FILES))
SOLVERS_NAMES=  $(SOLVERS_BASES:$(SOLVERS_DIR)/%=%)

CFLAGS=         -Wall -Wextra -Werror -pedantic
IFLAGS=         -I $(INC_DIR)

all: $(SOLVERS_NAMES)

%: $(SOLVERS_DIR)/%.cpp $(SRC_FILES)
	$(CXX) -o $@.o $^ $(CFLAGS) $(IFLAGS)

clean:
	rm -f *.o

.PHONY: all clean
