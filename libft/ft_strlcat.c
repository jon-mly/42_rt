/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:15:21 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 15:28:26 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		src_len;
	size_t		dest_len;

	i = -1;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		src_len += size;
	else
		src_len += dest_len;
	while (src[++i] && i + dest_len + 1 < size)
		dest[i + dest_len] = src[i];
	dest[dest_len + i] = '\0';
	return (src_len);
}
