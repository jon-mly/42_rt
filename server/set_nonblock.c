/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nonblock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:07:52 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/28 13:10:35 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	set_nblock(int *sock, bool chx)
{
	int	flag;

	flag = fcntl(*sock, F_GETFL);
	if (chx == true)
		fcntl(*sock, F_SETFL, flag | O_NONBLOCK);
	else
		fcntl(*sock, F_SETFL, flag | O_ASYNC);
}
