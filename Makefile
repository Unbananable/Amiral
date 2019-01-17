# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 17:58:51 by dtrigalo          #+#    #+#              #
#    Updated: 2019/01/17 17:06:57 by dtrigalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror -g

SRC1 = main.c draw_line.c

MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

OBJSFD = objects

OBJS = $(addprefix $(OBJSFD)/,$(SRC1:.c=.o))

LIBFT_HDR = -I./libft/includes
LIB_BINARY = -L./libft -lft
LIBFT= libft/libft.a

MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft re

$(OBJSFD):
	@mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	@gcc $(CFLAGS) $(LIBFT_HDR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(CYAN)\nCompiling $@...$(NC)"
	@gcc $(FLAGS) $(MLX) $(OBJS) $(LIB_BINARY) -o $@
	@echo "$(CYAN)$@ is ready$(NC)"

clean:
	@echo "$(MAGENTA)\nDeleting object files...$(NC)"
	@/bin/rm -f $(OBJS)
	@rm -rf $(OBJSFD)
	@make -C ./libft clean

fclean: clean
	@echo "$(MAGENTA)\nDeleting executable...$(NC)"
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
