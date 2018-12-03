all:
	@make -C srcs/
	@make -C srcs/client

clean:
	@make clean -C srcs/client
	@make clean -C srcs/

fclean:
	@make fclean -C srcs/client
	@make fclean -C srcs/
	
re:	fclean all

.PHONY:				all clean fclean re
