/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:53:05 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/08 17:56:32 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*object;

	if (size == 0)
		return (NULL);
	if (!(object = (void*)malloc(size)))
		return (NULL);
	i = -1;
	while (++i < size)
		((char*)object)[i] = 0;
	return (object);
}
