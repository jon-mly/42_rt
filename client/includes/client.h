/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillaume <guillaume@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:29:01 by aabelque          #+#    #+#             */
/*   Updated: 2019/02/16 17:01:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
** ====== includes
*/

# include "../../libft/libft.h"
# include "../../minilibx/mlx.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <pthread.h>
# include <signal.h>

# ifdef __APPLE__
#  include <OpenCL/cl.h>
# else
#  include <CL/cl.h>
# endif

/*
** ======= macros
*/

# define DEFAULT_SIZE 100
# define FOV 0.50

# define KEY_ESC 53

# define TRUE 1
# define FALSE 0
# define SOCKET_ERROR -1

# define SIZE_OBJ sizeof(t_object)
# define SIZE_LIGHT sizeof(t_light)

/*
** ======= enumerations
*/

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct hostent		t_hostent;

typedef enum	e_object_type
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE,
	DISC,
	RECTANGLE,
	TRIANGLE,
	PARALLELOGRAM,
	HYPERBOLOID
}				t_object_type;

typedef enum	e_light_type
{
	OMNI = 0,
	AMBIANT,
	PROJECTOR
}				t_light_type;

typedef enum			e_texture
{
	NONE = 0,
	CHECKER,
	HORIZONTAL_CIRCLE,
	VERTICAL_CIRCLE,
	DOTS,
	DOTS_REVERTED,
	DOTS_CROWN,
	DOTS_REVERTED_CROWN,
	PERLIN,
	WOOD,
	MARBLE
}						t_texture;

typedef enum			e_texture_algo
{
	NO_ALGO = 0,
	PROCEDURAL,
	PERLIN_ALGO
}						t_texture_algo;

typedef enum			e_bump_mapping
{
	FLAT = 0,
	VERTICAL_SIN,
	HORIZONTAL_SIN
}						t_bump_mapping;

typedef enum				e_client_state
{
	WAIT_DATA = 0,
	RENDERING,
	SENDING
}							t_client_state;

typedef enum				e_server_state
{
	WAIT_CLIENTS = 0,
	WAIT_RENDER,
	DISPLAY_RENDER
}							t_server_state;

/*
** ======= structures
*/

typedef struct				s_pixel
{
	int					x;
	int					y;
}							t_pixel;

typedef struct				s_vector
{
	float				x;
	float				y;
	float				z;
}							t_vector;

typedef t_vector			t_point;

typedef struct				s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;
}							t_color;

typedef struct				s_object
{
	int					id;
	int					index;
	int					intersect;
	int					finite;
	int					covered;
	int					has_density;
	float				norm;
	float				radius;
	float				angle;
	float				y_angle;
	float				x_angle;
	float				brillance;
	float				diffuse;
	float				reflection;
	float				transparency;
	float				refraction;
	float				height;
	float				width;
	float				rho;
	float				sigma;
	float				tau;
	t_point				center;
	t_point				point;
	t_point				origin;
	t_point				intersectiion;
	t_vector			direction;
	t_vector			normal;
	t_vector			first_vect;
	t_vector			second_vect;
	t_color				color;
	t_object_type		typpe;
	t_texture			texture_type;
	t_texture_algo		texture_algo;
	t_bump_mapping		bump_mapping;
}							t_object;

typedef struct				s_light
{
	float				angle;
	float				power;
	t_point				posiition;
	t_vector			direction;
	t_color				color;
	t_light_type		typpe;
}							t_light;

typedef struct				s_camera
{
	t_vector			posiition;
	t_vector			direction;
	t_vector			discplane;
	t_point				spot;
	t_vector			normal;
	t_vector			up_left_corner;
	t_vector			horizontal_vect;
	t_vector			vertical_vect;
	float				width;
	float				height;
	float				plane_dist;
	float				horizontal_step;
	float				vertical_step;
	float				x_angle;
	float				y_angle;
	float				z_angle;
	int					top_line;
	int					bottom_line;
}							t_camera;

typedef struct				s_settings
{
	int					gl_enabled;
	int					bshadows;
	unsigned int		depth;
	unsigned int		aliasing;
	unsigned int		spread;
	unsigned int		sep;
	unsigned int		gl_sampling;
	unsigned int		render_w;
	unsigned int		render_h;
}							t_settings;

typedef struct				s_scene
{
	t_object			*objects;
	t_light				*lights;
	int					objects_count;
	int					lights_count;
	int					top_bound;
	int					bottom_bound;
	t_color				theme;
	float				power;
	t_settings			sett;
}							t_scene;

typedef	struct				s_opencl
{
	size_t				img_s;
	size_t				imgxy[2];
	size_t				origin[3];
	size_t				region[3];
	int					*bufhst;
	char				*kernel_src;
	cl_device_type		dev_type;
	cl_int				err;
	cl_uint				num_dev;
	cl_mem				input_scene;
	cl_mem				input_cam;
	cl_mem				output;
	cl_mem				structobj;
	cl_mem				structlight;
	cl_platform_id		platform_id;
	cl_image_format		format;
	cl_image_desc		desc;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
}							t_opencl;

typedef struct				s_srv
{
	int					nbclient;
	int					id;
	int					sockmax;
	int					sz;
	int					socket;
	int					socket_cl;
	int					err;
	int					port;
	int					sockets[10];
	char				*addr;
	socklen_t			size_cl;
	socklen_t			sin_sz;
	t_sockaddr_in		sin;
	t_sockaddr_in		sin_cl;
	t_client_state		cl_state;
	t_hostent			*hostinfo;
}							t_srv;

typedef struct				s_render_bounds
{
	int					top;
	int					bottom;
}							t_render_bounds;

typedef struct				s_env
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_str;
	char				data_o[SIZE_OBJ];
	char				data_l[SIZE_LIGHT];
	int					i;
	int					obj_ct;
	int					light_ct;
	int					win_height;
	int					win_width;
	int					img_height;
	int					img_width;
	int					line_size;
	int					bpp;
	int					endian;
	int					light_i;
	int					obj_i;
	int					is_direct_hit;
	int					child;
	int					err;
	struct timespec		tim;
	t_render_bounds		bounds;
	t_scene				scene;
	t_object			object;
	t_camera			camera;
	t_opencl			opcl;
	t_srv				srv;
	pthread_t			thr;
}							t_env;

/*
** ======= prototypes
*/

void						await_data(t_env *env);
void						perform_rendering(t_env *env);
void						send_rendering(t_env *env);
void						ft_error(char *str);
void						server_connect(t_env *e);
int							send_data(t_env *e);
int							recv_obj_light(t_env *e);
void						create_client(t_env *e);
void						init_env_client(t_env *e, char *str);
void						create_srv(t_env *e);
void						init_env_server(t_env *e);
void						*loop_data(void *arg);
void						loop_recv(t_env *e);
void						*waitcl(void *arg);
void						exit_usage2(void);
void						init_env2(t_env *env);
void						deserialize_obj(char *data, t_object *obj);
void						deserialize_pt(char *data, t_point *obj);
void						deserialize_float(float *data, t_object *obj);
void						deserialize_light(char *data, t_light *light);
int							error_gpu(t_opencl *opcl);
void						opencl_init(t_opencl *opcl, t_env *env);
void						opencl_init2(t_opencl *opcl, t_env *e);
void						opencl_draw(t_opencl *opcl, t_env *e);
void						opencl_free(t_opencl *opcl);
void						set_opencl_env(t_env *env, t_opencl *opcl);
void						create_kernel(cl_program program,
		cl_kernel *kernel, const char *func);
char						*get_kernel_source(char *file);
void						create_prog(t_opencl *opcl);
void						exit_error(t_env *env);
void						exit_normally(t_env *env);
void						exit_invalid_file(void);
t_env						*init_env(t_env *env, char *file_name);
void						calculate_scene(t_env *env);
t_camera					init_camera(t_env *env);
t_camera					set_camera(int fd, t_env *env);
int							handle_key_event(int key, void *param);
int							expose_event(void *param);
int							exit_properly(void *param);
void						fill_pixel(t_env *env, int x, int y, t_color color);
void						fill_pixel_value(t_env *env, int x,
		int y, int color_value);
t_vector					vector(float x, float y, float z);
t_vector					vector_points(t_point p1, t_point p2);
t_point						point(float x, float y, float z);
t_pixel						pixel(int x, int y);
t_color						color(int r, int g, int b, int a);
float						vector_norm(t_vector vector);
t_vector					normalize_vector(t_vector vector);
float						dot_product(t_vector vect_1, t_vector vect_2);
float						points_norm(t_point p1, t_point p2);
t_object					intersect_object(t_object ray, t_object object);
t_vector					shape_normal(t_object ray, t_object object);
void						pixel_raytracing(int x, int y, t_env *env);
t_scene						get_sample_scene(void);
t_color						get_color_on_intersection(t_object ray,
		t_object *clt_obj, t_env *e);
void						deinit_env(t_env *env);
int							line_len(char **line);
void						clear_line(char **line);
char						**split_new_line(int fd);
t_light						*add_light(int fd, t_light *existing_lights,
		int count);
t_object					add_new_object(int fd, char *type);
t_scene						create_scene(t_env *env, char *file_name, int fd);
t_object					cylinder_intersection(t_object ray,
		t_object cylinder);
t_object					cone_intersection(t_object ray, t_object cone,
		t_vector distance);
t_object					plane_intersection(t_object ray, t_object plane);
t_object					sphere_intersection(t_object ray, t_object sphere);
t_vector					cone_normal(t_object ray, t_object cone);
t_vector					cylinder_normal(t_object ray, t_object cylinder);
t_vector					plane_normal(t_object ray, t_object plane);
t_vector					sphere_normal(t_object ray, t_object sphere);
float						degrees_to_radian(int degrees);
t_vector					vect_rotate_x(t_vector vector, float angle,
		int inverse);
t_vector					vect_rotate_z(t_vector vector, float angle,
		int inverse);
t_vector					vect_rotate_y(t_vector vector, float angle,
		int inverse);
t_object					init_ray(int x, int y, t_camera camera);
float						closest_distance_quadratic(float a, float b,
		float c);
void						ft_ocl_init_error(const int ret);
void						ft_ocl_kernel_error(const int ret,
		const size_t index);
size_t						file_len(int fd);
int							hit_test(t_object *clt_obj, t_object *obj,
		t_object l_ray, float norm);
t_object					parse_object(int fd, t_object *object);
t_object					*expand_objects(t_object *objects,
		int previous_count);
t_vector					point_from_vector(t_point origin,
		t_vector direction, float norm);
t_scene						create_dependant_objects(t_object object, int fd,
		t_scene scene, int id);
t_vector					rotate_cylinder_angles(t_object cylinder,
		t_vector vect, int reverse);
t_vector					rotate_cone_angles(t_object cone,
		t_vector vect, int reverse);
t_vector					rotate_vector_angles(t_object reference,
		t_vector vect, int reverse);
t_vector					cross_product(t_vector vect_1, t_vector vect_2);

#endif
