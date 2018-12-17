/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_float.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:26:42 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 16:59:45 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	void	deserialize_float4(float *data, t_object *obj)
{
	obj->first_vect.z = *data;
	data++;
	obj->second_vect.x = *data;
	data++;
	obj->second_vect.y = *data;
	data++;
	obj->second_vect.z = *data;
	data++;
}

static	void	deserialize_float3(float *data, t_object *obj)
{
	obj->origin.z = *data;
	data++;
	obj->intersectiion.x = *data;
	data++;
	obj->intersectiion.y = *data;
	data++;
	obj->intersectiion.z = *data;
	data++;
	obj->direction.x = *data;
	data++;
	obj->direction.y = *data;
	data++;
	obj->direction.z = *data;
	data++;
	obj->normal.x = *data;
	data++;
	obj->normal.y = *data;
	data++;
	obj->normal.z = *data;
	data++;
	obj->first_vect.x = *data;
	data++;
	obj->first_vect.y = *data;
	data++;
	deserialize_float4(data, obj);
}

static	void	deserialize_float2(float *data, t_object *obj)
{
	obj->width = *data;
	data++;
	obj->rho = *data;
	data++;
	obj->sigma = *data;
	data++;
	obj->tau = *data;
	data++;
	obj->center.x = *data;
	data++;
	obj->center.y = *data;
	data++;
	obj->center.z = *data;
	data++;
	obj->point.x = *data;
	data++;
	obj->point.y = *data;
	data++;
	obj->point.z = *data;
	data++;
	obj->origin.x = *data;
	data++;
	obj->origin.y = *data;
	data++;
	deserialize_float3(data, obj);
}

void			deserialize_float(float *data, t_object *obj)
{
	obj->norm = *data;
	data++;
	obj->radius = *data;
	data++;
	obj->angle = *data;
	data++;
	obj->y_angle = *data;
	data++;
	obj->x_angle = *data;
	data++;
	obj->brillance = *data;
	data++;
	obj->diffuse = *data;
	data++;
	obj->reflection = *data;
	data++;
	obj->transparency = *data;
	data++;
	obj->refraction = *data;
	data++;
	obj->height = *data;
	data++;
	deserialize_float2(data, obj);
}
