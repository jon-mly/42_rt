/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:12:27 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 16:12:39 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*last_created_node;
	t_list		*node_to_add;
	t_list		*first_node;

	last_created_node = NULL;
	while (lst)
	{
		node_to_add = ft_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
		if (last_created_node)
		{
			last_created_node->next = node_to_add;
			last_created_node = last_created_node->next;
		}
		else
		{
			last_created_node = node_to_add;
			first_node = node_to_add;
		}
		lst = lst->next;
	}
	return (first_node);
}
