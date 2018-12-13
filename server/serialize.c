/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:09:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/13 19:17:50 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	serialize_float(t_object *obj, float *data)
{
	//printf("htonl(obj.x) %f\n", htonl(obj.x));
	//printf("ntohl(obj.x) %f\n", ntohl(obj.x));
//	printf("obj.x %f\n", obj.x);
//	*data = obj.x;
//	printf("serialize *data %f\n", data[0]);
	//printf("*data %f\n", data);
//	data++;
//	*data = obj.y;
//	data++;
//	*data = obj.z;
//	printf("**data %f\n", *data);
	*data = obj->norm;
	printf("**radius %f\n", obj->radius);
	printf("**obj->diff %f\n", obj->diffuse);
	//printf("**data %f\n", *data);
	data++;
	printf("**data %f\n", *data);
	*data = obj->radius;
	printf("**data %f\n", *data);
	data++;
	*data = obj->angle;
	data++;
	*data = obj->y_angle;
	data++;
	*data = obj->x_angle;
	data++;
	*data = obj->brillance;
	data++;
	printf("**diff %f\n", *data);
	*data = obj->diffuse;
	printf("**diff %f\n", *data);
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
static	void	serialize_char(t_object obj, char *data)
{
	int		i;
	
	i = 0;
	while (i < 30)
	{
		*data = obj.name[i];
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
	printf("*hasdensity %d\n", obj->has_density);
	*data = obj->has_density;
	printf("*data %d\n", *data);
	data++;
}

void			serialize_obj(t_object *obj, char *data)
{
	int		*itmp;
	float	*ftmp;
	//char	*ctmp;

	itmp = (int *)data;
	serialize_int(obj, itmp);
	printf("itmp[0] %d\n", itmp[0]);
	printf("itmp[5] %d\n", itmp[5]);
	ftmp = (float *)itmp;
	serialize_float(obj, ftmp);
	//printf("serialize *ftmp %f\n", ftmp[0]);
	//ctmp = (char *)ftmp;
	//serialize_char(obj, ctmp);
}
