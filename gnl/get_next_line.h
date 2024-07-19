#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../Libft/libft.h"

# define BUFFER_SIZE 20

char	*get_next_line(int fd);
void	ft_strcpy(char *dst, const char *src);

#endif