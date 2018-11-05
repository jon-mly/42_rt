/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:14:05 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/10/23 18:41:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dest_overlap(void *dest, void *src, size_t n)
{
	return (src + n > dest && src + n <= dest + n);
}

void		*ft_memmove(void *dest, void *src, size_t n)
{
	int		i;

	if (dest_overlap(dest, src, n))
	{
		i = n;
		while (--i >= 0)
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
	}
	else
	{
		i = -1;
		while (++i < (int)n)
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
	}
	return (dest);
}
