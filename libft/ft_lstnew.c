/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:12:36 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 13:12:37 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_node;

	if (!(new_node = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new_node->next = NULL;
	new_node->content_size = (content) ? content_size : 0;
	if (content)
	{
		if (!(new_node->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(new_node->content, content, content_size);
	}
	else
		new_node->content = NULL;
	return (new_node);
}
