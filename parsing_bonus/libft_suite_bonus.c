/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_suite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:09:29 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/05 12:10:07 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size != '\0')
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*byte_ptr;

	i = 0;
	byte_ptr = (unsigned char *)ptr;
	while (i < num)
	{
		byte_ptr[i] = (unsigned char)value;
		i++;
	}
	return (byte_ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*byte_dest;
	char		*byte_src;

	if (!src && !dest)
		return (NULL);
	if (src == dest)
		return (dest);
	i = 0;
	byte_dest = (char *)dest;
	byte_src = (char *)src;
	while (i < n)
	{
		byte_dest[i] = byte_src[i];
		i++;
	}
	return (byte_dest);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	s = src;
	d = dest;
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	else if (d < s)
		ft_memcpy(dest, src, len);
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*s;
	char	c2;

	i = 0;
	c2 = (char)c;
	s = (char *)str;
	while (s[i] != '\0')
	{
		if (s[i] == c2)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c2)
		return ((char *)(s + i));
	if (!s[i])
		return (NULL);
	return (NULL);
}
