LIBFT_REP = ./libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = ./minilibx/
MINILIBX = $(MLX)/mlx.a

INTERFACE = ./interface

SERVER = ./server

CLIENT = ./client

all:
	make -C $(LIBFT_REP)
	make -C $(MLX)
	@make -C $(INTERFACE)
	@make -C $(SERVER)
	@make -C $(CLIENT)

norme:
	@make norme -C $(LIBFT_REP)
	@make norme -C $(INTERFACE)
	@make norme -C $(CLIENT)
	@make norme -C $(SERVER)

clean:
	@make clean -C $(LIBFT_REP)
	@make clean -C $(MLX)
	@make clean -C $(INTERFACE)
	@make clean -C $(CLIENT)
	@make clean -C $(SERVER)

fclean: clean
	@make fclean -C $(LIBFT_REP)
	@make fclean -C $(INTERFACE)
	@make fclean -C $(CLIENT)
	@make fclean -C $(SERVER)
	
re:	fclean all

.PHONY:	all clean fclean re
