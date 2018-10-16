/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:14:46 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 13:14:47 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == (unsigned char)c)
			return ((char*)s + i);
	}
	if (s[i] == (unsigned char)c)
		return ((char*)s + i);
	return (NULL);
}
