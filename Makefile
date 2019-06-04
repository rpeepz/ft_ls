# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 20:19:37 by rpapagna          #+#    #+#              #
#    Updated: 2019/06/04 14:07:55 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls
ARCHIVE = libft/libft.a

CFLAGS	= -Wall -Werror -Wextra
INCL	= -I includes/

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
MAG		=\033[0;35m
NC		=\033[0m

SRCS 	=ft_ls.c\
		get_.c\
		main.c\
		print.c\
		t_file_mergesort.c\
		t_init.c\
		color/ls_color.c

.PHONY: clean 1mo debug

all:	$(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG)OK!$(NC)]\n" #PRINT

clean:
		@make -C libft clean

fclean:
		@printf "[$(RED)$(NAME)$(NC)]\t\tRm binary\n"
		@make -C libft fclean
		@rm -rf $(NAME).dSYM
		@rm -rf $(NAME)
		@rm -rf includes/$(NAME).h.gch

re: fclean all

$(NAME):
		@make -C libft
		@gcc $(CFLAGS) $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)

1mo:
		@gcc -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG)OK!$(NC)]\n" #PRINT

debug:
		@gcc -g -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)
		@printf "[$(YELLOW)debug$(NC)]\t\t[$(MAG)OK!$(NC)]\n" #PRINT
