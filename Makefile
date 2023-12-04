##
# Project Title
#
# @file
# @version 0.1

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

CXXFLAGS += -g
CXXFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address
SFMLFLAGS += -lsfml-graphics -lsfml-window -lsfml-system


main: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SFMLFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) main


# end
