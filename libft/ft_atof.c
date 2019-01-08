/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:41:14 by aabelque          #+#    #+#             */
/*   Updated: 2018/10/23 13:21:10 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double		ft_get_dec(const char *str)
{
	double	nb;
	double	dec;
	int		i;
	int		j;

	nb = 0.0;
	dec = 0.0;
	i = 0;
	j = 0;
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10.0) + (*(str++) - '0');
	if (*(str++) == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			dec = (dec * 10.0) + (*(str++) - '0');
			i++;
		}
	}
	while (j++ < i)
		dec /= 10.0;
	return (nb + dec);
}

double				ft_atof(const char *str)
{
	int		sign;
	double	res;

	res = 0.0;
	sign = 1;
	if (!*str)
		return (0);
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
			|| *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	res = ft_get_dec(str) * sign;
	return (res);
}
