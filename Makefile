LIBFT_REP = ./libft/
LIBFT = $(LIBFT_REP)libft.a

MLX = ./minilibx/
MINILIBX = $(MLX)/mlx.a

SERVER = ./server

CLIENT = ./client

all:
	make -C $(LIBFT_REP)
	make -C $(MLX)
	@make -C $(SERVER)
	@make -C $(CLIENT)

norme:
	@make norne -C $(LIBFT_REP)
	@make norme -C $(CLIENT)
	@make norme -C $(SERVER)

clean:
	@make clean -C $(LIBFT_REP)
	@make clean -C $(MLX)
	@make clean -C $(CLIENT)
	@make clean -C $(SERVER)

fclean:
	@make fclean -C $(LIBFT_REP)
	@make fclean -C $(CLIENT)
	@make fclean -C $(SERVER)
	
re:	fclean all

.PHONY:	all clean fclean re
