/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:26:08 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/09 13:31:08 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	size_t		match;

	i = -1;
	if (!(*to_find))
		return ((char*)str);
	while (str[++i] && i < len)
	{
		if (str[i] == *to_find)
		{
			match = 0;
			while (to_find[match] && match + i < len &&
					to_find[match] == str[i + match])
				match++;
			if (!(to_find[match]))
				return ((char*)str + i);
		}
	}
	return (NULL);
}
