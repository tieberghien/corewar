# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etieberg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 16:50:44 by etieberg          #+#    #+#              #
#    Updated: 2018/04/11 17:02:50 by etieberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
	
NAME		=	asm
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra #-fsanitize=address #-O3 #-g

LIB_PATH	=	libft
LIB		=	$(LIB_PATH)/libft.a
LIB_LINK	=	-L. $(LIB)

INC_DIR		=	includes
INCS		=	-I $(INC_DIR) -I $(LIB_PATH)/includes/.

SRC_DIR 	= 	src

SRC		=	main.c			\
			assembler.c		\
			read.c			\
			ops_datafill.c	\
			build_ops.c		\
			get_op.c		\
			name_comments.c

OBJ_DIR		=	obj

SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: obj $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB_LINK)

$(LIB):
	make -C $(LIB_PATH) re

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

obj:
	mkdir -p obj

clean:
	make -C $(LIB_PATH) clean
	rm -f $(OBJS)
	rm -Rf obj

fclean: clean
	rm -f $(LIB)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
