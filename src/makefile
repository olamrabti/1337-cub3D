NAME = cub3D

CC = gcc -fsanitize=address -g

SRC =main.c drawing_utils.c parsing.c

OBJS = $(SRC:.c=.o)

MLX = libmlx42.a -Iinclude -ldl -lglfw -pthread -lm #libmlx.a should not be included in files it should be made during make.

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