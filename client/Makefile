NAME = rt_client
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = ../libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = ../minilibx/
MINILIBX = $(MLX)/mlx.a

INCLUDE_FLAG = -I ./includes/

SRCS_REP = ./
SRCS = main_client.c \
		  init_client.c \
		  init_env.c \
		  deserialize.c \
		  deserialize_light.c \
		  deserialize_float.c \
		  parser_helper.c \
		  math_tools2.c \
		  math_tools.c \
		  constructors.c \
		  opencl_init.c \
		  opencl_init2.c \
		  opencl_draw.c \
		  opencl_free.c \
		  error_gpu.c \
		  ft_ocl_init_error.c \
		  ft_ocl_kernel_error.c \
		  deinit.c \
		  exit.c \
		  events.c \
		  camera_init.c \
		  
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
	mv $(NAME) ../
	@echo "\033[3;32m[ ✔ ] Client ready.\033[0m"

%.o: %.c ./includes/client.h Makefile
	@gcc $(INCLUDE_FLAG) -c $< -o $@

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
	rm -rf ../$(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
