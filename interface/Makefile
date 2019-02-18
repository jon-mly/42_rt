NAME = rt_interface
REP = ../interface/
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = ../libft/
LIBFT = $(LIBFT_REP)libft.a

INCLUDE_FLAG = -I ./includes/

SRCS_REP = srcs/

INTERFACE_REP = interface/
SRCS = main.c \
		$(INTERFACE_REP)initializers.c \
		$(INTERFACE_REP)initializers2.c \
		$(INTERFACE_REP)initializers3.c \
		$(INTERFACE_REP)signals.c \
		$(INTERFACE_REP)signals2.c \
		$(INTERFACE_REP)update_signals.c \

SRC = $(addprefix $(SRCS_REP), $(SRCS))

O_SRCS = $(SRC:.c=.o)

W_FLAGS = -Wall -Wextra -Werror

GTK_INCLUDE = `pkg-config --cflags gtk+-3.0`
GTK_LIB = `pkg-config --libs gtk+-3.0`

$(REP): $(O_SRCS)
	gcc $(INCLUDE_FLAG) $(GTK_INCLUDE) $(SRC) $(LIBFT) -o $(NAME) $(GTK_LIB)
	mv $(NAME) ../
	@echo "\033[3;32m[ ✔ ] RT_interface ready.\033[0m"

%.o: %.c ./includes/rt_interface.h Makefile
	@gcc $(INCLUDE_FLAG) $(GTK_INCLUDE) -c $< -o $@

all: $(REP)

norme:
	@norminette $(SRC)
	@norminette includes/
	@echo "\033[3;32m[ ✔ ] Interface norme done.\033[0m"

clean:
	rm -rf $(O_SRCS)

fclean: clean
	rm -rf ../$(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: all clean fclean re
