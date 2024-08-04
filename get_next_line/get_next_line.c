/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:30:06 by olamrabt          #+#    #+#             */
/*   Updated: 2024/08/02 11:44:53 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strchrnl(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

 void ft_free(char *str)
{
	free(str);
	str = NULL;
}
char	*ft_fill_stock(int fd, char *stock)
{
	char	*buffer;
	int		i;
	int		j;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || read(fd, NULL, 0) < 0)
		return (ft_free(stock), NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(stock), NULL);
	while (1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (ft_free(buffer), ft_free(stock), NULL);
		if (i == 0)
			break ;
		buffer[i] = '\0';
		stock = ft_strjoin(stock, buffer);
		j = 0;
		if (ft_strchrnl(buffer))
			return (ft_free(buffer), (stock));
	}
	return (ft_free(buffer), (stock));
}

char	*ft_getline(char *stock)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		line = malloc(sizeof(char) * (i + 1));
	else
		line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = stock[j];
		j++;
	}
	if (stock[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_updatestock(char *str, size_t i)
{
	char	*copy;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str + i);
	if (len == 0)
		return (ft_free(str), NULL);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (ft_free(str), NULL);
	j = 0;
	while (str[i])
		copy[j++] = str[i++];
	copy[j] = '\0';
	ft_free(str);
	return (copy);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	line = NULL;
	stock = ft_fill_stock(fd, stock);
	if (!stock)
		return (NULL);
	line = ft_getline(stock);
	if (!line)
		return (ft_free(stock), NULL);
	stock = ft_updatestock(stock, ft_strlen(line));
	return (line);
}
