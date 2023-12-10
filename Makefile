##
# Project Title
#
# @file
# @version 0.1

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEPENDENCY_RULES = $(SRC:.cpp=.d)

CXXFLAGS += -MMD -MP
CXXFLAGS += -Wall
CXXFLAGS += -O3 -march=native
CXXFLAGS += -DREMOVE_SFML
#CXXFLAGS += -g
#CXXFLAGS += -fsanitize=address
#LDFLAGS += -fsanitize=address
LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system


main: $(OBJ)
	$(CXX)  $(CXXFLAGS) $(LDFLAGS) $^ -o $@

-include $(DEPENDENCY_RULES)

clean:
	rm -f $(OBJ) main $(DEPENDENCY_RULES)


# end
