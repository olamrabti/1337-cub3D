/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:23:45 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/02 01:10:18 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*safe_alloc(t_addr **addr, size_t count, size_t size)
{
	char	*copy;

	if (count != 0 && size > 9223372036854775807ULL / count)
		return (NULL);
	copy = malloc(count * size);
	if (!copy)
		exit(1);
	ft_bzero(copy, size * count);
	add_addr(addr, new_addr(copy));
	return (copy);
}

t_addr	*new_addr(void *value)
{
	t_addr	*node;

	node = malloc(sizeof(t_addr));
	if (!node)
		exit(1);
	node->nxt = NULL;
	node->address = value;
	return (node);
}

int	add_addr(t_addr **list, t_addr *new)
{
	t_addr	*temp;

	if (!list || !new)
		return (1);
	new->nxt = NULL;
	if (!*list)
	{
		*list = new;
		return (0);
	}
	temp = *list;
	while (temp->nxt != NULL)
	{
		temp = temp->nxt;
	}
	temp->nxt = new;
	return (0);
}
