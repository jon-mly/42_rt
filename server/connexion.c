/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:24:22 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/19 18:45:05 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			*request_rendering(t_env *e)
{
	t_env		tmp[10];
	pthread_t	thr2[10];
	int 		i;
	int		bpp;
	int		s_l;
	int		endian;

	i = -1;
	while (++i < e->srv.nbclient)
	{
		printf("i: %d\n", i);
		tmp[i] = *e;
		tmp[i].srv.socket_cl = tmp[i].srv.sockets[i];
		tmp[i].srv.crrnt_sckt_id = i;
		if (pthread_create(&thr2[i], NULL, loop_data, &tmp[i]))
		{
			ft_putendl("Error function pthread_create()");
			exit(EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < e->srv.nbclient)
	{
		if (pthread_join(thr2[i], NULL))
		{
			ft_putendl("Error function pthread_create()");
			exit(EXIT_FAILURE);
		}
	}
	printf("request addr img %p\n", e->img_str);
	if ((mlx_put_image_to_window(e->mlx_ptr, e->win_ptr,
					e->img_ptr, 0, 0)) == -1)
		ft_putendl("Failed to put image to window");
	ft_putendl("YOUHOU");
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
	printf("Server state is no more WAIT_CLIENTS\n");
	pthread_exit(NULL);
}

void			*loop_data(void *arg)
{
	t_env		*e;
	int			err;
	int 		size;
	char 		*tmp;
	char 		*ptr;

	e = (t_env *)arg;
	size = sizeof(char) * WIN_WIDTH * WIN_HEIGHT * 4;
	if ((tmp = (char*)malloc(size)) == NULL)
		return (NULL);
	ptr = tmp;
	if ((err = send_obj_light(e)) == SOCKET_ERROR)
	{
		perror("send()");
		exit(EXIT_FAILURE);
	}
	while (size > 0)
	{
		if ((err = recv(e->srv.socket_cl, ptr, (int)fmin(1024, size), 0)) < 0)
		{
			perror("recv()");
			exit(EXIT_FAILURE);
		}
		size -= err;
		ptr += err;
	}
	int offset = sizeof(char) * WIN_WIDTH * e->bounds.top * 4;
	size = sizeof(char) * WIN_WIDTH * (1 + e->bounds.bottom - e->bounds.top) * 4;
	ft_memmove(e->img_str + offset, tmp + offset, size);
	free(tmp);
	printf("err %d\n", err);
	pthread_exit(NULL);
}
