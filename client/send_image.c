/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:51:47 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/18 15:26:00 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			send_img(t_env *e)
{
	size_t		size_img;

	size_img = sizeof(char) * e->opcl.img_s * e->bpp;
	e->err = send(e->srv.socket, e->img_str, size_img, 0);
	return (e->err);
}
