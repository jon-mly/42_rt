/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:10:03 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 17:24:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	void	deserialize_uchar(unsigned char *data, t_object *obj)
{
	obj->color.r = *data;
	data++;
	obj->color.g = *data;
	data++;
	obj->color.b = *data;
	data++;
	obj->color.a = *data;
}

static	void	deserialize_int(int *data, t_object *obj)
{
	obj->id = *data;
	printf("Object id : %d\n", obj->id);
	data++;
	obj->index = *data;
	data++;
	obj->intersect = *data;
	data++;
	obj->finite = *data;
	data++;
	obj->covered = *data;
	data++;
	obj->has_density = *data;
	data++;
}

void			deserialize_pt(char *data, t_point *obj)
{
	t_point *ftmp;

	ftmp = (t_point *)data;
	*obj = *ftmp;
	printf("Point x = %.2f, y = %.2f z = %.2f\n", obj->x, obj->y, obj->z);
}

void			deserialize_obj(char *data, t_object *obj)
{
	// int				*itmp;
	// float			*ftmp;
	// unsigned char	*utmp;

	// itmp = (int *)data;
	// deserialize_int(itmp, obj);
	// ftmp = (float *)itmp;
	// deserialize_float(ftmp, obj);
	// utmp = (unsigned char *)ftmp;
	// deserialize_uchar(utmp, obj);
	t_object 	*otmp;
	otmp = (t_object *)data;
	*obj = *otmp;

	// printf("Object :\n");
	// printf("- id : %d\n", obj->id);
	// printf("- index : %d\n", obj->index);
	// printf("- intersect : %d\n", obj->intersect);
	// printf("- finite : %d\n", obj->finite);
	// printf("- covered : %d\n", obj->covered);
	// printf("- has_density : %d\n", obj->has_density);
	// printf("- norm : %.2f\n", obj->norm);
	// printf("- radius : %.2f\n", obj->radius);
	// printf("- angle : %.2f\n", obj->angle);
	// printf("- x_angle : %.2f\n", obj->x_angle);
	// printf("- y_angle : %.2f\n", obj->y_angle);
	// printf("- brillance : %.2f\n", obj->brillance);
	// printf("- diffuse : %.2f\n", obj->diffuse);
	// printf("- reflection : %.2f\n", obj->reflection);
	// printf("- transparency : %.2f\n", obj->transparency);
	// printf("- refraction : %.2f\n", obj->refraction);
	// printf("- height : %.2f\n", obj->height);
	// printf("- width : %.2f\n", obj->width);
	// printf("- rho : %.2f\n", obj->rho);
	// printf("- sigma : %.2f\n", obj->sigma);
	// printf("- tau : %.2f\n", obj->tau);
	// printf("- center : %.2f %.2f %.2f\n", obj->center.x, obj->center.y, obj->center.z);
	// printf("- point : %.2f %.2f %.2f\n", obj->point.x, obj->point.y, obj->point.z);
	// printf("- origin : %.2f %.2f %.2f\n", obj->origin.x, obj->origin.y, obj->origin.z);
	// printf("- intersectiion : %.2f %.2f %.2f\n", obj->intersectiion.x, obj->intersectiion.y, obj->intersectiion.z);
	// printf("- direction : %.2f %.2f %.2f\n", obj->direction.x, obj->direction.y, obj->direction.z);
	// printf("- normal : %.2f %.2f %.2f\n", obj->normal.x, obj->normal.y, obj->normal.z);
	// printf("- first_vect : %.2f %.2f %.2f\n", obj->first_vect.x, obj->first_vect.y, obj->first_vect.z);
	// printf("- second_vect : %.2f %.2f %.2f\n", obj->second_vect.x, obj->second_vect.y, obj->second_vect.z);
	// printf("- color : %u %u %u %u\n", obj->color.r, obj->color.g, obj->color.b, obj->color.a);
}
