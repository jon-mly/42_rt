/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 09:55:05 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 12:53:38 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	serialize_ulight(t_light *light, unsigned char *data)
{
	*data = light->color.r;
	data++;
	*data = light->color.g;
	data++;
	*data = light->color.b;
	data++;
	*data = light->color.a;
}

static	void	serialize_flight(t_light *light, float *data)
{
	*data = light->angle;
	data++;
	*data = light->power;
	data++;
	*data = light->posiition.x;
	data++;
	*data = light->posiition.y;
	data++;
	*data = light->posiition.z;
	data++;
	*data = light->direction.x;
	data++;
	*data = light->direction.y;
	data++;
	*data = light->direction.z;
	data++;
}

void			serialize_light(t_light *light, char *data)
{
	float			*ftmp;
	unsigned char	*utmp;

	ftmp = (float *)data;
	serialize_flight(light, ftmp);
	utmp = (unsigned char *)ftmp;
	serialize_ulight(light, utmp);
}
