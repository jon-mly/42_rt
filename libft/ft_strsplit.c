/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:15:45 by jmlynarc          #+#    #+#             */
/*   Updated: 2019/01/06 14:33:55 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, char sep)
{
	return (c == sep || c == '\0');
}

static char	*fill_word(size_t beginning, const char *src, char sep)
{
	char	*word;
	size_t	i;
	size_t	length;

	length = 0;
	while (!is_separator(src[beginning + length], sep))
		length++;
	if (!(word = ft_strnew(length)))
		return (NULL);
	i = -1;
	while (++i < length)
		word[i] = src[beginning + i];
	word[i] = '\0';
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		word;
	size_t		len;

	if (!(s))
		return (NULL);
	i = -1;
	len = 1;
	word = 0;
	while (s[++i])
		len += (i > 0 && !is_separator(s[i - 1], c) && is_separator(s[i], c));
	if (!(tab = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
	{
		if ((i == 0 && !is_separator(s[i], c)) ||
			(i > 0 && is_separator(s[i - 1], c) && !is_separator(s[i], c)))
			tab[word++] = fill_word(i, s, c);
	}
	tab[word] = NULL;
	return (tab);
}
