# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/05 21:56:14 by slynn-ev          #+#    #+#              #
#    Updated: 2018/03/11 19:11:08 by slynn-ev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = SRC

SRC_NAME = ft_printf/ft_printf.c \
get_next_line/get_next_line.c \
ft_printf/ft_putbase.c \
ft_printf/num_flags.c \
ft_printf/num_flags_cont.c \
ft_printf/num_printers.c \
ft_printf/print_chars.c \
ft_printf/print_numbers.c \
ft_printf/unicode.c \
ft_printf/fd.c \
libft/strings/ft_add_charpointer.c \
libft/strings/ft_str_to_intdata.c \
libft/strings/ft_strcat.c \
libft/strings/ft_strchr.c \
libft/strings/ft_strclr.c \
libft/strings/ft_strcmp.c \
libft/strings/ft_strcpy.c \
libft/strings/ft_strdebug.c \
libft/strings/ft_strdel.c \
libft/strings/ft_strdup.c \
libft/strings/ft_strndup.c \
libft/strings/ft_strequ.c \
libft/strings/ft_striter.c \
libft/strings/ft_striteri.c \
libft/strings/ft_strjoin.c \
libft/strings/ft_strjoin_free.c \
libft/strings/ft_strlcat.c \
libft/strings/ft_strlen.c \
libft/strings/ft_strmap.c \
libft/strings/ft_strmapi.c \
libft/strings/ft_strncat.c \
libft/strings/ft_strncmp.c \
libft/strings/ft_strncpy.c \
libft/strings/ft_strnequ.c \
libft/strings/ft_strnew.c \
libft/strings/ft_strnstr.c \
libft/strings/ft_strrchr.c \
libft/strings/ft_strsplit.c \
libft/strings/ft_strstr.c \
libft/strings/ft_strsub.c \
libft/strings/ft_strtrim.c \
libft/strings/ft_tolower.c \
libft/strings/ft_toupper.c \
libft/print/ft_put_inta.c \
libft/print/ft_putchar.c \
libft/print/ft_putchar_fd.c \
libft/print/ft_putendl.c \
libft/print/ft_putendl_fd.c \
libft/print/ft_putnbr.c \
libft/print/ft_putnbr_fd.c \
libft/print/ft_putstr.c \
libft/print/ft_putstr_fd.c \
libft/print/ft_putstrn.c \
libft/print/ft_unicode_putchar.c \
libft/memory/ft_bzero.c \
libft/memory/ft_memalloc.c \
libft/memory/ft_memccpy.c \
libft/memory/ft_memchr.c \
libft/memory/ft_memcmp.c \
libft/memory/ft_memcpy.c \
libft/memory/ft_memdel.c \
libft/memory/ft_memmove.c \
libft/memory/ft_memset.c \
libft/numbers/ft_abs.c \
libft/numbers/ft_atoi.c \
libft/numbers/ft_atoi_base.c \
libft/numbers/ft_atol.c \
libft/numbers/ft_intdebug.c \
libft/numbers/ft_itoa.c \
libft/numbers/ft_power.c \
libft/numbers/ft_numlen.c \
libft/list/ft_lstadd.c \
libft/list/ft_lstaddend.c \
libft/list/ft_lstdel.c \
libft/list/ft_lstdel_link.c \
libft/list/ft_lstdelone.c \
libft/list/ft_lstiter.c \
libft/list/ft_lstmap.c \
libft/list/ft_lstnew.c \
libft/list/ft_lstnew_ptr.c \
libft/list/ft_lstnew_str.c \
libft/list/ft_lsttstr_del.c \
libft/list/ft_print_list.c \
libft/checks/ft_isalnum.c \
libft/checks/ft_isalpha.c \
libft/checks/ft_isascii.c \
libft/checks/ft_isdigit.c \
libft/checks/ft_isprint.c \
libft/list/ft_lstnew_str.c \
libft/list/ft_lstdel_link.c \

CPPFLAGS = -I Includes

FLAGS = -Wall -Wextra -Werror -O3

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj

DEPS = Includes/libft.h \
Includes/ft_printf.h \
Includes/get_next_line.h \

NAME = libft.a

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@echo "###\nlibftprintf.a compiled"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEPS)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(dir $(OBJ))
	@gcc $(FLAGS) -o $@ -c $< $(CPPFLAGS)
	@echo "#" | tr -d '\n'

	
clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

