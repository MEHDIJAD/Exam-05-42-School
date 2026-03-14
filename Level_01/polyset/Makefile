NAME = polyset
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = array_bag.cpp main.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp tree_bab.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
