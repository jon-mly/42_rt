/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:47:20 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 15:39:49 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	if (!(s))
		return (NULL);
	if (!(dest = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		dest[i] = s[i + start];
	return (dest);
}
