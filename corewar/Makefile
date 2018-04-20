LIB = libft/libft.a

SRC = src/main.c src/assembler.c src/read.c src/ops_datafill.c src/build_ops.c src/get_op.c src/name_comments.c

OBJ_PATH = obj

SRC_NAME = $(notdir $(SRC))

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INCLUDES = -Iincludes -Ilibft/Includes

FLAGS = -Wall -Wextra -Werror -g

NAME = asm

all : library $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $(OBJ) $(LIB)

library :
	make -C libft

$(OBJ_PATH)/%.o: src/%.c
	@mkdir -p $(OBJ_PATH)
	@gcc -c $< $(FLAGS) -o $@ $(INCLUDES)

clean :
	make clean -C libft
	rm -fr obj

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all
