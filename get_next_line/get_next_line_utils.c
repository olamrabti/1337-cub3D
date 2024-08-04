/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:50:25 by olamrabt          #+#    #+#             */
/*   Updated: 2024/08/02 11:38:33 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free(char *str)
{
	free(str);
	str = NULL;
}

// void	*ft_memmove(void *s1, void *s2, size_t n)
// {
// 	unsigned char	*d;
// 	unsigned char	*s;

// 	if (!s2 && !s1)
// 		return (NULL);
// 	d = (unsigned char *)s1;
// 	s = (unsigned char *)s2;
// 	if (d > s && d < s + n)
// 	{
// 		d += n;
// 		s += n;
// 		while (n--)
// 			*(--d) = *(--s);
// 	}
// 	else
// 	{
// 		while (n--)
// 			*d++ = *s++;
// 	}
// 	return (s1);
// }

// size_t	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*arr;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// 	if (!arr)
// 		return (NULL);
// 	ft_memmove(arr, s1, s1_len);
// 	ft_free(s1);
// 	ft_memmove(arr + s1_len, s2, s2_len);
// 	arr[s1_len + s2_len] = '\0';
// 	return (arr);
// }

int	ft_strchrnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}
