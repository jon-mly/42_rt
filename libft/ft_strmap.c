/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:37:25 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 15:38:11 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char *s, char (*f)(char))
{
	int		i;
	char	*dest;

	if (!(s))
		return (NULL);
	if (!(dest = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (s[++i])
		dest[i] = (*f)(s[i]);
	dest[i] = '\0';
	return (dest);
}
