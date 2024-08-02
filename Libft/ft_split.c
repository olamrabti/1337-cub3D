/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:52:18 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/19 16:51:43 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_free(char **copy, size_t j)
{
	while (j--)
		free(copy[j]);
	free(copy);
	return (NULL);
}

static char	**str_split(char const *s, char c, size_t i, size_t len)
{
	size_t	j;
	char	**copy;

	j = 0;
	copy = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!copy)
		return (NULL);
	while (j < count_words(s, c))
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] && s[i + len] != c)
			len++;
		copy[j] = (char *)malloc((len + 1) * sizeof(char));
		if (!copy[j])
			return (ft_free(copy, j));
		ft_strlcpy(copy[j], (s + i), len + 1);
		i += len;
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	return (str_split(s, c, i, len));
}
