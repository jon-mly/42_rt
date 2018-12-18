/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:09:35 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/18 15:26:01 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			recv_img(t_env *e)
{
	size_t		size_img;

	size_img = sizeof(char) * (WIN_WIDTH * WIN_HEIGHT) * e->bpp;

	e->err = recv(e->srv.socket_cl, &e->img_str, size_img, 0);
	return (e->err);
}
