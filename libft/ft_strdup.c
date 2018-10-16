/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:41:11 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/09 12:44:53 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	if (!(dest = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (s[++i])
		dest[i] = s[i];
	return (dest);
}
