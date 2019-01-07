/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:50:34 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 10:14:13 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_env_server(t_env *e)
{
	e->srv.id = -1;
	e->srv.nbclient = 0;
	e->srv.sz = 0;
	e->srv.sockmax = 0;
	e->srv.socket = 0;
	e->srv.err = 0;
	e->err = 0;
	e->srv.size_cl = 0;
	e->srv.sin_sz = 0;
	ft_memset(&e->srv.sin, 0, sizeof(e->srv.sin));
	e->srv.sin.sin_addr.s_addr = htonl(INADDR_ANY);
	e->srv.sin.sin_family = AF_INET;
	e->srv.sin.sin_port = htons(e->srv.port);
	e->srv.state = WAIT_CLIENTS;
	e->tim = (struct timespec){0, 500000};
}
