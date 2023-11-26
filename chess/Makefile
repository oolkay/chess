SRC = main.cpp Pieces.cpp Board.cpp 
OBJ = $(SRC:.cpp=.o)

all: compile

compile:
	c++ main.cpp Pieces.cpp Board.cpp -o chess



clean:
	rm -f *.o chess

re: clean all

.PHONY: all clean

