NAME = rt_client
REP = ../rt_client
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = ../libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = ../minilibx/
MINILIBX = $(MLX)/mlx.a

INCLUDE_FLAG = -I ./includes/

SRCS_REP = srcs/
SRCS = main_client.c \
		  init_client.c \
		  init_env.c \
		  rendering.c \
		  deserialize.c \
		  deserialize_light.c \
		  parser_helper.c \
		  recv_img.c \
		  math_tools2.c \
		  math_tools3.c \
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

$(REP): $(O_SRCS)
	gcc -g $(INCLUDE_FLAG) $(W_FLAGS) $(MLX_FLAGS_LOCAL) $(MATH_FLAG) $(SRC) $(LIBFT) -o $(NAME)
	mv $(NAME) ../
	@echo "\033[3;32m[ ✔ ] Client ready.\033[0m"

%.o: %.c ./includes/client.h Makefile
	@gcc $(INCLUDE_FLAG) -c $< -o $@

all: $(REP)

norme:
	@norminette $(SRC)
	@norminette includes/
	@echo "\033[3;32m[ ✔ ] Client norme done.\033[0m"

clean:
	rm -rf $(O_SRCS)

fclean: clean
	rm -rf ../$(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
