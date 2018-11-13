extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object		sphere_intersect(t_object ray, t_object sphere)
{
	float		a;
	float		b;
	float		c;
	t_vector	distance;

	distance = vector_pts(sphere.center, ray.origin);
	a = dot_prod(ray.direction, ray.direction);
	b = 2 * dot_prod(ray.direction, distance);
	c = dot_prod(distance, distance) - pow((float)sphere.radius, (float)2);
	ray.norm = closest_dist_quad(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

__device__ t_object	plane_intersect(t_object ray, t_object plane)
{
	if (dot_prod(plane.normal, ray.direction) == 0)
	{
		ray.intersect = FALSE;
		return (ray);
	}
	ray.norm = (dot_prod(plane.normal, plane.point) - dot_prod(plane.normal,
			ray.origin)) / dot_prod(plane.normal, ray.direction);
	ray.intersect = (ray.norm > 0 || ray.norm < 10000000);
	return (ray);
}

__device__ t_object		cylinder_intersect(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;

	distance = vector_pts(cylinder.point, ray.origin);
	ray_dir = rotate_vec_angles(cylinder, ray.direction, 0);
	distance = rotate_vec_angles(cylinder, distance, 0);
	a = pow((float)ray_dir.x, (float)2) + pow((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow((float)distance.x, (float)2) + pow((float)distance.y, (float)2) - pow((float)cylinder.radius, (float)2);
	ray.norm = closest_dist_quad(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}
