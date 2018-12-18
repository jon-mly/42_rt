/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:24:22 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/18 17:56:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			*waitcl(void *arg)
{
	t_env		*e;
	t_env		tmp;
	pthread_t	thr;
	pthread_t	thr2[10];
	
	e = (t_env *)arg;
	printf("e : %p\n", (void*)e);
	if (pthread_create(&thr, NULL, await_new_client, e))
	{
		ft_putendl("Error function pthread_create()");
		exit(EXIT_FAILURE);
	}	
	while (e->srv.state == WAIT_CLIENTS)
		;
	pthread_cancel(thr);
	printf("Server state is no more WAIT_CLIENTS\n");
	int i = -1;
	while (++i < e->srv.nbclient)
	{
		tmp = *e;
		tmp.srv.socket_cl = tmp.srv.sockets[i];
		printf("nbclient %d\n", tmp.srv.nbclient);
		if (pthread_create(&thr2[i], NULL, loop_data, &tmp))
		{
			ft_putendl("Error function pthread_create()");
			exit(EXIT_FAILURE);
		}
		if (pthread_join(thr2[i], NULL))
		{
			ft_putendl("Error function pthread_create()");
			exit(EXIT_FAILURE);
		}
	}
	//i = -1;
	//while (++i < e->srv.nbclient)
	//{
//	}
	pthread_exit(NULL);
}

void			*loop_data(void *arg)
{
	t_env		*e;
	int			err;

	e = (t_env *)arg;
	if ((err = send_obj_light(e)) == SOCKET_ERROR)
	{
		perror("send()");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}
