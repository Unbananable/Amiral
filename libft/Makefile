# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 09:24:35 by dtrigalo          #+#    #+#              #
#    Updated: 2019/02/08 11:27:18 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

CYAN = \033[0;36m
MAGENTA = \033[0;35m
NC = \033[0m

SRCS =	 	ft_abs.c \
			ft_print_int_array.c \
			ft_itoa_base.c	\
			ft_atoi.c		\
			ft_bzero.c		\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isalpha.c	\
			ft_lstdel.c		\
			ft_isprint.c	\
			ft_lstdelone.c	\
			ft_lstiter.c	\
			ft_lstmap.c		\
			ft_lstnew.c		\
			ft_itoa.c		\
			ft_memalloc.c	\
			ft_memccpy.c	\
			ft_memcmp.c		\
			ft_memdel.c		\
			ft_memcpy.c		\
			ft_lstadd.c		\
			ft_memmove.c	\
			ft_putchar.c	\
			ft_memset.c		\
			ft_putchar_fd.c	\
			ft_memchr.c		\
			ft_putendl_fd.c	\
			ft_putendl.c	\
			ft_putnbr.c		\
			ft_putnbr_fd.c	\
			ft_putstr_fd.c	\
			ft_putstr.c		\
			ft_stpcpy.c		\
			ft_strclr.c		\
			ft_strcat.c		\
			ft_strchr.c		\
			ft_strdel.c		\
			ft_strcmp.c		\
			ft_strcpy.c		\
			ft_strequ.c		\
			ft_striter.c	\
			ft_striteri.c	\
			ft_strdup.c		\
			ft_strlen.c		\
			ft_strjoin.c	\
			ft_strmap.c		\
			ft_strmapi.c	\
			ft_strlcat.c	\
			ft_strncat.c	\
			ft_strncmp.c	\
			ft_strnequ.c	\
			ft_strnew.c		\
			ft_strncpy.c	\
			ft_strnstr.c	\
			ft_strrchr.c	\
			ft_strsub.c		\
			ft_strstr.c		\
			ft_strtrim.c	\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_strsplit.c	\
			ft_isspace.c	\
			ft_isupper.c	\
			ft_islower.c	\
			ft_is_prime.c	\
			ft_power.c		\
			ft_fact.c		\
			ft_doubletoa.c	\
			ft_llitoa.c		\
			ft_litoa.c		\
			ft_putwchar.c	\
			ft_wchar_to_bytes.c \
			ft_double_power.c	\
			ft_ldouble_power.c \
			ft_filelinecount.c \
			ft_fopen.c \
			ft_fclose.c \
			ft_fgetc.c \
			ft_atoi_base.c

SRCSFD = srcs/
SRCS_PATH = $(addprefix $(SRCSFD),$(SRCS))
OBJS = $(SRCS:.c=.o)
OBJSFD = objects/
OBJS_PATH = $(addprefix $(OBJSFD), $(OBJS))

HDR = -I./includes

all: $(NAME)

$(NAME): $(OBJSFD) $(OBJS_PATH)
	@echo "$(CYAN)\nCompiling binary...$(NC)"
	@ar rc $(NAME) $(OBJS_PATH)
	@ranlib $(NAME)
	@echo "$(CYAN)libft.a is created$(NC)"

$(OBJSFD):
	@mkdir $@

$(OBJSFD)%.o: $(SRCSFD)%.c
	@gcc $(FLAGS) $(HDR) -c $< -o $@

clean:
	@echo "$(MAGENTA)\nDeleting libft object files...$(NC)"
	@rm -Rf $(OBJSFD)

fclean: clean
	@echo "$(MAGENTA)\nDeleting the library...$(NC)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
