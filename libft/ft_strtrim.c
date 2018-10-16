/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:01:41 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 15:41:02 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static int	get_beginning(char const *s)
{
	int		beginning;

	beginning = 0;
	while (is_space(s[beginning]))
		beginning++;
	return (beginning);
}

static int	get_end(char const *s)
{
	int		end;

	end = ft_strlen(s) - 1;
	while (is_space(s[end]) && end > 0)
		end--;
	return ((end >= 0) ? end : 0);
}

char		*ft_strtrim(char const *s)
{
	int		beginning;
	int		end;
	int		i;
	char	*dest;

	if (!(s))
		return (NULL);
	beginning = get_beginning(s);
	end = get_end(s);
	beginning = (end < beginning) ? end - 1 : beginning;
	if (!(dest = ft_strnew(end - beginning + 1)))
		return (NULL);
	i = -1;
	while (++i + beginning <= end && s[beginning + i])
		dest[i] = s[beginning + i];
	dest[i] = '\0';
	return (dest);
}
