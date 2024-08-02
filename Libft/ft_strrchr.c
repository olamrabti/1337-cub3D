/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:52:50 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/17 15:43:30 by olamrabt         ###   ########.fr       */
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
