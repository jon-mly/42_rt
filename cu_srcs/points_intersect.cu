extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_object		finite_cylinder_intersection(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		closest_norm;
	float		farest_norm;

	distance = vector_pts(cylinder.point, ray.origin);
	ray_dir = rotate_vec_angles(cylinder, ray.direction, 0);
	distance = rotate_vec_angles(cylinder, distance, 0);
	a = powf((float)ray_dir.x, (float)2) + powf((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = powf((float)distance.x, (float)2) + powf((float)distance.y, (float)2) - powf((float)cylinder.radius, (float)2);
	closest_norm = closest_dist_quad(a, b, c);
	farest_norm = farest_distance_quadratic(a, b, c);
	ray.intersect = FALSE;
	if (closest_norm > EPSILON)
	{
		ray.norm = closest_norm;
		ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
		distance = vector_pts(cylinder.point, ray.intersectiion);
		distance = rotate_vec_angles(cylinder, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cylinder.height);
	}
	if (!ray.intersect && farest_norm > EPSILON)
	{
		ray.norm = farest_norm;
		ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
		distance = vector_pts(cylinder.point, ray.intersectiion);
		distance = rotate_vec_angles(cylinder, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cylinder.height);		
	}
	return (ray);
}

__device__ t_object		finite_cone_intersection(t_object ray, t_object cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;
	float		closest_norm;
	float		farest_norm;

	distance = vector_pts(cone.center, ray.origin);
	ray_dir = rotate_vec_angles(cone, ray.direction, 0);
	distance = rotate_vec_angles(cone, distance, 0);
	k = -1 - powf((float)(tanf((float)(cone.angle))), (float)2);
	a = powf((float)vec_norm(ray_dir), (float)2) + k * powf((float)ray_dir.z, (float)2);
	b = 2 * (dot_prod(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = powf((float)vec_norm(distance), (float)2) + k * powf((float)distance.z, (float)2);
	ray.intersect = FALSE;
	closest_norm = closest_dist_quad(a, b, c);
	farest_norm = farest_distance_quadratic(a, b, c);
	if (closest_norm > EPSILON)
	{
		ray.norm = closest_norm;
		ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
		distance = vector_pts(cone.center, ray.intersectiion);
		distance = rotate_vec_angles(cone, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cone.height);
	}
	if (!ray.intersect && farest_norm > EPSILON)
	{
		ray.norm = farest_norm;
		ray.intersectiion = point_from_vec(ray.origin, ray.direction, ray.norm);
		distance = vector_pts(cone.center, ray.intersectiion);
		distance = rotate_vec_angles(cone, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cone.height);		
	}
	return (ray);
}

__device__	t_object		cone_intersect(t_object ray, t_object cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;

	distance = vector_pts(cone.center, ray.origin);
	ray_dir = rotate_vec_angles(cone, ray.direction, 0);
	distance = rotate_vec_angles(cone, distance, 0);
	k = -1 - powf((float)(tanf((float)(cone.angle))), (float)2);
	a = powf((float)vec_norm(ray_dir), (float)2) + k * powf((float)ray_dir.z, (float)2);
	b = 2 * (dot_prod(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = powf((float)vec_norm(distance), (float)2) + k * powf((float)distance.z, (float)2);
	ray.norm = closest_dist_quad(a, b, c);
	if (ray.norm < EPSILON)
		ray.norm = farest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

__device__ t_object			hyperboloid_intersection(t_object ray, t_object hyperboloid)
{
	t_vector		distance;
	t_vector		ray_dir;
	float			a;
	float			b;
	float			c;

	distance = vector_pts(hyperboloid.center, ray.origin);
	ray_dir = rotate_vec_angles(hyperboloid, ray.direction, 0);
	distance = rotate_vec_angles(hyperboloid, distance, 0);
	a = powf(1 / hyperboloid.rho, 2) * (powf(ray_dir.x, 2) + powf(ray_dir.y, 2))
		- powf(1 / hyperboloid.sigma, 2) * powf(ray_dir.z, 2);
	b = 2 * (powf(1 / hyperboloid.rho, 2) * (distance.x * ray_dir.x + distance.y * ray_dir.y)
		- powf(1 / hyperboloid.sigma, 2) * distance.z * ray_dir.z);
	c = powf(1 / hyperboloid.rho, 2) * (powf(distance.x, 2) + powf(distance.y, 2))
		- powf(1 / hyperboloid.sigma, 2) * powf(distance.z, 2) - 1;
	ray.norm = closest_dist_quad(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}
