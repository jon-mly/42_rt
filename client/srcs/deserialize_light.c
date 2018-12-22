/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:01:35 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:12:25 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			deserialize_light(char *data, t_light *light)
{
	t_light			*ltmp;

	ltmp = (t_light *)data;
	*light = *ltmp;
}
