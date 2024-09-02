NAME = cub3D

NAME_BONUS = cub3D_bonus

HEADERS = cub3d.h cub3d.h Libft/libft.h

CC = cc -Wall -Werror -Wextra  -Ofast -g #-fsanitize=address

MLX = libmlx42.a -Iinclude  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib" #libmlx.a should not be included in files it should be made during make.

SRC = main.c\
		get_next_line/get_next_line.c\
		src/address_collector.c\
		src/address_collector_utils.c\
		src/drawing_utils.c\
		src/player.c\
		src/dda.c\
		src/3d_walls.c\
		src/dda_utils.c\
		parsing/start_parsing.c\
		parsing/save_vars.c\
		parsing/check_vars.c\
		parsing/save_player_pos.c\
		parsing/split_map.c\
		parsing/valide_map.c\
		parsing/double_check_vars.c\
		parsing/fill_map_with_sp.c\
		parsing/parsing_map.c\
		parsing/parsing_helpers.c\
		parsing/ft_split.c\
		parsing/stores_f_c.c\
		parsing/check_zero.c\

SRC_BONUS = bonus_src/main_bonus.c\
		bonus_src/address_collector_bonus.c\
		bonus_src/address_collector_utils_bonus.c\
		bonus_src/drawing_utils_bonus.c\
		bonus_src/player_bonus.c\
		bonus_src/dda_bonus.c\
		bonus_src/3d_walls_bonus.c\
		bonus_src/animation_bonus.c\
		bonus_src/dda_utils_bonus.c\
		bonus_src/minimap_bonus.c\
		get_next_line/get_next_line.c\
		parsing_bonus/start_parsing_bonus.c\
		parsing_bonus/save_vars_bonus.c\
		parsing_bonus/check_vars_bonus.c\
		parsing_bonus/save_player_pos_bonus.c\
		parsing_bonus/split_map_bonus.c\
		parsing_bonus/valide_map_bonus.c\
		parsing_bonus/double_check_vars_bonus.c\
		parsing_bonus/fill_map_with_sp_bonus.c\
		parsing_bonus/parsing_map_bonus.c\
		parsing_bonus/parsing_helpers_bonus.c\
		parsing_bonus/ft_split_bonus.c\
		parsing_bonus/stores_f_c_bonus.c\
		parsing_bonus/check_zero_bonus.c\


LIBFT_SRC = Libft/ft_atoi.c\
			Libft/ft_putendl_fd.c\
			Libft/ft_strncmp.c\
			Libft/ft_bzero.c\
			Libft/ft_putnbr_fd.c\
			Libft/ft_strnstr.c\
			Libft/ft_calloc.c\
			Libft/ft_putstr_fd.c\
			Libft/ft_strrchr.c\
			Libft/ft_isalnum.c\
			Libft/ft_strtrim.c\
			Libft/ft_isalpha.c\
			Libft/ft_strchr.c\
			Libft/ft_substr.c\
			Libft/ft_isascii.c\
			Libft/ft_strdup.c\
			Libft/ft_tolower.c\
			Libft/ft_isdigit.c\
			Libft/ft_memchr.c\
			Libft/ft_striteri.c\
			Libft/ft_toupper.c\
			Libft/ft_isprint.c\
			Libft/ft_memcmp.c\
			Libft/ft_strjoin.c\
			Libft/ft_itoa.c\
			Libft/ft_memcpy.c\
			Libft/ft_strlcat.c\
			Libft/ft_memmove.c\
			Libft/ft_strlcpy.c\
			Libft/ft_memset.c\
			Libft/ft_strlen.c\
			Libft/ft_putchar_fd.c\
			Libft/ft_strmapi.c\

all : $(NAME)

OBJS = $(SRC:.c=.o) $(LIBFT_SRC:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c $(HEADERS) /bonus_src/cub3d_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

OBJS_BONUS = $(SRC_BONUS:.c=.o) $(LIBFT_SRC:.c=.o)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX) -o $(NAME_BONUS)

clean :
	@rm -f $(OBJS) $(OBJS_BONUS)


fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)

re : fclean all