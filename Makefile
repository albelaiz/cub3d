NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./ft_libft/libft.a

SRC = main.c\
	  parse.c\
	  utils.c\


OBJ = $(SRC=.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./ft_libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C ./ft_libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C ./ft_libft fclean

re: fclean all

.PHONY :clean