## Name of Project

NAME = libft.a

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs

## Compilating Utilities

FLAGS = -Wall -Wextra -Werror -Ofast

INC = $(INC_DIR:%=-I ./%)
CC = clang $(FLAGS) $(INC)

## List of Functions

SRC_FT =	ft_atoi 					\
					ft_isdigit				\
					ft_lstdel					\
					ft_memchr					\
					ft_putendl				\
					ft_stradd_in			\
					ft_striter				\
					ft_strncmp				\
					ft_strsub					\
					ft_atoi_base			\
					ft_isprint				\
					ft_lstdelone			\
					ft_memcmp					\
					ft_putendl_fd			\
					ft_strcat					\
					ft_striteri				\
					ft_strncpy				\
					ft_strtrim				\
					ft_atoll					\
					ft_itoa						\
					ft_lstiter				\
					ft_memcpy					\
					ft_putnbr					\
					ft_strchr					\
					ft_strjoin				\
					ft_strndup				\
					ft_swap						\
					ft_bzero					\
					ft_itoa_base			\
					ft_lstmap					\
					ft_memdel					\
					ft_putnbr_fd			\
					ft_strclr					\
					ft_strlcat				\
					ft_strnequ				\
					ft_tolower				\
					ft_c_in_str				\
					ft_lst_clear			\
					ft_lstnew					\
					ft_memmove				\
					ft_putstr					\
					ft_strcmp					\
					ft_strlen					\
					ft_strnew					\
					ft_toupper				\
					ft_free_factory		\
					ft_lst_push_back	\
					ft_malloc_factory	\
					ft_memset					\
					ft_putstr_fd			\
					ft_strcpy					\
					ft_strlendup			\
					ft_strnstr				\
					ft_ulltoa_base		\
					ft_isalnum				\
					ft_lst_push_front	\
					ft_memalloc				\
					ft_parse_str			\
					ft_putunicode			\
					ft_strdel					\
					ft_strmap					\
					ft_strrchr				\
					get_next_line			\
					ft_isalpha				\
					ft_lst_size				\
					ft_memalloc_exit	\
					ft_putchar				\
					ft_realloc				\
					ft_strdup					\
					ft_strmapi				\
					ft_strsplit				\
					ft_isascii				\
					ft_lstadd					\
					ft_memccpy				\
					ft_putchar_fd			\
					ft_stradd					\
					ft_strequ					\
					ft_strncat				\
					ft_strstr					\


## List of Utilities

OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o)
SRC = $(SRC_FT:%=$(SRC_DIR)/%.c)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[1;30m[All OK]\0033[0;37m"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(COLOR)Creating    : \0033[0;32m$@\0033[0;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	@$(CC) -c $< -o $@
	@echo "$(COLOR)Compilating : \0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[0;37m"

$(NAME): $(OBJ_DIR) $(SRC) $(INC_DIR)/libft.h
	@$(MAKE) -j -s $(OBJ)
	@echo "$(COLOR)Objects\t\t\0033[0;32m[Created]\0033[0;37m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)Objects\t\t\0033[0;31m[Deleted]\0033[0;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[0;31m[Deleted]\0033[0;37m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/

.PHONY: all clean fclean re norme
