/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cu_rt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:48:09 by aabelque          #+#    #+#             */
/*   Updated: 2018/11/13 12:20:07 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CU_RT_H
# define CU_RT_H

#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
#  define HOST_DEVICE __host__ __device__
# else
#  define HOST_DEVICE
# endif
#endif

#include "../includes/rt.h"

/*
 ** =============== Host function =================
*/
void						init_gpu(t_env *e, t_cuda *gpu);
void						malloc_gpu(t_env *e, t_cuda *gpu);
void						copy_gpu(t_env *e, t_cuda *gpu);
void						call_kernel(t_env *e, t_cuda *gpu);

/*
 ** =============== Device function =================
*/

HOST_DEVICE t_color			raytracing(int x, int y, t_scene *scene,
		t_camera *camera, t_object *obj, t_light *light, float aliasing_var);
HOST_DEVICE t_object		init_primary_ray(int x, int y, t_camera camera,
		float aliasing_variation, int horizontal);
HOST_DEVICE t_color			primary_ray(t_scene *scene, t_object *obj,
		t_light *light, t_object ray, int depth, int refraction);
HOST_DEVICE t_color			average_color(t_color c1, t_color c2);
HOST_DEVICE int				color_to_int(t_color color);
HOST_DEVICE t_color			textured_color_if_needed(t_object object,
		t_point intersection);
HOST_DEVICE t_object		object_with_local_parameters(t_object object,
		t_color local_color);
HOST_DEVICE t_object		init_reflected_ray(t_object original_ray,
		t_object intersected_object);
HOST_DEVICE t_object		init_refracted_ray(t_object original_ray, 
		t_object intersected_object, float next_refraction,
		float next_transparency);
HOST_DEVICE t_color 	add_color(t_color base, t_color overlay);
HOST_DEVICE t_color			direct_light_raytracing(t_scene *scene,
		t_object *obj, t_light *light, t_object ray);
HOST_DEVICE t_color			get_color_on_inters(t_object ray,
		int closest_object_index, t_object intersected_object, t_scene *scene,
		t_light *light, t_object *obj);
HOST_DEVICE t_vector			vector_pts(t_point p1, t_point p2);
HOST_DEVICE t_vector			normalize_vec(t_vector vec);
HOST_DEVICE t_object			intersect_obj(t_object ray, t_object object);
HOST_DEVICE t_vector			point_from_vec(t_point origin, t_vector direction,
		float norm);
HOST_DEVICE unsigned char		maximize_color_value(int color_value);
HOST_DEVICE t_color			procedural_color(t_object object, t_point intersection);
HOST_DEVICE t_color			perlin_algo_texture_color(t_object object, t_point intersection);
HOST_DEVICE t_color			checker_texture_color(t_object object, t_point intersection);
HOST_DEVICE t_color			circles_color(t_object object, t_point intersection, int horizontal);
HOST_DEVICE t_color			dots_color(t_object object, t_point intersection, int invert_gradient, int reverse);
HOST_DEVICE t_color			perlin_color(t_object object, t_point intersection);
HOST_DEVICE t_color			wood_color(t_object object, t_point intersection);
HOST_DEVICE t_color			marble_color(t_object object, t_point intersection);
HOST_DEVICE t_vector			reflected_vector(t_vector incident, t_vector normal);
HOST_DEVICE t_color			fade_color(t_color color, float multiplier);
HOST_DEVICE t_vector			shape_norml(t_object ray, t_object object);
HOST_DEVICE t_vector			refracted_vector(t_object ray, t_object object,
		float next_refraction_index);
HOST_DEVICE t_object			light_plane(t_object ray, t_light light);
HOST_DEVICE t_color			glare_color_from_distance(float distance, t_light light);
HOST_DEVICE t_vector			scale_vector(t_vector vect, float scale);
HOST_DEVICE float				pts_norm(t_point p1, t_point p2);
HOST_DEVICE t_color			ambiant_color(t_scene scene, t_object object);
HOST_DEVICE t_object			get_shadow_ray(t_light light, t_object ray,
		t_object object);
HOST_DEVICE int				hiit_test(t_object clt_obj, t_object obj,
		t_object l_ray, float norm);
HOST_DEVICE t_color			filter_light_through_object(t_color initial_color,
		t_object object);
HOST_DEVICE int				colors_are_equals(t_color c1, t_color c2);
HOST_DEVICE t_object			light_ray_from_shadow_ray(t_object shadow_ray,
		t_light light);
HOST_DEVICE t_color			diffuse_light_for_intersection(t_object light_ray,
		t_object ray, t_object object, t_light light);
HOST_DEVICE t_color			specular_light_for_intersection(t_object light_ray,
		t_object ray, t_object object, t_light light);
HOST_DEVICE float				vec_norm(t_vector vec);
HOST_DEVICE t_vector			sum_vectors(t_vector vect1, t_vector vect2);
HOST_DEVICE float				dot_prod(t_vector vect_1, t_vector vect_2);
HOST_DEVICE t_object			finite_cylinder_intersection(t_object ray,
		t_object cylinder);
HOST_DEVICE t_object			finite_cone_intersection(t_object ray, t_object cone);
HOST_DEVICE t_object			cone_intersect(t_object ray, t_object cone);
HOST_DEVICE t_object			disc_intersection(t_object ray, t_object disc);
HOST_DEVICE t_object			rectangle_intersection(t_object ray,
		t_object rectangle);
HOST_DEVICE t_object			triangle_intersection(t_object ray, t_object triangle);
HOST_DEVICE t_object			parallelogram_intersection(t_object ray,
		t_object parallelogram);
HOST_DEVICE t_object			hyperboloid_intersection(t_object ray,
		t_object hyperboloid);
HOST_DEVICE t_object			sphere_intersect(t_object ray, t_object sphere);
HOST_DEVICE t_object			plane_intersect(t_object ray, t_object plane);
HOST_DEVICE t_object			cylinder_intersect(t_object ray, t_object cylinder);
HOST_DEVICE t_vector			rotate_vec_angles(t_object reference,
		t_vector vect, int reverse);
HOST_DEVICE t_vector			cross_prod(t_vector vect_1, t_vector vect_2);
HOST_DEVICE t_vector			vec_rotate_x(t_vector vector, float angle,
		int inverse);
HOST_DEVICE t_vector			vec_rotate_y(t_vector vector, float angle,
		int inverse);
HOST_DEVICE float				closest_dist_quad(float a, float b, float c);
HOST_DEVICE int				is_texture_even(int value);
HOST_DEVICE t_color			interpolate_color(t_color c1, t_color c2,
		float ratio);
HOST_DEVICE float				perlin_noise(int octaves, float frequency,
		float persistence, t_point point);
HOST_DEVICE float				get_perlin_noise_value(float x, float y, float z);
HOST_DEVICE float				bounded_color_value(float color_value,
		float min_value, float max_value);
HOST_DEVICE int				integer_part(float value);
HOST_DEVICE float				fractional_part(float value);
HOST_DEVICE t_vector			get_random_gradient(int int_x, int int_y, int int_z);
HOST_DEVICE float				perlin_polynom(float value);
HOST_DEVICE float				linear_interpolation(float a, float b, float ratio);
HOST_DEVICE t_vector			hyperboloid_norml(t_object ray, t_object hyperboloid);
HOST_DEVICE t_vector			sphere_norml(t_object ray, t_object sphere);
HOST_DEVICE t_vector			plane_norml(t_object ray, t_object plane);
HOST_DEVICE t_vector			cylinder_norml(t_object ray, t_object cylinder);
HOST_DEVICE t_vector			cone_norml(t_object ray, t_object cone);
HOST_DEVICE t_color			ambiant_light_for_intersection(t_object light_ray,
		t_object ray, t_object object, t_light light);
HOST_DEVICE t_color			projector_light_for_intersection(t_object light_ray,
		t_object ray, t_object object, t_light light);
HOST_DEVICE t_color			omni_light_for_intersection(t_object light_ray,
		t_object ray, t_object object, t_light light);
HOST_DEVICE int				revert_sphere_normal(t_object ray, t_object sphere);
HOST_DEVICE int				projector_color_coord(float intensity, float distance,
		int obj_color, int light_color);
HOST_DEVICE int				omni_color_coord(float cosinus, float distance,
		int obj_color, int light_color);
HOST_DEVICE float				farest_distance_quadratic(float a, float b, float c);
HOST_DEVICE t_color			main_refracted_raytracing(t_scene *scene, t_object *obj,
		t_light *light, t_object ray);
HOST_DEVICE t_color			ponctual_refracted_raytracing(t_scene *scene,
		t_object *obj, t_light *light, t_object ray);
HOST_DEVICE t_color			main_reflected_raytracing(t_scene *scene, t_object *obj,
		t_light *light, t_object ray);
HOST_DEVICE t_color			ponctual_reflected_raytracing(t_scene *scene,
		t_object *obj, t_light *light, t_object ray);
#endif
