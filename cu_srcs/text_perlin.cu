extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			perlin_color(t_object object, t_point intersection)
{
	t_point		altered_coordinates;
	t_color		color;
	float		noise;

	altered_coordinates = intersection;
	noise = perlin_noise(10, 0.01, 0.25, altered_coordinates) * 2;
	color.r = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.g = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.b = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.a = 0;
	// color.a = bounded_color_value((1 - noise) * 255, 0, 255);
	return (color);
}

__device__ t_color			wood_color(t_object object, t_point intersection)
{
	t_point		altered_coordinates;
	t_color		color;
	float		noise;

	altered_coordinates = intersection;
	noise = 20 * perlin_noise(5, 0.005, 0.20, altered_coordinates);
	noise -= (int)noise;
	color.r = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.g = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.b = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.a = 0;
	return (color);
}

__device__ t_color			marble_color(t_object object, t_point intersection)
{
	t_point		altered_coordinates;
	t_color		color;
	float		noise;

	altered_coordinates = intersection;
	noise = altered_coordinates.x / 5 + altered_coordinates.y / 18 + altered_coordinates.z / 63;
	noise = cosf(noise + perlin_noise(10, 0.1, 0.10, altered_coordinates) * 5);
	color.r = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.g = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.b = bounded_color_value((1 - noise) / 2 * 255, 0, 255);
	color.a = 0;
	return (color);
}

__device__ float			perlin_noise(int octaves, float frequency, float persistence, t_point point)
{
	float		noise;
	//float		amplitude;
	//float		geometric_limit;
	int			octave;
	t_point		values;

	octave = -1;
	//amplitude = 1.0;
	noise = 0;
	while (++octave < octaves)
	{
		values = (t_point){point.x * frequency * octave,
			point.y * frequency * octave,
			point.z * frequency * octave};
		noise += (1 / octave) * get_perlin_noise_value(values.x, values.y, values.z);
	}
	//geometric_limit = (1 - persistence) / (1 - amplitude);
	// return (noise * geometric_limit);
	// return ((noise * geometric_limit) / 2 + 0.5);
	// return ((1 + noise) / 2);
	return (noise);
}

__device__ float			get_perlin_noise_value(float x, float y, float z)
{
	int			int_x;
	int			int_y;
	int			int_z;
	float		square_noises[8];
	float		polynomials_factors[3];
	float		horizontal_interpolations[4];
	float		vertical_interpolations[2];

	int_x = integer_part(x) % 256;
	int_y = integer_part(y) % 256;
	int_z = integer_part(z) % 256;
	x = fractional_part(x);
	y = fractional_part(y);
	z = fractional_part(z);

	square_noises[0] = dot_prod(get_random_gradient(int_x, int_y, int_z), (t_vector){x, y, z});
	square_noises[1] = dot_prod(get_random_gradient(int_x, int_y, int_z + 1), (t_vector){x, y, z - 1.0});
	square_noises[2] = dot_prod(get_random_gradient(int_x, int_y + 1, int_z), (t_vector){x, y - 1.0, z});
	square_noises[3] = dot_prod(get_random_gradient(int_x, int_y + 1, int_z + 1), (t_vector){x, y - 1.0, z - 1.0});
	square_noises[4] = dot_prod(get_random_gradient(int_x + 1, int_y, int_z), (t_vector){x - 1.0, y, z});
	square_noises[5] = dot_prod(get_random_gradient(int_x + 1, int_y, int_z + 1), (t_vector){x - 1.0, y, z - 1.0});
	square_noises[6] = dot_prod(get_random_gradient(int_x + 1, int_y + 1, int_z), (t_vector){x - 1.0, y - 1.0, z});
	square_noises[7] = dot_prod(get_random_gradient(int_x + 1, int_y + 1, int_z + 1), (t_vector){x - 1.0, y - 1.0, z - 1.0});

	polynomials_factors[0] = perlin_polynom(x);
	polynomials_factors[1] = perlin_polynom(y);
	polynomials_factors[2] = perlin_polynom(z);

	horizontal_interpolations[0] = linear_interpolation(square_noises[0], square_noises[4], polynomials_factors[0]);
	horizontal_interpolations[1] = linear_interpolation(square_noises[2], square_noises[6], polynomials_factors[0]);
	horizontal_interpolations[2] = linear_interpolation(square_noises[1], square_noises[5], polynomials_factors[0]);
	horizontal_interpolations[3] = linear_interpolation(square_noises[3], square_noises[7], polynomials_factors[0]);

	vertical_interpolations[0] = linear_interpolation(horizontal_interpolations[0], horizontal_interpolations[1], polynomials_factors[1]);
	vertical_interpolations[1] = linear_interpolation(horizontal_interpolations[2], horizontal_interpolations[3], polynomials_factors[1]);

	return (linear_interpolation(vertical_interpolations[0], vertical_interpolations[1], polynomials_factors[2]));
}
