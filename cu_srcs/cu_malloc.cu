extern "C" {
	#include <rt.h>
	#include "cu_rt.h"
}

#include <cuda.h>
#include <cuda_runtime.h>

void	init_gpu(t_env *e, t_cuda *gpu)
{
	gpu->img_s = WIN_WIDTH * WIN_HEIGHT;
	gpu->d_img = NULL;
	gpu->render_img = NULL;
	gpu->d_obj = NULL;
	gpu->d_scene = NULL;
	gpu->d_cam = NULL;
	gpu->d_light = NULL;
	gpu->img_s = sizeof(int) * WIN_WIDTH * WIN_HEIGHT;
	gpu->size_obj = sizeof(t_object) * e->scene.objects_count;
	gpu->size_scene = sizeof(t_scene);
	gpu->size_cam = sizeof(t_camera);
	gpu->size_light = sizeof(t_light) * e->scene.lights_count;
}

void checkGpuMem()
{

	float free_m,total_m,used_m;

	size_t free_t,total_t;

	cudaMemGetInfo(&free_t,&total_t);

	free_m =(uint)free_t/1048576.0 ;

	total_m=(uint)total_t/1048576.0;

	used_m=total_m-free_m;

	printf ( "  mem free %lu .... %f MB mem total %lu....%f MB mem used %f MB\n",free_t,free_m,total_t,total_m,used_m);

}

void	malloc_gpu(t_env *e, t_cuda *gpu)
{
	cudaError_t			err;
	
	if (!(gpu->render_img = (int *)malloc(gpu->img_s)))
	{
		ft_putendl("Error malloc render_img");
		exit(EXIT_FAILURE);
	}
	checkGpuMem();
	err = cudaMalloc( (void **)&gpu->d_img, gpu->img_s);
	if (err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc d_img");
		exit(EXIT_FAILURE);
	}
	//checkGpuMem();
	err = cudaMalloc( (void **)&gpu->d_obj, gpu->size_obj);
	if (err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc d_obj");
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc( (void **)&gpu->d_scene, gpu->size_scene);
	if (err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc d_scene");
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc( (void **)&gpu->d_cam, gpu->size_cam);
	if (err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc d_cam");
		exit(EXIT_FAILURE);
	}
	err = cudaMalloc( (void **)&gpu->d_light, gpu->size_light);
	if (err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc d_light");
		exit(EXIT_FAILURE);
	}
}

void	copy_gpu(t_env *e, t_cuda *gpu)
{
	cudaError_t			err;
	
	err = cudaMemcpy(gpu->d_obj, e->scene.objects, gpu->size_obj, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device d_obj");
		exit(EXIT_FAILURE);
	}
	err = cudaMemcpy(gpu->d_scene, &e->scene, gpu->size_scene, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device d_scene");
		exit(EXIT_FAILURE);
	}
	err = cudaMemcpy(gpu->d_cam, &e->camera, gpu->size_cam, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device d_cam");
		exit(EXIT_FAILURE);
	}
	err = cudaMemcpy(gpu->d_light, e->scene.lights, gpu->size_light, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device d_light");
		exit(EXIT_FAILURE);
	}
}
