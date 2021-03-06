NAME = avm
CC = g++
SRC = src/VM.cpp src/exceptions.cpp src/main.cpp
FLAGS = -Wall -Wextra -Werror -std=c++11 -Wno-unknown-escape-sequence

OS := $(shell uname -s)

ifeq ($(OS), Linux)
	FLAGS = -Wall -Wextra -std=c++11
endif


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