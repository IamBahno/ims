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


main: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) main


# end
