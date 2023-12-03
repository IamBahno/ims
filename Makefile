##
# Project Title
#
# @file
# @version 0.1

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)


main: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@


# end
