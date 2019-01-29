# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 17:58:51 by dtrigalo          #+#    #+#              #
#    Updated: 2019/01/29 17:26:30 by anleclab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror 

MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

SRC = main.c \
	  error.c \
	  reader.c \
	  projection.c \
	  get_placement_info.c \
	  new_image.c \
	  draw_image.c \
	  events.c \
	  event_actions.c
SRCSFD = srcs/
OBJSFD = objs/
OBJS = $(addprefix $(OBJSFD),$(SRC:.c=.o))

HDR = -I./includes
LIBFT_HDR = -I./libft/includes
LIB_BINARY = -L./libft -lft
LIBFT= libft/libft.a

MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

all: $(LIBFT) $(NAME)

$(NAME): $(OBJSFD) $(LIBFT) $(OBJS)
	@echo "$(CYAN)\nCompiling $@...$(NC)"
	@gcc $(FLAGS) $(MLX) $(OBJS) $(LIB_BINARY) -o $@
	@echo "$(CYAN)$@ is ready$(NC)"

$(LIBFT):
	@make -C libft

$(OBJSFD):
	@mkdir $@

$(OBJSFD)%.o: $(SRCSFD)%.c
	@gcc $(CFLAGS) $(HDR) $(LIBFT_HDR) -c $< -o $@

clean:
	@echo "$(MAGENTA)\nDeleting object files...$(NC)"
	@rm -rf $(OBJSFD)
	@make -C ./libft clean

fclean: clean
	@echo "$(MAGENTA)\nDeleting executable...$(NC)"
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
