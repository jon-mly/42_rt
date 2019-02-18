/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finite_objects_expander_xml.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:12:34 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/18 11:12:40 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	t_scene		create_cylinders_ends(t_object cylinder, t_scene scene,
		int id)
{
	t_object		top_disc;
	t_object		bottom_disc;

	bottom_disc = (t_object){.typpe = DISC, .point = cylinder.point,
		.bump_mapping = cylinder.bump_mapping, .txt_type = cylinder.txt_type,
		.txt_algo = cylinder.txt_algo, .normal = cylinder.direction,
		.color = cylinder.color, .diffuse = cylinder.diffuse,
		.brillance = cylinder.brillance,
		.radius = cylinder.radius, .reflection = cylinder.reflection,
		.refraction = cylinder.refraction,
		.transparency = cylinder.transparency};
	bottom_disc.id = id;
	top_disc = bottom_disc;
	top_disc.point = point_from_vector(bottom_disc.point, cylinder.direction,
			cylinder.height);
	top_disc.id = id;
	scene.objects_count++;
	top_disc.index = scene.objects_count - 1;
	scene.objects = expand_objects(scene.objects, scene.objects_count);
	scene.objects[scene.objects_count - 1] = top_disc;
	scene.objects_count++;
	bottom_disc.index = scene.objects_count - 1;
	scene.objects = expand_objects(scene.objects, scene.objects_count);
	scene.objects[scene.objects_count - 1] = bottom_disc;
	return (scene);
}

static	t_scene		create_cone_end(t_object cone, t_scene scene, int id)
{
	t_object		top_disc;

	top_disc = (t_object){.typpe = DISC, .normal = cone.direction,
		.bump_mapping = cone.bump_mapping, .txt_type = cone.txt_type,
		.color = cone.color, .diffuse = cone.diffuse,
		.brillance = cone.brillance,
		.reflection = cone.reflection, .transparency = cone.transparency,
		.refraction = cone.refraction};
	top_disc.point = point_from_vector(cone.center, cone.direction,
			cone.height);
	top_disc.radius = cone.height * tan(cone.angle);
	top_disc.id = id;
	scene.objects_count++;
	top_disc.index = scene.objects_count - 1;
	scene.objects = expand_objects(scene.objects, scene.objects_count);
	scene.objects[scene.objects_count - 1] = top_disc;
	return (scene);
}

/*
** For finite objects, will create the other objects that are required to
** compose the finite object.
** Assumes that the object given in parameter is finite.
*/

t_scene				create_dependant_objects_xml(t_object object, t_scene scene,
		int id)
{
	if (object.typpe == CYLINDER)
		scene = create_cylinders_ends(object, scene, id);
	else if (object.typpe == CONE)
		scene = create_cone_end(object, scene, id);
	return (scene);
}
