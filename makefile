NAME = cub3D

CC = cc -fsanitize=address -g

SRC = main.c src/drawing_utils.c src/parsing.c gnl/get_next_line.c src/address_collector.c src/address_collector_utils.c

OBJS = $(SRC:.c=.o) $(LIBFT_SRC:.c=.o)

MLX = libmlx42.a -Iinclude -ldl -lglfw -pthread -lm #libmlx.a should not be included in files it should be made during make.

LIBFT_SRC = Libft/ft_atoi.c Libft/ft_putendl_fd.c Libft/ft_strncmp.c\
Libft/ft_bzero.c Libft/ft_putnbr_fd.c Libft/ft_strnstr.c\
Libft/ft_calloc.c Libft/ft_putstr_fd.c Libft/ft_strrchr.c\
Libft/ft_isalnum.c Libft/ft_split.c Libft/ft_strtrim.c\
Libft/ft_isalpha.c Libft/ft_strchr.c Libft/ft_substr.c\
Libft/ft_isascii.c Libft/ft_strdup.c Libft/ft_tolower.c\
Libft/ft_isdigit.c Libft/ft_memchr.c Libft/ft_striteri.c Libft/ft_toupper.c\
Libft/ft_isprint.c Libft/ft_memcmp.c Libft/ft_strjoin.c\
Libft/ft_itoa.c Libft/ft_memcpy.c Libft/ft_strlcat.c Libft/ft_memmove.c Libft/ft_strlcpy.c\
Libft/ft_memset.c Libft/ft_strlen.c Libft/ft_putchar_fd.c Libft/ft_strmapi.c

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean :
	@rm -f $(OBJS)


fclean : clean
	@rm -f $(NAME)

re : fclean all

%.o: %.c cub3d.h gnl/get_next_line.h Libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@