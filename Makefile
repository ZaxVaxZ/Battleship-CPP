CXX = c++
CXXFLAGS = -Wall -Wextra -Werror
SRC = Board.cpp Human_Board.cpp main.cpp NPC_Board.cpp
OBJ = $(SRC:.cpp=.o)
NAME = battleship

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: $.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
