/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:44:37 by olamrabt          #+#    #+#             */
/*   Updated: 2023/12/21 14:46:09 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char	*ft_strjoin(char *s1, char *s2);
void	*ft_memmove(void *s1, void *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_updatestock(char *str, size_t i);
char	*ft_fill_stock(int fd, char *stock);
size_t	ft_strlen(char *str);
void	ft_free(char *str);
int		ft_strchrnl(char *str);
char	*ft_getline(char *stock);

#endif
