# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:17:31 by ygaude            #+#    #+#              #
#    Updated: 2017/10/29 05:19:28 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER = checker
PUSH_SWAP = push_swap

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft/

CHECKER_DIR = checker_file/

PUSH_SWAP_DIR = push_swap_file/


all: $(CHECKER) $(PUSH_SWAP)


$(CHECKER):
	@make -C $(CHECKER_DIR) $(CHECKER)
	@mv $(CHECKER_DIR)/$(CHECKER) ./
	@echo "Done ! Checker"

$(PUSH_SWAP):
	@make -C $(PUSH_SWAP_DIR) $(PUSH_SWAP)
	@mv $(PUSH_SWAP_DIR)/$(PUSH_SWAP) ./
	@echo "Done ! Push_swap"

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(CHECKER_DIR) clean
	@make -C $(PUSH_SWAP_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(CHECKER_DIR) fclean
	@make -C $(PUSH_SWAP_DIR) fclean
	@rm -rf $(CHECKER) $(PUSH_SWAP)

re: fclean all

norme : norminette | grep "Error" -B2
