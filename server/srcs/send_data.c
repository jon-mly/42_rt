/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:46:55 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:21:29 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	int			send_nb_light_obj(t_env *e)
{
	e->err = send(e->srv.socket_cl, &e->srv.id, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = send(e->srv.socket_cl, &e->scene.objects_count, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = send(e->srv.socket_cl, &e->scene.lights_count, sizeof(int), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = send(e->srv.socket_cl, &e->scene.theme, sizeof(t_color), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = send(e->srv.socket_cl, &e->scene.power, sizeof(float), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	return (e->err);
}

static t_renderbds	bounds_at(t_env *env, int socket_index, int sockets_count)
{
	t_renderbds		bounds;
	float			top;
	float			bottom;

	top = env->win_height * ((float)socket_index / (float)sockets_count);
	bottom = env->win_height * ((float)(socket_index + 1)
			/ (float)sockets_count);
	bounds.top = (int)floor(top);
	bounds.bottom = (int)floor(bottom) - 1;
	return (bounds);
}

static int			send_render_bounds(t_env *e)
{
	e->err = send(e->srv.socket_cl, (void*)&e->bounds,
			sizeof(t_renderbds), 0);
	return (e->err);
}

static	int			send_cam_scene(t_env *e)
{
	e->err = send(e->srv.socket_cl, &e->camera, sizeof(t_camera), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	e->err = send(e->srv.socket_cl, &e->scene.sett, sizeof(t_settings), 0);
	if (e->err == SOCKET_ERROR)
		return (e->err);
	return (e->err);
}

int					send_obj_light(t_env *e)
{
	e->i = -1;
	if ((e->err = send_nb_light_obj(e)) == SOCKET_ERROR)
		return (e->err);
	e->bounds = bounds_at(e, e->srv.crrnt_sckt_id, e->srv.nbclient);
	if ((e->err = send_render_bounds(e)) == SOCKET_ERROR)
		return (e->err);
	if ((e->err = send_cam_scene(e)) == SOCKET_ERROR)
		return (e->err);
	while (++e->i < e->scene.objects_count)
	{
		serialize_obj(&e->scene.objects[e->i], e->data_o);
		e->err = send(e->srv.socket_cl, (void *)e->data_o, sizeof(t_object), 0);
		if (e->err == SOCKET_ERROR)
			return (e->err);
		nanosleep(&e->tim, &e->tim);
	}
	e->i = -1;
	while (++e->i < e->scene.lights_count)
	{
		serialize_light(&e->scene.lights[e->i], e->data_l);
		e->err = send(e->srv.socket_cl, (void *)e->data_l, sizeof(t_light), 0);
		if (e->err == SOCKET_ERROR)
			return (e->err);
	}
	return (e->err);
}
