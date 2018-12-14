/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:10:35 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/14 15:47:23 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	serialize_float4(t_object *obj, float *data)
{
	*data = obj->first_vect.z;
	data++;
	*data = obj->second_vect.x;
	data++;
	*data = obj->second_vect.y;
	data++;
	*data = obj->second_vect.z;
	data++;
}

static	void	serialize_float3(t_object *obj, float *data)
{
	*data = obj->origin.z;
	data++;
	*data = obj->intersectiion.x;
	data++;
	*data = obj->intersectiion.y;
	data++;
	*data = obj->intersectiion.z;
	data++;
	*data = obj->direction.x;
	data++;
	*data = obj->direction.y;
	data++;
	*data = obj->direction.z;
	data++;
	*data = obj->normal.x;
	data++;
	*data = obj->normal.y;
	data++;
	*data = obj->normal.z;
	data++;
	*data = obj->first_vect.x;
	data++;
	*data = obj->first_vect.y;
	data++;
	serialize_float4(obj, data);
}

static	void	serialize_float2(t_object *obj, float *data)
{
	*data = obj->width;
	data++;
	*data = obj->rho;
	data++;
	*data = obj->sigma;
	data++;
	*data = obj->tau;
	data++;
	printf("serialize obj->center.x %f\n", obj->center.x);
	*data = obj->center.x;
	printf("serialize *data %f\n", *data);
	data++;
	*data = obj->center.y;
	data++;
	*data = obj->center.z;
	data++;
	*data = obj->point.x;
	data++;
	*data = obj->point.y;
	data++;
	*data = obj->point.z;
	data++;
	*data = obj->origin.x;
	data++;
	*data = obj->origin.y;
	data++;
	serialize_float3(obj, data);
}

void			serialize_float(t_object *obj, float *data)
{
	*data = obj->norm;
	data++;
	*data = obj->radius;
	data++;
	*data = obj->angle;
	data++;
	*data = obj->y_angle;
	data++;
	*data = obj->x_angle;
	data++;
	*data = obj->brillance;
	data++;
	*data = obj->diffuse;
	data++;
	*data = obj->reflection;
	data++;
	*data = obj->transparency;
	data++;
	*data = obj->refraction;
	data++;
	*data = obj->height;
	data++;
	serialize_float2(obj, data);
}
