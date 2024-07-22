#include "../cub3d.h"

int	is_duplicate(t_addr *list, t_addr *node)
{
	t_addr	*curr;

	curr = list;
	while (curr && curr != node)
	{
		if (curr->address == node->address)
			return (1);
		curr = curr->nxt;
	}
	return (0);
}

void	ft_lstdelone(t_addr *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->address);
		free(lst);
	}
}

void	ft_addrclear(t_addr **lst, void (*del)(void *))
{
	t_addr	*tmp;

	tmp = NULL;
	if (!lst || !del)
		return ;
	while (*lst)
	{
		if (!is_duplicate(*lst, *lst))
		{
			tmp = (*lst)->nxt;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
		else
			*lst = (*lst)->nxt;
	}
	*lst = NULL;
}