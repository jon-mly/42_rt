/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:19:30 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 16:06:18 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*u_dest;
	unsigned char	*u_src;

	i = -1;
	u_dest = (unsigned char*)dest;
	u_src = (unsigned char*)src;
	while (++i < n)
	{
		u_dest[i] = u_src[i];
		if (u_src[i] == (unsigned char)c)
			return (&(u_dest[i + 1]));
	}
	return (NULL);
}
