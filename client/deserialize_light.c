/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:01:35 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 12:53:38 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	void	deserialize_ulight(unsigned char *data, t_light *light)
{
	light->color.r = *data;
	data++;
	light->color.g = *data;
	data++;
	light->color.b = *data;
	data++;
	light->color.a = *data;
}

static	void	deserialize_flight(float *data, t_light *light)
{
	light->angle = *data;
	data++;
	light->power = *data;
	data++;
	light->posiition.x = *data;
	data++;
	light->posiition.y = *data;
	data++;
	light->posiition.z = *data;
	data++;
	light->direction.x = *data;
	data++;
	light->direction.y = *data;
	data++;
	light->direction.z = *data;
	data++;
}

void			deserialize_light(char *data, t_light *light)
{
	float			*ftmp;
	unsigned char	*utmp;

	ftmp = (float *)data;
	deserialize_flight(ftmp, light);
	utmp = (unsigned char *)ftmp;
	deserialize_ulight(utmp, light);

	// printf("Light :\n");
	// printf("- angle : %.2f\n", light->angle);
	// printf("- power : %.2f\n", light->power);
	// printf("- position : %.2f %.2f %.2f\n", light->posiition.x, light->posiition.y, light->posiition.z);
	// printf("- direction : %.2f %.2f %.2f\n", light->direction.x, light->direction.y, light->direction.z);
	// printf("- color : %u %u %u %u\n", light->color.r, light->color.g, light->color.b, light->color.a);
}
