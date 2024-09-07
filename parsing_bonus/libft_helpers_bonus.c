/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:01:28 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:53:19 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

static int	check_overflow(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	size_t				i;
	int					signe;
	unsigned long long	total;

	i = 0;
	signe = 1;
	total = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (total > (9223372036854775807ULL - (str[i] - '0')) / 10)
			return (check_overflow(signe));
		total = total * 10 + str[i] - '0';
		i++;
	}
	return ((int)(signe * total));
}

static int	equal(const char *s1, const char *s2, size_t len)
{
	int	i;

	i = 0;
	while (*s1 && *s2 && len)
	{
		if (s1[i] != s2[i])
			return (0);
		s1++;
		s2++;
		len--;
	}
	if (*s2 == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!haystack && !len)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (*haystack == *needle && equal(haystack, needle, len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
