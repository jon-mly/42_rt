/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:59:35 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/08 18:02:22 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t		i;
	char		*str;

	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < size)
		str[i] = '\0';
	str[i] = '\0';
	return (str);
}
