/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:39:00 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/22 20:32:33 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*copy;

	if (count != 0 && size > 9223372036854775807ULL / count)
		return (NULL);
	copy = (char *)malloc(count * size);
	if (!copy)
		return (NULL);
	ft_bzero(copy, size * count);
	return (copy);
}
