# define TRUE 1
# define FALSE 0

/*
** The maximum allowed depth of rays.
*/
# define MAX_DEPTH 10

/*
** The maximum allowed margin error
*/
# define EPSILON 0.05

# define CIRCLES_WIDTH 2.3
# define CHECKER_WIDTH 40.0
# define DOTS_WIDTH 2.3
# define DOTS_SPREAD 5.0
# define BUMP_HEIGHT 0.1
# define BUMP_WIDTH 5

# define WHITE (t_color){255, 255, 255, 0}
# define BLACK (t_color){0, 0, 0, 0}
# define TRANSPARENT (t_color){255, 255, 255, 255}
# define BLUE (t_color){0, 191, 255, 0}
# define PURPLE (t_color){128,0,128, 0}
# define GREEN (t_color){124,252,0, 0}
# define WOOD_LIGHT (t_color){160, 121, 61, 0}
# define WOOD_DARK (t_color){130, 91, 31, 0}

# define GI_WIDTH (M_PI)
# define GI_HALF_WIDTH (M_PI / 2)

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

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef t_vector	t_point;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}				t_color;

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
}							t_camera;

typedef struct				s_light
{
	float				angle;
	float				power;
	t_point				posiition;
	t_vector			direction;
	t_color				color;
	t_light_type		typpe;
}							t_light;

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

int				omni_color_coord(float cosinus, float distance, int obj_color, int light_color);
int             projector_color_coord(float intensity, float distance, int obj_color, int light_color);
t_color			diffuse_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light);
t_object		init_omni_light_ray(t_light light, t_object ray, t_object object);
t_object		init_ambiant_light_ray(t_light light, t_object ray, t_object object);
int				color_to_int(t_color color);
t_object		intersect_object(t_object ray, t_object object);
t_vector		normalize_vector(t_vector vec);
t_vector		vector_points(t_point p1, t_point p2);
t_vector		vect_rotate_x(t_vector vector, float angle, int inverse);
t_vector		vect_rotate_y(t_vector vector, float angle, int inverse);
t_vector		vect_rotate_z(t_vector vector, float angle, int inverse);
float			vector_norm(t_vector vec);
float			dot_product(t_vector vect_1, t_vector vect_2);
float			closest_distance_quadratic(float a, float b, float c);
t_object		cone_intersection(t_object ray, t_object cone);
t_color			color(int r, int g, int b, int a);
t_vector		shape_normal(t_object ray, t_object object);
t_vector		sphere_normal(t_object ray, t_object sphere);
t_vector		plane_normal(t_object ray, t_object plane);
t_vector		cylinder_normal(t_object ray, t_object cylinder);
t_vector		cone_normal(t_object ray, t_object cone);
float			points_norm(t_point p1, t_point p2);
t_object		sphere_intersection(t_object ray, t_object sphere);
t_object		plane_intersection(t_object ray, t_object plane);
t_object		cylinder_intersection(t_object ray, t_object cylinder);
t_color 		add_color(t_color base, t_color overlay);
int				revert_cone_normal(t_object ray, t_object cone);
int				revert_cylinder_normal(t_object ray, t_object cylinder);
int				revert_sphere_normal(t_object ray, t_object sphere);
t_color			omni_light_for_intersection(t_object light_ray, t_object ray, t_object
		object, t_light light);
t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object
		object, t_light light);
t_color			ambiant_color(t_scene scene, t_object object);
t_color			projector_light_for_intersection(t_object light_ray, t_object ray, t_object
		object, t_light light);
t_object		init_projector_light_ray(t_light light, t_object ray, t_object object);
t_object		finite_cylinder_intersection(t_object ray, t_object cylinder);
t_object		disc_intersection(t_object ray, t_object disc);
float			farest_distance_quadratic(float a, float b, float c);
t_vector		point_from_vector(t_point origin, t_vector direction, float norm);
t_vector		scale_vector(t_vector vect, float scale);
t_object		finite_cone_intersection(t_object ray, t_object cone);
t_vector		reflected_vector(t_vector incident, t_vector normal);
t_color			specular_light_for_intersection(t_object light_ray, t_object ray,
		t_object object, t_light light);
t_color			raytracing(global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light, float aliasing_variation);
t_color			average_color(t_color c1, t_color c2);
unsigned char	maximize_color_value(int color_value);
t_vector		rotate_vector_angles(t_object reference, t_vector vect,
			int reverse);
t_object		rectangle_intersection(t_object ray, t_object rectangle);
t_vector	cross_product(t_vector vect_1, t_vector vect_2);
t_object		triangle_intersection(t_object ray, t_object triangle);
t_object		parallelogram_intersection(t_object ray, t_object parallelogram);
t_object		init_reflected_ray(t_object original_ray, t_object intersected_object);
t_vector		refracted_vector(t_object object, t_object ray, float next_refraction_index);
t_object		init_refracted_ray(t_object original_ray, t_object intersected_object,
	float next_refraction, float next_transparency);
t_color			refracted_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int depth, int current_object_id);
t_vector	sum_vectors(t_vector vect1, t_vector vect2);
t_color			primary_ray(global t_scene *scene, global t_object *obj,
		global t_light *light, t_object ray, int depth, int refraction);
t_color			fade_color(t_color color, float multiplier);
t_color			reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
		t_object ray, int depth);
t_object		get_shadow_ray(t_light light, t_object ray, t_object object);
t_object		light_ray_from_shadow_ray(t_object shadow_ray, t_light light);
int				colors_are_equals(t_color c1, t_color c2);
t_color			filter_light_through_object(t_color initial_color, t_object object);
t_object		init_primary_ray(int x, int y, t_camera camera, float aliasing_variation, int horizontal);
float			fresnel_reflection_index(float n1, float n2, float cos_alpha, float cos_beta);
t_color			textured_color_if_needed(t_object object, t_point intersection);
t_color			checker_texture_color(t_object object, t_point intersection);
int				is_texture_even(int value);
t_color			circles_color(t_object object, t_point intersection, int horizontal);
t_color			dots_color(t_object object, t_point intersection, int invert_gradient, int reverse);
t_object		object_with_local_parameters(t_object object, t_color local_color, int inside_object);
t_color			get_color_on_intersection(t_object ray, t_object intersected_object,
		global t_scene *scene, global t_light *light, global t_object *obj, int with_GI);
int				hit_test(t_object clt_obj, t_object obj, t_object l_ray, float norm);
int				integer_part(float value);
float			fractional_part(float value);
t_vector		get_random_gradient(int int_x, int int_y, int int_z);
float			perlin_polynom(float value);
float			linear_interpolation(float a, float b, float ratio);
float			get_perlin_noise_value(float x, float y, float z);
float			perlin_noise(int octaves, float frequency, float persistence, t_point point);
t_color			procedural_color(t_object object, t_point intersection);
t_color			perlin_algo_texture_color(t_object object, t_point intersection);
float			bounded_color_value(float color_value, float min_value, float max_value);
t_color			perlin_color(t_object object, t_point intersection);
t_object		hyperboloid_intersection(t_object ray, t_object hyperboloid);
t_vector		hyperboloid_normal(t_object ray, t_object hyperboloid);
t_color			wood_color(t_object object, t_point intersection);
t_color			marble_color(t_object object, t_point intersection);
t_color			direct_light_raytracing(global t_scene *scene, global t_object *obj,
		global t_light *light, t_object ray, float closest_distance);
t_color			glare_color_localized_spot(float distance, t_light light);
t_object		light_plane(t_object ray, t_light light);
t_color			glare_color_ambiant_light(t_object ray, t_light light);
t_vector		vertical_perturbation(t_vector original, t_point point);
t_vector		horizontal_perturbation(t_vector original, t_point point);
t_vector		bump_mapped_normale(t_object object, t_vector normal, t_point point);
int				circles_noise(t_vector intersection, int horizontal);
t_color			interpolate_two_colors(t_color c1, t_color c2, float ratio);
t_color			interpolate_three_colors(t_color c1, t_color c2, t_color c3, float ratio);
t_color			interpolate_four_colors(t_color c1, t_color c2, t_color c3, t_color c4, float ratio);
t_color			ponctual_reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
		t_object ray);
t_light			randomize_light_position(t_light light, int rand, float light_sep);
float 			noise3D(float x, float y, float z);
float 			random_value(int index);
float 			light_algo_random_pos(int rand, int minus, int plus, float light_sep);
t_color			direct_illumination_by(t_light light, t_object intersected_object, 
		t_object ray, global t_scene *scene, global t_object *obj, int randomized);
t_color			indirect_diffuse_on_point(t_vector normal, t_point origin,
		global t_scene *scene, global t_light *light, global t_object *obj);
t_object		init_global_illumination_ray(t_vector direction, t_point origin,
		t_object base_object);
t_vector		random_vector_in_hemisphere(t_vector normal, int index);


__constant unsigned char hash_table[512] = {151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,151,
	160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
};

__constant t_vector perlin_vectors[16] = {
    (t_vector){1,1,0}, (t_vector){-1,1,0}, (t_vector){1,-1,0}, (t_vector){-1,-1,0},
    (t_vector){1,0,1}, (t_vector){-1,0,1}, (t_vector){1,0,-1}, (t_vector){-1,0,-1},
    (t_vector){0,1,1}, (t_vector){0,-1,1}, (t_vector){0,1,-1}, (t_vector){0,-1,-1},
    (t_vector){1,1,0}, (t_vector){-1,1,0}, (t_vector){0,-1,1}, (t_vector){0,-1,-1}};






/*
** ========== RANDOM NUMBERS
*/

float noise3D(float x, float y, float z)
{
    float ptr = 0.0f;
    return fract(sin(x*112.9898f + y*179.233f + z*237.212f) * 43758.5453f, &ptr);
}

float random_value(int index)
{
	int		id;
	int		iterations;
	int		counter;
	float	random_number;

	id = get_global_id(1) * get_global_size(0) + get_global_id(0);
	iterations = (id % (id * get_global_size(1) + index)) % 12 + 1;
	counter = -1;
	random_number = 0.0;
	while (++counter < iterations)
		random_number = noise3D((float)id, (float)(hash_table[id % 512]), index + (int)random_number * 1000);
	return (random_number);
}



/*
** ========== MATHEMATIC HELPERS
*/

/*
** COLORS
*/

t_color		color(int r, int g, int b, int a)
{
	t_color		color;

	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;
	color.a = (unsigned char)a;
	return (color);
}

/*
** VECTORS
*/

t_vector	normalize_vector(t_vector vec)
{
	float		norm;

	norm = vector_norm(vec);
	vec.x /= norm;
	vec.y /= norm;
	vec.z /= norm;
	return (vec);
}

t_vector	point_from_vector(t_point origin, t_vector direction, float norm)
{
	t_point		point;

	point.x = origin.x + direction.x * norm;
	point.y = origin.y + direction.y * norm;
	point.z = origin.z + direction.z * norm;
	return (point);
}

t_vector	scale_vector(t_vector vect, float scale)
{
	vect.x *= scale;
	vect.y *= scale;
	vect.z *= scale;
	return (vect);
}

t_vector	sum_vectors(t_vector vect1, t_vector vect2)
{
	t_vector	sum;

	sum.x = vect1.x + vect2.x;
	sum.y = vect1.y + vect2.y;
	sum.z = vect1.z + vect2.z;
	return (sum);
}

t_vector	vector_points(t_point p1, t_point p2)
{
	t_vector	vec;

	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.z = p2.z - p1.z;
	return (vec);
}

t_vector	vect_rotate_x(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x;
		rotated.y = vector.y * cos(angle) + vector.z * sin(angle);
		rotated.z = -vector.y * sin(angle) + vector.z * cos(angle);
	}
	else
	{
		rotated.x = vector.x;
		rotated.y = cos(angle) * vector.y - sin(angle) * vector.z;
		rotated.z = sin(angle) * vector.y + cos(angle) * vector.z;
	}
	return (rotated);
}

t_vector	vect_rotate_z(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cos(angle) + vector.y * sin(angle);
		rotated.y = -vector.x * sin(angle) + vector.y * cos(angle);
		rotated.z = vector.z;
	}
	else
	{
		rotated.x = cos(angle) * vector.x - sin(angle) * vector.y;
		rotated.y = sin(angle) * vector.x + cos(angle) * vector.y;
		rotated.z = vector.z;
	}
	return (rotated);
}

t_vector	vect_rotate_y(t_vector vector, float angle, int inverse)
{
	t_vector	rotated;

	if (!inverse)
	{
		rotated.x = vector.x * cos(angle) - vector.z * sin(angle);
		rotated.y = vector.y;
		rotated.z = vector.x * sin(angle) + vector.z * cos(angle);
	}
	else
	{
		rotated.x = cos(angle) * vector.x + sin(angle) * vector.z;
		rotated.y = vector.y;
		rotated.z = -sin(angle) * vector.x + cos(angle) * vector.z;
	}
	return (rotated);
}

t_vector	rotate_vector_angles(t_object reference, t_vector vect,
			int reverse)
{	if (!reverse)
	{
		vect = vect_rotate_y(vect, reference.y_angle, reverse);
		vect = vect_rotate_x(vect, reference.x_angle, reverse);
	}
	else
	{
		vect = vect_rotate_x(vect, reference.x_angle, reverse);
		vect = vect_rotate_y(vect, reference.y_angle, reverse);
	}
	return (vect);
}

t_vector	cross_product(t_vector vect_1, t_vector vect_2)
{
	t_vector	cross;

	cross.x = vect_1.y * vect_2.z - vect_1.z * vect_2.y;
	cross.y = vect_1.z * vect_2.x - vect_1.x * vect_2.z;
	cross.z = vect_1.x * vect_2.y - vect_1.y * vect_2.x;
	return (cross);
}

t_vector		random_vector_in_hemisphere(t_vector normal, int index)
{
	int			randomized_start;
	float		x_angle;
	float		y_angle;
	float		z_angle;
	t_vector	randomized;

	randomized_start = (int)hash_table[max(index, -index)];
	x_angle = (random_value((int)(sin(normal.x + normal.y + normal.z + randomized_start) * randomized_start * 10)) * GI_WIDTH) - GI_HALF_WIDTH;
	y_angle = (random_value((int)(x_angle * 1000) * hash_table[randomized_start]) * GI_WIDTH) - GI_HALF_WIDTH;
	z_angle = (random_value((int)(y_angle * x_angle * 1000) * hash_table[randomized_start]) * GI_WIDTH) - GI_HALF_WIDTH;
	randomized = vect_rotate_x(randomized, x_angle, 0);
	randomized = vect_rotate_y(normal, y_angle, 0);
	randomized = vect_rotate_z(randomized, z_angle, 0);
	return (randomized);
}

/*
** NUMBERS
*/

float		vector_norm(t_vector vec)
{
	float		norm;

	norm = sqrt((float)(pow((float)vec.x, (float)2) + pow((float)vec.y, (float)2) + pow((float)vec.z, (float)2)));
	return (norm);
}

float		dot_product(t_vector vect_1, t_vector vect_2)
{
	float		product;

	product = (vect_1.x * vect_2.x) +
				(vect_1.y * vect_2.y) +
				(vect_1.z * vect_2.z);
	return (product);
}

int			integer_part(float value)
{
	if (value >= 0)
		return ((int)value);
	return ((int)value - 1);
}

float		fractional_part(float value)
{
	float		int_part;

	int_part = integer_part(fabs(value));
	if (value >= 0)
		int_part = (float)((int)value);
	else
		int_part = (float)((int)value - 1);
	return (value - int_part);
}

float		linear_interpolation(float a, float b, float ratio)
{
	return (a + (b - a) * ratio);
}


/*
** =========== COLORS CALCULATION
*/

t_color		interpolate_two_colors(t_color c1, t_color c2, float ratio)
{
	return (add_color(fade_color(c1, ratio), fade_color(c2, 1 - ratio)));
}

t_color		interpolate_three_colors(t_color c1, t_color c2, t_color c3, float ratio)
{
	if (ratio < 1.0 / 2.0)
		return (add_color(fade_color(c1, ratio * 2), fade_color(c2, 1 - ratio * 2)));
	else
		return (add_color(fade_color(c2, (ratio - 1.0 / 2.0) * 2), fade_color(c3, 1 - (ratio - 1.0 / 2.0) * 2)));
}

t_color		interpolate_four_colors(t_color c1, t_color c2, t_color c3, t_color c4, float ratio)
{
	if (ratio < 1.0 / 3.0)
		return (add_color(fade_color(c1, ratio * 3), fade_color(c2, 1 - ratio * 3)));
	if (ratio < 2.0 / 3.0)
		return (add_color(fade_color(c2, (ratio - 1.0 / 3.0) * 3), fade_color(c3, 1 - (ratio - 1.0 / 3.0) * 3)));
	return (add_color(fade_color(c3, (ratio - 2.0 / 3.0) * 3), fade_color(c4, 1 - (ratio - 2.0 / 3.0) * 3)));
}

t_color		fade_color(t_color color, float multiplier)
{
	multiplier = fmax(fmin(multiplier, 1), 0);
	color.r = (unsigned char)((float)color.r * multiplier);
	color.g = (unsigned char)((float)color.g * multiplier);
	color.b = (unsigned char)((float)color.b * multiplier);
	color.a = (unsigned char)((float)color.a * multiplier);
	return (color);
}

int			colors_are_equals(t_color c1, t_color c2)
{
	return (c1.r == c2.r
		&& c1.g == c2.g
		&& c1.b == c2.b
		&& c1.a == c2.a);
}

t_color 	add_color(t_color base, t_color overlay)
{
	t_color 	final;

	final.r = maximize_color_value(base.r + overlay.r);
	final.g = maximize_color_value(base.g + overlay.g);
	final.b = maximize_color_value(base.b + overlay.b);
	final.a = maximize_color_value(base.a + overlay.a);
	return (final);
}

t_color		average_color(t_color c1, t_color c2)
{
	t_color		final;

	final.r = (c1.r + c2.r) / 2;
	final.g = (c1.g + c2.g) / 2;
	final.b = (c1.b + c2.b) / 2;
	final.a = (c1.a + c2.a) / 2;
	return (final);
}

float		bounded_color_value(float color_value, float min_value, float max_value)
{
	if (color_value < min_value)
		return (min_value);
	else if (color_value > max_value)
		return (max_value);
	return (color_value);
}

int			is_texture_even(int value)
{
	if (value >= 0)
		return (value % 2 == 0);
	else
		return ((value) % 2 == 0);
}

/*
** Solves a quadratic equation but with the aim of returning a distance, which
** has to be a positive value.
** If the value is negative, the equation has no solution.
** Several cases are to be distinguished, in order in the function's body :
** - discriminant < 0 : the ray does not intersect the object
** From this point and for simplication, both x1 and x2 are replaced
** if needed so that x1 <= x2.
** - x1 <= 0 and x2 <= 0 : both intersections are behind the camera,
** so there is no intersection to be represented on screen.
** - x2 > 0 and x1 <= 0 : the camera is inside the object, with one
** point behind the camera, and one in front of it. The one to be
** represented is the one in front of it, so the highest norm
** value.
** - x1 > 0 and x2 > 0 : both intersections are beyond the camera,
** the closest one is to be retained.
*/

float		closest_distance_quadratic(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;
	float 		buffer;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt(discriminant)) / (2 * a);
	x2 = (-b + sqrt(discriminant)) / (2 * a);
	if (x2 < x1)
	{
		buffer = x2;
		x2 = x1;
		x1 = buffer;
	}
	if (x1 <= 0 && x2 <= 0)
		return (-1);
	else if (x2 > 0 && x1 <= 0)
		return (x2);
	return (x1);
}

float	farest_distance_quadratic(float a, float b, float c)
{
	float		discriminant;
	float		x1;
	float		x2;
	float 		buffer;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	x1 = (-b - sqrt(discriminant)) / (2 * a);
	x2 = (-b + sqrt(discriminant)) / (2 * a);
	if (x2 < x1)
	{
		buffer = x2;
		x2 = x1;
		x1 = buffer;
	}
	if (x1 <= 0 && x2 <= 0)
		return (-1);
	else if (x2 > 0 && x1 <= 0)
		return (x2);
	return (x2);
}


float		points_norm(t_point p1, t_point p2)
{
	float		distance;

	distance = sqrt((float)(pow((float)(p2.x - p1.x), (float)2) 
		+ pow((float)(p2.y - p1.y), (float)2) 
		+ pow((float)(p2.z - p1.z), (float)2)));
	return (distance);
}

unsigned char	maximize_color_value(int color_value)
{
	return ((unsigned char)(fmax(fmin((float)color_value, (float)255), 0)));
}



/*
** ===================================================
** NOISE FUNCTIONS
** ===================================================
*/

/*
** ========== CLASSICL PROCEDURAL NOISES
*/

int				circles_noise(t_vector intersection, int horizontal)
{
	t_vector	adjusted;
	int			distance;

	adjusted = scale_vector(intersection, 1.0 / CIRCLES_WIDTH);
	if (horizontal)
		distance = (int)sqrt((adjusted.x * adjusted.x + adjusted.z * adjusted.z));
	else
		distance = (int)sqrt((adjusted.x * adjusted.x + adjusted.y * adjusted.y));
	return (distance % 2 == 0);
}


/*
** ========== PERLIN ALGORITHMS
*/

t_vector		get_random_gradient(int int_x, int int_y, int int_z)
{
	int			hashed_random_value;

	int_x = (int)hash_table[(int)fabs((float)int_x)];
	int_y += (int)hash_table[(int)fabs((float)int_x)];
	int_z += (int)hash_table[(int)fabs((float)int_y)];
	hashed_random_value = hash_table[int_z] % 16;
	hashed_random_value %= 16;
	return (perlin_vectors[hashed_random_value]);
}

float			perlin_polynom(float value)
{
	return (6.0 * pow(value, 5) - 15 * pow(value, 4) + 10 * pow(value, 3));
}

float			get_perlin_noise_value(float x, float y, float z)
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

	square_noises[0] = dot_product(get_random_gradient(int_x, int_y, int_z), (t_vector){x, y, z});
	square_noises[1] = dot_product(get_random_gradient(int_x, int_y, int_z + 1), (t_vector){x, y, z - 1.0});
	square_noises[2] = dot_product(get_random_gradient(int_x, int_y + 1, int_z), (t_vector){x, y - 1.0, z});
	square_noises[3] = dot_product(get_random_gradient(int_x, int_y + 1, int_z + 1), (t_vector){x, y - 1.0, z - 1.0});
	square_noises[4] = dot_product(get_random_gradient(int_x + 1, int_y, int_z), (t_vector){x - 1.0, y, z});
	square_noises[5] = dot_product(get_random_gradient(int_x + 1, int_y, int_z + 1), (t_vector){x - 1.0, y, z - 1.0});
	square_noises[6] = dot_product(get_random_gradient(int_x + 1, int_y + 1, int_z), (t_vector){x - 1.0, y - 1.0, z});
	square_noises[7] = dot_product(get_random_gradient(int_x + 1, int_y + 1, int_z + 1), (t_vector){x - 1.0, y - 1.0, z - 1.0});

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

float			perlin_noise(int octaves, float frequency, float persistence, t_point point)
{
	float		noise;
	float		amplitude;
	int			octave;
	t_point		values;

	octave = -1;
	amplitude = 1.0;
	noise = 0;
	while (++octave < octaves)
	{
		values = (t_point){point.x * frequency * octave,
			point.y * frequency * octave,
			point.z * frequency * octave};
		noise += amplitude * get_perlin_noise_value(values.x, values.y, values.z);
		amplitude *= persistence;
		frequency *= 2;
	}
	noise = fabs(noise);
	return (noise);
}



/*
** ===================================================
** GEOMETRIC CALCULATIONS
** ===================================================
*/

/*
** ========== NORMAL PERTURBATION ALGORITHMS
*/

t_vector		vertical_perturbation(t_vector original, t_point point)
{
	float		perturbation;
	t_vector	normal;

	perturbation = sin(point.x / BUMP_WIDTH) * BUMP_HEIGHT;
	normal = original;
	normal.x += perturbation;
	return (normalize_vector(normal));
}

t_vector		horizontal_perturbation(t_vector original, t_point point)
{
	float		perturbation;
	t_vector	normal;

	perturbation = sin(point.y / BUMP_WIDTH) * BUMP_HEIGHT;
	normal = original;
	normal.y += perturbation;
	return (normalize_vector(normal));
}

t_vector		bump_mapped_normale(t_object object, t_vector normal, t_point point)
{
	if (object.bump_mapping == VERTICAL_SIN)
		return (vertical_perturbation(normal, point));
	else if (object.bump_mapping == HORIZONTAL_SIN)
		return (horizontal_perturbation(normal, point));
	return (normal);
}


/*
** ========== NORMALE VECTOR CALCULATION
*/

int		revert_cone_normal(t_object ray, t_object cone)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cone.center, ray.origin);
	rotate_vector_angles(cone, light_to_center, 0);
	border = pow((float)light_to_center.z, (float)2) * pow((float)tan(cone.angle), (float)2);
	light_distance = pow((float)light_to_center.x, (float)2) + pow((float)light_to_center.y, (float)2);
	return (light_distance < border);
}

t_vector		cone_normal(t_object ray, t_object cone)
{
	t_vector	distance;
	float		normal_dist;
	t_point		normal_point;
	t_point		normal_point_2;
	t_vector	normal;

	distance = vector_points(cone.center, ray.intersectiion);
	distance = rotate_vector_angles(cone, distance, 0);
	normal_dist = (cos(cone.angle) + tan(cone.angle) * sin(cone.angle)) *
		vector_norm(distance);
	normal_point = (t_point){0, 0, normal_dist};
	normal_point_2 = (t_point){0, 0, -normal_dist};
	if (points_norm(normal_point, distance) > points_norm(normal_point_2,
				distance))
		normal_point = normal_point_2;
	normal = vector_points(normal_point, distance);
	if (dot_product(normalize_vector(normal), rotate_vector_angles(cone, ray.direction, 0)) > 0)
		normal = vector_points(distance, normal_point);
	normal = rotate_vector_angles(cone, normal, 1);
	return (normalize_vector(normal));
}

int		revert_cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	light_to_center;
	float		border;
	float		light_distance;

	light_to_center = vector_points(cylinder.point, ray.origin);
	rotate_vector_angles(cylinder, light_to_center, 0);
	border = pow(cylinder.radius, 2);
	light_distance = pow(light_to_center.x, 2) + pow(light_to_center.y, 2);
	return (light_distance < border);
}

t_vector		cylinder_normal(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_point		normal_point;
	t_vector	normal;

	distance = vector_points(cylinder.point, ray.intersectiion);
	distance = rotate_vector_angles(cylinder, distance, 0);
	normal_point = (t_point){0, 0, distance.z};
	normal = vector_points(normal_point, distance);
	if (dot_product(normalize_vector(normal), rotate_vector_angles(cylinder, ray.direction, 0)) > 0)
		normal = vector_points(distance, normal_point);
	normal = rotate_vector_angles(cylinder, normal, 1);
	return (normalize_vector(normal));
}

t_vector		hyperboloid_normal(t_object ray, t_object hyperboloid)
{
	t_vector	normal;
	t_vector	distance;

	distance = vector_points(hyperboloid.center, ray.intersectiion);
	distance = rotate_vector_angles(hyperboloid, distance, 0);
	normal = (t_vector){
		distance.x,
		distance.y,
		-pow(hyperboloid.rho / hyperboloid.sigma, 2) * distance.z
	};
	normal = rotate_vector_angles(hyperboloid, normal, 1);
	return (normalize_vector(normal));
}

t_vector		plane_normal(t_object ray, t_object plane)
{
	t_vector	normal;

	if (dot_product(ray.direction, plane.normal) <= 0)
		return (normalize_vector(plane.normal));
	normal.x = -(plane.normal.x);
	normal.y = -(plane.normal.y);
	normal.z = -(plane.normal.z);
	return (normalize_vector(normal));
}

/*
** Returns true if the origin of the light ray is inside the sphere,
** meaning that only the inner surface is to be enlighted.
*/

int		revert_sphere_normal(t_object ray, t_object sphere)
{
	t_vector	distance_vector;

	distance_vector = vector_points(ray.origin, sphere.center);
	return (vector_norm(distance_vector) < sphere.radius);
}

t_vector		sphere_normal(t_object ray, t_object sphere)
{
	t_vector	normal;

	if (revert_sphere_normal(ray, sphere))
		normal = vector_points(ray.intersectiion, sphere.center);
	else
		normal = vector_points(sphere.center, ray.intersectiion);
	return (normalize_vector(normal));
}

t_vector			shape_normal(t_object ray, t_object object)
{
	t_vector		normal;

	if (object.typpe == SPHERE)
		normal = (sphere_normal(ray, object));
	else if (object.typpe == PLANE || object.typpe == DISC || object.typpe == RECTANGLE
		|| object.typpe == TRIANGLE || object.typpe == PARALLELOGRAM)
		normal = (plane_normal(ray, object));
	else if (object.typpe == CYLINDER)
		normal = (cylinder_normal(ray, object));
	else if (object.typpe == HYPERBOLOID)
		normal = (hyperboloid_normal(ray, object));
	else
		normal = (cone_normal(ray, object));
	if (object.bump_mapping == FLAT)
		return (normal);
	return (bump_mapped_normale(object, normal, ray.intersectiion));
}




/*
** ========== INTERSECTION POINTS CALCULATION
*/

t_object		cone_intersection(t_object ray, t_object cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_vector_angles(cone, ray.direction, 0);
	distance = rotate_vector_angles(cone, distance, 0);
	k = -1 - pow((float)(tan((float)(cone.angle))), (float)2);
	a = pow((float)vector_norm(ray_dir), (float)2) + k * pow((float)ray_dir.z, (float)2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow((float)vector_norm(distance), (float)2) + k * pow((float)distance.z, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	if (ray.norm < EPSILON)
		ray.norm = farest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object	finite_cone_intersection(t_object ray, t_object cone)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		k;
	float		closest_norm;
	float		farest_norm;

	distance = vector_points(cone.center, ray.origin);
	ray_dir = rotate_vector_angles(cone, ray.direction, 0);
	distance = rotate_vector_angles(cone, distance, 0);
	k = -1 - pow((float)(tan((float)(cone.angle))), (float)2);
	a = pow((float)vector_norm(ray_dir), (float)2) + k * pow((float)ray_dir.z, (float)2);
	b = 2 * (dot_product(distance, ray_dir) + k * ray_dir.z * distance.z);
	c = pow((float)vector_norm(distance), (float)2) + k * pow((float)distance.z, (float)2);
	ray.intersect = FALSE;
	closest_norm = closest_distance_quadratic(a, b, c);
	farest_norm = farest_distance_quadratic(a, b, c);
	if (closest_norm > EPSILON)
	{
		ray.norm = closest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cone.center, ray.intersectiion);
		distance = rotate_vector_angles(cone, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cone.height);
	}
	if (!ray.intersect && farest_norm > EPSILON)
	{
		ray.norm = farest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cone.center, ray.intersectiion);
		distance = rotate_vector_angles(cone, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cone.height);		
	}
	return (ray);
}

t_object	plane_intersection(t_object ray, t_object plane)
{
	if (dot_product(plane.normal, ray.direction) == 0)
	{
		ray.intersect = FALSE;
		return (ray);
	}
	ray.norm = (dot_product(plane.normal, plane.point) - dot_product(plane.normal,
			ray.origin)) / dot_product(plane.normal, ray.direction);
	ray.intersect = (ray.norm > 0 || ray.norm < 10000000);
	return (ray);
}

t_object	disc_intersection(t_object ray, t_object disc)
{
	ray = plane_intersection(ray, disc);
	if (!ray.intersect)
		return (ray);
	ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	ray.intersect = vector_norm(vector_points(ray.intersectiion, disc.point)) < disc.radius;
	return (ray);
}

t_object	sphere_intersection(t_object ray, t_object sphere)
{
	float		a;
	float		b;
	float		c;
	t_vector	distance;

	distance = vector_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, distance);
	c = dot_product(distance, distance) - pow((float)sphere.radius, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object		cylinder_intersection(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;

	distance = vector_points(cylinder.point, ray.origin);
	ray_dir = rotate_vector_angles(cylinder, ray.direction, 0);
	distance = rotate_vector_angles(cylinder, distance, 0);
	a = pow((float)ray_dir.x, (float)2) + pow((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow((float)distance.x, (float)2) + pow((float)distance.y, (float)2) - pow((float)cylinder.radius, (float)2);
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object		finite_cylinder_intersection(t_object ray, t_object cylinder)
{
	t_vector	distance;
	t_vector	ray_dir;
	float		a;
	float		b;
	float		c;
	float		closest_norm;
	float		farest_norm;

	distance = vector_points(cylinder.point, ray.origin);
	ray_dir = rotate_vector_angles(cylinder, ray.direction, 0);
	distance = rotate_vector_angles(cylinder, distance, 0);
	a = pow((float)ray_dir.x, (float)2) + pow((float)ray_dir.y, (float)2);
	b = 2 * (distance.x * ray_dir.x + distance.y * ray_dir.y);
	c = pow((float)distance.x, (float)2) + pow((float)distance.y, (float)2) - pow((float)cylinder.radius, (float)2);
	closest_norm = closest_distance_quadratic(a, b, c);
	farest_norm = farest_distance_quadratic(a, b, c);
	ray.intersect = FALSE;
	if (closest_norm > EPSILON)
	{
		ray.norm = closest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cylinder.point, ray.intersectiion);
		distance = rotate_vector_angles(cylinder, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cylinder.height);
	}
	if (!ray.intersect && farest_norm > EPSILON)
	{
		ray.norm = farest_norm;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
		distance = vector_points(cylinder.point, ray.intersectiion);
		distance = rotate_vector_angles(cylinder, distance, 0);
		ray.intersect = (distance.z >= 0 && distance.z <= cylinder.height);		
	}
	return (ray);
}

t_object			hyperboloid_intersection(t_object ray, t_object hyperboloid)
{
	t_vector		distance;
	t_vector		ray_dir;
	float			a;
	float			b;
	float			c;

	distance = vector_points(hyperboloid.center, ray.origin);
	ray_dir = rotate_vector_angles(hyperboloid, ray.direction, 0);
	distance = rotate_vector_angles(hyperboloid, distance, 0);
	a = pow(1 / hyperboloid.rho, 2) * (pow(ray_dir.x, 2) + pow(ray_dir.y, 2))
		- pow(1 / hyperboloid.sigma, 2) * pow(ray_dir.z, 2);
	b = 2 * (pow(1 / hyperboloid.rho, 2) * (distance.x * ray_dir.x + distance.y * ray_dir.y)
		- pow(1 / hyperboloid.sigma, 2) * distance.z * ray_dir.z);
	c = pow(1 / hyperboloid.rho, 2) * (pow(distance.x, 2) + pow(distance.y, 2))
		- pow(1 / hyperboloid.sigma, 2) * pow(distance.z, 2) - 1;
	ray.norm = closest_distance_quadratic(a, b, c);
	ray.intersect = ray.norm > 0;
	return (ray);
}

t_object		rectangle_intersection(t_object ray, t_object rectangle)
{
	t_vector	intersection_dist;

	ray = plane_intersection(ray, rectangle);
	if (!ray.intersect)
		return (ray);
	ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	intersection_dist = vector_points(rectangle.point, ray.intersectiion);
	intersection_dist = rotate_vector_angles(rectangle, intersection_dist, 0);
	ray.intersect = (intersection_dist.x >= 0 && intersection_dist.z >= 0
		&& intersection_dist.x < rectangle.width && intersection_dist.z < rectangle.height);
	return (ray);
}

t_object		triangle_intersection(t_object ray, t_object triangle)
{
	t_vector	distance;
	float		a;
	float		b;
	float		k;

	distance = vector_points(triangle.point, ray.origin);
	k = -dot_product(cross_product(triangle.second_vect, triangle.first_vect), ray.direction);
	if (k == 0)
		return (ray);
	a = -dot_product(cross_product(distance, triangle.first_vect), ray.direction) / k;
	b = -dot_product(cross_product(triangle.second_vect, distance), ray.direction) / k;
	ray.intersect = (a >= 0 && b >= 0 && a + b < 1);
	ray.norm = dot_product(cross_product(triangle.second_vect, triangle.first_vect), distance) / k;
	return (ray);
}

t_object		parallelogram_intersection(t_object ray, t_object parallelogram)
{
	t_vector	distance;
	float		a;
	float		b;
	float		k;

	distance = vector_points(parallelogram.point, ray.origin);
	k = -dot_product(cross_product(parallelogram.second_vect, parallelogram.first_vect), ray.direction);
	if (k == 0)
		return (ray);
	a = -dot_product(cross_product(distance, parallelogram.first_vect), ray.direction) / k;
	b = -dot_product(cross_product(parallelogram.second_vect, distance), ray.direction) / k;
	ray.intersect = (a >= 0 && b >= 0 && a < 1 && b < 1);
	ray.norm = dot_product(cross_product(parallelogram.second_vect, parallelogram.first_vect), distance) / k;
	return (ray);
}

t_object			intersect_object(t_object ray, t_object object)
{
	if (object.typpe == SPHERE)
		ray = sphere_intersection(ray, object);
	else if (object.typpe == PLANE)
		ray = plane_intersection(ray, object);
	else if (object.typpe == CYLINDER)
		ray = (object.finite) 
			? finite_cylinder_intersection(ray, object) 
			: cylinder_intersection(ray, object);
	else if (object.typpe == CONE)
		ray = (object.finite)
			? finite_cone_intersection(ray, object)
			: cone_intersection(ray, object);
	else if (object.typpe == DISC)
		ray = disc_intersection(ray, object);
	else if (object.typpe == RECTANGLE)
		ray = rectangle_intersection(ray, object);
	else if (object.typpe == TRIANGLE)
		ray = triangle_intersection(ray, object);
	else if (object.typpe == PARALLELOGRAM)
		ray = parallelogram_intersection(ray, object);
	else if (object.typpe == HYPERBOLOID)
		ray = hyperboloid_intersection(ray, object);
	if (ray.intersect)
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	return (ray);
}




/* 
** ===================================================
** ========== TEXTURES
** ===================================================
*/

/*
** ========== PROCEDURAL TEXTURES
*/

t_color			checker_texture_color(t_object object, t_point intersection)
{
	t_color		alternate;
	t_point		adjusted;
	int			x_even;
	int			y_even;
	int			z_even;

	alternate = TRANSPARENT;
	adjusted = scale_vector(intersection, 1.0 / CHECKER_WIDTH);
	x_even = is_texture_even((int)((adjusted.x < -EPSILON) ? adjusted.x - 1 : adjusted.x));
	y_even = is_texture_even((int)((adjusted.y < -EPSILON) ? adjusted.y - 1 : adjusted.y));
	z_even = is_texture_even((int)((adjusted.z < -EPSILON) ? adjusted.z - 1 : adjusted.z));
	if (z_even)
	{
		if ((x_even && y_even)
			|| (!x_even && !y_even))
			return (object.color);
		return (alternate);
	}
	else
	{
		if ((x_even && y_even)
			|| (!x_even && !y_even))
			return (alternate);
		return (object.color);
	}
}

t_color			circles_color(t_object object, t_point intersection, int horizontal)
{
	t_color		alternate;

	alternate = TRANSPARENT;
	if (circles_noise(intersection, horizontal))
		return (object.color);
	return (alternate);
}

t_color			dots_color(t_object object, t_point intersection, int invert_gradient, int reverse)
{
	float		norm;
	t_color		internal_color;
	t_color		external_color;
	t_point		closest_dot;

	closest_dot = (t_point){round(intersection.x / (float)DOTS_SPREAD) * DOTS_SPREAD,
		round(intersection.y / (float)DOTS_SPREAD) * DOTS_SPREAD,
		round(intersection.z / (float)DOTS_SPREAD) * DOTS_SPREAD};
	if (reverse)
	{
		external_color = object.color;
		internal_color = TRANSPARENT;
	}
	else
	{
		internal_color = object.color;
		external_color = TRANSPARENT;
	}
	norm = points_norm(intersection, closest_dot);
	if (norm <= DOTS_WIDTH / 2)
		return (internal_color);
	else if (norm <= DOTS_WIDTH)
	{
		if (invert_gradient)
			return (interpolate_two_colors(internal_color, external_color,
				((norm - DOTS_WIDTH / 2) / (DOTS_WIDTH / 2))));
		else
			return (interpolate_two_colors(internal_color, external_color,
				1 - (norm - DOTS_WIDTH / 2) / (DOTS_WIDTH / 2)));
	}
	return (external_color);
}

/*
** ========== TEXTURES USING PERLIN ALGORITHM
*/

/*
** WOOD
*/

t_color			wood_color(t_object object, t_point intersection)
{
	t_point		altered_coordinates;
	t_color		color;
	float		noise;

	altered_coordinates = intersection;
	noise = 100 * perlin_noise(2, 0.0025, 0.1, altered_coordinates);
	noise -= (int)noise;
	color = interpolate_two_colors(WOOD_LIGHT, WOOD_DARK, noise * 2);
	return (color);
}

t_color			marble_color(t_object object, t_point intersection)
{
	t_point		altered_coordinates;
	t_color		color;
	float		noise;

	altered_coordinates = intersection;
	noise = altered_coordinates.x / 10
		+ altered_coordinates.y / 18
		+ altered_coordinates.z / 63;
	noise = cos(noise / 3 + perlin_noise(10, 0.0001, 0.60, altered_coordinates) * 30) + 1;
	noise *= 1.1;
	color = interpolate_two_colors(WHITE, BLACK, noise / 2);
	return (color);
}

t_color			perlin_color(t_object object, t_point intersection)
{
	t_color		color;
	float		noise;

	noise = perlin_noise(8, 0.001, 0.6, intersection) * 2;
	color = interpolate_four_colors(BLUE, BLACK, GREEN, PURPLE, noise);
	return (color);
}

/*
** ========== GLOBAL TEXTURING FUNCTIONS
*/

t_color			procedural_color(t_object object, t_point intersection)
{
	if (object.texture_type == CHECKER)
		return (checker_texture_color(object, intersection));
	else if (object.texture_type == HORIZONTAL_CIRCLE || object.texture_type == VERTICAL_CIRCLE)
		return (circles_color(object, intersection, object.texture_type == VERTICAL_CIRCLE));
	else if (object.texture_type == DOTS || object.texture_type == DOTS_CROWN
		|| object.texture_type == DOTS_REVERTED || object.texture_type == DOTS_REVERTED_CROWN)
		return (dots_color(object, intersection,
			object.texture_type == DOTS_CROWN || object.texture_type == DOTS_REVERTED_CROWN,
			object.texture_type == DOTS_REVERTED || object.texture_type == DOTS_REVERTED_CROWN));
	return (object.color);
}

t_color			perlin_algo_texture_color(t_object object, t_point intersection)
{
	if (object.texture_type == PERLIN)
		return (perlin_color(object, intersection));
	else if (object.texture_type == WOOD)
		return (wood_color(object, intersection));
	else if (object.texture_type == MARBLE)
		return (marble_color(object, intersection));
	return (TRANSPARENT);
}

t_color			textured_color_if_needed(t_object object, t_point intersection)
{
	if (object.texture_algo == PROCEDURAL)
		return (procedural_color(object, intersection));
	else if (object.texture_algo == PERLIN_ALGO)
		return (perlin_algo_texture_color(object, intersection));
	return (object.color);
}

t_object		object_with_local_parameters(t_object object, t_color local_color, int inside_object)
{
	t_object	local_object;

	local_object = object;
	local_object.color = local_color;
	local_object.transparency = (float)fmax(object.transparency, (float)(local_color.a / 255.0));
	local_object.reflection = object.reflection;
	if (inside_object)
	{
		local_object.reflection = 0.0;
		local_object.brillance = 0.0;
	}
	return (local_object);
}


/*
** ========== SPECULAR VECTOR CALCULATION
*/

/*
** Returns the symetric of the incident vector (from light to object) around
** the normal on the surface.
*/

t_vector		reflected_vector(t_vector incident, t_vector normal)
{
	float		dot_coeff;
	t_vector	reflected;

	dot_coeff = dot_product(scale_vector(incident, 2), normal);
	reflected = scale_vector(normal, -dot_coeff);
	reflected.x += incident.x;
	reflected.y += incident.y;
	reflected.z += incident.z;
	return (normalize_vector(reflected));
}


/*
** ========== REFRACTED VECTOR CALCULATION
*/

/*
** Returns the refracted vector of the ray's direction when hitting the surface
** of the object.
** The initial refraction index is expected to be set in the ray's parameters.
**
** The angle between the normal and the source vector is calculated using the
** oriented angle between the normal (from intersection to outside) and the 
** inverse of the ray's direction, which is originally from outside to the
** intersection.
*/

t_vector		refracted_vector(t_object ray, t_object object, float next_refraction_index)
{
	t_vector	normal;
	t_vector	refracted;
	float		incident_cos;
	float		refraction_indexes_ratio;

	normal = shape_normal(ray, object);
	refraction_indexes_ratio = ray.refraction / next_refraction_index;
	if (fabs(refraction_indexes_ratio - 1) < EPSILON)
		return (ray.direction);
	incident_cos = 1.0 - pow(refraction_indexes_ratio, 2) * (1.0 - pow(dot_product(normal, ray.direction), 2));
	if (incident_cos < 0) {
		return reflected_vector(ray.direction, normal);
	}
	refracted = scale_vector(ray.direction, refraction_indexes_ratio);
	refracted = sum_vectors(refracted, scale_vector(normal, -1 * refraction_indexes_ratio * dot_product(ray.direction, normal)));
	refracted = sum_vectors(refracted, scale_vector(normal, -1 * sqrt(incident_cos)));
	return (normalize_vector(refracted));
}

/*
** Returns the ratio "Fr" of light that should be reflected on a transparent surface.
** The quantity of light that is refracted is equal to 1 - Fr.
** The parameters are as follows :
** - n1 : the refraction index of the incident middle (where the incident ray is),
** - n2 : the refraction index of the refracted middle (where the refracted ray will be),
** - cos_alpha : the cosinus of the angle between the incident ray and the normal on its
** side,
** - cos_beta : the cosinus of the angle betwenn the refracted ray and the normal on its
** side.
*/

float			fresnel_reflection_index(float n1, float n2, float cos_alpha, float cos_beta)
{
	float		parralel_index;
	float		perpendicular_index;

	parralel_index = pow((n2 * cos_alpha - n1 * cos_beta) / (n2 * cos_alpha + n1 * cos_beta), 2);
	perpendicular_index = pow((n1 * cos_beta - n2 * cos_alpha) / (n1 * cos_beta + n2 * cos_alpha), 2);
	return (0.5 * (parralel_index + perpendicular_index));
}




/*
** ========== COLORATION TOOL
*/

int			color_to_int(t_color color)
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




/*
** ========== LIGHTING
*/

/*
** Supposing there is no object between the light and the intersection, the
** color on this point is calculated, based on the angle between the normal
** of the object on a particular point.
*/

int		omni_color_coord(float cosinus, float distance, int obj_color,
	int light_color)
{
	float	distance_factor;
	float	k;
	float	color_value;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = sqrt(-cosinus) / distance_factor;
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = maximize_color_value((int)color_value);
	return ((int)color_value);
}

int		projector_color_coord(float intensity, float distance, int obj_color, int light_color)
{
	float		color_value;
	float		distance_factor;
	float		k;

	distance_factor = 0.02 * pow((float)(distance / 1.3), (float)2) + 1;
	k = intensity / distance_factor;
	color_value = ((float)obj_color + (float)light_color) * k;
	color_value = maximize_color_value((int)color_value);
	return ((int)color_value);
}

t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_color		color;
	float		distance;
	float		cosinus;

	cosinus = dot_product(scale_vector(light_ray.direction, -1),
		shape_normal(ray, object)) * object.diffuse * (1 - object.transparency);
	if (cosinus <= 0)
		return (BLACK);
	distance = 100.0 * (100.0 / light.power);
	color.r = omni_color_coord(-cosinus, distance, object.color.r, light_ray.color.r);
	color.g = omni_color_coord(-cosinus, distance, object.color.g, light_ray.color.g);
	color.b = omni_color_coord(-cosinus, distance, object.color.b, light_ray.color.b);
	color.a = 0;
	return (color);
}

t_color			omni_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	t_color		color;

	light_ray.intersectiion = ray.intersectiion;
	normal = shape_normal(ray, object);
	cosinus = dot_product(light_ray.direction, normal) * object.diffuse * (1 - object.transparency);
	if (cosinus >= 0)
		return (BLACK);
	distance = points_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power);
	color.r = omni_color_coord(cosinus, distance, object.color.r, light_ray.color.r) * object.diffuse;
	color.g = omni_color_coord(cosinus, distance, object.color.g, light_ray.color.g) * object.diffuse;
	color.b = omni_color_coord(cosinus, distance, object.color.b, light_ray.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

t_color			projector_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	t_vector	normal;
	float		cosinus;
	float		distance;
	float 		intensity;
	t_color		color;

	if (dot_product(light.direction, light_ray.direction) < cos(light.angle))
		return (BLACK);
	light_ray.intersectiion = ray.intersectiion;
	normal = shape_normal(ray, object);
	distance = points_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power);
	cosinus = dot_product(light.direction, light_ray.direction);
	intensity = (1 / (1 - cos(light.angle))) * cosinus - (cos(light.angle) / (1 - cos(light.angle)));
	intensity *= object.diffuse * (1 - object.transparency);
	cosinus = dot_product(light_ray.direction, normal);
	if (cosinus >= 0)
		return (BLACK);
	intensity = -cosinus * intensity;
	color.r = projector_color_coord(intensity, distance, object.color.r, light_ray.color.r) * object.diffuse;
	color.g = projector_color_coord(intensity, distance, object.color.g, light_ray.color.g) * object.diffuse;
	color.b = projector_color_coord(intensity, distance, object.color.b, light_ray.color.b) * object.diffuse;
	color.a = 0;
	return (color);
}

t_color			diffuse_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light)
{
	if (light.typpe == AMBIANT)
		return (ambiant_light_for_intersection(light_ray, ray, object, light));
	else if (light.typpe == PROJECTOR)
		return (projector_light_for_intersection(light_ray, ray, object, light));
	return (omni_light_for_intersection(light_ray, ray, object, light));
}

t_color			specular_light_for_intersection(t_object light_ray, t_object ray,
	t_object object, t_light light)
{
	float		distance;
	float		intensity;
	t_vector	incident;
	t_vector	reflected;
	t_color		specular;

	if (light.typpe == PROJECTOR && dot_product(light_ray.direction, light.direction) < cos(light.angle))
		return (BLACK);
	incident = scale_vector(light_ray.direction, -1);
	distance = (light.typpe != AMBIANT)
		? points_norm(ray.intersectiion, light_ray.origin) * (100.0 / light.power)
		: 100.0 * (100.0 / light.power);
		distance = 1;
	reflected = reflected_vector(incident, shape_normal(ray, object));
	intensity = pow(fmax(dot_product(reflected, ray.direction), 0), (int)(object.brillance * 100)) * pow(object.brillance, 2);
	if (light.typpe == PROJECTOR)
		intensity *= (1 / (1 - cos(light.angle))) * dot_product(light.direction, light_ray.direction) - (cos(light.angle) / (1 - cos(light.angle)));
	specular.r = projector_color_coord(intensity, distance, object.color.r, light_ray.color.r);
	specular.g = projector_color_coord(intensity, distance, object.color.g, light_ray.color.g);
	specular.b = projector_color_coord(intensity, distance, object.color.b, light_ray.color.b);
	specular.a = 0;
	return (specular);
}

int				hit_test(t_object clt_obj, t_object obj, t_object l_ray, float norm)
{
	if (!(l_ray.intersect && l_ray.norm > EPSILON))
		return (0);
	if (clt_obj.index == obj.index)
		return (l_ray.norm < norm - 0.1);
	return (l_ray.norm < norm);
}

t_color			ambiant_color(t_scene scene, t_object object)
{
	t_color		ambiant_color;
	float		factor;

	factor = scene.power * object.diffuse * (1 - object.transparency);
	ambiant_color.r = (unsigned char)(factor * (object.color.r * scene.theme.r / 255.0));
	ambiant_color.g = (unsigned char)(factor * (object.color.g * scene.theme.g / 255.0));
	ambiant_color.b = (unsigned char)(factor * (object.color.b * scene.theme.b / 255.0));
	ambiant_color.a = 0;
	return (ambiant_color);
}

t_color			filter_light_through_object(t_color initial_color, t_object object)
{
	t_color		final_color;
	float		transparency;

	transparency = fmax(object.transparency, (float)((float)object.color.a / 255.0));
	final_color = interpolate_two_colors(initial_color, object.color, transparency);
	return (fade_color(final_color, object.transparency));
}


/*
** A light ray is a ray beginning from the position of the light itself,
** and directed to the intersection between the initial ray and the closest
** object.
** A shadow ray is the opposit vector of the light ray, beginning from
** the intersection, directed towards the origin of the light.
** A base color (shadow color) is given so that, if an object stands
** between the light spot and the intersection, the latter is shadowed.
*/

/*
** Light ray from the object to the light, or towards the light in the case of an
** Ambiant light.
*/
t_object	get_shadow_ray(t_light light, t_object ray, t_object object)
{
	t_object		shadow_ray;
	t_vector		direction;

	if (light.typpe == AMBIANT)
		shadow_ray.direction = scale_vector(light.direction, -1);
	else
	{
		direction = vector_points(ray.intersectiion, light.posiition);
		shadow_ray.norm = vector_norm(direction);
		shadow_ray.direction = normalize_vector(direction);
	}
	shadow_ray.origin = point_from_vector(ray.intersectiion, shadow_ray.direction, EPSILON);
	shadow_ray.intersect = FALSE;
	shadow_ray.color = light.color;
	return (shadow_ray);
}

/*
** Reverses the shadow ray to get a ray from the light to the intersection of the
** object.
*/

t_object	light_ray_from_shadow_ray(t_object shadow_ray, t_light light)
{
	t_object	light_ray;

	light_ray = shadow_ray;
	light_ray.direction = scale_vector(shadow_ray.direction, -1);
	light_ray.origin = (light.typpe == AMBIANT) ? shadow_ray.origin : light.posiition;
	return (light_ray);
}

float light_algo_random_pos(int rand, int minus, int plus, float light_sep)
{
	float		nb;
	float		var;

	var = (float)(rand / 7);
	nb = 0;
	if (rand % 7 == plus)
		nb = light_sep;
	else if (rand % 7 == minus)
		nb = -light_sep;
	return (nb * var);
}

t_light			randomize_light_position(t_light light, int rand, float light_sep)
{
	t_light 	randomized;

	if (light.typpe == AMBIANT)
		return (light);
	randomized = light;
	randomized.posiition.x += light_algo_random_pos(rand, 1, 2, light_sep);
	randomized.posiition.y += light_algo_random_pos(rand, 3, 4, light_sep);
	randomized.posiition.z += light_algo_random_pos(rand, 5, 6, light_sep);
	return (randomized);
}

/*
** For each object that is not the intersected one, check if the ray
** intersects with the object. If so, the point on closest_object is shadowed.
** Else, the coloration calculated in the case there is no object in between is
** returned and applied.
**
** If [randomized] is set to 1, the function will iterate several times the ray
** casting while randomizing the position of the light to produce a blurred shadow
** effect.
*/ 

t_color			direct_illumination_by(t_light light, t_object intersected_object, 
	t_object ray, global t_scene *scene, global t_object *obj, int randomized)
{
	t_light		current_light;
	t_object	light_ray;
	t_object	shadow_ray;
	t_color		coloration;
	t_object	object_inbetween;
	int 		light_goes_through;
	int			rand;
	int			max_iter;
	int			object_index;
	int			total_color[4] = {0};
	float		norm;

	max_iter = ((light.typpe != AMBIANT) & scene->sett.bshadows)
		? scene->sett.spread * 7
		: 1;
	rand = -1;
	while (++rand < max_iter)
	{
		if (rand > 0 && rand % 7 == 0)
			continue;
		coloration = BLACK;
		current_light = randomize_light_position(light, rand, scene->sett.sep);
		light_goes_through = 1;
		shadow_ray = get_shadow_ray(current_light, ray, intersected_object);
		norm = shadow_ray.norm;
		object_index = -1;
		while (++object_index < scene->objects_count && light_goes_through)
		{
			shadow_ray = intersect_object(shadow_ray, obj[object_index]);
			if (shadow_ray.intersect && ((current_light.typpe == AMBIANT && shadow_ray.norm > EPSILON)
				|| (current_light.typpe != AMBIANT && hit_test(intersected_object,
					obj[object_index], shadow_ray, norm))))
			{
				shadow_ray.intersectiion = point_from_vector(shadow_ray.origin,
					shadow_ray.direction, shadow_ray.norm);
				object_inbetween = object_with_local_parameters(obj[object_index], 
					textured_color_if_needed(obj[object_index], shadow_ray.intersectiion), 0);
				shadow_ray.color = filter_light_through_object(shadow_ray.color, object_inbetween);
			}
			light_goes_through = (!(colors_are_equals(shadow_ray.color, BLACK)));
		}
		if (light_goes_through)
		{
			light_ray = light_ray_from_shadow_ray(shadow_ray, current_light);
			coloration = add_color(coloration, diffuse_light_for_intersection(light_ray, ray, 
				intersected_object, current_light));
			coloration = add_color(coloration, specular_light_for_intersection(light_ray, ray,
				intersected_object, current_light));
		}
		total_color[0] += (int)coloration.r;
		total_color[1] += (int)coloration.g;
		total_color[2] += (int)coloration.b;
		total_color[3] += (int)coloration.a;
	}
	return (t_color){
		(unsigned char)((float)total_color[0] / ((float)max_iter)),
		(unsigned char)((float)total_color[1] / ((float)max_iter)),
		(unsigned char)((float)total_color[2] / ((float)max_iter)),
		(unsigned char)((float)total_color[3] / ((float)max_iter))
	};
}

/*
** Calculates the lighting on a point.
** Should only be used for a visible point since this function will calculate
** all the lighting effect (diffuse, specular, ambiant), and, if enabled,
** will randomize the position of a light several times to create a blurry
** shadow effect. The function is therefore very costly in ressources.
*/

t_color			get_color_on_intersection(t_object ray, t_object intersected_object,
	global t_scene *scene, global t_light *light, global t_object *obj, int with_GI)
{
	int			light_index;
	t_color		full_color;
	t_color		indirect_color;

	light_index = -1;
	full_color = ambiant_color(*scene, intersected_object);
	while (++light_index < scene->lights_count)
		full_color = add_color(full_color, direct_illumination_by(light[light_index],
			intersected_object, ray, scene, obj, TRUE));
	if (with_GI)
	{
		indirect_color = indirect_diffuse_on_point(shape_normal(ray, intersected_object),
			ray.intersectiion, scene, light, obj);
		full_color = add_color(full_color, fade_color(indirect_color, 1));
	}
	return (full_color);
}



/*
** ==================================================================
** GLOBAL ILLUMINATION
** ==================================================================
*/

t_object		init_global_illumination_ray(t_vector direction, t_point origin,
	t_object base_object)
{
	t_object	ray;

	ray.direction = direction;
	ray.origin = point_from_vector(origin, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.transparency = 0;
	ray.refraction = 100;
	ray.reflection = 0;
	return (ray);
}

t_color			indirect_diffuse_on_point(t_vector normal, t_point origin,
	global t_scene *scene, global t_light *light, global t_object *obj)
{
	int			rand;
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_object			ray;
	t_object			intersected_object;
	t_vector			direction;
	t_color				added_color;
	int					total_color[4] = {0};

	rand = -1;
	while (++rand < (int)scene->sett.gl_sampling)
	{
		direction = random_vector_in_hemisphere(normal, rand);
		ray = init_global_illumination_ray(direction, origin, intersected_object);
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance)
				|| closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
				textured_color_if_needed(obj[closest_object_index], ray.intersectiion), 0);
			added_color = get_color_on_intersection(ray, intersected_object, scene, light, obj, FALSE);
			added_color = fade_color(added_color,
				dot_product(direction, normal) * 
				(600.0 / ray.norm) * M_PI);
			total_color[0] += (int)added_color.r;
			total_color[1] += (int)added_color.g;
			total_color[2] += (int)added_color.b;
			total_color[3] += (int)added_color.a;
		}
	}
	return ((t_color){
		(unsigned char)((float)total_color[0] / (float)scene->sett.gl_sampling),
		(unsigned char)((float)total_color[1] / (float)scene->sett.gl_sampling),
		(unsigned char)((float)total_color[2] / (float)scene->sett.gl_sampling),
		(unsigned char)((float)total_color[3] / (float)scene->sett.gl_sampling),
	});
}




/*
** ==================================================================
** INTERSECTION
** ==================================================================
*/

/*
** ========== GLARE EFFECT
*/

/*
** Returns a plane centered on the light, and which normal vector is the opposite of
** [ray.direction].
*/

t_object		light_plane(t_object ray, t_light light)
{
	t_object	plane;

	plane.typpe = PLANE;
	plane.point = light.posiition;
	plane.normal = scale_vector(ray.direction, -1);
	return (plane);
}

t_color			glare_color_localized_spot(float distance, t_light light)
{
	float		intensity;

	intensity = pow((light.power / 30 - distance) / (light.power / 30), 4);
	return (fade_color(light.color, intensity));
}

t_color			glare_color_ambiant_light(t_object ray, t_light light)
{
	float		min_cosinus;
	float		cos_with_ray;
	float		intensity;

	min_cosinus = sqrt((float)100.0 / (light.power + (float)6000.0)) + sqrt((float)3.0) / 2.0;
	cos_with_ray = dot_product(ray.direction, scale_vector(light.direction, -1));
	if (cos_with_ray < min_cosinus)
		return (BLACK);
	intensity = (1 / (1 - min_cosinus)) * (cos_with_ray - min_cosinus);
	intensity = pow(intensity, 4);
	return (fade_color(light.color, intensity));
}

t_color			direct_light_raytracing(global t_scene *scene, global t_object *obj,
	global t_light *light, t_object ray, float closest_distance)
{
	t_color		glare_color;
	t_light		current_light;
	t_object	associated_plane;
	float		distance_from_origin;
	int			light_index;

	light_index = -1;
	glare_color = BLACK;
	while (++light_index < scene->lights_count)
	{
		current_light = light[light_index];
		if (current_light.typpe != PROJECTOR ||
			(current_light.typpe == PROJECTOR && dot_product(current_light.direction,
			scale_vector(normalize_vector(vector_points(ray.origin, current_light.posiition)),
			 -1)) >= cos(current_light.angle)))
		{
			associated_plane = light_plane(ray, current_light);
			ray = intersect_object(ray, associated_plane);
			if (ray.intersect && ray.norm > 0
				&& ((current_light.typpe != AMBIANT && closest_distance > 0
					&& ray.norm < closest_distance - EPSILON)
					|| closest_distance < 0))
			{
				distance_from_origin = points_norm(ray.intersectiion, current_light.posiition);
				if (current_light.typpe != AMBIANT && distance_from_origin <= current_light.power / 30)
					glare_color = add_color(glare_color,
						glare_color_localized_spot(distance_from_origin, current_light));
				else if (current_light.typpe == AMBIANT)
					glare_color = add_color(glare_color,
						glare_color_ambiant_light(ray, current_light));
			}
		}
	}
	return (glare_color);
}

/*
** ========== REFRACTED LIGHT
*/

t_object		init_refracted_ray(t_object original_ray, t_object intersected_object,
	float next_refraction, float next_transparency)
{
	t_object		ray;

	ray.direction = refracted_vector(original_ray, intersected_object, next_refraction);
	ray.origin = point_from_vector(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.transparency = next_transparency;
	ray.refraction = next_refraction;
	ray.reflection = intersected_object.reflection * original_ray.reflection;
	return (ray);
}

/*
** Adds the index to the array if not contained already, otherwise removes it.
**
** Is used to keep track of the objects the refracted ray is in.
** This method implies that the objects are simple shapes described by
** quadratic functions.
**
** The index defines a unit, not an object as contained in t_object*.
*/

void			update_tab(int intersected_obj_id, int *tab)
{
	int			i;

	i = -1;
	while (++i < MAX_DEPTH * 2)
	{
		if (tab[i] == intersected_obj_id)
		{
			tab[i] = -1;
			return;
		}
	}
	i = 0;
	while (i < MAX_DEPTH * 2 && tab[i] >= 0)
		i++;
	if (i < MAX_DEPTH * 2)
		tab[i] = intersected_obj_id;
}

float			get_next_refraction_index(int *tab, __global t_object *objects)
{
	float		index;
	int			i;

	if (!ray_in_object(tab))
		return (1.0);
	i = -1;
	index = 0.0;
	while (++i < MAX_DEPTH * 2)
	{
		if (tab[i] >= 0 && objects[tab[i]].refraction > index)
			index = objects[tab[i]].refraction;
	}
	return (index);
}

int				ray_in_object(int *tab)
{
	int			i;

	i = -1;
	while (++i < MAX_DEPTH * 2)
	{
		if (tab[i] >= 0)
			return (TRUE);
	}
	return (FALSE);
}

void			set_array_first_iter(int *tab, int first_object)
{
	int			i;

	i = 0;
	tab[i] = first_object;
	while (++i < MAX_DEPTH * 2)
		tab[i] = -1;
}

t_color			refracted_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int depth, int current_object_id)
{
	int					object_index;
	int 				closest_object_index;
	int					inside_object;
	float				closest_distance;
	t_color				added_color;
	t_color				colorout;
	t_object			intersected_object;
	int					tab[MAX_DEPTH * 2];

	set_array_first_iter(tab, current_object_id);
	colorout = BLACK;
	inside_object = 1;
		closest_object_index = -1;
    depth--;
	while (++depth < scene->sett.depth * 2) {
		added_color = BLACK;
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance)
				|| closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
				textured_color_if_needed(obj[closest_object_index], ray.intersectiion), inside_object);
			added_color = get_color_on_intersection(ray, intersected_object, scene, light, obj, FALSE);
			if (intersected_object.reflection > 0 && !inside_object)
				added_color = add_color(added_color, reflected_raytracing(scene, obj, light,
					init_reflected_ray(ray, intersected_object), depth + 1));
			added_color = add_color(added_color, direct_light_raytracing(scene, obj, light, ray,
				(closest_object_index != -1) ? ray.norm : -1));
			colorout = add_color(colorout, fade_color(added_color, ray.transparency));
			update_tab(closest_object_index, tab);
			inside_object = ray_in_object(tab);
		}
		if (closest_object_index == -1 || intersected_object.transparency == 0)
			return (colorout);
		if (inside_object == 0)
			ray = init_refracted_ray(ray, intersected_object,
				1, ray.transparency);
		else
			ray = init_refracted_ray(ray, intersected_object,
				get_next_refraction_index(tab, obj), intersected_object.transparency);
	}
	return (colorout);
}

/*
** ========== REFLECTED LIGHT
*/

t_object		init_reflected_ray(t_object original_ray, t_object intersected_object)
{
	t_object		ray;

	ray.direction = reflected_vector(original_ray.direction, shape_normal(original_ray, intersected_object));
	ray.direction = normalize_vector(ray.direction);
	ray.origin = point_from_vector(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.reflection = intersected_object.reflection * original_ray.reflection * (1 - intersected_object.transparency);
	ray.refraction = intersected_object.refraction;
	ray.transparency = intersected_object.transparency;
	return (ray);
}

t_color			reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int depth)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	t_color				colorout;
	t_object			intersected_object;

	colorout = BLACK;
    depth--;
	while (++depth < scene->sett.depth) {
		added_color = BLACK;
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance)
				|| closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			intersected_object = object_with_local_parameters(obj[closest_object_index],
				textured_color_if_needed(obj[closest_object_index], ray.intersectiion), 0);
			added_color = get_color_on_intersection(ray, intersected_object, scene, light, obj, FALSE);
			if (intersected_object.transparency > 0)
				added_color = add_color(added_color, refracted_raytracing(scene, obj, light,
					init_refracted_ray(ray, intersected_object,
					intersected_object.refraction, intersected_object.transparency), depth + 1, intersected_object.id));
			added_color = fade_color(added_color, ray.reflection);
		}
		colorout = add_color(colorout, added_color);
		if (closest_object_index == -1 || intersected_object.reflection == 0)
			return (colorout);
		ray = init_reflected_ray(ray, intersected_object);
	}
	return (colorout);
}

/*
** ========== INITIAL INTERSECTION
*/

t_object		init_primary_ray(int x, int y, t_camera camera, float aliasing_variation, int horizontal)
{
	t_object		ray;
	t_point			projector_point;
	float			virtual_x;
	float			virtual_y;			

	if (aliasing_variation > 0 && aliasing_variation < 1)
	{
		virtual_x = (float)x + ((horizontal) ? aliasing_variation : 0);
		virtual_y = (float)y + ((!horizontal) ? aliasing_variation : 0);
	}
	else
	{
		virtual_x = (float)x + aliasing_variation;
		virtual_y = (float)y + aliasing_variation;
	}
	projector_point.x = camera.up_left_corner.x + virtual_x * camera.horizontal_vect.x + virtual_y * camera.vertical_vect.x;
	projector_point.y = camera.up_left_corner.y + virtual_x * camera.horizontal_vect.y + virtual_y * camera.vertical_vect.y;
	projector_point.z = camera.up_left_corner.z + virtual_x * camera.horizontal_vect.z + virtual_y * camera.vertical_vect.z;
	ray.direction = vector_points(camera.spot, projector_point);
	ray.direction = normalize_vector(ray.direction);
	ray.origin = camera.spot;
	ray.refraction = 1;
	ray.reflection = 1;
	ray.transparency = 1;
	ray.intersect = FALSE;
	return (ray);
}

t_color			primary_ray(global t_scene *scene, global t_object *obj,
	global t_light *light, t_object ray, int depth, int refraction)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				colorout;
	t_color				refracted_color;
	t_color				reflected_color;
	t_object			intersected_object;

	colorout = BLACK;
	reflected_color = BLACK;
	refracted_color = BLACK;
	closest_object_index = -1;
	object_index = -1;
	while (++object_index < scene->objects_count)
	{
		ray = intersect_object(ray, obj[object_index]);
		if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) ||
			closest_object_index == -1) && ray.norm > EPSILON)
		{
			closest_object_index = object_index;
			closest_distance = ray.norm;
		}
	}
	if (closest_object_index != -1)
	{
		ray.norm = closest_distance;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
		intersected_object = object_with_local_parameters(obj[closest_object_index],
			textured_color_if_needed(obj[closest_object_index], ray.intersectiion), 0);
		colorout = get_color_on_intersection(ray, intersected_object, scene, light, obj, scene->sett.gl_enabled);
		if (intersected_object.reflection > 0)
			reflected_color = reflected_raytracing(scene, obj, light,
				init_reflected_ray(ray, intersected_object), 1);
		if (intersected_object.transparency > 0)
			refracted_color = refracted_raytracing(scene, obj, light,
				init_refracted_ray(ray, intersected_object,
					intersected_object.refraction, intersected_object.transparency), 1, intersected_object.id);
		colorout = add_color(colorout, add_color(refracted_color, reflected_color));
	}
	colorout = add_color(colorout, direct_light_raytracing(scene, obj, light, ray,
		(closest_object_index != -1) ? ray.norm : -1));
	return (colorout);
}

/*
** ========== MAIN FUNCTION
*/

t_color			raytracing(global t_scene *scene, global t_camera *camera,
	global t_object *obj, global t_light *light, float aliasing_variation)
{
	int					x;
	int					y;
	int					idx;
	t_object			ray;
	t_color				horizontal_color;
	t_color				vertical_color;

	x = get_global_id(0);
	y = get_global_id(1);
	idx = get_global_size(0) * get_global_id(1) + get_global_id(0);
	ray = init_primary_ray(x, y, *camera, aliasing_variation, 0);
	horizontal_color = primary_ray(scene, obj, light, ray, 0, 0);
	if (aliasing_variation == 0 || aliasing_variation == 1)
		return (horizontal_color);
	ray = init_primary_ray(x, y, *camera, aliasing_variation, 1);
	vertical_color = primary_ray(scene, obj, light, ray, 0, 0);
	return (average_color(horizontal_color, vertical_color));
}

__kernel void				pixel_raytracing_gpu(__write_only image2d_t out, global t_scene *scene,
	global t_camera *camera, global t_object *obj, global t_light *light)
{
	int					x;
	int					y;
	int					aliasing_iter;
	float				aliasing_variation;
	t_color				average;

	y = get_global_id(1);
	if (y < scene->top_bound || y > scene->bottom_bound)
		return;
	x = get_global_id(0);
	aliasing_iter = -1;
	while (++aliasing_iter < scene->sett.aliasing)
	{
		aliasing_variation = (float)aliasing_iter / (float)scene->sett.aliasing;
		if (aliasing_iter == 0)
			average = raytracing(scene, camera, obj, light, aliasing_variation);
		else
			average = average_color(average, raytracing(scene, camera, obj, light, aliasing_variation));
	}
	write_imagei(out, (int2)(x, y), (int4)(average.b, average.g, average.r, 0));
}
