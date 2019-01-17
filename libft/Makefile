# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 09:24:35 by dtrigalo          #+#    #+#              #
#    Updated: 2019/01/17 16:07:17 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

CYAN = \033[0;36m
MAGENTA = \033[0;35m
NC = \033[0m

FT_PRINTF = accufield_functions.c color_functions.c conv_functions_binary.c \
			conv_functions_char.c conv_functions_double.c conv_functions_int.c \
			conv_functions_longdouble.c conv_functions_percentage.c \
			exit_error.c flag_functions.c ft_printf.c parse_accufield.c \
			parse_conv.c parse_flag.c tools.c

LIBFT = 	ft_abs.c \
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
			get_next_line.c

OBJSFD = objects

FT_PRINTF_SRCS = $(addprefix srcs/ft_printf/,$(FT_PRINTF))

LIBFT_SRCS = $(addprefix srcs/,$(LIBFT))

SRCS = $(LIBFT_SRCS) $(FT_PRINTF_SRCS)

OBJECTS = $(LIBFT:.c=.o) $(FT_PRINTF:.c=.o)

OBJS = $(addprefix $(OBJSFD)/, $(OBJECTS))

VPATH = srcs:srcs/ft_printf

HDR = -I./includes

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)\nCompiling binary...$(NC)"
	@ar src $@ $(OBJS)
	@ranlib $@
	@echo "$(CYAN)libft.a is created$(NC)"

$(OBJSFD):
	@mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	@gcc $(FLAGS) $(HDR) -c $< -o $@

clean:
	@echo "$(MAGENTA)\nDeleting libft object files...$(NC)"
	@/bin/rm -f $(OBJS)
	@rm -rf $(OBJSFD)

fclean: clean
	@echo "$(MAGENTA)\nDeleting the library...$(NC)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
