/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:42 by olamrabt          #+#    #+#             */
/*   Updated: 2023/10/31 13:52:42 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int		i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	while (--size && *src)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = '\0';
	while (*(src++))
		i++;
	return (i);
}
