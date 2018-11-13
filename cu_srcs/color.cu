extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color		average_color(t_color c1, t_color c2)
{
	t_color		final;

	final.r = (c1.r + c2.r) / 2;
	final.g = (c1.g + c2.g) / 2;
	final.b = (c1.b + c2.b) / 2;
	final.a = (c1.a + c2.a) / 2;
	return (final);
}

__device__ int			color_to_int(t_color color)
{
	int 	r;
	int 	g;
	int		b;
	int 	a;

	r = (int)color.r;
	g = (int)color.g;
	b = (int)color.b;
	a = (int)color.a;
	return (a << 24 | r << 16 | g << 8 | b);
}

__device__ t_color		add_color(t_color base, t_color overlay)
{
	t_color 	final;

	final.r = maximize_color_value(base.r + overlay.r);
	final.g = maximize_color_value(base.g + overlay.g);
	final.b = maximize_color_value(base.b + overlay.b);
	final.a = maximize_color_value(base.a + overlay.a);
	return (final);
}

__device__ unsigned char	maximize_color_value(int color_value)
{
	return ((unsigned char)(fmaxf(fminf((float)color_value, (float)255), 0)));
}

__device__ t_color		fade_color(t_color color, float multiplier)
{
	color.r = (unsigned char)((float)color.r * multiplier);
	color.g = (unsigned char)((float)color.g * multiplier);
	color.b = (unsigned char)((float)color.b * multiplier);
	color.a = (unsigned char)((float)color.a * multiplier);
	return (color);
}

__device__ float		pts_norm(t_point p1, t_point p2)
{
	float		distance;

	distance = sqrt((float)(pow((float)(p2.x - p1.x), (float)2) + pow((float)(p2.y - p1.y), (float)2) + pow((float)(p2.z - p1.z), (float)2)));
	return (distance);
}

__device__ int			colors_are_equals(t_color c1, t_color c2)
{
	return (c1.r == c2.r
		&& c1.g == c2.g
		&& c1.b == c2.b
		&& c1.a == c2.a);
}
