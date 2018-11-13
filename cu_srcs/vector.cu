extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_vector		vector_pts(t_point p1, t_point p2)
{
	t_vector	vec;

	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.z = p2.z - p1.z;
	return (vec);
}

__device__ t_vector		normalize_vec(t_vector vec)
{
	float		norm;

	norm = vec_norm(vec);
	vec.x /= norm;
	vec.y /= norm;
	vec.z /= norm;
	return (vec);
}

__device__ t_vector		point_from_vec(t_point origin, t_vector direction, float norm)
{
	t_point		point;

	point.x = origin.x + direction.x * norm;
	point.y = origin.y + direction.y * norm;
	point.z = origin.z + direction.z * norm;
	return (point);
}

__device__ t_vector		reflected_vector(t_vector incident, t_vector normal)
{
	float		dot_coeff;
	t_vector	reflected;

	dot_coeff = dot_prod(scale_vector(incident, 2), normal);
	reflected = scale_vector(normal, -dot_coeff);
	reflected.x += incident.x;
	reflected.y += incident.y;
	reflected.z += incident.z;
	return (normalize_vec(reflected));
}

__device__ t_vector		refracted_vector(t_object ray, t_object object, float next_refraction_index)
{
	t_vector	normal;
	t_vector	refracted;
	float		incident_cos;
	float		refraction_indexes_ratio;

	normal = shape_norml(ray, object);
	refraction_indexes_ratio = ray.refraction / next_refraction_index;
	if (fabs(refraction_indexes_ratio - 1) < EPSILON)
		return (ray.direction);
	incident_cos = 1.0 - pow(refraction_indexes_ratio, 2) * (1.0 - pow(dot_prod(normal, ray.direction), 2));
	refracted = scale_vector(ray.direction, refraction_indexes_ratio);
	refracted = sum_vectors(refracted, scale_vector(normal, -1 * refraction_indexes_ratio * dot_prod(ray.direction, normal)));
	refracted = sum_vectors(refracted, scale_vector(normal, -1 * sqrt(incident_cos)));
	return (normalize_vec(refracted));
}
