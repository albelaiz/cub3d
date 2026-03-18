NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx

MLX = ./MLX42-master/build/libmlx42.a

GLFW = /goinfre/yaamaich/homebrew/Cellar/glfw/3.4/lib/libglfw.3.4.dylib

FRAMEWORKS = -framework OpenGL -framework AppKit

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c parse.c validation.c map_normalize.c player_init.c move_player.c \
      utils.c recasting.c recasting_utils.c recasting_ray.c recasting_tex.c \
      draw.c init_game.c parse_utils.c recasting_tex_draw.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(GLFW) $(FRAMEWORKS)  -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
