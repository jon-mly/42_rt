/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:14:13 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 13:14:15 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	unsigned int	abs;

	if (nb < 0)
		ft_putchar('-');
	if (nb == 0)
		ft_putchar('0');
	else
	{
		abs = (nb < 0) ? -nb : nb;
		if (abs >= 10)
			ft_putnbr(abs / 10);
		ft_putchar((abs % 10) + '0');
	}
}
