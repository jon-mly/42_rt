extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_vector			shape_norml(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		return (sphere_norml(ray, object));
	else if (object.typpe == PLANE || object.typpe == DISC || object.typpe == RECTANGLE
		|| object.typpe == TRIANGLE || object.typpe == PARALLELOGRAM)
		return (plane_norml(ray, object));
	else if (object.typpe == CYLINDER)
		return (cylinder_norml(ray, object));
	else if (object.typpe == HYPERBOLOID)
		return (hyperboloid_norml(ray, object));
	else
		return (cone_norml(ray, object));
}

__device__ t_vector			hyperboloid_norml(t_object ray, t_object hyperboloid)
{
	t_vector	normal;
	t_vector	distance;

	distance = vector_pts(hyperboloid.center, ray.intersectiion);
	distance = rotate_vec_angles(hyperboloid, distance, 0);
	normal = (t_vector){
		distance.x,
		distance.y,
		-pow(hyperboloid.rho / hyperboloid.sigma, 2) * distance.z
	};
	normal = rotate_vec_angles(hyperboloid, normal, 1);
	return (normalize_vec(normal));
}

__device__ t_vector			sphere_norml(t_object ray, t_object sphere)
{
	t_vector	normal;

	if (revert_sphere_normal(ray, sphere))
		normal = vector_pts(ray.intersectiion, sphere.center);
	else
		normal = vector_pts(sphere.center, ray.intersectiion);
	return (normalize_vec(normal));
}

__device__ t_vector			plane_norml(t_object ray, t_object plane)
{
	t_vector	normal;

	if (dot_prod(ray.direction, plane.normal) <= 0)
		return (normalize_vec(plane.normal));
	normal.x = -(plane.normal.x);
	normal.y = -(plane.normal.y);
	normal.z = -(plane.normal.z);
	return (normalize_vec(normal));
}

__device__ t_vector			cylinder_norml(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_point		normal_point;
	t_vector	normal;

	distance = vector_pts(cylinder.point, ray.intersectiion);
	distance = rotate_vec_angles(cylinder, distance, 0);
	normal_point = (t_point){0, 0, distance.z};
	normal = vector_pts(normal_point, distance);
	if (dot_prod(normalize_vec(normal), rotate_vec_angles(cylinder, ray.direction, 0)) > 0)
		normal = vector_pts(distance, normal_point);
	normal = rotate_vec_angles(cylinder, normal, 1);
	return (normalize_vec(normal));
}
