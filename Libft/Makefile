# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 13:53:07 by olamrabt          #+#    #+#              #
#    Updated: 2023/10/31 13:53:07 by olamrabt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
	ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\

SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\


NAME = libft.a 
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_ALL = $(OBJS) $(OBJS_BONUS)
CC = cc
HEADER = libft.h
FLAGS = -Wall -Werror -Wextra
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $^

bonus: $(OBJS_ALL)
	ar -rc $(NAME) $^

%.o: %.c $(HEADER) 
	$(CC) $(FLAGS) -c $<

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: fclean clean bonus all re re_bonus

