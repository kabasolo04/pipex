NAME = pipex
NAME_BONUS = pipex
CC = cc
LIBFT_LIB = src/libft/
LIBFT_FLAGS = -L src/libft/ -lft
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
RM		= rm -f

SRC =	src/mandatory/main.c \
		src/mandatory/get_path.c \
		src/mandatory/daddy.c \

OBJ = $(SRC:%.c=%.o)

SRC_BONUS =	src/bonus/main_bonus.c \
			src/bonus/get_path_bonus.c \
			src/bonus/here_doc_bonus.c \
			src/bonus/daddy_bonus.c \

OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

all: $(NAME)

.c.o:
		$(CC) -I includes/. $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		make -C $(LIBFT_LIB)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)

bonus:  $(OBJ_BONUS)
		make -C $(LIBFT_LIB)
		@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_FLAGS) -o $(NAME)

clean:
		$(RM) src/*/*.o

fclean:	clean
		$(RM) $(NAME)
		$(RM) $(NAME_BONUS)
		@make -C $(LIBFT_LIB) fclean

re:		fclean all

.PHONY: bonus all clean fclean re