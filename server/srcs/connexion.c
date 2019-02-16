/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:47:37 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 18:41:15 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			*request_rendering(t_env *e)
{
	t_env		tmp[10];
	pthread_t	thr2[10];
	int			i;

	i = -1;
	while (++i < e->srv.nbclient)
	{
		tmp[i] = *e;
		tmp[i].srv.socket_cl = tmp[i].srv.sockets[i];
		tmp[i].srv.crrnt_sckt_id = i;
		if (pthread_create(&thr2[i], NULL, loop_data, &tmp[i]))
			ft_error("Error function pthread_create()");
	}
	i = -1;
	while (++i < e->srv.nbclient)
	{
		if (pthread_join(thr2[i], NULL))
			ft_error("Error function pthread_create()");
	}
	if ((mlx_put_image_to_window(e->mlx_ptr, e->win_ptr,
					e->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	return (NULL);
}

void			*waitcl(void *arg)
{
	t_env		*e;
	pthread_t	thr;

	e = (t_env *)arg;
	if (pthread_create(&thr, NULL, await_new_client, e))
	{
		ft_putendl("Error function pthread_create()");
		exit(EXIT_FAILURE);
	}
	while (e->srv.state == WAIT_CLIENTS)
		;
	pthread_cancel(thr);
	pthread_exit(NULL);
}

void			*loop_data(void *arg)
{
	t_env		*e;
	char		*tmp;
	char		*ptr;

	e = (t_env *)arg;
	e->size = e->img_width * e->img_height * 4 * sizeof(char);
	if ((tmp = (char*)malloc(e->size)) == NULL)
		return (NULL);
	ptr = tmp;
	if ((e->err = send_obj_light(e)) == SOCKET_ERROR)
		ft_error("send_obj_light()");
	while (e->size > 0)
	{
		if ((e->err = recv(e->srv.socket_cl, ptr,
						(int)fmin(1024, e->size), 0)) < 0)
			ft_error("recv()");
		e->size -= e->err;
		ptr += e->err;
	}
	e->offset = sizeof(char) * e->img_width * e->bounds.top * 4;
	e->size = sizeof(char) * e->img_width * (1 + e->bounds.bottom
			- e->bounds.top) * 4;
	ft_memmove(e->img_str + e->offset, tmp + e->offset, e->size);
	free(tmp);
	pthread_exit(NULL);
}
