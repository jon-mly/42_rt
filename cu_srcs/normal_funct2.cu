extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_vector		cone_norml(t_object ray, t_object cone)
{
	t_vector	distance;
	float		normal_dist;
	t_point		normal_point;
	t_point		normal_point_2;
	t_vector	normal;

	distance = vector_pts(cone.center, ray.intersectiion);
	distance = rotate_vec_angles(cone, distance, 0);
	normal_dist = (cosf(cone.angle) + tan(cone.angle) * sinf(cone.angle)) *
		vec_norm(distance);
	normal_point = (t_point){0, 0, normal_dist};
	normal_point_2 = (t_point){0, 0, -normal_dist};
	if (pts_norm(normal_point, distance) > pts_norm(normal_point_2,
				distance))
		normal_point = normal_point_2;
	normal = vector_pts(normal_point, distance);
	if (dot_prod(normalize_vec(normal), rotate_vec_angles(cone, ray.direction, 0)) > 0)
		normal = vector_pts(distance, normal_point);
	normal = rotate_vec_angles(cone, normal, 1);
	return (normalize_vec(normal));
}

__device__ int			revert_sphere_normal(t_object ray, t_object sphere)
{
	t_vector	distance_vector;

	distance_vector = vector_pts(ray.origin, sphere.center);
	return (vec_norm(distance_vector) < sphere.radius);
}
