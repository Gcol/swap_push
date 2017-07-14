# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/13 05:32:56 by gcollett          #+#    #+#              #
#    Updated: 2017/07/13 05:33:51 by gcollett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	checker.c \

SRCDIR = ./srcs/

OBJ = $(SRC:.c=.o)

LIBSRC = 

LIBOBJ = $(LIBSRC:.c=.o)

LDFLAGS = -I./include/

CFLAGS = -Wall -Werror -Wextra

LIBDIR = ../libft/
OBJDIR	= ./objs/
SRCDIR	= ./srcs/

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(OBJ))

LIBS = ../libft/libft.a

RM = rm -f

all : $(NAME)

$(NAME) :
	@make -C libft/ re
	@echo "\t\033[33;32m'MAKE' ->\t\033[1;34m$(NAME)\033[0m :\tLibrary compilation in progress..."
	@gcc $(GCC_FLAGS) -Ilibft/ -Iincludes/ -c $(SRCS)
	@ar rc $(NAME) $(OBJ) $(addprefix $(LIBDIR), $(LIBOBJ))
	@ranlib $(NAME)
	@mkdir -p $(OBJDIR)
	@mv $(OBJ) $(OBJDIR)
	@ranlib $(NAME)
	@echo "\t\033[33;32m'MAKE' ->\t\033[1;34m$(NAME)\033[0m :\tLibrary compilation completed sucessfully !"

clean :
	@echo "\t\033[1;31m'CLEAN' ->\tDestruction\033[0m:\tfiles .o for the library \033[1;34m$(NAME)\033[0m"
	@rm -rf objs
	@echo "\t\033[1;31m'CLEAN' ->\tDestruction\033[0m:\tfiles .o for the library \033[1;34m$(NAME)\033[0m completed successfully !"
	@make -C libft/ clean

fclean : clean
	@$(RM) $(NAME)
	@echo "\t\033[1;31m'FCLEAN' ->\tDestruction\033[0m of library \033[1;34m$(NAME)\033[0m completed successfully !"
	@make -C libft/ fclean

re : fclean all

compile :
	@gcc $(CFLAGS) $(addprefix $(SRCDIR), $(SRC)) main.c libft/libft.a -g

cc:
	@gcc -o test $(addprefix $(SRCDIR), $(SRC)) main.c libft/libft.a -g

compexec : compile
	@./a.out

cexec : cc
	@./a.out
