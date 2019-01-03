NAME = rt
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = ../libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = ../minilibx/
MINILIBX = $(MLX)/mlx.a

INCLUDE_FLAG = -I ./includes/

SRCS_REP = srcs/
HELPER_REP = helpers/
PARSER_REP = parser/
SHAPES_REP = shapes/
SRCS = main.c \
		env_init.c \
		serialize.c \
		serialize_light.c \
		exit.c \
		camera_init.c \
		events.c \
		deinit.c \
		connexion.c \
		init_serv.c \
		send_data.c \
		create_server.c \
		$(HELPER_REP)constructors.c \
		$(HELPER_REP)math_tools.c \
		$(HELPER_REP)math_tools2.c \
		$(HELPER_REP)math_tools3.c \
		$(HELPER_REP)parser_helper.c \
		$(HELPER_REP)lighting_helper.c \
		$(PARSER_REP)light_creation.c \
		$(PARSER_REP)object_creation.c \
		$(PARSER_REP)object_creation2.c \
		$(PARSER_REP)scene_creation.c \
		$(PARSER_REP)camera_parser.c \
		$(PARSER_REP)object_parser.c \
		$(PARSER_REP)object_parser2.c \
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
	mv $(NAME) ../
	@echo "\033[3;32m[ ✔ ] RT ready.\033[0m"

%.o: %.c ./includes/rt.h Makefile
	@gcc $(INCLUDE_FLAG) -c $< -o $@

all: $(NAME)

normelibft:
	$(MAKE) -C $(LIBFT_REP) norme

norme:
	@norminette $(SRC)
	@norminette includes/
	@echo "\033[3;32m[ ✔ ] Server norme done.\033[0m"

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
