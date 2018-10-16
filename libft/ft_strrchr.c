/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:15:37 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 13:15:38 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	if (!(*s))
		return (NULL);
	i = ft_strlen(s) + 1;
	while (--i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char*)s + i);
	}
	if (s[i] == (unsigned char)c)
		return ((char*)s + i);
	return (NULL);
}
