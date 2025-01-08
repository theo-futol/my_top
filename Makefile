##
## EPITECH PROJECT, 2024
## MAKEFILE
## File description:
## makefile
##

SRC = src/find_flag.c \
	  src/procfs.c \
	  src/files_system.c \
	  src/my_uptime.c \
	  src/count_users.c \
	  src/display.c \
	  src/all_proc.c \
	  src/tools.c \
	  src/mem.c \
	  src/memory.c \
	  src/my_str_to_word_array.c \
	  main.c

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o my_top -lncurses

clean:
	rm  -f $(OBJ)

fclean:
	make clean
	rm -f my_top

re: fclean all
