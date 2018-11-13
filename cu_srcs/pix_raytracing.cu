extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

__device__ t_color			raytracing(int x, int y, t_scene *scene, t_camera *camera, t_object *obj, t_light *light, float aliasing_var)
{
	t_object			ray;
	t_color				horizontal_color;
	t_color				vertical_color;

	ray = init_primary_ray(x, y, *camera, aliasing_var, 0);
	horizontal_color = primary_ray(scene, obj, light, ray, 0, 0);
	if (aliasing_var == 0 || aliasing_var == 1)
		return (horizontal_color);
	ray = init_primary_ray(x, y, *camera, aliasing_var, 1);
	vertical_color = primary_ray(scene, obj, light, ray, 0, 0);
	return (average_color(horizontal_color, vertical_color));
}

__global__ void pixRaytracing(int *img, t_scene *scene, t_camera *cam, t_object *obj, t_light *light)
{
	int		x;
	int		y;
	int		idx;
	int		aliasing_iter;
	float	aliasing_var;
	t_color	average;

	x = blockIdx.x * blockDim.x + threadIdx.x;
	y = blockIdx.y * blockDim.y + threadIdx.y;
	idx = y * WIN_WIDTH + x;
	if (x == 0 && y == 0)
	{
		printf("camera width: %f\n", cam->width);
		printf("camera height: %f\n", cam->height);
	}
	aliasing_iter = -1;
	while (++aliasing_iter < ALIASING)
	{
		aliasing_var = (float)aliasing_iter / (float)ALIASING;
		if (aliasing_iter == 0 || aliasing_iter == 1)
			average = raytracing(x, y, scene, cam, obj, light, aliasing_var);
		else
			average = average_color(average, raytracing(x, y, scene, cam, obj, light, aliasing_var));
	}
	if (x == 0 && y == 0)
		printf("average: %d\n", color_to_int(average));
	img[idx] = color_to_int(average);
}

void	call_kernel(t_env *e, t_cuda *gpu)
{
	cudaError_t			err;
	static dim3 block(8, 8);
	static dim3 grid(WIN_WIDTH/block.x, WIN_HEIGHT/block.y);
	
	printf("camera width: %f\n", e->camera.width);
	printf("camera height: %f\n", e->camera.height);
	//printf("block.x = %d\n block.y = %d\n", block.x, block.y);
	//printf("grid.x = %d\n grid.y = %d\n", grid.x, grid.y);
	pixRaytracing<<<1, 1>>>(gpu->d_img, gpu->d_scene, gpu->d_cam, gpu->d_obj, gpu->d_light);
	err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		ft_putendl("Error kernel");
		printf("error: %d %s\n", err, cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	err = cudaMemcpy(gpu->render_img, gpu->d_img, gpu->img_s, cudaMemcpyDeviceToHost);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy device to host d_img");
		printf("error: %d\n", err);
		exit(EXIT_FAILURE);
	}
}
