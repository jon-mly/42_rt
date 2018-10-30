# define TRUE 1
# define FALSE 0
# define MAX_DEPTH 5
# define ALIASING 3
# define EPSILON 0.001
# define BLACK (t_color){0, 0, 0, 0}
# define CIRCLES_WIDTH 6.0
# define CHECKER_WIDTH 4.0
# define DOTS_WIDTH 1.0
# define DOTS_SPREAD 3.0

typedef enum	e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	DISC,
	RECTANGLE,
	TRIANGLE,
	PARALLELOGRAM
}				t_object_type;

typedef enum	e_light_type
{
	OMNI,
	AMBIANT,
	PROJECTOR
}				t_light_type;

typedef enum			e_texture
{
	NONE,
	CHECKER,
	HORIZONTAL_CIRCLE,
	VERTICAL_CIRCLE,
	DOTS,
	DOTS_REVERTED,
	DOTS_CROWN,
	DOTS_REVERTED_CROWN
}						t_texture;

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

typedef struct	s_camera
{
	t_vector	posiition;
	t_vector	direction;
	t_vector	plane;
	t_point		spot;
	t_vector	normal;
	t_vector	up_left_corner;
	t_vector	horizontal_vect;
	t_vector	vertical_vect;
	float		width;
	float		height;
	float		plane_dist;
	float		horizontal_step;
	float		vertical_step;
	float		x_angle;
	float		y_angle;
	float		z_angle;
}				t_camera;

typedef struct	s_light
{
	t_point			posiition;
	t_vector		direction;
	float			angle;
	t_light_type	typpe;
	t_color			color;
	float			power;
}				t_light;

typedef struct			s_object
{
	int					id;
	t_color				color;
	t_point				center;
	t_point				point;
	t_point				origin;
	t_point				intersectiion;
	t_vector			direction;
	t_vector			normal;
	t_vector			first_vect;
	t_vector			second_vect;
	float				norm;
	float				test;
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
	t_object_type		typpe;
	t_texture			texture_type;
	int					intersect;
	int					finite;
	int					covered;
	int					has_density;
	char				*name;
}						t_object;

typedef struct	s_scene
{
	t_object	*objects;
	t_light		*lights;
	int			objects_count;
	int			lights_count;
	t_color		theme;
	float		power;
}				t_scene;

int				omni_color_coord(float cosinus, float distance, int obj_color, int light_color);
int             projector_color_coord(float intensity, float distance, int obj_color, int light_color);
t_color			diffuse_light_for_intersection(t_object light_ray, t_object ray, t_object object, t_light light);
t_object		init_omni_light_ray(t_light light, t_object ray, t_object object);
t_object	init_ambiant_light_ray(t_light light, t_object ray, t_object object);
int				color_to_int(t_color color);
t_color			get_color_on_intersection(t_object ray, global t_object *closest_object, global t_scene *scene, global t_light *light, global t_object *obj);
t_object		intersect_object(t_object ray, t_object object);
t_vector		normalize_vector(t_vector vec);
t_vector		vector_points(t_point p1, t_point p2);
// t_object		init_primary_ray(int x, int y, t_camera camera, float aliasing_variation);
t_vector	vect_rotate_x(t_vector vector, float angle, int inverse);
t_vector	vect_rotate_y(t_vector vector, float angle, int inverse);
t_vector	vect_rotate_z(t_vector vector, float angle, int inverse);
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
t_color 	add_color(t_color base, t_color overlay);
int		revert_cone_normal(t_object ray, t_object cone);
int		revert_cylinder_normal(t_object ray, t_object cylinder);
int		revert_sphere_normal(t_object ray, t_object sphere);
int				hit_test(global t_object *clt_obj, global t_object *obj, t_object l_ray, float norm);
t_color			omni_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light);
t_color			ambiant_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light);
t_color			ambiant_color(t_scene scene, t_object object);
t_color			projector_light_for_intersection(t_object light_ray, t_object ray, t_object
	object, t_light light);
t_object	init_projector_light_ray(t_light light, t_object ray, t_object object);
t_object		finite_cylinder_intersection(t_object ray, t_object cylinder);
t_object	disc_intersection(t_object ray, t_object disc);
float	farest_distance_quadratic(float a, float b, float c);
t_vector	point_from_vector(t_point origin, t_vector direction, float norm);
t_vector	scale_vector(t_vector vect, float scale);
t_object	finite_cone_intersection(t_object ray, t_object cone);
t_vector		reflected_vector(t_vector incident, t_vector normal);
t_color			specular_light_for_intersection(t_object light_ray, t_object ray,
	t_object object, t_light light);
t_color			raytracing(global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light, float aliasing_variation);
t_color		average_color(t_color c1, t_color c2);
unsigned char	maximize_color_value(int color_value);
t_vector	rotate_vector_angles(t_object reference, t_vector vect,
			int reverse);
t_object		rectangle_intersection(t_object ray, t_object rectangle);
t_vector	cross_product(t_vector vect_1, t_vector vect_2);
t_object		triangle_intersection(t_object ray, t_object triangle);
t_object		parallelogram_intersection(t_object ray, t_object parallelogram);
// t_object		init_reflected_ray(t_object original_ray, t_object intersected_object, float previous_reflection);
t_object		init_reflected_ray(t_object original_ray, t_object intersected_object);
t_vector		refracted_vector(t_object object, t_object ray, float next_refraction_index);
t_object		init_refracted_ray(t_object original_ray, t_object intersected_object,
	float next_refraction, float next_transparency);
t_color			refracted_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int ponctual);
t_vector	sum_vectors(t_vector vect1, t_vector vect2);
t_color			primary_ray(global t_scene *scene, global t_object *obj,
	global t_light *light, t_object ray, int depth, int refraction);
t_color		fade_color(t_color color, float multiplier);
t_color			reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int ponctual);
// t_color		average_color(t_color c1, t_color c2);t_color		average_color(t_color c1, t_color c2)
t_object	get_shadow_ray(t_light light, t_object ray, t_object object);
t_object	light_ray_from_shadow_ray(t_object shadow_ray, t_light light);
int			colors_are_equals(t_color c1, t_color c2);
t_color			filter_light_through_object(t_color initial_color, t_object object);
t_object		init_primary_ray(int x, int y, t_camera camera, float aliasing_variation, int horizontal);
float			fresnel_reflection_index(float n1, float n2, float cos_alpha, float cos_beta);
t_color			textured_color_if_needed(t_object object, t_point intersection);
t_color			checker_texture_color(t_object object, t_point intersection);
int			is_texture_even(int value);
t_color			circles_color(t_object object, t_point intersection, int horizontal);
t_color		interpolate_color(t_color c1, t_color c2, float ratio);
t_color			dots_color(t_object object, t_point intersection, int invert_gradient, int reverse);


/*
** ========== MATHEMATIC HELPERS
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

float		vector_norm(t_vector vec)
{
	float		norm;

	norm = sqrt((float)(pow((float)vec.x, (float)2) + pow((float)vec.y, (float)2) + pow((float)vec.z, (float)2)));
	return (norm);
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

float		dot_product(t_vector vect_1, t_vector vect_2)
{
	float		product;

	product = (vect_1.x * vect_2.x) +
				(vect_1.y * vect_2.y) +
				(vect_1.z * vect_2.z);
	return (product);
}

t_vector	cross_product(t_vector vect_1, t_vector vect_2)
{
	t_vector	cross;

	cross.x = vect_1.y * vect_2.z - vect_1.z * vect_2.y;
	cross.y = vect_1.z * vect_2.x - vect_1.x * vect_2.z;
	cross.z = vect_1.x * vect_2.y - vect_1.y * vect_2.x;
	return (cross);
}

t_color		fade_color(t_color color, float multiplier)
{
	color.r = (unsigned char)((float)color.r * multiplier);
	color.g = (unsigned char)((float)color.g * multiplier);
	color.b = (unsigned char)((float)color.b * multiplier);
	color.a = (unsigned char)((float)color.a * multiplier);
	// color.g = multiplier;
	// color.b = multiplier;
	// color.a = multiplier;
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


// t_color		average_color(t_color c1, t_color c2)
// {
// 	int		r;
// 	int		g;
// 	int		b;
// 	int		a;
// 	t_color final_color;

// 	r = (c1.r + c2.r) / 2;
// 	g = (c1.g + c2.g) / 2;
// 	b = (c1.b + c2.r) / 2;
// 	a = (c1.a + c2.a) / 2;
// 	final_color.r = (unsigned char)r;
// 	final_color.g = (unsigned char)g;
// 	final_color.b = (unsigned char)b;
// 	final_color.a = (unsigned char)a;
// 	return (final_color);
// }

/*
** =========== COLORS CALCULATION
*/

t_color		interpolate_color(t_color c1, t_color c2, float ratio)
{
	t_color		result;

	result.r = fmin(fmax(c1.r * (1 - ratio) + c2.r * ratio, 0), 255);
	result.g = fmin(fmax(c1.g * (1 - ratio) + c2.g * ratio, 0), 255);
	result.b = fmin(fmax(c1.b * (1 - ratio) + c2.b * ratio, 0), 255);
	result.a = fmin(fmax(c1.a * (1 - ratio) + c2.a * ratio, 0), 255);
	return (result);
}

t_color		fade_color(t_color color, float multiplier)
{
	color.r = (unsigned char)((float)color.r * multiplier);
	color.g = (unsigned char)((float)color.g * multiplier);
	color.b = (unsigned char)((float)color.b * multiplier);
	color.a = (unsigned char)((float)color.a * multiplier);
	// color.g = multiplier;
	// color.b = multiplier;
	// color.a = multiplier;
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

	distance = sqrt((float)(pow((float)(p2.x - p1.x), (float)2) + pow((float)(p2.y - p1.y), (float)2) + pow((float)(p2.z - p1.z), (float)2)));
	return (distance);
}

unsigned char	maximize_color_value(int color_value)
{
	float		ratio_value;

	ratio_value = (float)(color_value) / 255.0;
	return ((int)(fmax(fmin((float)color_value, (float)255), 0)));
	// return ((unsigned char)(((1 - exp((float)(-1.1 * ratio_value))) * 255)));
}


/*
** ========== NORMAL VECTOR CALCULATION
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
	// if ((!cone.finite || cone.covered) && revert_cone_normal(ray, cone))
	// 	normal = vector_points(distance, normal_point);
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
	// Could be removed since light inside a cylinder is not to be managed
	// if ((!cylinder.finite || cylinder.covered) && revert_cylinder_normal(ray, cylinder))
	// 	normal = vector_points(distance, normal_point);
	if (dot_product(normalize_vector(normal), rotate_vector_angles(cylinder, ray.direction, 0)) > 0)
		normal = vector_points(distance, normal_point);
	normal = rotate_vector_angles(cylinder, normal, 1);
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
	if (object.typpe == SPHERE)
		return (sphere_normal(ray, object));
	else if (object.typpe == PLANE || object.typpe == DISC || object.typpe == RECTANGLE
		|| object.typpe == TRIANGLE || object.typpe == PARALLELOGRAM)
		return (plane_normal(ray, object));
	else if (object.typpe == CYLINDER)
		return (cylinder_normal(ray, object));
	else
		return (cone_normal(ray, object));
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
	// if (ray.intersect)
	// 	printf("%.2f\n", ray.norm);
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
	if (ray.intersect)
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, ray.norm);
	return (ray);
}

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

	alternate = color(0, 0, 0, 0);
	adjusted = scale_vector(intersection, 1.0 / CHECKER_WIDTH);
	x_even = is_texture_even((int)(adjusted.x < -EPSILON) ? adjusted.x - 1 : adjusted.x);
	y_even = is_texture_even((int)(adjusted.y < -EPSILON) ? adjusted.y - 1 : adjusted.y);
	z_even = is_texture_even((int)(adjusted.z < -EPSILON) ? adjusted.z - 1 : adjusted.z);
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
	t_point		adjusted;
	int			distance;

	alternate = color(0, 0, 0, 0);
	adjusted = scale_vector(intersection, 1.0 / CIRCLES_WIDTH);
	if (horizontal)
		distance = (int)sqrt((adjusted.x * adjusted.x + adjusted.z * adjusted.z));
	else
		distance = (int)sqrt((adjusted.x * adjusted.x + adjusted.y * adjusted.y));
	if (distance % 2 == 0)
		return (object.color);
	return (alternate);
}

t_color			dots_color(t_object object, t_point intersection, int invert_gradient, int reverse)
{
	float		norm;
	t_color		internal_color;
	t_color		external_color;
	t_point		closest_dot;

	closest_dot = (t_point){round(intersection.x / DOTS_SPREAD) * DOTS_SPREAD,
		round(intersection.y / DOTS_SPREAD) * DOTS_SPREAD,
		round(intersection.z / DOTS_SPREAD) * DOTS_SPREAD};
	if (reverse)
	{
		external_color = object.color;
		internal_color = color(0, 0, 0, 0);
	}
	else
	{
		internal_color = object.color;
		external_color = color(0, 0, 0, 0);
	}
	norm = points_norm(intersection, closest_dot);
	if (norm <= DOTS_WIDTH / 2)
		return (internal_color);
	else if (norm <= DOTS_WIDTH)
	{
		if (invert_gradient)
			return (interpolate_color(internal_color, external_color,
				1 - ((norm - DOTS_WIDTH / 2) / (DOTS_WIDTH / 2))));
		else
			return (interpolate_color(internal_color, external_color,
				(norm - DOTS_WIDTH / 2) / (DOTS_WIDTH / 2)));
	}
	return (external_color);
}

t_color			textured_color_if_needed(t_object object, t_point intersection)
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
	t_vector	opposed_direction;
	t_vector	refracted;
	float		incident_cos;
	float		refraction_indexes_ratio;

	normal = shape_normal(ray, object);
	opposed_direction = scale_vector(ray.direction, -1);
	refraction_indexes_ratio = ray.refraction / next_refraction_index;
	if (fabs(refraction_indexes_ratio - 1) < EPSILON)
		return (ray.direction);
	incident_cos = 1.0 - pow(refraction_indexes_ratio, 2) * (1.0 - pow(dot_product(normal, ray.direction), 2));
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

	cosinus = dot_product(scale_vector(light_ray.direction, -1), shape_normal(ray, object)) * object.diffuse;
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
	cosinus = dot_product(light_ray.direction, normal) * object.diffuse;
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
	intensity *= object.diffuse;
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


int				hit_test(global t_object *clt_obj, global t_object *obj, t_object l_ray, float norm)
{
	if (!(l_ray.intersect && l_ray.norm > EPSILON))
		return (0);
	if (clt_obj == obj)
		return (l_ray.norm < norm - 0.1);
	return (l_ray.norm < norm);
}

t_color			ambiant_color(t_scene scene, t_object object)
{
	t_color		ambiant_color;
	float		factor;

	factor = scene.power * object.diffuse;
	ambiant_color.r = factor * (object.color.r * scene.theme.r / 255.0);
	ambiant_color.g = factor * (object.color.g * scene.theme.g / 255.0);
	ambiant_color.b = factor * (object.color.b * scene.theme.b / 255.0);
	ambiant_color.a = 0;
	return (ambiant_color);
}

t_color			filter_light_through_object(t_color initial_color, t_object object)
{
	t_color		final_color;

	final_color = fade_color(initial_color, object.transparency);
	final_color.r = final_color.r * object.color.r / 255.0;
	final_color.g = final_color.g * object.color.g / 255.0;
	final_color.b = final_color.b * object.color.b / 255.0;
	return (final_color);
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

/*
** For each light, light ray created.
** For each object that is not the intersected one, check if the ray
** intersects with the object. If so, the point on closest_object is shadowed.
** Else, the coloration calculated in the case there is no object in between is
** returned and applied.
*/

t_color			get_color_on_intersection(t_object ray, global t_object *closest_object, global t_scene *scene, global t_light *light, global t_object *obj)
{
	t_object	light_ray;
	t_object	shadow_ray;
	int			light_index;
	int			object_index;
	float		norm;
	t_color		coloration;
	t_object	intersected_object;
	int 		light_goes_through;

	light_index = -1;
	coloration = ambiant_color(*scene, *closest_object);
	while (++light_index < scene->lights_count)
	{
		light_goes_through = 1;
		shadow_ray = get_shadow_ray(light[light_index], ray, *closest_object);
		norm = shadow_ray.norm;
		object_index = -1;
		while (++object_index < scene->objects_count && light_goes_through)
		{
			shadow_ray = intersect_object(shadow_ray, obj[object_index]);
			if (shadow_ray.intersect && ((light[light_index].typpe == AMBIANT && shadow_ray.norm > EPSILON)
				|| (light[light_index].typpe != AMBIANT && hit_test(closest_object, &obj[object_index], shadow_ray, norm))))
				shadow_ray.color = filter_light_through_object(shadow_ray.color, obj[object_index]);
			light_goes_through = (!(colors_are_equals(shadow_ray.color, BLACK)));
			// TODO: change direction of light 
		}
		if (light_goes_through)
		{
			intersected_object = *closest_object;
			intersected_object.color = textured_color_if_needed(intersected_object, ray.intersectiion);
			light_ray = light_ray_from_shadow_ray(shadow_ray, light[light_index]);
			coloration = add_color(coloration, diffuse_light_for_intersection(light_ray, ray, intersected_object, light[light_index]));
			coloration = add_color(coloration, specular_light_for_intersection(light_ray, ray, intersected_object, light[light_index]));
		}
	}
	return (coloration);
}

/*
** If the ray does not reach any object and extends infinitely, depending on its proximity
** with a light, a glare effect is generated.
*/

// t_color			get_direct_light_glare(t_object ray, global t_light *lights)
// {

// }

/*
** ==================================================================
** INTERSECTION
** ==================================================================
*/

/*
** ========== GLARE EFFECT
*/

// t_color			direct_light_raytracing(t_ray )

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

t_color			refracted_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int ponctual)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	t_color				colorout;
	int					iter_count;
	int					max_iterations;
	int					inside_object;
	int					current_object_id;

	iter_count = -1;
	// max_iterations = (ponctual) ? 1 : MAX_DEPTH;
	max_iterations = MAX_DEPTH;
	colorout = BLACK;
	current_object_id = -1;
	inside_object = FALSE;
	while (++iter_count < max_iterations * 2) {
		added_color = BLACK;
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		// Test : only the ray that touches a new object produces light.
		// Supposes that once inside an object, the ray will only touch
		// the other side of the same object.
		if (closest_object_index != -1)
		{
			if (inside_object && current_object_id == obj[closest_object_index].id)
				inside_object = FALSE;
			else if (!inside_object)
			{
				current_object_id = obj[closest_object_index].id;
				inside_object = TRUE;
			}
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			added_color = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
			added_color = fade_color(added_color, ray.transparency);
			if (!ponctual && obj[closest_object_index].reflection > 0)
				added_color = add_color(added_color, reflected_raytracing(scene, obj, light,
					init_reflected_ray(ray, obj[closest_object_index]), 1));
			colorout = add_color(colorout, added_color);
		}
		if (closest_object_index == -1 || obj[closest_object_index].transparency == 0)
			return (colorout);
		if (!inside_object)
			ray = init_refracted_ray(ray, obj[closest_object_index],
				1, ray.transparency);
		else
			ray = init_refracted_ray(ray, obj[closest_object_index],
				obj[closest_object_index].refraction, obj[closest_object_index].transparency);

		
	}
	return (colorout);
}

/*
** ========== REFLECTED LIGHT
*/

t_object		init_reflected_ray(t_object original_ray, t_object intersected_object)
{
	t_object	ray;

	ray.direction = reflected_vector(original_ray.direction, shape_normal(original_ray, intersected_object));
	ray.direction = normalize_vector(ray.direction);
	ray.origin = point_from_vector(original_ray.intersectiion, ray.direction, EPSILON);
	ray.intersect = FALSE;
	ray.reflection = intersected_object.reflection * original_ray.reflection;
	ray.refraction = intersected_object.refraction;
	ray.transparency = intersected_object.transparency;
	return (ray);
}

t_color			reflected_raytracing(global t_scene *scene, global t_object *obj, global t_light *light,
	t_object ray, int ponctual)
{
	int					object_index;
	int 				closest_object_index;
	float				closest_distance;
	t_color				added_color;
	int					iter_count;
	t_color				colorout;
	int					max_iterations;

	iter_count = -1;
	max_iterations = (ponctual) ? 1 : MAX_DEPTH;
	colorout = BLACK;
	while (++iter_count < MAX_DEPTH) {
		added_color = BLACK;
		closest_object_index = -1;
		object_index = -1;
		while (++object_index < scene->objects_count)
		{
			ray = intersect_object(ray, obj[object_index]);
			if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
			{
				closest_object_index = object_index;
				closest_distance = ray.norm;
			}
		}
		if (closest_object_index != -1)
		{
			ray.norm = closest_distance;
			ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
			added_color = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
			if (!ponctual && obj[closest_object_index].transparency > 0)
				added_color = add_color(added_color, refracted_raytracing(scene, obj, light,
					init_refracted_ray(ray, obj[closest_object_index],
					obj[closest_object_index].refraction, obj[closest_object_index].transparency), 1));
			added_color = fade_color(added_color, ray.reflection);
		}
		colorout = add_color(colorout, added_color);
		if (closest_object_index == -1 || obj[closest_object_index].reflection == 0)
			return (colorout);
		ray = init_reflected_ray(ray, obj[closest_object_index]);
	}
	return (colorout);
}

/*
** ========== INITIAL INTERSECTION
*/

t_object		init_primary_ray(int x, int y, t_camera camera, float aliasing_variation, int horizontal)
{
	t_object	ray;
	t_point		projector_point;
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

	colorout = BLACK;
	reflected_color = BLACK;
	refracted_color = BLACK;
	closest_object_index = -1;
	object_index = -1;
	while (++object_index < scene->objects_count)
	{
		ray = intersect_object(ray, obj[object_index]);
		if (ray.intersect && ((closest_object_index != -1 && ray.norm < closest_distance) || closest_object_index == -1) && ray.norm > EPSILON)
		{
			closest_object_index = object_index;
			closest_distance = ray.norm;
		}
	}
	if (closest_object_index != -1)
	{
		ray.norm = closest_distance;
		ray.intersectiion = point_from_vector(ray.origin, ray.direction, closest_distance);
		colorout = get_color_on_intersection(ray, &obj[closest_object_index], scene, light, obj);
		if (obj[closest_object_index].reflection > 0)
			reflected_color = reflected_raytracing(scene, obj, light,
				init_reflected_ray(ray, obj[closest_object_index]), 0);
		if (obj[closest_object_index].transparency > 0)
			refracted_color = refracted_raytracing(scene, obj, light,
				init_refracted_ray(ray, obj[closest_object_index],
					obj[closest_object_index].refraction, obj[closest_object_index].transparency), 0);
		colorout = add_color(colorout, add_color(refracted_color, reflected_color));
	}
	return (colorout);
}

/*
** ========== MAIN FUNCTION
*/

t_color			raytracing(global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light, float aliasing_variation)
{
	int					x;
	int					y;
	int					idx;
	t_object				ray;
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

__kernel void				pixel_raytracing_gpu(__write_only image2d_t out, global t_scene *scene, global t_camera *camera, global t_object *obj, global t_light *light)
{
	int					x;
	int					y;
	int			aliasing_iter;
	float		aliasing_variation;
	t_color		average;

	x = get_global_id(0);
	y = get_global_id(1);
	aliasing_iter = -1;
	//TODO: set aliasing value into scene
	while (++aliasing_iter < ALIASING)
	{
		aliasing_variation = (float)aliasing_iter / (float)ALIASING;
		if (aliasing_iter == 0 || aliasing_iter == 1)
			average = raytracing(scene, camera, obj, light, aliasing_variation);
		else
			average = average_color(average, raytracing(scene, camera, obj, light, aliasing_variation));
	}
	write_imagei(out, (int2)(x, y), (int4)(average.b, average.g, average.r, 0));
}
