/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:12:54 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 13:12:55 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(int nb)
{
	size_t	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb /= 10;
	}
	return ((len > 0) ? len : 1);
}

static void		fill_str(int nb, char *str, size_t size, int neg)
{
	size_t			i;
	unsigned int	abs;

	i = size - 1 + neg;
	abs = nb * ((neg) ? -1 : 1);
	if (abs == 0)
		str[0] = '0';
	while (abs != 0)
	{
		str[i--] = (abs % 10) + '0';
		abs /= 10;
	}
}

char			*ft_itoa(int nb)
{
	char	*str;
	size_t	size;

	size = len(nb);
	if (!(str = ft_strnew(size + (nb < 0))))
		return (NULL);
	if (nb < 0)
		str[0] = '-';
	fill_str(nb, str, size, (nb < 0));
	str[size + 1 + (nb < 0)] = '\0';
	return (str);
}
