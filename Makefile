##
## EPITECH PROJECT, 2020
## B-PSU-402-LYN-4-1-strace-flavien.allix
## File description:
## Makefile
##

SRC = \
		src/main.c \
		src/check_args.c \
		src/get_word.c \
		src/get_env_and_av.c\
		src/core_s.c\
		src/syscalls.c\
		src/command_write.c\
		src/core_p.c\

CXX = gcc
CXXFLAGS = -W -Wall -Wextra -g
CPPFLAGS = -I ./include/
LIBFLAGS =
NAME = strace

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LIBFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	@./$(NAME)

.PHONY: all clean fclean re test
