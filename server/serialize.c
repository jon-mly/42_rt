/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:09:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/12 19:10:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	serialize_float(t_object *obj, float *data)
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
	*data = obj->width;
	data++;
	*data = obj->rho;
	data++;
	*data = obj->sigma;
	data++;
	data++;
}
static	void	serialize_char(t_object *obj, char *data)
{
	int		i;
	
	i = 0;
	while (i < 20)
	{
		*data = obj->name[i];
		data++;
		i++;
	}
}
static	void	serialize_int(t_object *obj, int *data)
{
	*data = obj->id;
	data++;
	*data = obj->index;
	data++;
	*data = obj->intersect;
	data++;
	*data = obj->finite;
	data++;
	*data = obj->covered;
	data++;
	*data = obj->has_density;
	data++;
}

void			serialize_obj(t_object *obj, char *data)
{
	//int		*itmp;
	float	*ftmp;
	char	*ctmp;

	int *itmp = (int *)data;
	serialize_int(obj, itmp);
	ftmp = (float *)itmp;
	serialize_float(obj, ftmp);
	ctmp = (char *)ftmp;
	serialize_char(obj, ctmp);
}
