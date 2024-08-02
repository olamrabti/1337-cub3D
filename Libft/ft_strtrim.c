/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:05:00 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/17 15:43:02 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_set(char const *s1, char const *set)
{
	size_t	size;
	size_t	i;

	size = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		size--;
		i++;
	}
	if (size == 0)
		return (0);
	i = ft_strlen(s1) - 1;
	while (i && ft_strchr(set, s1[i]))
	{
		size--;
		i--;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	size_t	i;

	if (!set || !s1)
		return (NULL);
	i = 0;
	if (!*s1 || !ft_strncmp(s1, set, ft_strlen(s1)))
	{
		copy = ft_calloc(1, sizeof(char));
		return (copy);
	}
	copy = (char *)malloc(sizeof(char) * (ft_count_set(s1, set) + 1));
	if (!copy)
		return (NULL);
	while (ft_strchr(set, s1[i]))
		i++;
	ft_strlcpy(copy, &s1[i], ft_count_set(s1, set) + 1);
	return (copy);
}
