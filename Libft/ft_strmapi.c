/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:31:13 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/17 11:46:13 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*copy;

	i = 0;
	if (!s || !f)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = f(i, s[i]);
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
