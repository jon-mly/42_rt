/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:30:34 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/06 20:13:17 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	int		recv_nb_light_obj(t_env *e)
{
	e->err = recv(e->srv.socket, &e->srv.id, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->obj_ct, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->light_ct, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->scene.theme, sizeof(t_color), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->scene.power, sizeof(float), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->scene.objects_count = e->obj_ct;
	e->scene.lights_count = e->light_ct;
	if (!(e->scene.objects = (t_object *)malloc(sizeof(t_object) * e->obj_ct)))
		exit(EXIT_FAILURE);
	if (!(e->scene.lights = (t_light *)malloc(sizeof(t_light) * e->light_ct)))
		exit(EXIT_FAILURE);
	return (e->err);
}

static int		recv_render_bounds(t_env *e)
{
	e->err = recv(e->srv.socket, &e->bounds, sizeof(t_render_bounds), 0);
	e->scene.top_bound = e->bounds.top;
	e->scene.bottom_bound = e->bounds.bottom;
	return (e->err);
}

static	int		recv_cam_scene(t_env *e)
{
	e->err = recv(e->srv.socket, &e->camera, sizeof(t_camera), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = recv(e->srv.socket, &e->scene.sett, sizeof(t_settings), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	return (e->err);
}

int				recv_obj_light(t_env *e)
{
	e->i = -1;
	if ((e->err = recv_nb_light_obj(e)) == SOCKET_ERROR)
		return (e->err);
	if ((e->err = recv_render_bounds(e)) == SOCKET_ERROR)
		return (e->err);
	if ((e->err = recv_cam_scene(e)) == SOCKET_ERROR)
		return (e->err);
	while (++e->i < e->obj_ct)
	{
		e->err = recv(e->srv.socket, (void *)e->data_o, sizeof(t_object), 0);
		if (e->err == SOCKET_ERROR)
			return (e->err);
		deserialize_obj(e->data_o, &e->scene.objects[e->i]);
	}
	e->i = -1;
	while (++e->i < e->light_ct)
	{
		ft_bzero(e->data_l, sizeof(t_light));
		e->err = recv(e->srv.socket, (void *)e->data_l, sizeof(t_light), 0);
		if (e->err == SOCKET_ERROR)
			return (e->err);
		deserialize_light(e->data_l, &e->scene.lights[e->i]);
	}
	return (e->err);
}
