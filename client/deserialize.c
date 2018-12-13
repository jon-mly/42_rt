/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:10:03 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/13 18:41:42 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	void	deserialize_int(int *data, t_object *obj)
{
	obj->id = *data;
	data++;
	obj->index = *data;
	data++;
	obj->intersect = *data;
	data++;
	obj->finite = *data;
	data++;
	obj->covered = *data;
	data++;
	//printf("client has_density %d\n", *data);
	obj->has_density = *data;
	//printf("client has_density %d\n", obj->has_density);
	data++;
}

static	void	deserialize_float(float *data, t_object *obj)
{
	//printf("*data %f\n", *data);
//	obj->x = *data;
//	printf("client obj.x %f\n", obj.x);
//	data++;
//	obj->y = *data;
//	printf("client obj.y %f\n", obj.y);
//	data++;
//	obj->z = *data;
//	printf("client obj.z %f\n", obj.z);
	obj->norm = *data;
	data++;
	printf("**client data %f\n", *data);
	obj->radius = *data;
	printf("**client radius %f\n", obj->radius);
	data++;
	obj->angle = *data;
	data++;
	obj->y_angle = *data;
	data++;
	obj->x_angle = *data;
	data++;
	obj->brillance = *data;
	data++;
	printf("**client diff %f\n", *data);
	obj->diffuse = *data;
	printf("**client diff %f\n", obj->diffuse);
	data++;
	obj->reflection = *data;
	data++;
	obj->transparency = *data;
	data++;
	obj->refraction = *data;
	data++;
	obj->height = *data;
	data++;
	obj->width = *data;
	data++;
	obj->rho = *data;
	data++;
	obj->sigma = *data;
	data++;
	data++;
}

static	void	deserialize_char(char *data, t_object obj)
{
	int		i;

	i = 0;
	obj.name = (char *)malloc(sizeof(char) * 20);
	write(1, "y\n", 2);
	while (i < 30)
	{
		printf("*data %c\n", *data);
		write(1, "y\n", 2);
		obj.name[i] = *data;
		printf("name[i] %c\n", obj.name[i]);
		write(1, "y\n", 2);
		data++;
		write(1, "y\n", 2);
		i++;
		write(1, "y\n", 2);
	}
}

void			deserialize_obj(char *data, t_object *obj)
{
	int		*itmp;
	float	*ftmp;
	//char	*ctmp;

	//printf("*data %c\n", *data);
	write(1, "Z\n", 2);
	itmp = (int *)data;
	printf("client data[5] %d\n", data[5]);
	printf("client itmp[5] %d\n", itmp[5]);
	//printf("*ftmp %f\n", *ftmp);
	//printf("*itmp %d\n", *itmp);
	//write(1, "Z\n", 2);
	deserialize_int(itmp, obj);
	write(1, "Z\n", 2);
	ftmp = (float *)itmp;
//	write(1, "Z\n", 2);
	deserialize_float(ftmp, obj);
	//printf("client obj.x %f\n", obj->x);
	//printf("client obj.y %f\n", obj->y);
	//printf("client obj.z %f\n", obj->z);
//	write(1, "Z\n", 2);
	//ctmp = (char *)ftmp;
//	write(1, "Z\n", 2);
	//deserialize_char(ctmp, obj);
	write(1, "Z\n", 2);
}
