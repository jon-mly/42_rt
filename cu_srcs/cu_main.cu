#include "rt.h"
#include "cu_rt.h"

extern "C" void	init_gpu(t_env *e, t_cuda gpu)
{
	gpu->img_s = WIDTH * HEIGHT;
	gpu->err = 0;
	gpu->data_img = NULL;
	gpu->render_img = NULL;
	gpu->data_obj = NULL;
	gpu->data_scene = NULL;
	gpu->data_cam = NULL;
	gpu->data_light = NULL;
	gpu->img_s = sizeof(int) * WIDTH * HEIGHT;
	gpu->size_obj = sizeof(t_object) * e->scene.objects_count;
	gpu->size_scene = sizeof(t_scene);
	gpu->size_cam = sizeof(t_camera);
	gpu->size_light = sizeof(t_light) * e->scene.lights_count;
}

extern "C" void	malloc_gpu(t_cuda gpu)
{
	if (!(gpu->render_img = (int *)malloc(gpu->img_s)))
	{
		ft_putendl("Error malloc render_img");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMalloc( (void **)&gpu->data_img, gpu->img_s);
	if (gpu->err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc data_img");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMalloc( (void **)&gpu->data_obj, gpu->size_obj);
	if (gpu->err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc gpu_obj");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMalloc( (void **)&gpu->data_scene, gpu->size_scene);
	if (gpu->err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc gpu_scene");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMalloc( (void **)&gpu->data_cam, gpu->size_cam);
	if (gpu->err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc gpu_cam");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMalloc( (void **)&gpu->data_light, gpu->size_light);
	if (gpu->err != cudaSuccess)
	{
		ft_putendl("Error cudaMalloc gpu_light");
		exit(EXIT_FAILURE);
	}
}

extern "C" void	copy_gpu(t_env *e, t_cuda gpu)
{
	gpu->err = cudaMemcpy(gpu->data_obj, e->object, gpu->size_obj, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device data_obj");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMemcpy(gpu->data_scene, e->scene, gpu->size_scene, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device data_scene");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMemcpy(gpu->data_cam, e->cam, gpu->size_cam, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device data_cam");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMemcpy(gpu->data_light, e->light, gpu->size_light, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device data_light");
		exit(EXIT_FAILURE);
	}
}

extern "C" void	call_kernel(t_env *e, t_cuda gpu)
{
	static dim3 grid;
	static dim3 block;

	block(1024, 1024);
	grid(WIDTH/block.x, WIDTH/block.y);
	pix_raytracing <<< grid, block >>> (gpu->render_img, gpu->data_scene, gpu->data_cam, gpu->data_obj, gpu->data_light);
	gpu->err = cudaGetLastError();
	if (gpu->err != cudaSuccess)
	{
		ft_putendl("Error kernel");
		exit(EXIT_FAILURE);
	}
	gpu->err = cudaMemcpy(gpu->render_img, gpu->data_img, gpu->img_s, cudaMemcpyHostToDevice);
	if (err != cudaSuccess)
	{
		ft_putendl("Problem cpy host to device data_light");
		exit(EXIT_FAILURE);
	}
}
