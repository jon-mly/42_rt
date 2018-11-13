extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object			intersect_obj(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		ray = sphere_intersect(ray, object);
	else if (object.typpe == PLANE)
		ray = plane_intersect(ray, object);
	else if (object.typpe == CYLINDER)
		ray = (object.finite) 
			? finite_cylinder_intersection(ray, object) 
			: cylinder_intersect(ray, object);
	else if (object.typpe == CONE)
		ray = (object.finite)
			? finite_cone_intersection(ray, object)
			: cone_intersect(ray, object);
	else if (object.typpe == DISC)
		ray = disc_intersection(ray, object);
	else if (object.typpe == RECTANGLE)
		ray = rectangle_intersection(ray, object);
	else if (object.typpe == TRIANGLE)
		ray = triangle_intersection(ray, object);
	else if (object.typpe == PARALLELOGRAM)
		ray = parallelogram_intersection(ray, object);
	else if (object.typpe == HYPERBOLOID)
		ray = hyperboloid_intersection(ray, object);
	if (ray.intersect)
		ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
	return (ray);
}

__device__ t_object		disc_intersection(t_object ray, t_object disc)
{
	ray = plane_intersect(ray, disc);
	if (!ray.intersect)
		return (ray);
	ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
	ray.intersect = vec_norm(vector_pts(ray.intersectiion, disc.point)) < disc.radius;
	return (ray);
}

__device__ t_object		rectangle_intersection(t_object ray, t_object rectangle)
{
	t_vector	intersection_dist;

	ray = plane_intersect(ray, rectangle);
	if (!ray.intersect)
		return (ray);
	ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
	intersection_dist = vector_pts(rectangle.point, ray.intersectiion);
	intersection_dist = rotate_vec_angles(rectangle, intersection_dist, 0);
	ray.intersect = (intersection_dist.x >= 0 && intersection_dist.z >= 0
		&& intersection_dist.x < rectangle.width && intersection_dist.z < rectangle.height);
	return (ray);
}

__device__ t_object		triangle_intersection(t_object ray, t_object triangle)
{
	t_vector	distance;
	float		a;
	float		b;
	float		k;

	distance = vector_pts(triangle.point, ray.origin);
	k = -dot_prod(cross_prod(triangle.second_vect, triangle.first_vect), ray.direction);
	if (k == 0)
		return (ray);
	a = -dot_prod(cross_prod(distance, triangle.first_vect), ray.direction) / k;
	b = -dot_prod(cross_prod(triangle.second_vect, distance), ray.direction) / k;
	ray.intersect = (a >= 0 && b >= 0 && a + b < 1);
	ray.norm = dot_prod(cross_prod(triangle.second_vect, triangle.first_vect), distance) / k;
	return (ray);
}

__device__ t_object		parallelogram_intersection(t_object ray, t_object parallelogram)
{
	t_vector	distance;
	float		a;
	float		b;
	float		k;

	distance = vector_pts(parallelogram.point, ray.origin);
	k = -dot_prod(cross_prod(parallelogram.second_vect, parallelogram.first_vect), ray.direction);
	if (k == 0)
		return (ray);
	a = -dot_prod(cross_prod(distance, parallelogram.first_vect), ray.direction) / k;
	b = -dot_prod(cross_prod(parallelogram.second_vect, distance), ray.direction) / k;
	ray.intersect = (a >= 0 && b >= 0 && a < 1 && b < 1);
	ray.norm = dot_prod(cross_prod(parallelogram.second_vect, parallelogram.first_vect), distance) / k;
	return (ray);
}
