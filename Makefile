# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 20:19:37 by rpapagna          #+#    #+#              #
#    Updated: 2019/05/23 22:15:52 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls
ARCHIVE = libft.a

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
MAG		=\033[0;35m
NC		=\033[0m

CFLAGS	= -Wall -Werror -Wextra
INCL	= -I includes/

SRCS 	=get_.c\
		main.c\
		t_init.c

PRINTF	= convert_percent.c \
		convert_b.c \
		convert_c.c \
		convert_f.c \
		convert_i.c \
		convert_o.c \
		convert_p.c \
		convert_s.c \
		convert_u.c \
		convert_x.c \
		do_things.c \
		get_mods.c \
		finders.c 

LIBFT	= ft_atoi.c \
		ft_bzero.c \
		ft_countwords.c \
		ft_intlen.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isupper.c \
		ft_itoa_base.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_pipewrench.c \
		ft_printf.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strchri.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcnew.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strpop.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c

OBJ		= $(patsubst %.c,%.o,$(LIBFT))
OBJ		+= $(patsubst %.c,%.o,$(PRINTF))

all:	$(NAME)

$(NAME):
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG):/:$(NC)]\r" #PRINT
		@gcc -g $(CFLAGS) -c $(addprefix ft_printf/,$(PRINTF)) $(INCL)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG):\:$(NC)]\r" #PRINT
		@gcc -g $(CFLAGS) -c $(addprefix libft/,$(LIBFT)) $(INCL)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG):/:$(NC)]\r" #PRINT
		@ar -rcs $(ARCHIVE) $(OBJ)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG):\:$(NC)]\r" #PRINT
		@gcc $(CFLAGS) $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG)OK!$(NC)]\n" #PRINT

clean:
		@printf "[$(RED)obj$(NC)]\t\tRm objects\n" #PRINT
		@rm -rf $(OBJ)

fclean: clean
		@printf "[$(RED)$(ARCHIVE)$(NC)]\tRm archive\n"
		@rm -rf $(ARCHIVE)
		@printf "[$(RED)$(NAME)$(NC)]\t\tRm binary\n"
		@rm -rf $(NAME).dSYM
		@rm -rf $(NAME)

re: fclean all

1mo:	clean
		@rm -rf $(NAME)
		gcc -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t\t[$(MAG)OK!$(NC)]\n" #PRINT

debug:
		@rm -rf $(NAME).dSYM
		@rm -rf $(NAME)
		gcc -g -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)
		@printf "[$(YELLOW)debug$(NC)]\t\t[$(MAG)OK!$(NC)]\n" #PRINT

.PHONY: all clean fclean re 1mo debug