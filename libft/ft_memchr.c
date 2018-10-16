/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:12:44 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 16:06:22 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = -1;
	while (++i < n)
	{
		if (((unsigned char*)s)[i] == (unsigned char)c)
			return ((unsigned char*)s + i);
	}
	return (NULL);
}
