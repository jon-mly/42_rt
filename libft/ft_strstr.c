/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:11:54 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/09 13:30:15 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		match;

	i = -1;
	if (!(*to_find))
		return ((char*)str);
	while (str[++i])
	{
		if (str[i] == *to_find)
		{
			match = 0;
			while (to_find[match] && str[i + match] == to_find[match])
				match++;
			if (!(to_find[match]))
				return ((char *)str + i);
		}
	}
	return (NULL);
}
