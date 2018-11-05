/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 11:46:40 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/11/05 13:41:32 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** A light ray is ignited, beginning from the position of the light itself,
** and directed to the intersection between the initial ray and the closest
** object.
** A base color (shadow color) is given so that, if an object stands
** between the light spot and the intersection, the latter is shadowed.
*/

static t_object		init_light_ray(t_light light, t_object ray, t_object object)
{
	t_object		light_ray;
	t_vector		direction;

	(void)object;
	light_ray.origin = light.posiition;
	direction = vector_points(light_ray.origin, ray.intersectiion);
	light_ray.norm = vector_norm(direction);
	light_ray.direction = normalize_vector(direction);
	light_ray.intersect = FALSE;
	light_ray.color = color(0, 0, 0, 0);
	return (light_ray);
}

/*
** Supposing there is no object between the light and the intersection, the
** color on this point is calculated, based on the angle between the normal
** of the object on a particular point.
*/

static int			color_coord(float cosinus, float distance, int obj_color,
	int light_color)
{
	float	dist_fact;
	float	k;
	float	color_value;

	dist_fact = 0.02 * pow(distance / 1.3, 2) + 1;
	k = sqrt(-cosinus) / dist_fact;
	color_value = ((float)obj_color / (4 * dist_fact)) + k * (float)light_color;
	color_value = fmax(fmin(color_value, 255), 0);
	return ((int)color_value);
}

/*
** Returns the color that has to be applied if the object is enlighted, or its
** shadowed color otherwise.
** - normal: normal vector on the surface. Is oriented outside if the light's
** origin is out of the object, else, the normal will be oriented to the
** inside of the object (for sphere, cones and cylinders).
** - for some angles, the point will be naturally shadowed :
** 	1) 	if the ngle between the light ray and the normal is inferior or equal
** 		to +/-90 degrees.
** 	2)	if the angle between the normal (=> the side that should be enlightened)
** 		and the camera's vector is inferior or equal to +/- 90 degrees.
*/

static t_color		light_for_intersection(t_object light_ray, t_object ray,
		t_object object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	light_ray.intersectiion = ray.intersectiion;
	normal = shape_normal(ray, object);
	if ((object.typpe == CONE || object.typpe == CYLINDER) &&
			dot_product(shape_normal(ray, object),
				shape_normal(light_ray, object)) < 0)
		return ((t_color){0, 0, 0, 0});
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (light_ray.color);
	distance = points_norm(ray.intersectiion, light_ray.origin);
	color.r = color_coord(cosinus, distance, object.color.r, light.color.r);
	color.g = color_coord(cosinus, distance, object.color.g, light.color.g);
	color.b = color_coord(cosinus, distance, object.color.b, light.color.b);
	color.a = 0;
	return (color);
}

static t_color		add_color(t_color base, t_color overlay)
{
	t_color			final;

	final.r = (int)fmin((double)(base.r + overlay.r), (double)255);
	final.g = (int)fmin((double)(base.g + overlay.g), (double)255);
	final.b = (int)fmin((double)(base.b + overlay.b), (double)255);
	final.a = (int)fmin((double)(base.a + overlay.a), (double)255);
	return (final);
}

/*
** For each light  light ray created.
** For each object that is not the intersected one, check if the ray
** intersects with the object. If so, the point on closest_object is shadowed.
** Else, the coloration calculated in the case there is no object in between is
** returned and applied.
*/

t_color				get_color_on_intersection(t_object ray,
		t_object *clt_obj, t_env *e)
{
	t_object		light_r;
	float			norm;
	t_color			col;

	e->light_i = -1;
	col = color(clt_obj->color.r / 4, clt_obj->color.g / 4,
			clt_obj->color.b / 4, 0);
	while (++e->light_i < e->scene.lights_count)
	{
		e->is_direct_hit = 1;
		light_r = init_light_ray(e->scene.lights[e->light_i], ray, *clt_obj);
		norm = light_r.norm;
		e->obj_i = -1;
		while (++e->obj_i < e->scene.objects_count && e->is_direct_hit)
		{
			light_r = intersect_object(light_r, e->scene.objects[e->obj_i]);
			if (hit_test(clt_obj, &e->scene.objects[e->obj_i], light_r, norm))
				e->is_direct_hit = 0;
		}
		if (e->is_direct_hit)
			col = add_color(col, light_for_intersection(light_r, ray,
						*clt_obj, e->scene.lights[e->light_i]));
	}
	return (col);
}
