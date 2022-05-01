##
## EPITECH PROJECT, 2020
## makefile for print
## File description:
## Makefile
##

SRC	=	sources/main.c	\
		sources/assets.c	\
		sources/assets_2.c	\
		sources/assets_3.c	\
		sources/commands.c	\
		sources/central.c	\
		sources/array.c	\
		sources/commands_cond.c	\
		sources/str_managment.c	\
		sources/env_handling.c	\
		sources/error_handling.c	\
		sources/execve_handling.c	\
		sources/cmd_imput.c 	\
		sources/cd_assets.c		\
		sources/my_setenv.c	\
		sources/my_unsetenv.c	\
		sources/redirections.c	\
		sources/my_pipe.c

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

CFLAGS	=	-W -Wall -Wextra -I./include

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:		clean
			rm $(NAME)

re:    	fclean	\
		all