/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_imgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:08:37 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/27 16:32:06 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_img_to_client(t_env *e)
{
	while (e->srv.
}

int		min_y(int id, int nb_client)
{
	return ((id / nb_client) * HEIGHT);
}

int		max_y(int id, int nb_client)
{
	return ((id + 1 / nb_client) * HEIGHT);
}
