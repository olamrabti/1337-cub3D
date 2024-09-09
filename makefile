NAME = cub3D

NAME_BONUS = cub3D_bonus

HEADERS = cub3d.h MLX42.h

HEADERS_BONUS = /bonus_src/cub3d_bonus.h MLX42.h

CC = cc -Wall -Werror -Wextra -Ofast

MLX = libmlx42.a -Iinclude  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"

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
		parsing/libft_utils.c\
		parsing/libft_helpers.c\
		parsing/libft_suite.c\
	

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
		parsing_bonus/get_next_line_bonus.c\
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
		parsing_bonus/libft_utils_bonus.c\
		parsing_bonus/libft_helpers_bonus.c\
		parsing_bonus/libft_suite_bonus.c\


all : $(NAME) 

OBJS = $(SRC:.c=.o) $(LIBFT_SRC:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%_bonus.o: %_bonus.c $(HEADERS_BONUS) 
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