# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 13:24:05 by aannara           #+#    #+#              #
#    Updated: 2020/09/07 16:56:56 by sdiego           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ./src/ft_printf.c ./src/mini_lib.c ./src/modifiers.c ./src/specifiers.c ./src/spec_d_i.c ./src/spec_octal.c ./src/spec_u.c ./src/spec_x.c ./src/spec_f.c ./src/spec_s.c ./src/spec_p.c ./src/double_to_str.c ./src/help_spec_f.c ./src/help_spec_f_2.c

OBJ = $(SRC:.c=.o)

CFLAGS = -o

INCLUDES = ./include

HEADERS = $(INCLUDES)/ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	ar rc $(NAME) $(OBJ)

.c.o: $(HEADERS)
	gcc -Wall -Wextra -Werror $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -fr ./src/*.o

fclean: clean
	rm -fr $(NAME)

re: fclean all
