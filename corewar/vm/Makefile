LIB = libft/libft.a

SRC_NAME = vm_main.c \
		read_champ.c \
		display_intro.c \
		vm_mem.c		\
		free_and_dup.c

OBJ_PATH = obj

SRC_PATH = src

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INCLUDES = -I includes -I libft/Includes

FLAGS = -Wall -Wextra -Werror -g

NAME = corewar

all : library $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $@ $(OBJ) $(LIB)

library :
	make -C libft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@gcc -c $< $(FLAGS) -o $@ $(INCLUDES)

clean :
	make clean -C libft
	rm -fr obj

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all
