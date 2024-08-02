/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:37:17 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/17 13:13:59 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*put_str(int n, char *str, int count)
{
	str[count] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		while (--count)
		{
			str[count] = n % 10 + 48;
			n /= 10;
		}
		return (str);
	}
	while (count--)
	{
		str[count] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	count;
	int		temp;
	char	*str;

	count = 1;
	temp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (temp / 10)
	{
		temp /= 10;
		count++;
	}
	if (n < 0)
		count++;
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	return (put_str(n, str, count));
}
