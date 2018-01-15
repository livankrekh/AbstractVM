NAME = avm
CC = g++
SRC = src/VM.cpp src/exceptions.cpp
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC:.cpp=.o)
	$(CC) -o $(NAME) $(SRC:.cpp=.o) $(FLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -f $(SRC:.cpp=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all