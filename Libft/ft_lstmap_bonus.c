/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:36:34 by olamrabt          #+#    #+#             */
/*   Updated: 2023/11/17 11:24:45 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		temp = lst->next;
		new = ft_lstnew(NULL);
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new->content = f(lst->content);
		ft_lstadd_back(&head, new);
		lst = temp;
	}
	return (head);
}
