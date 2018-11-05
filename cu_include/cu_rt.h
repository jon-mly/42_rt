#ifndef CU_RT_H
# define CU_RT_H

#ifdef __cplusplus
extern "C"
#endif

void	init_gpu(t_env *e, t_cuda gpu);
void	malloc_gpu(t_cuda gpu);
void	copy_gpu(t_env *e, t_cuda gpu);
void	call_kernel(t_env *e, t_cuda gpu);
#endif
