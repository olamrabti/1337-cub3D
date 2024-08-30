/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:50 by olamrabt          #+#    #+#             */
/*   Updated: 2024/08/30 05:35:45 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	count;

	count = 1;
	if ((char)c == '\0')
		return ((char *)str + ft_strlen(str));
	while (*str)
	{
		str++;
		count++;
	}
	while (count--)
	{
		if (*str == (char)c)
			return ((char *)str);
		str--;
	}
	return (0);
}
