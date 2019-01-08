all:
	make -C libft/
	@make -C server/
	@make -C client/

norme:
	@make norme -C client/
	@make norme -C server/

clean:
	@make clean -C client/
	@make clean -C server/

fclean:
	@make fclean -C client/
	@make fclean -C server/
	
re:	fclean all

.PHONY:	all clean fclean re
