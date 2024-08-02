/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:32 by olamrabt          #+#    #+#             */
/*   Updated: 2023/10/31 13:52:32 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;

	if (!s[0])
	{
		copy = (char *)malloc(sizeof(char));
		if (!copy)
			return (NULL);
		copy[0] = '\0';
		return (copy);
	}
	copy = (char *)malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, ft_strlen(s));
	copy[ft_strlen(s)] = '\0';
	return (copy);
}
