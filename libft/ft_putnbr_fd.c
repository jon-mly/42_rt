/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:14:22 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/13 13:14:23 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int		abs;

	if (nb < 0)
		ft_putchar_fd('-', fd);
	if (nb == 0)
		ft_putchar_fd('0', fd);
	else
	{
		abs = (nb < 0) ? -nb : nb;
		if (abs >= 10)
			ft_putnbr_fd((abs / 10), fd);
		ft_putchar_fd(((abs % 10) + '0'), fd);
	}
}
