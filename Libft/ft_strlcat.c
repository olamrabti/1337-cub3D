/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:25:38 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/11 10:25:38 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	total_len;

	if (!dest && !size)
		return (0);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	total_len = dest_len + src_len;
	if (dest_len >= size)
		return (size + src_len);
	if (src_len >= size - dest_len)
		src_len = size - dest_len - 1;
	if (src_len > 0)
	{
		ft_memcpy(dest + dest_len, src, src_len);
		dest[dest_len + src_len] = '\0';
	}
	return (total_len);
}
