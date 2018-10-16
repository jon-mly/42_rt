NAME = rtv1
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = minilibx/
MINILIBX = $(MLX)/mlx.a

INCLUDE_FLAG = -I includes/

SRCS_REP = srcs/
HELPER_REP = helpers/
PARSER_REP = parser/
SHAPES_REP = shapes/
SRCS = main.c \
		shapes_intersection.c \
		shapes_normal.c \
		env_init.c \
		graphic_manager.c \
		exit.c \
		camera_init.c \
		events.c \
		pixel_drawing.c \
		raytracing.c \
		lighting.c \
		deinit.c \
		opencl_init.c \
		opencl_init2.c \
		opencl_draw.c \
		opencl_free.c \
		ft_ocl_init_error.c \
		ft_ocl_kernel_error.c \
		error_gpu.c \
		$(HELPER_REP)constructors.c \
		$(HELPER_REP)math_tools.c \
		$(HELPER_REP)math_tools2.c \
		$(HELPER_REP)parser_helper.c \
		$(HELPER_REP)lighting_helper.c \
		$(PARSER_REP)light_creation.c \
		$(PARSER_REP)object_creation.c \
		$(PARSER_REP)scene_creation.c \
		$(PARSER_REP)camera_parser.c \
		$(PARSER_REP)object_parser.c \
		$(PARSER_REP)finite_objects_expander.c \
		$(SHAPES_REP)cylinder.c \
		$(SHAPES_REP)cone.c \
		$(SHAPES_REP)plane.c \
		$(SHAPES_REP)sphere.c \


SRC = $(addprefix $(SRCS_REP), $(SRCS))

O_SRCS = $(SRC:.c=.o)

W_FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -I ~/Library -g -L ~/Library -lmlx -framework OpenGL -framework \
			AppKit -framework OpenCL

MLX_FLAGS_LOCAL = -I $(MLX) -g -L $(MLX) -lmlx -framework OpenGL -framework \
			AppKit -framework OpenCL

MATH_FLAG = -lm

$(NAME): $(O_SRCS)
	make -C $(LIBFT_REP)
	make -C $(MLX)
	gcc -g $(INCLUDE_FLAG) $(MLX_FLAGS_LOCAL) $(MATH_FLAG) $(SRC) $(LIBFT) -o $(NAME)
	@echo "\033[3;32m[ ✔ ] Rtv1 ready.\033[0m"

%.o: %.c includes/rtv1.h Makefile
	@gcc  $(INCLUDE_FLAG) -c $< -o $@

all: $(NAME)

normelibft:
	$(MAKE) -C $(LIBFT_REP) norme

norme:
	@norminette $(SRC)
	@norminette includes/
	@echo "\033[3;32m[ ✔ ] Norme is done.\033[0m"

clean:
	make clean -C $(LIBFT_REP)
	make clean -C $(MLX)
	rm -rf $(O_SRCS)

fclean: clean
	make fclean -C $(LIBFT_REP)
#	make fclean -C $(MLX)
	rm -rf $(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
