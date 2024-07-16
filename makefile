NAME = mlx

CC = gcc -fsanitize=address -g

SRC =main.c drawing_utils.c

OBJS = $(SRC:.c=.o)

MLX = libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean :
	@rm -f $(OBJS)


fclean : clean
	@rm -f $(NAME)

re : fclean all

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@