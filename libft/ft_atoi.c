/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:12:30 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/12/17 14:44:23 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		neg;
	long	nb;

	nb = 0;
	neg = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' ||
			*str == '\r' || *str == '\v')
		str++;
	if (*str == '+' | *str == '-')
		neg = *(str++) == '-' ? -1 : 1;
	while (ft_isdigit(*str))
		nb = nb * 10 + (*(str++) - 48);
	return ((int)nb * neg);
}
