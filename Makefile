# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabelque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 10:29:54 by aabelque          #+#    #+#              #
#    Updated: 2018/11/12 15:43:26 by aabelque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt
ASSOCIATED_REP = $(NAME).dSYM

CC = nvcc
NVCC_P = /Developer/NVIDIA/CUDA-9.1/bin/
NVCC = $(addprefix $(NVCC_P), $(CC))
NVCC_ARCH = -m64 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35

LIBFT_REP = libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = minilibx/
MINILIBX = $(MLX)/mlx.a

INCLUDE_FLAG = -I includes
INCLUDE_CU = -I cu_include
INCLUDE_LIB = -I./libft/ -I./

SRCS_CU_REP = cu_srcs/
CUDA_SRCS = cu_malloc.cu \
			pix_raytracing.cu \
			init_intersection.cu \
			color.cu \
			color2.cu \
			text_function.cu \
			light_refl.cu \
			light_refra.cu \
			glare_effect.cu \
			get_col_inter.cu \
			vector.cu \
			vector2.cu \
			vector3.cu \
			calcul_intersect.cu \
			calcul_intersect2.cu \
			procedural_text.cu \
			text_perlin.cu \
			text_perlin2.cu \
			normal_funct.cu \
			normal_funct2.cu \
			lighting.cu \
			lighting2.cu \
			lighting3.cu \
			math_numb.cu \
			points_intersect.cu

SRCS_REP = srcs/
HELPER_REP = helpers/
PARSER_REP = parser/
SHAPES_REP = shapes/
SRCS = 	main.c \
		env_init.c \
		graphic_manager.c \
		exit.c \
		camera_init.c \
		events.c \
		deinit.c \
		pixel_drawing.c \
		raytracing.c \
		shapes_intersection.c \
		lighting.c \
		shapes_normal.c \
		$(SHAPES_REP)cylinder.c \
		$(SHAPES_REP)cone.c \
		$(SHAPES_REP)plane.c \
		$(SHAPES_REP)sphere.c \
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

SRC_CUDA = $(addprefix $(SRCS_CU_REP), $(CUDA_SRCS))
SRC = $(addprefix $(SRCS_REP), $(SRCS))

O_SRCS = $(SRC:.c=.o)
OC_SRCS = $(SRC_CUDA:.c=.o)

NVCC_STD = -Xcompiler -stdlib=libc++
NVCC_LIB = -Xlinker -rpath -Xlinker /Developer/NVIDIA/CUDA-9.1/lib/
NVCC_INC = -Xlinker -rpath -Xlinker /Developer/NVIDIA/CUDA-9.1/include/
W_FLAGS = -Xcompiler -Wall -Xcompiler -Wextra -Xcompiler -Werror -rdc=true 
C_FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -I ~/Library -g -L ~/Library -lmlx -Xlinker -framework,OpenGL -Xlinker -framework,AppKit -Xlinker -framework,OpenCL

MLX_FLAGS_LOCAL = -I $(MLX) -L $(MLX) -lmlx -Xlinker -framework,OpenGL -Xlinker -framework,AppKit -Xlinker -framework,OpenCL    

MATH_FLAG = -lm

all: $(NAME)

$(NAME): $(OC_SRCS) $(O_SRCS)
	make -C $(LIBFT_REP)
	make -C $(MLX)
	$(NVCC) -O3 -o $(NAME) $(W_FLAGS) $(NVCC_ARCH) $(NVCC_STD) $(INCLUDE_FLAG) $(INCLUDE_CU) $(MLX_FLAGS_LOCAL) $(MATH_FLAG) $(OC_SRCS) $(O_SRCS) $(LIBFT) $(INCLUDE_LIB) $(NVCC_LIB)
	@echo "\033[3;32m[ ✔ ] RT ready.\033[0m"

%.o: %.c includes/rt.h Makefile
	gcc -O3 $(C_FLAGS) $(INCLUDE_FLAG) $(INCLUDE_CU) -c $< -o $@

%.o: %.cu
	$(NVCC) -O3 -g -G $(W_FLAGS) $(NVCC_ARCH) $(NVCC_LIB) $(NVCC_INC) $(NVCC_STD) -Xlinker $(INCLUDE_CU) -Xlinker $(INCLUDE_FLAG) $< -o $@

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
	rm -rf $(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
